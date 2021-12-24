#include <_scatter.hpp>


_scatter::_scatter(const size_t &height, const size_t &width
                  ,const long double &xmin, const long double &xmax
                  ,const long double &ymin, const long double &ymax
                  ,const std::vector<double> &x
                  ,const std::vector<double> &y
                  ,const graphoptions &options) :
height(height), width(width), 
xmin(xmin), xmax(xmax), 
ymin(ymin), ymax(ymax),
x(x), y(y), options(options) 
{
	assert(this->x.size() != 0);
	assert(this->y.size() != 0);
	assert(this->x.size() == this->y.size());
}


void _scatter::set_dims(const size_t &height, const size_t &width)
{
	this->height = height;
	this->width = width;
}


void _scatter::set_xbounds(const double &xmin, const double &xmax)
{
	this->xmin = xmin;
	this->xmax = xmax;
}


void _scatter::set_ybounds(const double &ymin, const double &ymax)
{
	this->ymin = ymin;
	this->ymax = ymax;
}


void _scatter::set_data(const std::vector<double> &x, const std::vector<double> &y)
{
	assert(this->x.size() != 0);
	assert(this->y.size() != 0);
	assert(this->x.size() == this->y.size());
	this->x = x;
	this->y = y;
}


void _scatter::set_options(const graphoptions &options)
{
    this->options = options;
}


