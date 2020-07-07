#include <stdexcept>
#include <cstring>
#include "vector.h"

Vector::Vector(size_t N) {
    if (N < 0) {
        throw new std::invalid_argument("Vector size cannot be negative");
    }
    Vector::N = N;
    vec = new elem_t[N];
}

Vector &Vector::operator=(const Vector &v) {
    delete vec;
    N = v.N;
    vec = new elem_t[N];
    memcpy(vec, v.vec, N * sizeof(elem_t));
    return *this;
}

elem_t &Vector::operator[](const int idx) const {
    if (idx < 0 || idx >= N) {
        throw new std::out_of_range("Vector index is out of range.");
    }
    return vec[idx]; 
}

Vector operator*(const Matrix &mt, const Vector &v) {
    if (mt.N != v.N) {
        throw new std::logic_error("Matrix and vector sizes must match.");
    }
    size_t N = v.N;
    Vector v_new(N);
    for (int i = 0; i < N; i++) {
        elem_t cell = 0;
        for (int j = 0; j < N; j++) {
            cell += mt[i][j] * v[j];
        }
        v_new[i] = cell;
    }
    return v_new;
}

Vector operator+(const Vector &v1, const Vector &v2) {
    if (v1.N != v2.N) {
        throw new std::logic_error("Vector sizes must match.");
    }
    size_t N = v1.N;
    Vector v(N);
    for (int i = 0; i < N; i++) {
        v[i] = v1[i] + v2[i];
    }
    return v;
}

Vector operator-(const Vector &v1, const Vector &v2) {
    if (v1.N != v2.N) {
        throw new std::logic_error("Vector sizes must match.");
    }
    size_t N = v1.N;
    Vector v(N);
    for (int i = 0; i < N; i++) {
        v[i] = v1[i] - v2[i];
    }
    return v;
}

Vector::~Vector() {
    delete vec;
}