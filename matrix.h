#ifndef MATRIX_H
#define MATRIX_H

#include "includes.h"

class Vector;

class Matrix {
    size_t N;
    elem_t *mat;
public:
    Matrix(size_t size);
    Matrix &operator=(const Matrix& mt);
    elem_t *operator[](int idx) const;
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend Vector operator*(const Matrix &mt, const Vector &v);
    inline size_t size() const { return N; }
    ~Matrix();
};

#endif MATRIX_H