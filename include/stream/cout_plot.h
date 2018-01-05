//
// Created by Alan de Freitas on 13/09/17.
//

#ifndef COUT_PLOT_H
#define COUT_PLOT_H

#include <vector>
#include <iostream>
#include <cmath>
#include "termcolor/termcolor.hpp"
#include "utils/pretty_table/pretty_table.h"

namespace utils {

    class plot {
        public:
            plot() : x_data(1, vector<double>(100)), y_data(3, vector<double>(100)) {
                for (int i = 0; i < x_data[0].size(); ++i) {
                    x_data[0][i] = i-20;
                    y_data[0][i] = i-20;
                    y_data[1][i] = std::sin(x_data[0][i]/10)*50;
                    y_data[2][i] = std::cos((x_data[0][i]+20)/10)*70;
                }
            }

            ////////////////////////////////////////////////
            //                OPERATORS                   //
            ////////////////////////////////////////////////
            friend std::ostream &operator<<(std::ostream &, plot &);

        private:
            vector<vector<double>> y_data;
            vector<vector<double>> x_data;
            int x_resolution{60};
            int y_resolution{14};
    };

    std::ostream &operator<<(std::ostream &stream, plot &plot) {
        int min_y_i = 0;
        int min_y_j = 0;
        int max_y_i = 0;
        int max_y_j = 0;
        for (int i = 0; i < plot.y_data.size(); ++i) {
            for (int j = 0; j < plot.y_data[i].size(); ++j) {
                if (plot.y_data[i][j] < plot.y_data[min_y_i][min_y_j]) {
                    min_y_i = i;
                    min_y_j = j;
                }
                if (plot.y_data[i][j] > plot.y_data[max_y_i][max_y_j]) {
                    max_y_i = i;
                    max_y_j = j;
                }
            }
        }

        int min_x_i = 0;
        int min_x_j = 0;
        int max_x_i = 0;
        int max_x_j = 0;
        for (int i = 0; i < plot.x_data.size(); ++i) {
            for (int j = 0; j < plot.x_data[i].size(); ++j) {
                if (plot.x_data[i][j] < plot.x_data[min_x_i][min_x_j]) {
                    min_x_i = i;
                    min_x_j = j;
                }
                if (plot.x_data[i][j] > plot.x_data[max_x_i][max_x_j]) {
                    max_x_i = i;
                    max_x_j = j;
                }
            }
        }

        double max_x = plot.x_data[max_x_i][max_x_j];
        double min_x = plot.x_data[min_x_i][min_x_j];
        double range_x = max_x - min_x;
        double max_y = plot.y_data[max_y_i][max_y_j];
        double min_y = plot.y_data[min_y_i][min_y_j];
        double range_y = max_y - min_y;
        double x_step_size = range_x / (plot.x_resolution);
        double y_step_size = range_y / (plot.y_resolution);

        utils::table t(plot.y_resolution + 2, plot.x_resolution + 4);
        t.border_height(0).border_size(0).padding(0).vertical_separator('1').horizontal_separator('2').corner_separator(
                '3').min_width(1);
        // make axis
        t[0][0] = "y_axis";
        t[0][0].text_color(utils::color::blue).bold(true);
        int x_zero_pos = std::ceil(((0.0 - min_x) / range_x) * (plot.x_resolution)) + 2;
        for (int i = 0; i < t.row_count(); ++i) {
            t[i][x_zero_pos] = "|";
        }
        t[t.row_count() - 1][t.column_count() - 1] = "x_axis";
        t[t.row_count() - 1][t.column_count() - 1].text_color(utils::color::blue).bold(true);
        int y_zero_pos = t.row_count() - 2 - std::ceil(((0.00 - min_y) / range_y) * (plot.y_resolution));
        for (int i = 1; i < t.column_count()-1; ++i) {
            t[y_zero_pos][i] = "-";
        }
        t[y_zero_pos][x_zero_pos] = "+";

        for (int i = 0; i < plot.y_data.size(); ++i) {
            vector<double> &x = plot.x_data[0];
            if (plot.x_data.size() >= plot.y_data.size()) {
                x = plot.x_data[i];
            }
            vector<double> &y = plot.y_data[i];
            for (int j = 0; j < std::min(x.size(), y.size()) - 2; ++j) {
                int x_pos = std::ceil(((x[j] - min_x) / range_x) * (plot.x_resolution)) + 2;
                int y_pos = t.row_count() - 2 - std::ceil(((y[j] - min_y) / range_y) * (plot.y_resolution));
                t[y_pos][x_pos] = "*";
                t[y_pos][x_pos].text_color(utils::color((i+4)%9));
            }
        }
        stream << t;
        return stream;
    }


}

#endif //COUT_PLOT_H
