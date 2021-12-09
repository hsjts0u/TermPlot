#include "../include/_scatter.hpp"

_scatter::_scatter(const size_t height, const size_t width
                  ,const long double xmin, const long double xmax
                  ,const long double ymin, const long double ymax
                  ,std::vector<unsigned short>x
                  ,std::vector<unsigned short>y
                  ,const graphoptions &options) :
height(height), width(width), 
xmin(xmin), xmax(xmax), 
ymin(ymin), ymax(ymax),
x(x), y(y), options(options) { }

void _scatter::graph() 
{
    
}