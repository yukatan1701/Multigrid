#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

class Vector {
    size_t N;
    elem_t *vec;
public:
    Vector(size_t N);
    Vector &operator=(const Vector &v);
    elem_t &operator[](const size_t idx) const;
    friend Vector operator*(const Matrix &mt, const Vector &v);
    friend Vector operator+(const Vector &v1, const Vector &v2);
    friend Vector operator-(const Vector &v1, const Vector &v2);
    double norm() const;
    void print() const;
    elem_t size() const { return N; }
    ~Vector();
};

#endif