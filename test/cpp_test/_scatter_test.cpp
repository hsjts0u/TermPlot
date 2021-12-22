#include <TermPlot.hpp>

int main()
{
    
    const size_t height = 80;
	const size_t width = 80;

	const long double xmin = -20;
	const long double xmax = 20;
	const long double ymin = -20;
	const long double ymax = 20;

    std::vector<double> x;
    std::vector<double> y;

    for (int i = -20; i <= 20; ++i)
    {
        x.push_back(i);
        y.push_back(i);
    }

    _scatter object(height, width, xmin, xmax, ymin, ymax, x, y, graphoptionsdefault);
    object.plot();

    return 0;

}