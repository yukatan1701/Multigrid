#ifndef MATRIX_H
#define MATRIX_H

#include "includes.h"
#include <cstring>
#include <iostream>

class Matrix {
    size_t N;
    elem_t *mat;
public:
    Matrix(size_t size);
    Matrix &operator=(const Matrix &mt);
    Matrix &operator+=(const Matrix &mt);
    elem_t *operator[](size_t idx) const;
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(elem_t alpha, const Matrix &mt);
    inline size_t size() const { return N; }
    friend std::ostream &operator<<(std::ostream &o, const Matrix &mt);
    void clear() { memset(mat, 0, (N + 1) * (N + 1) * sizeof(elem_t)); }
    void print() const;
    /*void fill_diagonals(elem_t lower, elem_t central, elem_t upper);
    void load_from_blocks(const Matrix &m_lower, const Matrix &m_center,
                          const Matrix &m_upper, elem_t alpha);*/
    ~Matrix();
};

#endif