#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <chrono>

#include "utils.h"

using namespace std;
using namespace utl;

int main()
{
    cout << on_yellow << bold << "Thread Pool" << reset << endl;

    cout << bold << underline << "Slepping Threads" << reset << endl;
    {
        thread_pool pool(thread::hardware_concurrency());
        vector<future<int>> results;

        const int number_of_jobs = 2;

        for (int i = 0; i < number_of_jobs; ++i) {
            results.emplace_back(
                    pool.enqueue([i] {
                        cout << "hello " << i << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        cout << "world " << i << endl;
                        return i * i;
                    })
            );
        }

        for (auto &&result: results) {
            cout << result.get() << ' ';
        }
        cout << endl;
    }

    cout << bold  << underline << "Interleaved Evolutionary Algorithm" << reset << endl;


    cout << bold << underline << "Evaluation Functions" << reset << endl;
    {
        thread_pool pool(thread::hardware_concurrency());

        auto print_container = [](auto &container) {
            for (auto &&item : container) {
                cout << item << " ";
            }
            cout << endl;
        };

        auto evaluation_function = [](double &x) {
            return x * x;
        };

        const int population_size = 100;
        using individual = double;

        // Initial population
        vector<individual> population(population_size);
        default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        uniform_real_distribution<double> distribution(0.0, 10.0);
        boost::generate(population,[&generator, &distribution]() { return distribution(generator); });

        // Generation 0
        // Population
        cout << underline << "Current population" <<  reset << endl;
        print_container(population);

        // Tournament candidates (not in parallel)
        const int parents_per_child = 2;
        const int candidates_per_tournament = 2;
        vector<size_t> tournament_candidates(population_size * parents_per_child * candidates_per_tournament);
        uniform_int_distribution<size_t> tournament_distribution(0, population_size - 1);
        boost::generate(tournament_candidates, [&generator, &tournament_distribution]() { return tournament_distribution(generator); });
        cout << underline << "Parent candidates" << reset << endl;
        print_container(tournament_candidates);

        for (int i = 0; i < population_size; ++i) {
            if (find(tournament_candidates.begin(),tournament_candidates.end(),i) == tournament_candidates.end()){
                cout << "Parent " << i << " is not even a candidate" << endl;
            }
        }

        // Push evaluation to thread pool / (In practice we will be also getting child evaluation from the last iteration)
        vector<future<double>> results(population_size);
        for (auto &&parent : tournament_candidates) {
            if (!results[parent].valid()){
                results[parent] = pool.enqueue([&evaluation_function, &population, &parent] {
                    return evaluation_function(population[parent]);
                });
            }
        }

        // Push tournaments to thread pool / Get evaluation results from the pool
        // Each tournament round waits for the evaluation of 2 parents
        vector<double> population_fitness(population_size,0.0);
        vector<future<size_t>> tournament_results(population_size*parents_per_child);

        for (int i = 0; i < population_size * parents_per_child; i++) {
            tournament_results[i] = pool.enqueue([&population_fitness,i,&tournament_candidates,&results] {
                int first_candidate = i * parents_per_child;
                const vector<size_t> candidate_positions(tournament_candidates.begin()+first_candidate,tournament_candidates.begin()+first_candidate+candidates_per_tournament);
                vector<size_t> candidate_fitness(parents_per_child);
                for (int j = 0; j < candidate_positions.size(); ++j) {
                    if (results[candidate_positions[j]].valid()){
                        population_fitness[candidate_positions[j]] = results[candidate_positions[j]].get();
                    }
                    candidate_fitness[j] = population_fitness[candidate_positions[j]];
                }
                return candidate_positions[boost::max_element(candidate_fitness) - candidate_fitness.begin()];
            });
        }

        cout << underline << "Current population fitness" << reset << endl;
        {
            double sum = 0;
            int valid_f = 0;
            for (int i = 0; i < population_size; ++i) {
                auto &&item = population_fitness[i];
                cout << i << ":" << population[i] << ":fx(" << item << ") ";
                sum += item;
                valid_f += item != 0;
            }
            cout << endl;
            cout << "Average fitness: " << on_green << sum/valid_f << reset << endl;
        }

        // In practice we would inserting here the survival selection in the process as well
        // We would only generate the children that are candidates to survival selection (saving time once more)

        // Push child generation to thread pool / get tournament results from the pool
        // Each child generation waits for two tournament results between two parents
        vector<future<individual>> children_generation_results(population_size);
        vector<size_t> parent_indexes(population_size*parents_per_child);

        for (int i = 0; i < population_size; ++i) {
            children_generation_results[i] = pool.enqueue([&tournament_results,i,&population,&parent_indexes] {
                for (int j = 0; j < parents_per_child; ++j) {
                    parent_indexes[i*candidates_per_tournament+j] = tournament_results[i*candidates_per_tournament+j].get();
                }
                return (population[parent_indexes[i*parents_per_child]] + population[parent_indexes[i*parents_per_child+1]])/2;
            });
        }

        cout << underline << "Parent indexes" << reset << endl;
        print_container(parent_indexes);

        // Push child evaluation to thread pool / get children generation from the pool
        vector<individual> children(population_size);
        vector<future<double>> children_evaluation_results(population_size);

        for (int i = 0; i < population_size; ++i) {
            children_evaluation_results[i] = pool.enqueue([i, &evaluation_function, &children, &children_generation_results] {
                children[i] = children_generation_results[i].get();
                return evaluation_function(children[i]);
            });
        }

        cout << underline << "Children" <<  reset << endl;
        print_container(children);

        // Get children fitness
        // (in practice we would be pushing the next tournament or selection procedure)
        vector<double> children_fitness(population_size);
        for (int i = 0; i < population_size; ++i) {
            children_fitness[i] = children_evaluation_results[i].get();
        }

        cout << underline << "Children fitness" << reset << endl;
        {
            double sum = 0;
            int valid_f = 0;
            for (int i = 0; i < population_size; ++i) {
                auto &&item = children_fitness[i];
                cout << i << ":" << population[i] << ":fx(" << item << ") ";
                sum += item;
                valid_f += item != 0;
            }
            cout << endl;
            cout << "Average fitness: " << on_green << sum/valid_f << reset << endl;
        }

    }

    cout << on_yellow << bold << underline << "GPU OpenCL Compute"
              << reset << endl;

    cout << bold << underline << "Get default GPU device and setup context" << reset << endl;
    {
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device, compute::command_queue::enable_profiling);
//        cout << "timer1 considers time to copy data" << endl;
//        cout << "timer2 ignores time to copy data" << endl;
//        cpu_timer timer;
//        cpu_timer timer2;
//        timer.stop();
//        timer2.stop();
        string result1;
        string result2;
        string result3;

        int goal = 1000;
        progress_bar p(goal,20);
        cout << p.bar() << endl;
        for (int i = 0; i < goal; ++i) {
            cout << p.star(i);
            // generate random data on the host
            vector<float> host_vector(100000);
            generate(host_vector, std::rand);

            // print data
            // cout << "Host data" << host_vector << endl;

//            timer.resume();

            // create a vector on the device
            compute::vector<float> device_vector(host_vector.size(), context);

            // transfer data from the host to the device
            compute::copy(host_vector.begin(), host_vector.end(), device_vector.begin(), queue);

//            timer2.resume();

            // calculate the square-root of each element in-place
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );

//            timer2.stop();

            // Copy values back to the host
            compute::copy(
                    device_vector.begin(), device_vector.end(), host_vector.begin(), queue
            );

//            timer.stop();

//            // cout << timer.format() << '\n';
//            // cout << timer2.format() << '\n';

            // print values
            // cout << "Host data returned" << host_vector << endl;

        }
        cout << endl;
