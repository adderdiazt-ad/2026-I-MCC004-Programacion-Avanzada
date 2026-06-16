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

using namespace std;

template <typename T>
void PrintM(T &n, ostream &os) { os << n << " "; }

template <typename T>
void inv_elem(T &n) {
    if (n != 0)  n = 1 / n;
}

template <typename T>
class Matrix1 {
    private:
        T      **m_pMat = nullptr;
        size_t   m_rows = 0, m_cols = 0;
    public:
        Matrix1(){};
        Matrix1 (size_t rows, size_t cols);
        ~Matrix1()     { Destroy(); }
        Matrix1 (const Matrix1 &other) = delete;
        Matrix1 (Matrix1 &&other);
        void     Create();

        T get(size_t r, size_t c) const;
        void set(size_t r, size_t c, T value);

        istream &Read(istream &is);
        template <typename Func, typename... Args>
        void ApplyFunctionToAll(Func func, Args&& ...args);
        ostream &Print(ostream &os) const;
        void Destroy();
        T* operator[](size_t row) { return m_pMat[row]; }
        Matrix1<T> operator+(const Matrix1<T> &other) const;
        Matrix1<T> operator-(const Matrix1<T> &other) const;
        Matrix1<T> operator*(T value) ;
        Matrix1<T> operator*(const Matrix1<T> &other) const;
        Matrix1<T> &operator=( Matrix1<T> &&other);
        Matrix1<T> &Transpose();
        Matrix1<T> &Map(const std::function<T(T)>& func);
};
template <typename T>
Matrix1<T>::Matrix1(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
    Create();
    this->ApplyFunctionToAll([](T &n,size_t i,size_t j, Matrix1<T> &mat) {n = 0;}, *this);
}
template <typename T>
Matrix1<T>::Matrix1(Matrix1 &&other) {
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
Matrix1<T>& Matrix1<T>::Transpose() {
    Matrix1<T> temp;
    temp.m_rows = m_cols;
    temp.m_cols = m_rows;
    temp.Create(); 
    temp.ApplyFunctionToAll([this](T &n, size_t i, size_t j) {
         n = this->m_pMat[j][i];
    });
    *this = move(temp);
    return *this;
}
template <typename T>
Matrix1<T>& Matrix1<T>::Map(const function<T(T)>& func) {
    this->ApplyFunctionToAll([&func](T &n, size_t i, size_t j) {n = func(n); });
    return *this;
}
template <typename T>
T Matrix1<T>::get(size_t r, size_t c) const {
    return (r<m_rows && c<m_cols) ? m_pMat[r][c] : throw invalid_argument("Índice fuera de los límites"); 
}
template <typename T>
void Matrix1<T>::set(size_t r, size_t c, T value) {
    if(r<m_rows && c<m_cols) m_pMat[r][c] = value;
    else throw invalid_argument("Índice fuera de los límites");
}
template <typename T>
istream &Matrix1<T>::Read(istream &is) {
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
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw invalid_argument("Error de dimensiones: Para la suma, ambas matrices deben tener el mismo número de filas y columnas.");
    }
    Matrix1<T> m3(other.m_rows, other.m_cols);
    m3.ApplyFunctionToAll([](T &n, size_t i, size_t j, const Matrix1<T> &m1, const Matrix1<T> &m2) {
        n = m1.m_pMat[i][j] + m2.m_pMat[i][j];
    }, *this, other);
    return m3;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator-(const Matrix1<T> &other) const{
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