#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <functional>
#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>
#include <regex>
#include <vector>
#include <string>
#include <shared_mutex>
#include <mutex>

using namespace std;

/**
 * @brief Imprime un elemento en el flujo de salida seguido de un espacio.
 * * @tparam T Tipo de dato del elemento.
 * @param n Referencia al elemento que se va a imprimir.
 * @param os Flujo de salida donde se imprimirá el elemento.
 */
template <typename T>
void PrintM(T &n, ostream &os) { os << n << " "; }

/**
 * @brief Invierte el valor numérico de un elemento (1 / n).
 * * @tparam T Tipo de dato del elemento.
 * @param n Referencia al elemento que se va a invertir.
 */
template <typename T>
void inv_elem(T &n) {
    if (n != 0)  n = 1 / n;
}

/**
 * @class Matrix1
 * @brief Clase que representa una matriz genérica bidimensional.
 * * @tparam T Tipo de dato de los elementos almacenados en la matriz.
 */
template <typename T>
class Matrix1 {
    private:
        /** @brief Puntero doble que almacena los datos de la matriz dinámicamente. */
        T      **m_pMat = nullptr;
        /** @brief Número de filas "m_rows" de la matriz. */
        size_t   m_rows = 0, m_cols = 0;
        /** @brief Mutex para sincronización de acceso a la matriz. */
        mutable shared_mutex m_mutex;
    public:
        /**
         * @brief Constructor por defecto. Crea una matriz vacía.
         */
        Matrix1(){};

        /**
         * @brief Constructor parametrizado. Crea una matriz de dimensiones específicas inicializada en 0.
         * @param rows Número de filas.
         * @param cols Número de columnas.
         */
        Matrix1 (size_t rows, size_t cols);

        /**
         * @brief Destructor. Libera la memoria asignada a la matriz.
         */
        ~Matrix1()     { Destroy(); }

        /**
         * @brief Constructor de copia (Eliminado). No se permite la copia implícita.
         */
        Matrix1 (const Matrix1 &other) = delete;

        /**
         * @brief Constructor de movimiento. Transfiere la propiedad de los datos de otra matriz.
         * * @param other Matriz temporal (rvalue) de la cual se moverán los datos.
         */
        Matrix1 (Matrix1 &&other);

        /**
         * @brief Obtiene el valor de un elemento en una posición específica.
         * * @param r Índice de la fila.
         * @param c Índice de la columna.
         * @return T Valor en la posición especificada.
         * @throw std::invalid_argument Si los índices están fuera de los límites.
         */
        T get(size_t r, size_t c) const;

        /**
         * @brief Establece el valor de un elemento en una posición específica.
         * * @param r Índice de la fila.
         * @param c Índice de la columna.
         * @param value Nuevo valor a asignar.
         * @throw std::invalid_argument Si los índices están fuera de los límites.
         */
        void set(size_t r, size_t c, T value);

        /**
         * @brief Lee una matriz desde un flujo de entrada según un formato específico usando expresiones regulares.
         * * @param is Flujo de entrada.
         * @return istream& Referencia al flujo de entrada.
         * @throw std::invalid_argument Si el formato es incorrecto o faltan datos.
         */
        istream &Read(istream &is);

        /**
         * @brief Imprime la matriz en un flujo de salida.
         * * @param os Flujo de salida.
         * @return ostream& Referencia al flujo de salida.
         */
        ostream &Print(ostream &os) const;
        
        /**
         * @brief Suma dos matrices.
         * * @param other Matriz a sumar.
         * @return Matrix1<T> Nueva matriz resultante de la suma.
         * @throw std::invalid_argument Si las matrices no tienen las mismas dimensiones.
         */
        Matrix1<T> operator+(const Matrix1<T> &other) const;
        
        /**
         * @brief Resta dos matrices.
         * * @param other Matriz a restar.
         * @return Matrix1<T> Nueva matriz resultante de la resta.
         * @throw std::invalid_argument Si las matrices no tienen las mismas dimensiones.
         */
        Matrix1<T> operator-(const Matrix1<T> &other) const;
        
