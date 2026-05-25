#ifndef __ARRAY4_H__
#define __ARRAY4_H__
#include <functional>
#include <iostream>

using namespace std;

template <typename T>
void Print4(T &n, ostream &os) { os << n << " "; }

template <typename T>
class Array4 {
    private:
        T      *m_pArray = nullptr;
        size_t  m_size   = 0;
    public:
        Array4()      { }
        ~Array4()     { Destroy(); }
        void     Create() { m_pArray = new T[m_size]; };
        istream &Read(istream &is);
        template <typename Func, typename... Args>
        void ApplyFunctionToAll(Func func, Args&& ...args);
        ostream &Print(ostream &os);
        void Destroy();
};

template <typename T>
istream &Array4<T>::Read(istream &is) {
    is >> m_size;
    Create();
    for (size_t i = 0; i < m_size; ++i)
        is >> m_pArray[i];
    return is;
}

// Variadic template
template <typename T>
template <typename Func, typename... Args>
void Array4<T>::ApplyFunctionToAll(Func func, Args&& ...args) {
    for (size_t i = 0; i < m_size; ++i)
        // func(m_pArray[i], args...);
        func(m_pArray[i], forward<Args>(args)...);
}

template <typename T>
ostream &Array4<T>::Print(ostream &os) {
    os << m_size << " \n";
    for (size_t i = 0; i < m_size; ++i)
        os << m_pArray[i] << " ";
    os << endl;
    return os;
}

template <typename T>
void Array4<T>::Destroy() {
    if (m_pArray != nullptr) {
        delete[] m_pArray;
        m_pArray = nullptr;
    }
}

template <typename T>
istream &operator>>(istream &is, Array4<T> &array){
    return array.Read(is);
}

template <typename T>
ostream &operator<<(ostream &os, Array4<T> &array){\
    array.ApplyFunctionToAll(Print4<T>, os);
    return os;
}


#endif // __ARRAY4_H__