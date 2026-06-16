#include<pybind11/pybind11.h>
#include<pybind11/operators.h>
#include <pybind11/functional.h>
#include<sstream>
#include "matrix1.h"
#include "types.h"
namespace py = pybind11;
template <typename T>
struct vectorptr {
    Matrix1<T>* mat; 
    size_t row;           
    T get(size_t col) const {return mat->get(row, col);}
    void set(size_t col, T value) {mat->set(row, col, value);}
};

template <typename T>
void bind_matrix(py::module &m, const std::string &name) {
    std::string proxy_name = "_MatrixRow_" + name;
    py::class_<vectorptr<T>>(m, proxy_name.c_str())
        .def("__getitem__", &vectorptr<T>::get)
        .def("__setitem__", &vectorptr<T>::set);

    py::class_<Matrix1<T>>(m, name.c_str())
        .def(py::init<size_t, size_t>())
        .def(py::init<>())
        .def("__getitem__", [](Matrix1<T> &m, size_t row){ return vectorptr{&m,row}; })
        .def("__str__", [](const Matrix1<T> &m) {
            stringstream ss;
            m.Print(ss);
            return ss.str();
        })
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def("__mul__", [](Matrix1<T> &mat, T value)    {return mat * value;})
        .def("__rmul__", [](Matrix1<T> &m, T value)     {return m * value;})
        .def("transpose", &Matrix1<T>::Transpose, py::return_value_policy::reference)
        .def_property_readonly("T", &Matrix1<T>::Transpose, py::return_value_policy::reference)
        .def("map", &Matrix1<T>::Map, py::return_value_policy::reference)
        .def("read_from_string", [](Matrix1<T> &mat, const std::string &texto) {
            std::istringstream iss(texto);
            mat.Read(iss);
        });
}

PYBIND11_MODULE(_matrix, m) {
    bind_matrix<T5>(m, "MatrixDouble");
    bind_matrix<TI>(m, "MatrixInt");
}