//        result1 = timer.format();
//        result3 = timer2.format();
//        timer.start();
//        timer.stop();
        cout << bold << underline << "Transforming data sequentially for comparison" << reset << endl;

        p.reset(goal,20);
        cout << p.bar() << endl;
        for (int i = 0; i < goal; ++i) {
            cout << p.star(i);
            // generate random data on the host
            vector<float> host_vector(100000);
            generate(host_vector.begin(), host_vector.end(), std::rand);

            // cout << "Host data: " << host_vector << endl;

//            timer.resume();

            // calculate the square-root of each element in-place
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );

//            timer.stop();

//            // cout << timer.format() << '\n';

            // cout << "Host data returned" << host_vector << endl;

        }
//        result2 = timer.format();

        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Time sync GPU: " << result1 << endl;
        cout << "Time async GPU" << result3 << endl;
        cout << "Time sequential: " << result2 << endl;

    }


    // hello world
    {
        // get the default device
        compute::device device = compute::system::default_device();

        // print the device's name
        cout << "Device name: " << device.name() << endl;
        cout << "Vendor: " << device.vendor() << endl;
        cout << "Compute units: " << device.compute_units() << endl;
        cout << "Clock frequency: " << device.clock_frequency() << endl;
        cout << "Driver Version: " << device.driver_version() << endl;
        cout << "Global memory size: " << device.global_memory_size() << endl;
        cout << "Local memory size: " << device.local_memory_size() << endl;
        cout << "Device id: " << device.id() << endl;
        cout << "Driver version: " << device.driver_version() << endl;
        cout << "Profile: " << device.profile() << endl;

    }

    // transfering data
    {
        // get default device and setup context
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device);

        // create data array on host
        int host_data[] = { 1, 3, 5, 7, 9 };

        // create vector on device
        compute::vector<int> device_vector(5, context);

        // copy from host to device
        compute::copy(
                host_data, host_data + 5, device_vector.begin(), queue
        );

        // create vector on host
        vector<int> host_vector(5);

        // copy data back to host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        cout << "Copying data: " << endl;
        for (auto &item : host_vector) {
            cout << item << " ";
        }
        cout << endl;
    }

    // transforming data on the device
    {
        // get default device and setup context
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device);

        // generate random data on the host
        vector<float> host_vector(10000);
        generate(host_vector.begin(), host_vector.end(), std::rand);
        // print the host vector
        cout << "Random Floats: " << endl;
        for (auto &item : host_vector) {
            cout << item << " ";
        }
        cout << endl;

        // create a vector on the device
        compute::vector<float> device_vector(host_vector.size(), context);

        // transfer data from the host to the device
        compute::copy(
                host_vector.begin(), host_vector.end(), device_vector.begin(), queue
        );

        // calculate the square-root of each element in-place
        compute::transform(
                device_vector.begin(),
                device_vector.end(),
                device_vector.begin(),
                compute::sqrt<float>(),
                queue
        );

        // copy values back to the host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        cout << "Square roots: " << endl;
        for (auto &item : host_vector) {
            cout << item << " ";
        }
        cout << endl;
    }

    // sorting data
    {
        // get the default compute device
        compute::device gpu = compute::system::default_device();

        // create a compute context and command queue
        compute::context ctx(gpu);
        compute::command_queue queue(ctx, gpu);

        // generate random numbers on the host
        vector<float> host_vector(1000000);
        generate(host_vector, std::rand);

        // create vector on the device
        compute::vector<float> device_vector(1000000, ctx);

        // copy data to the device
        compute::copy(
                host_vector.begin(), host_vector.end(), device_vector.begin(), queue
        );

        // sort data on the device
        compute::sort(
                device_vector.begin(), device_vector.end(), queue
        );

        // copy data back to the host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        cout << "Sorted data: " << endl;
        for (auto &item : host_vector) {
            cout << item << " ";
        }
        cout << endl;
    }

    cout << on_yellow << bold << underline << "Creating and Managing Threads"
              << reset << endl;

    cout << bold << underline << "Using boost::thread" << reset << endl;
    {
        auto wait = [](int seconds) {
            this_thread::sleep_for(chrono::seconds{seconds});
        };

        auto thread_func = [&wait]() {
            for (int i = 0; i < 5; ++i) {
                wait(1);
                cout << i << '\n';
            }
        };

        thread t{thread_func};
        t.join();
    }


    return 0;
}
