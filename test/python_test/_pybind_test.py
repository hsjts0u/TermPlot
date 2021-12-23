import sys
sys.path.insert(0, './build')

import numpy as np
import termplot

height = 80
width = 80

xmin = -20.0
xmax = 20.0
ymin = -20.0
ymax = 20.0

options = termplot.graphoptions()

xarr = np.arange(-19.0, 20.0)
yarr = np.arange(-19.0, 20.0)

graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
graph.plot()

xarr = [i for i in range(-19, 20)]
yarr = [i for i in range(-19, 20)]

graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
graph.plot()