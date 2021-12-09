#pragma once

#include "_base.hpp"

class _scatter : public _base
{

public:
    _scatter(const size_t height, const size_t width
            ,const long double xmin, const long double xmax
            ,const long double ymin, const long double ymax
            ,std::vector<unsigned short>x
            ,std::vector<unsigned short>y
            ,const graphoptions &options);
    ~_scatter() = default;
    void graph() override;

private:
    const size_t height; 
    const size_t width;
    const long double xmin;
    const long double xmax;
    const long double ymin;
    const long double ymax;
    std::vector<unsigned short> x;
    std::vector<unsigned short> y;
    const graphoptions options;

};