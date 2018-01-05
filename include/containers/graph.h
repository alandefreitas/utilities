//
// Created by Alan de Freitas on 30/03/17.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/random_spanning_tree.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/array.hpp>

namespace utl {
    template<typename VertexContainer = boost::setS, typename EdgeContainer = boost::vecS, typename Directed = boost::undirectedS, typename VertexProperty = boost::no_property, typename EdgeProperty = boost::no_property>
    class base_graph {
        public:
            /*
             *  Datatypes
             */
            using adjacency_list = boost::adjacency_list<VertexContainer, EdgeContainer, Directed, VertexProperty, EdgeProperty>;
            // adjacency_matrix<Directed, VertexProperty, EdgeProperty, GraphProperty, Allocator>
            // iterators
            using iterator = typename adjacency_list::vertex_iterator;
            using vertex_iterator = typename adjacency_list::vertex_iterator;
            using edge_iterator = typename adjacency_list::edge_iterator;
            using out_edge_iterator = typename adjacency_list::out_edge_iterator;
            using adjacency_iterator = typename adjacency_list::adjacency_iterator;
            // objects
            using vertex = typename adjacency_list::vertex_descriptor;
            using edge = typename adjacency_list::edge_descriptor;


            /*
             * Basic function for graph
             */
            vertex get_vertice(int i){
                return boost::vertex(i, g);
            }

            /*
             * Altering the graph
             */
            void clear() { g.clear(); }

            vertex add_vertex() {
                return boost::add_vertex(g);
            }

            vertex add_vertex(VertexProperty x) {
                vertex descriptor = boost::add_vertex(g);
                g[descriptor] = x;
                return descriptor;
            }

            edge add_edge(vertex v1, vertex v2) {
                return boost::add_edge(v1, v2, g).first;
            }

            adjacency_list &data() {
                return g;
            }

            /*
             * Algorithms
             */
            // breadth_first_search(vertex v, function predicate)
            // depth_first_search(vertex v, function predicate)
            // dijkstra_shortest_paths(vertex v)
            // random_spanning_tree(generator gen)

            /*
             * Operators
             */
            VertexProperty &operator[](vertex x) {
                return g[x];
            }

            EdgeProperty &operator[](edge x) {
                return g[x];
            }


            /*
             * Iterators
             */
            std::pair<iterator, iterator> get_vertices() {
                return boost::vertices(g);
            };

            iterator begin() {
                return boost::vertices(g).first;
            };

            iterator end() {
                return boost::vertices(g).second;
            };

            std::pair<edge_iterator, edge_iterator> get_edges() {
                return boost::edges(g);
            };

            edge_iterator begin_edges() {
                return boost::edges(g).first;
            }

            edge_iterator end_edges() {
                return boost::edges(g).second;
            }

            std::pair<adjacency_iterator, adjacency_iterator> get_adjacent_vertices(vertex v) {
                return boost::adjacent_vertices(v, g);
            };

            adjacency_iterator begin_adjacent_vertices(vertex v) {
                return boost::adjacent_vertices(v, g).first;
            }

            adjacency_iterator end_adjacent_vertices(vertex v) {
                return boost::adjacent_vertices(v, g).second;
            }

            size_t size_vertices() { return boost::num_vertices(g); };

            size_t size_edges() { return boost::num_edges(g); };


            /*
             * Display
             */
            // Non-modifying to get edges
            void print_vertices() {
                std::pair<iterator, iterator> vs = get_vertices();
                std::copy(vs.first, vs.second, std::ostream_iterator<vertex>{std::cout, "\n"});
            }

            void print_adjacent(vertex v) {
                std::pair<adjacency_iterator, adjacency_iterator> es = get_adjacent_vertices(v);
                std::copy(es.first, es.second, std::ostream_iterator<vertex>{std::cout, "\n"});
            }

            void print_edges() {
                std::pair<edge_iterator, edge_iterator> es = get_edges();
                std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});
            }

        private:
            // graph g
            adjacency_list g;
    };

    template<typename VertexContainer = boost::setS, typename EdgeContainer = boost::vecS, typename Directed = boost::bidirectionalS, typename VertexProperty = boost::no_property, typename EdgeProperty = boost::no_property>
    class directed_base_graph
            : public base_graph<VertexContainer, EdgeContainer, Directed, VertexProperty, EdgeProperty> {
        public:
            using adjacency_list = boost::adjacency_list<VertexContainer, EdgeContainer, Directed, VertexProperty, EdgeProperty>;
            // iterators
            using iterator = typename adjacency_list::vertex_iterator;
            using vertex_iterator = typename adjacency_list::vertex_iterator;
            using edge_iterator = typename adjacency_list::edge_iterator;
            using out_edge_iterator = typename adjacency_list::out_edge_iterator;
            using adjacency_iterator = typename adjacency_list::adjacency_iterator;
            // objects
            using vertex = typename adjacency_list::vertex_descriptor;
            using edge = typename adjacency_list::edge_descriptor;
            using in_edge_iterator = typename adjacency_list::in_edge_iterator;

            std::pair<in_edge_iterator, in_edge_iterator> get_in_edges(vertex v) {
                return boost::in_edges(v, this->data());
            };

            in_edge_iterator begin_in_edges(vertex v) {
                return boost::in_edges(v, this->data()).first;
            }

            in_edge_iterator end_in_edges(vertex v) {
                return boost::in_edges(v, this->data()).second;
            }

            std::pair<out_edge_iterator, out_edge_iterator> get_out_edges(vertex v) {
                return boost::out_edges(v, this->data());
            };

            out_edge_iterator begin_out_edges(vertex v) {
                return boost::out_edges(v, this->data()).first;
            }

            out_edge_iterator end_out_edges(vertex v) {
                return boost::out_edges(v, this->data()).second;
            }

            void print_in_edges(vertex v) {
                std::pair<in_edge_iterator, in_edge_iterator> es = get_in_edges(v);
                std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});

            }

            void print_out_edges(vertex v) {
                std::pair<out_edge_iterator, out_edge_iterator> es = get_out_edges(v);
                std::copy(es.first, es.second, std::ostream_iterator<edge>{std::cout, "\n"});
            }
    };

    using graph = base_graph<boost::setS, boost::vecS, boost::undirectedS, boost::no_property, boost::no_property>;
    using undirected_graph = graph;

    template<typename VertexProperty = boost::no_property, typename EdgeProperty = boost::no_property>
    using graph_container = base_graph<boost::setS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty>;

    using directed_graph = directed_base_graph<boost::setS, boost::vecS, boost::bidirectionalS, boost::no_property, boost::no_property>;

    template<typename VertexProperty = boost::no_property, typename EdgeProperty = boost::no_property>
    using directed_graph_container = directed_base_graph<boost::setS, boost::vecS, boost::bidirectionalS, VertexProperty, EdgeProperty>;


    /*
     * Add one more graph type in the future
     * adjacency_matrix<Directed, VertexProperty, EdgeProperty, GraphProperty, Allocator>
     */
}
#endif //GRAPH_H
