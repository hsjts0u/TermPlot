#include <_scatter.hpp>


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


void _scatter::set_options(const graphoptions &options)
{
    this->options = options;
}


int _scatter::plot() 
{

    const bool border = options.border;
    const bool axislabel = options.axislabel;
    const bool axisunitslabel = options.axisunitslabel;
    const char *const title = options.title;
    const unsigned int style = options.style;

    if (x.size() != y.size()) return 1;
    if (x.size() == 0) return 1;
    if (y.size() == 0) return 1;

    if (style >= (sizeof styles / sizeof styles[0])) return 1;
    if (height == 0) return 1;
    if (width == 0) return 1;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    const int aheight = height / 4;
    const int awidth = width / 2; 

    if (aheight > w.ws_row) return 1;
    if (awidth > w.ws_col) return 1;
    if (xmin >= xmax) return 1;
    if (ymin >= ymax) return 1;

    const long double xscl = width / (xmax - xmin);
	const long double yscl = height / (ymax - ymin);
	const long double xaxis = width - (xmax * xscl);
	const long double yaxis = ymax * yscl;
	const int divisor = 2 * 4 * ((width / 160.0) > 1 ? (width / 160) + 1 : 1);

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
			long double label;
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