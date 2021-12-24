import sys
sys.path.insert(0, './build')

import numpy as np
import termplot

def test_graphList():
    
    height = 80
    width = 80

    xmin = -20
    xmax = 20
    ymin = -20
    ymax = 20

    options = termplot.graphoptions()

    xarr = [i for i in range(-19, 20)]
    yarr = [i for i in range(-19, 20)]

    graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
    graph.plot()


def test_graphNumpy():
    
    height = 80
    width = 80

    xmin = -20
    xmax = 20
    ymin = -20
    ymax = 20

    options = termplot.graphoptions()

    xarr = np.arange(-19.0, 20.0)
    yarr = np.arange(-19.0, 20.0)

    graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
    graph.plot()


def test_OptionsChange():
    
    height = 80
    width = 80

    xmin = -20
    xmax = 20
    ymin = -20
    ymax = 20

    options = termplot.graphoptions()
    options.border = False
    options.axislabel = False 
    options.axisunitslabel = False
    options.title = "Title of Graph"
    options.style = 3
    options.color = 3

    xarr = np.arange(-19.0, 20.0)
    yarr = np.arange(-19.0, 20.0)

    graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
    graph.plot()


def test_DataChange():
    height = 80
    width = 80

    xmin = -20
    xmax = 20
    ymin = -20
    ymax = 20

    xarr = np.arange(-19.0, 20.0)
    yarr = np.arange(-19.0, 20.0)

    options = termplot.graphoptions()
    options.title = "Before"
    graph = termplot.scatter(height, width, xmin, xmax, ymin, ymax, xarr, yarr, options)
    graph.plot()

    options.title = "After"
    xarr = np.arange(-29, 30)
    yarr = np.power(xarr, 2)
    graph.set_dims(160, 160) # height, width
    graph.set_xbounds(-50, 50)
    graph.set_ybounds(-50, 50)
    graph.set_data(xarr, yarr)
    graph.set_options(options)
    graph.plot()


if __name__ == "__main__":
    test_graphList()
    test_graphNumpy()
    test_OptionsChange()
    test_DataChange()