int _scatter::plot() 
{

    const bool border = options.border;
    const bool axislabel = options.axislabel;
    const bool axisunitslabel = options.axisunitslabel;
    const char *const title = options.title.c_str();
    const unsigned int style = options.style;
	const unsigned int color = options.color;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (style >= (sizeof styles / sizeof styles[0])) 
	{
		std::cerr << "Style out of bound.\n";
		return 1;
	}

    if (height == 0) 
	{
		std::cerr << "The height cannot be zero, use height=-1 for automatic height.\n";
		return 1;
	}
    if (width == 0) 
	{
		std::cerr << "The width cannot be zero, use width=-1 for automatic height.\n";
		return 1;
	}
	if (height == (size_t)-1) height = w.ws_row * 4;
	if (width == (size_t)-1) width = w.ws_col * 2;

    const int aheight = height / 4;
    const int awidth = width / 2; 

    if (aheight > w.ws_row)
	{
		std::cerr << "The height of the graph (" << aheight << ") is greater then the height of the terminal (" << w.ws_row << ").\n";
		return 1;
	}
	if (awidth > w.ws_col)
	{
		std::cerr << "The width of the graph (" << awidth << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
		return 1;
	}
	
	if (xmin == 0 and xmax == 0)
	{
		xmin = std::numeric_limits<double>::max();
		xmax = std::numeric_limits<double>::min();

		for (auto const &x_val : x)
		{
			if (x_val < xmin)
				xmin = x_val;

			if (x_val > xmax)
				xmax = x_val;
		}
	}
	if (ymin == 0 and ymax == 0)
	{
		ymin = std::numeric_limits<double>::max();
		ymax = std::numeric_limits<double>::min();

		for (auto const &y_val : y)
		{
			if (y_val < ymin)
				ymin = y_val;

			if (y_val > ymax)
				ymax = y_val;
		}
	}
    if (xmin >= xmax)
	{
		std::cerr << "xmin must be less than xmax.\n";
		return 1;
	}
	if (ymin >= ymax)
	{
		std::cerr << "ymin must be less than ymax.\n";
		return 1;
	}

    const long double xscl = width / (xmax - xmin);
	const long double yscl = height / (ymax - ymin);
	const long double xaxis = width - (xmax * xscl);
	const long double yaxis = ymax * yscl;
	const int divisor = 2 * 4 * ((width / 160.0) > 1 ? (width / 160) + 1 : 1);

	std::vector<std::vector<unsigned short>> array(height, std::vector<unsigned short>(width, 0));
	for (unsigned int i = 0; i < x.size(); ++i)
	{
		if (x[i] >= xmin and x[i] < xmax and y[i] >= ymin and y[i] < ymax)
		{
			const long long ix = (x[i] * xscl) + xaxis;
			const long long iy = (yaxis - (y[i] * yscl)) - 1;

			array[ix][iy] = color + 1;
		}
	}

    setlocale(LC_CTYPE, "");

	if (title != NULL and title[0] != '\0')
		std::cout << wrap(title, w.ws_col) << "\n";

    for (unsigned int i = 0; i < height; i += 4)
	{
		const bool ayaxis = (i <= yaxis and (i + 4) > yaxis);
		const bool yaxislabel = (i <= (yaxis + 4) and (i + 4) > (yaxis + 4));

		std::ostringstream ylabelstrm;
		size_t ylabellength = 0;

		if (border and axislabel and axisunitslabel)
		{
			bool output = false;
			long double label = 0;
			int adivisor = divisor;
			if (i < yaxis)
				adivisor = -adivisor;

			for (long double k = yaxis + adivisor; ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or !axislabel) and !output; k += adivisor)
			{
				if (i <= k and (i + 4) > k)
				{
					label = ymax - (k / yscl);

					output = true;
				}
			}

			if (output)
			{
				ylabellength = outputlabel(label, ylabelstrm);
				ylabellength *= 2;
			}
		}

		for (unsigned int j = 0; j < width; j += 2)
		{
			const bool axaxis = (j <= xaxis and (j + 2) > xaxis);
			const bool xaxislabel = (j <= (xaxis - 2) and (j + 2) > (xaxis - 2));

			bool output = false;

			if (border)
			{
				if (axaxis and ayaxis)
				{
					std::cout << styles[style][6];
					output = true;
				}
				else if (axaxis)
				{
					if (axislabel and axisunitslabel)
					{
						int adivisor = divisor;
						if (i < yaxis)
							adivisor = -adivisor;

						for (long double k = yaxis + adivisor; ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or !axislabel) and !output; k += adivisor)
						{
							if (i <= k and (i + 4) > k)
							{
								std::cout << styles[style][7];
								output = true;
							}
						}
					}
					if (!output)
					{
						if (i == 0)
							std::cout << styles[style][4];
						else if (i >= (height - 4))
							std::cout << styles[style][10];
						else
							std::cout << styles[style][1];
						output = true;
					}
				}
				else if (ayaxis)
				{
					if (axislabel and axisunitslabel)
					{
						int adivisor = divisor;
						if (j < xaxis)
							adivisor = -adivisor;

						for (long double k = xaxis + adivisor; ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and (j < (width - 4) or !axislabel) and !output; k += adivisor)
						{
							if (j <= k and (j + 2) > k)
							{
								std::cout << styles[style][3];
								output = true;
							}
						}
					}
					if (!output)
					{
						if (j == 0)
							std::cout << styles[style][2];
						else if (j >= (width - 2))
							std::cout << styles[style][4];
						else
							std::cout << styles[style][0];
						output = true;
					}
				}
				else if (yaxislabel and xaxislabel and axislabel and axisunitslabel)
				{
					std::cout << "0";
					output = true;
				}
				else if (j >= (width - 2) and yaxislabel and axislabel)
				{
					std::cout << "x";
					output = true;
				}
				else if (yaxislabel and axislabel and axisunitslabel)
				{
					long double label;
					int adivisor = divisor;
					if (j < xaxis)
					{
						adivisor = -adivisor;
						j += 2;
					}

					for (long double k = xaxis + adivisor; ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and j < (width - 2) and !output; k += adivisor)
					{
						if (j <= k and (j + 2) > k)
						{
							label = (k / xscl) + xmin;

							output = true;
						}
					}

					if (adivisor < 0)
						j -= 2;

					if (output)
					{
						output = false;

						std::ostringstream strm;
						size_t length = outputlabel(label, strm);
						length *= 2;
						if ((j >= xaxis or (j + length) < (xaxis - 4)) and (j + length) < (width - 2))
						{
							std::cout << strm.str();

							if (length > 2)
								j += length - 2;

							if (adivisor < 0)
								output = true;
							else
								j += 2;
						}
					}
				}
				else if (i == 0 and xaxislabel and axislabel)
				{
					std::cout << "y";
					output = true;
				}
				else if ((j <= (xaxis - ylabellength) and (j + 2) > (xaxis - ylabellength)) and axislabel and axisunitslabel)
				{
					std::cout << ylabelstrm.str();
					output = true;
					if (ylabellength > 2)
						j += ylabellength - 2;
				}
			}

			if (!output)
			{
				unsigned int dot = 0;
				unsigned short color = 0;

				for (unsigned int k = 0; k < 2 and k < (width - j); ++k)
				{
					for (unsigned int l = 0; l < 4 and l < (height - i); ++l)
					{
						dot += (array[j + k][i + l] ? 1 : 0) * values[k][l];
						if (color)
						{
							if (array[j + k][i + l] and color != array[j + k][i + l])
								color = 1;
						}
						else
							color = array[j + k][i + l];
					}
				}

				if (color)
					--color;

				if (color)
					std::cout << colors[color];

				std::cout << "\e[1m" << dots[dot] << "\e[22m";

				if (color)
					std::cout << colors[0];
			}
		}

		std::cout << "\n";
	}

	std::cout << "\n";

    return 0;

}