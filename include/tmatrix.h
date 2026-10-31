// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size is too large");
    pMem = new T[sz]();
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this != &v)
    {
      TDynamicVector tmp(v);
      swap(*this, tmp);
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this != &v)
    {
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
    }
    return (*this);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz)
      throw out_of_range("Imdex is out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz)
      throw out_of_range("Imdex is out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (size_t i = 0; i < sz; i++)
      if (pMem[i] != v.pMem[i])
        return false;
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector result(*this);
    for (int i = 0; i < sz; i++)
      result.pMem[i] += val;
    return (result);
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector result(*this);
    for (int i = 0; i < sz; i++)
      result.pMem[i] -= val;
    return (result);
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector result(*this);
    for (int i = 0; i < sz; i++)
      result.pMem[i] *= val;
    return (result);
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw invalid_argument("sizes differ");
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; i++)
      result.pMem[i] += v.pMem[i];
    return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw invalid_argument("sizes differ");
    TDynamicVector result(*this);
    for (size_t i = 0; i < sz; i++)
      result.pMem[i] -= v.pMem[i];
    return result;
  }
  T operator*(const TDynamicVector& v)
    {
    if (sz != v.sz)
      throw invalid_argument("sizes differ");
    T sum = T();
    for (size_t i = 0; i < sz; i++)
      sum += pMem[i] * v.pMem[i];
    return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;  

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

    bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix result(*this);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        result.pMem[i][j] *= val;
    return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; i++)
    {
      T sum = T();
      for (size_t j = 0; j < sz; j++)
        sum += pMem[i][j] * v[j];
    result[i] = sum;
    }
    return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (this->size() != m.size())
      throw invalid_argument("Matrix sizes differ");
    TDynamicMatrix result(this->size());
    for (size_t i = 0; i < this->size(); i++)
      for (size_t j = 0; j < this->size(); j++)
        result[i][j] = (*this)[i][j] + m[i][j];
  return result;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if(sz != m.sz)
      throw invalid_argument("sizes of matrix differ");
    TDynamicMatrix result(this->size());
    for (size_t i = 0; i < this->size(); i++)
      for (size_t j = 0; j < this->size(); j++)
        result[i][j] = (*this)[i][j] - m[i][j];
  return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if(sz != m.sz)
      throw invalid_argument("sizes of matrix differ");

    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j< sz; j++)
      {
        T sum = T();
        for (size_t k = 0; k < sz; k++)
          sum += pMem[i][k] * m.pMem[k][j];
        result[i][j] = sum;
      }
    return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.size(); i++)
      for (size_t j = 0; j < v.size(); j++)
        istr >> v[i][j];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.size(); i++)
    {
      for (size_t j = 0; j < v.size(); j++)
        ostr << v[i][j] << ' ';
      ostr << '\n';
    }
    return ostr;
  }
};

#endif
