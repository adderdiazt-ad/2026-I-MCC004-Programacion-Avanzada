#ifndef __ARRAY3_H__
#define __ARRAY3_H__
#include <functional>
#include <iostream>

using namespace std;

template <typename T>
class Array3 {
    private:
        T      *m_pArray = nullptr;
        size_t  m_size   = 0;
    public:
        Array3()      {  }
        ~Array3()     { Destroy(); }
        void Create() { m_pArray = new T[m_size]; };
        void Read(istream &is);
        template <typename Func>
        void ApplyFunctionToAll(Func func);
        void Print(ostream &os);
        void Destroy();
};

template <typename T>
void Array3<T>::Read(istream &is) {
    is >> m_size;
    Create();
    for (size_t i = 0; i < m_size; ++i)
        is >> m_pArray[i];
}

template <typename T>
template <typename Func>
void Array3<T>::ApplyFunctionToAll(Func func) {
    for (size_t i = 0; i < m_size; ++i)
        func(m_pArray[i]);
}

template <typename T>
void Array3<T>::Print(ostream &os) {
    os << m_size << " \n";
    for (size_t i = 0; i < m_size; ++i)
        os << m_pArray[i] << " ";
    os << endl;
}

template <typename T>
void Array3<T>::Destroy() {
    if (m_pArray != nullptr) {
        delete[] m_pArray;
        m_pArray = nullptr;
    }
}

#endif // __ARRAY3_H__