        /**
         * @brief Multiplica la matriz por un escalar.
         * * @param value Escalar por el cual se multiplicará.
         * @return Matrix1<T> Nueva matriz resultante del producto.
         */
        Matrix1<T> operator*(T value) ;
        
        /**
         * @brief Multiplica dos matrices.
         * * @param other Matriz multiplicadora.
         * @return Matrix1<T> Nueva matriz resultante de la multiplicación.
         * @throw std::invalid_argument Si las columnas de la primera no coinciden con las filas de la segunda.
         */
        Matrix1<T> operator*(const Matrix1<T> &other) const;
        
        /**
         * @brief Operador de asignación por movimiento.
         * * @param other Matriz temporal a asignar.
         * @return Matrix1<T>& Referencia a la matriz actual.
         */
        Matrix1<T> &operator=( Matrix1<T> &&other);
        
        /**
         * @brief Transpone la matriz actual (intercambia filas por columnas).
         * * @return Matrix1<T>& Referencia a la matriz modificada.
         */
        Matrix1<T> &Transpose();
        
        /**
         * @brief Mapea una función unaria sobre cada elemento de la matriz y actualiza su valor.
         * * @param func Función que recibe un tipo T y retorna un tipo T.
         * @return Matrix1<T>& Referencia a la matriz modificada.
         */
        Matrix1<T> &Map(const std::function<T(T)>& func);

        /**
         * @brief Itera sobre todos los elementos aplicando una función. Seguro para multihilos.
         * @tparam Func Tipo de la función o lambda.
         * @tparam Args Tipos de los argumentos variables.
         * @param func Función que recibe (T &n, size_t i, size_t j, Args...).
         * @param args Argumentos adicionales variables que se pasarán a la función.
         * @return Matrix1<T>& Referencia a la matriz para permitir encadenamiento.
         */
        template <typename Func, typename... Args>
        void ForEach(Func func, Args&&... args);

    protected:
        
        /**
         * @brief Reserva memoria dinámica para la matriz según `m_rows` y `m_cols`.
         * @throw std::invalid_argument Si las dimensiones son menores o iguales a cero.
         */
        void Create();

        /**
         * @brief Libera la memoria asignada a la matriz y reinicia sus dimensiones a 0.
         */
        void Destroy();
    
        /**
         * @brief Sobrecarga del operador de subíndice para acceder directamente a una fila.
         * * @param row Índice de la fila.
         * @return T* Puntero al inicio de la fila solicitada.
         */
        T* operator[](size_t row)  { return m_pMat[row]; }

