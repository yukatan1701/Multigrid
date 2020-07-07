#include <cstring>
#include <stdexcept>
#include "matrix.h"

Matrix::Matrix(size_t N) {
    if (N < 0) {
        throw new std::invalid_argument("Matrix size cannot be negative.");
    }
    Matrix::N = N;
    mat = new elem_t[N * N];
}

Matrix &Matrix::operator=(const Matrix& mt) {
    delete mat;
    size_t N = mt.N;
    mat = new elem_t[N * N];
    memcpy(mat, mt.mat, N * N * sizeof(elem_t));
    return *this;
}

elem_t *Matrix::operator[](const int idx) const {
    if (idx < 0)
        throw new std::invalid_argument("Matrix index is negative.");
    return mat + idx * N;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    if (m1.N != m2.N) {
        throw new std::logic_error("Matrix sizes must match.");
    }

    Matrix mt(m1.N);
    size_t N = mt.N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            elem_t cell = 0;
            for (int k = 0; k < N; k++) {
                cell += m1[i][k] * m2[k][j];
            }
            mt[i][j] = cell;
        }
    }
    return mt;
}

Matrix::~Matrix() {
    delete mat;
}