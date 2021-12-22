#include <TermPlot.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(TermPlot, m)
{
    
    m.doc() = "C++ plotting library for Python";

    py::class_<graphoptions>(m, "graphoptions")
        .def_readwrite("border", &graphoptions::border)
        .def_readwrite("axislabel", &graphoptions::axislabel)
        .def_readwrite("axisunitslabel", &graphoptions::axisunitslabel)
        .def_readwrite("style", &graphoptions::style)
        .def_readwrite("color", &graphoptions::color);

    py::class_<_scatter>(m, "scatter")
        .def(
            py::init<const size_t &, const size_t &
            ,const long double &, const long double &
            ,const long double &, const long double &
            ,const std::vector<double> &
            ,const std::vector<double> &
            ,const graphoptions &>()
        ) 
        .def(
            py::init(
                [](const size_t &height, const size_t &width
                ,const long double &xmin, const long double &xmax
                ,const long double &ymin, const long double &ymax
                ,const py::array_t<double> &x
                ,const py::array_t<double> &y
                ,const graphoptions &options)
                {
                    
                    py::buffer_info x_info = x.request();
                    py::buffer_info y_info = y.request();

                    if (x_info.format != py::format_descriptor<double>::format())
                        throw std::runtime_error("Expecting Numpy array with type double!");
                    if (y_info.format != py::format_descriptor<double>::format())
                        throw std::runtime_error("Expecting Numpy array with type double!");
                    if (x_info.shape != y_info.shape) 
                        throw std::runtime_error("NumPy array shape should match!");
                    if (x_info.ndim != 1 or y_info.ndim != 1) 
                        throw std::runtime_error("NumPy array should have ndim=1!");

                    std::vector<double> x_points ((double *)x_info.ptr, (double *)x_info.ptr + x_info.shape[0]);
                    std::vector<double> y_points ((double *)y_info.ptr, (double *)y_info.ptr + y_info.shape[0]);

                    _scatter * obj = new _scatter(height, width, 
                                                  xmin, xmax, 
                                                  ymin, ymax,
                                                  x_points, y_points,
                                                  options);

                    return obj;

                }
            )
        ) 
        .def(
            "set_dims", &_scatter::set_dims 
        )
        .def(
            "set_xbounds", &_scatter::set_xbounds
        )
        .def(
            "set_ybounds", &_scatter::set_ybounds
        )
        .def(
            "set_data", &_scatter::set_data
        )
        .def(
            "set_data", [](_scatter &m, const py::buffer &x, const py::buffer &y) {
                
                py::buffer_info x_info = x.request();
                py::buffer_info y_info = y.request();

                if (x_info.format != py::format_descriptor<double>::format())
                    throw std::runtime_error("Expecting Numpy array with type double!");
                if (y_info.format != py::format_descriptor<double>::format())
                    throw std::runtime_error("Expecting Numpy array with type double!");
                if (x_info.shape != y_info.shape) 
                    throw std::runtime_error("NumPy array shape should match!");
                if (x_info.ndim != 1 or y_info.ndim != 1) 
                    throw std::runtime_error("NumPy array should have ndim=1!");

                std::vector<double> x_points ((double *)x_info.ptr, (double *)x_info.ptr + x_info.shape[0]);
                std::vector<double> y_points ((double *)y_info.ptr, (double *)y_info.ptr + y_info.shape[0]);
            
                m.set_data(x_points, y_points);

            }
        )
        .def(
            "set_options", &_scatter::set_options
        )
        .def(
            "plot", &_scatter::plot
        );

}