        /**
         * @brief Aplica una función a todos los elementos de la matriz de forma secuencial.
         * * @tparam Func Tipo de la función o lambda a aplicar.
         * @tparam Args Tipos de los argumentos adicionales.
         * @param func Función a aplicar. Debe aceptar (T &n, size_t i, size_t j, Args...).
         * @param args Argumentos adicionales que se pasarán a la función.
         */
        template <typename Func, typename... Args>
        void ApplyFunctionToAll(Func func, Args&& ...args);
        
};
template <typename T>
Matrix1<T>::Matrix1(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
    Create();
    this->ApplyFunctionToAll([](T &n,size_t i,size_t j, Matrix1<T> &mat) {n = 0;}, *this);
}
template <typename T>
Matrix1<T>::Matrix1(Matrix1 &&other) {
    unique_lock<shared_mutex> lock(other.m_mutex);
    m_pMat = exchange(other.m_pMat, nullptr);
    m_rows = exchange(other.m_rows, 0);
    m_cols = exchange(other.m_cols, 0);
}
template <typename T>
void Matrix1<T>::Create()
{   if(m_rows > 0 && m_cols > 0) {
        m_pMat = new T *[m_rows];
        for(size_t i = 0 ; i < m_rows ; ++i)
            m_pMat[i] = new T[m_cols];
    }else{
        throw invalid_argument("Error de dimensiones: El número de filas y columnas debe ser mayor que cero.");
    }
}
template <typename T>
template <typename Func, typename... Args>
void Matrix1<T>::ForEach(Func func, Args&&... args) {
        unique_lock<shared_mutex> lock(m_mutex);
        this->ApplyFunctionToAll(func, std::forward<Args>(args)...);
}
template <typename T>
Matrix1<T>& Matrix1<T>::Transpose() {
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    Matrix1<T> temp;
    temp.m_rows = m_cols;
    temp.m_cols = m_rows;
    temp.Create(); 
    temp.ApplyFunctionToAll([this](T &n, size_t i, size_t j) {
         n = this->m_pMat[j][i];
    });
    swap(this->m_pMat, temp.m_pMat);
    swap(this->m_rows, temp.m_rows);
    swap(this->m_cols, temp.m_cols);
    return *this;
}
template <typename T>
Matrix1<T>& Matrix1<T>::Map(const function<T(T)>& func) {
    unique_lock<std::shared_mutex> lock(m_mutex);
    this->ApplyFunctionToAll([&func](T &n, size_t i, size_t j) {n = func(n); });
    return *this;
}
template <typename T>
T Matrix1<T>::get(size_t r, size_t c) const {
    shared_lock<shared_mutex> lock(m_mutex);
    return (r<m_rows && c<m_cols) ? m_pMat[r][c] : throw invalid_argument("Índice fuera de los límites"); 
}
template <typename T>
void Matrix1<T>::set(size_t r, size_t c, T value) {
    unique_lock<shared_mutex> lock(m_mutex);
    if(r<m_rows && c<m_cols) m_pMat[r][c] = value;
    else throw invalid_argument("Índice fuera de los límites");
}
template <typename T>
istream &Matrix1<T>::Read(istream &is) {
    unique_lock<shared_mutex> lock(m_mutex);
    string text = "";
    string line;
    while (getline(is, line)) {
        text += line + " ";
        if (line.find(']') != string::npos) break;
    }
    regex dim_regex(R"(Matriz:\s*(\d+)\s*x\s*(\d+))");
    smatch dim_match;
    if (regex_search(text, dim_match, dim_regex)) {
        size_t new_rows = stoull(dim_match[1].str());
        size_t new_cols = stoull(dim_match[2].str());
        Destroy();
        m_rows = new_rows;
        m_cols = new_cols;
        Create();
        size_t start = text.find('[');
        size_t end = text.find(']');
        if (start != string::npos && end != string::npos && start < end) {
            string data_str = text.substr(start + 1, end - start - 1);
            regex num_regex(R"((-?\d+(\.\d+)?(e[-+]?\d+)?))");
            sregex_iterator num_it(data_str.begin(), data_str.end(), num_regex);
            sregex_iterator num_end;
            this->ApplyFunctionToAll([&num_it, &num_end](T &n, size_t i, size_t j) {
                if (num_it != num_end) {
                    stringstream ss(num_it->str());
                    ss >> n;  
                    ++num_it;
                } else {
                    throw invalid_argument("Faltan datos numéricos para llenar la matriz.");
                }
            });
        }
    } else {
        throw invalid_argument("Formato incorrecto. Se esperaba 'Matriz: Row x Col'.");
    }

    return is;
}
template <typename T>
ostream &Matrix1<T>::Print(ostream &os) const {
    shared_lock<shared_mutex> lock(m_mutex);
    os <<"Matriz: "<< m_rows << "x" << m_cols << "\n";
    os<<"[";
    for(size_t i = 0 ; i < m_rows-1 ; ++i) {
        for(size_t j = 0 ; j < m_cols ; ++j)
            os << m_pMat[i][j] << " ";
        os<<"\n";
    }
    if(m_rows > 0) {
        for(size_t j = 0 ; j < m_cols ; ++j)
            os << m_pMat[m_rows-1][j] << " ";
    }
    os<<"]\n";
    return os;
}
template <typename T>
template <typename Func, typename... Args>
void Matrix1<T>::ApplyFunctionToAll(Func func, Args&& ...args) {
    for(size_t i = 0 ; i < m_rows ; ++i)
        for(size_t j = 0 ; j < m_cols ; ++j)
            func(m_pMat[i][j],i,j, forward<Args>(args)...);
}
template <typename T>
ostream &operator<<(ostream &os, const Matrix1<T> &mat){
    return mat.Print(os);
}

