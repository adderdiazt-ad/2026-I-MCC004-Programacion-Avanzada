#include<pybind11/pybind11.h>
#include<pybind11/operators.h>
#include <pybind11/functional.h>
#include<sstream>
#include <string>

#include "matrix1.h"
#include "types.h"
namespace py = pybind11;

/**
 * @struct vectorptr
 * @brief Estructura proxy (Proxy Pattern) para permitir el acceso bidimensional seguro en Python (mat[row][col]).
 * @tparam T Tipo de dato de la matriz.
 */
template <typename T>
struct vectorptr {
   Matrix1<T>* mat;  /**< Puntero a la matriz original de C++ */
    size_t row;       /**< Índice de la fila seleccionada por el primer corchete */

    /**
     * @brief Lee el valor de una columna usando el método seguro get() (Usa shared_lock).
     * @param col Índice de la columna.
     * @return T Valor leído.
     */           
    T get(size_t col) const {return mat->get(row, col);}
    
    /**
     * @brief Escribe un valor en una columna usando el método seguro set() (Usa unique_lock).
     * @param col Índice de la columna.
     * @param value Valor a escribir.
     */
    void set(size_t col, T value) {mat->set(row, col, value);}
};

/**
 * @brief Función plantilla para registrar la clase Matrix1 y su proxy bidimensional en Python.
 * @tparam T Tipo de dato de la matriz (ej. int, double).
 * @param m Referencia al módulo principal de Pybind11.
 * @param name Nombre con el que la clase será expuesta en Python (ej. "MatrixInt").
 */
template <typename T>
void bind_matrix(py::module &m, const std::string &name) {
    std::string proxy_name = "_MatrixRow_" + name;
    py::class_<vectorptr<T>>(m, proxy_name.c_str())
        .def("__getitem__", &vectorptr<T>::get)
        .def("__setitem__", &vectorptr<T>::set);

    py::class_<Matrix1<T>>(m, name.c_str())
        .def(py::init<size_t, size_t>())
        .def(py::init<>())
        .def("__getitem__", [](Matrix1<T> &m, size_t row){ return vectorptr<T>{&m,row}; })
        .def("__str__", [](const Matrix1<T> &m) {
            stringstream ss;
            m.Print(ss);
            return ss.str();
        })
        .def(py::self + py::self, py::call_guard<py::gil_scoped_release>())
        .def(py::self - py::self, py::call_guard<py::gil_scoped_release>())
        .def(py::self * py::self, py::call_guard<py::gil_scoped_release>())
        .def("__mul__", []( Matrix1<T> &mat, T value)    {return mat * value;})
        .def("__rmul__", []( Matrix1<T> &m, T value)     {return m * value;})
        .def("transpose", &Matrix1<T>::Transpose, py::return_value_policy::reference)
        .def_property_readonly("T", &Matrix1<T>::Transpose, py::return_value_policy::reference)
        .def("map", &Matrix1<T>::Map, py::return_value_policy::reference)
        .def("read_from_string", [](Matrix1<T> &mat, const std::string &texto) {
            std::istringstream iss(texto);
            mat.Read(iss);
        });
}

/**
 * @brief Macro principal de Pybind11 que define la entrada del módulo.
 * Crea el módulo '_matrix' que se importará en Python.
 */
PYBIND11_MODULE(_matrix, m) {
    bind_matrix<T5>(m, "MatrixDouble");
    bind_matrix<TI>(m, "MatrixInt");
}