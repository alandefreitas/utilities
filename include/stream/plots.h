//
// Created by Alan de Freitas on 14/06/17.
//

#ifndef ECONOMIA_PLOTS_H
#define ECONOMIA_PLOTS_H

#include <map>
#include <vector>

#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "gnuplot-iostream.h"

namespace utl {

    static Gnuplot gp;

    template <class XTYPE, class YTYPE>
    void plot(XTYPE x,YTYPE y){
        std::vector<std::tuple<double, double>> pts(x.size());
        for (size_t i = 0; i < pts.size(); ++i) {
            pts[i] = std::make_tuple(x[i],y[i]);
        }

        gp << "set xrange [" << std::to_string(*std::min_element(x.begin(),x.end())) << ":" << std::to_string(*std::max_element(x.begin(),x.end())) <<  "]\n";
        gp << "set yrange [" << std::to_string(*std::min_element(y.begin(),y.end())) << ":" << std::to_string(*std::max_element(y.begin(),y.end())) <<  "]\n";
        // Data will be sent via a temporary file.  These are erased when you call
        // gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
        // (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
        // and won't be deleted (this is useful when creating a script).
        gp << "plot" << gp.file1d(pts) << "with lines title 'X'" << std::endl;
    }

    template <class YTYPE>
    void plot(YTYPE y){
        std::vector<unsigned> x(y.size());
        for (size_t i = 0; i < x.size(); ++i) {
            x[i] = i;
        }
        plot(x,y);
    }

    void plot1(){
        Gnuplot gp;
        // Create a script which can be manually fed into gnuplot later:
        //    Gnuplot gp(">script.gp");
        // Create script and also feed to gnuplot:
        //    Gnuplot gp("tee plot.gp | gnuplot -persist");
        // Or choose any of those options at runtime by setting the GNUPLOT_IOSTREAM_CMD
        // environment variable.

        // Gnuplot vectors (i.e. arrows) require four columns: (x,y,dx,dy)
        std::vector<boost::tuple<double, double, double, double> > pts_A;

        // You can also use a separate container for each column, like so:
        std::vector<double> pts_B_x;
        std::vector<double> pts_B_y;
        std::vector<double> pts_B_dx;
        std::vector<double> pts_B_dy;

        // You could also use:
        //   std::vector<std::vector<double> >
        //   boost::tuple of four std::vector's
        //   std::vector of std::tuple (if you have C++11)
        //   arma::mat (with the Armadillo library)
        //   blitz::Array<blitz::TinyVector<double, 4>, 1> (with the Blitz++ library)
        // ... or anything of that sort

        for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
            double theta = alpha*2.0*3.14159;
            pts_A.push_back(boost::make_tuple(
                    cos(theta),
                    sin(theta),
                    -cos(theta)*0.1,
                    -sin(theta)*0.1
            ));

            pts_B_x .push_back( cos(theta)*0.8);
            pts_B_y .push_back( sin(theta)*0.8);
            pts_B_dx.push_back( sin(theta)*0.1);
            pts_B_dy.push_back(-cos(theta)*0.1);
        }

        // Don't forget to put "\n" at the end of each line!
        gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
        // '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
        gp << "plot '-' with vectors title 'pts_A', '-' with vectors title 'pts_B'\n";
        gp.send1d(pts_A);
        gp.send1d(boost::make_tuple(pts_B_x, pts_B_y, pts_B_dx, pts_B_dy));
    }

    void plot2(){
        Gnuplot gp;

        std::vector<std::pair<double, double> > xy_pts_A;
        for(double x=-2; x<2; x+=0.01) {
            double y = x*x*x;
            xy_pts_A.push_back(std::make_pair(x, y));
        }

        std::vector<std::pair<double, double> > xy_pts_B;
        for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
            double theta = alpha*2.0*3.14159;
            xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
        }

        gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
        // Data will be sent via a temporary file.  These are erased when you call
        // gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
        // (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
        // and won't be deleted (this is useful when creating a script).
        gp << "plot" << gp.file1d(xy_pts_A) << "with lines title 'cubic',"
           << gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;
    }
}


#endif //ECONOMIA_PLOTS_H