template <typename T>
istream &operator>>(istream &is, Matrix1<T> &mat){
    return mat.Read(is);
}
template <typename T>
void Matrix1<T>::Destroy() {
    if (m_pMat != nullptr) {
        for(size_t i = 0 ; i < m_rows ; ++i)
            delete[] m_pMat[i];
        delete[] m_pMat;
        m_pMat = nullptr;
    }
    m_rows = 0;
    m_cols = 0;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator+(const Matrix1<T> &other) const{
    shared_lock<shared_mutex> lockThis(m_mutex, defer_lock);
    shared_lock<shared_mutex> lockOther(other.m_mutex, defer_lock);
    if (this == &other) lockThis.lock(); else lock(lockThis, lockOther);
    if (m_rows != other.m_rows || m_cols != other.m_cols) 
        throw invalid_argument("Error de dimensiones: Para la suma, ambas matrices deben tener el mismo número de filas y columnas.");
    Matrix1<T> m3(other.m_rows, other.m_cols);
    m3.ApplyFunctionToAll([](T &n, size_t i, size_t j, const Matrix1<T> &m1, const Matrix1<T> &m2) {
        n = m1.m_pMat[i][j] + m2.m_pMat[i][j];
    }, *this, other);
    return m3;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator-(const Matrix1<T> &other) const{
    shared_lock<shared_mutex> lockThis(m_mutex, defer_lock);
    shared_lock<shared_mutex> lockOther(other.m_mutex, defer_lock);
    if (this == &other) lockThis.lock(); else lock(lockThis, lockOther);   
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw invalid_argument("Error de dimensiones: Para la resta, ambas matrices deben tener el mismo número de filas y columnas.");
    }
    Matrix1<T> m3(other.m_rows, other.m_cols);
    m3.ApplyFunctionToAll([](T &n, size_t i, size_t j, const Matrix1<T> &m1, const Matrix1<T> &m2) {
        n = m1.m_pMat[i][j] - m2.m_pMat[i][j];
    }, *this, other);
    return m3;
}
template <typename T>
Matrix1<T> Matrix1<T>::operator*(T value) {
    shared_lock<shared_mutex> lock(m_mutex);
    Matrix1<T> m2(m_rows, m_cols);
    m2.ApplyFunctionToAll([](T &n, size_t i, size_t j,  Matrix1<T> &m1, T value) {
        n = value * m1[i][j];
    }, *this, value);
    return m2;
}
template <typename T>
Matrix1<T> operator*(T value, Matrix1<T> &matrix) {
    return matrix * value;
}
template <typename T>
Matrix1<T> Matrix1<T>::operator*(const Matrix1<T> &other) const{
    shared_lock<shared_mutex> lockThis(m_mutex, defer_lock);
    shared_lock<shared_mutex> lockOther(other.m_mutex, defer_lock);
    if (this == &other) lockThis.lock(); else lock(lockThis, lockOther);
    if(m_rows != other.m_cols) {
        throw invalid_argument("Error de dimensiones: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.");
    }
    Matrix1<T> m3(m_rows, other.m_cols);
    m3.ApplyFunctionToAll([](T &n, size_t i, size_t j, const Matrix1<T> &m1, const Matrix1<T> &m2) {
        n = 0;
        for(size_t k = 0 ; k < m1.m_cols ; ++k)
            n += m1.m_pMat[i][k] * m2.m_pMat[k][j];
    }, *this, other);
    return m3;
}

template <typename T>
Matrix1<T> &Matrix1<T>::operator=( Matrix1<T> &&result){
    if(this != &result) {
        unique_lock<shared_mutex> lockThis(m_mutex);
        Destroy();
        m_pMat = exchange(result.m_pMat, nullptr);
        m_rows = exchange(result.m_rows, 0);
        m_cols = exchange(result.m_cols, 0);
    }
    return *this;
}
template <typename T>
ostream &operator<<(ostream &os,  const Matrix1<T> &&result){
    return result.Print(os);
}
#endif // __MATRIX_H__