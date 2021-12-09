#include "scatter.hpp"

using namespace std;

int main()
{
	const size_t height = 160;
	const size_t width = 160;

	const long double xmin = -20;
	const long double xmax = 20;
	const long double ymin = -20;
	const long double ymax = 20;

	const size_t rows = 10;
	const size_t columns = 2;

	// Output array as plot
	cout << "\nOutput array as plot\n\n";
	{
		long double **array;
		array = new long double *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new long double[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = i + j; //rand();

		graphoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			graph(height, width, xmin, xmax, ymin, ymax, rows, array, aoptions);
		}

		if (array != NULL)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}

	return 0;
}