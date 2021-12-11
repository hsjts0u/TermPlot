#pragma once

#include "_base.hpp"

class _scatter : public _base
{

public:
    _scatter(const size_t &height, const size_t &width
            ,const long double &xmin, const long double &xmax
            ,const long double &ymin, const long double &ymax
            ,const std::vector<double> &x
            ,const std::vector<double> &y
            ,const graphoptions &options);
    ~_scatter() = default;

    void set_dims(const size_t &height, const size_t &width);
    void set_xbounds(const double &xmin, const double &xmax);
    void set_ybounds(const double &ymin, const double &ymax);
    void set_data(const std::vector<double> &x, const std::vector<double> &y);
    void set_options(const graphoptions &options);
    int plot() override;

private:
    size_t height; 
    size_t width;
    long double xmin;
    long double xmax;
    long double ymin;
    long double ymax;
    std::vector<double> x;
    std::vector<double> y;
    graphoptions options;

};