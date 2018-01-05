//
// Created by Alan de Freitas on 14/09/17.
//

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <string>


namespace utl {
    class progress_bar {
        public:
            progress_bar(int goal_ = 100,int resolution_ = 5):goal(goal_),resolution(resolution_){}
            std::string bar(){
                std::string str = "";
                str += "0%" + repeat_char(resolution-2,' ');
                for (int i = 10; i < 100; i+=10) {
                    str += std::to_string(i) + repeat_char(resolution-2,' ');
                }
                str += "100%\n";

                for (int i = 0; i < 100; i+=10) {
                    str += "|" + repeat_char(resolution-1,'-');
                }
                str += "|";
                return str;
            }

            std::string star(int i){
                const int progress = (i+1);
                const int n_of_stars = resolution*10+1;
                int star_pos = progress*n_of_stars/goal;
                if (stars < star_pos) {
                    int diff = star_pos - stars;
                    stars+= diff;
                    return repeat_char(diff,'*');
                } else {
                    return "";
                }
            }

            void reset(){
                stars = 0;
            }

            void reset(int new_goal){
                stars = 0;
                goal = new_goal;
            }

            void reset(int new_goal, int new_resolution){
                stars = 0;
                goal = new_goal;
                resolution = new_resolution;
            }

        private:
            int resolution = 5;
            int stars = 0;
            int goal = 100;

            std::string repeat_char(int n, char c){
                std::string str;
                for (int i = 0; i < n; ++i) {
                    str += c;
                }
                return str;
            }

    };
}


#endif //PROGRESS_BAR_H
