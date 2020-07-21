#include <cstring>
#include <stdexcept>
#include <iostream>
#include "matrix.h"

Matrix::Matrix(size_t N) {
    if (N < 0) {
        throw new std::invalid_argument("Matrix size cannot be negative.");
    }
    Matrix::N = N;
    mat = new elem_t[(N + 1) * (N + 1)];
    memset(mat, 0, sizeof(elem_t) * N * N);
}

Matrix::Matrix(const Matrix &mt) {
    Matrix::N = mt.N;
    mat = new elem_t[(N + 1) * (N + 1)];
    memcpy(mat, mt.mat, (N + 1) * (N + 1) * sizeof(elem_t));
}

Matrix &Matrix::operator=(const Matrix& mt) {
    delete [] mat;
    size_t N = mt.N;
    Matrix::N = N;
    mat = new elem_t[(N + 1) * (N + 1)];
    memcpy(mat, mt.mat, (N + 1) * (N + 1) * sizeof(elem_t));
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &mt) {
    if (N != mt.N) {
        throw new std::logic_error("Matrix sizes must match.");
    }
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            (*this)[i][j] += mt[i][j];
        }
    }
    return *this;
}

elem_t *Matrix::operator[](const size_t idx) const {
    if (idx < 1 || idx > N) {
        std::cerr << idx << " " << N << std::endl;
        throw new std::invalid_argument("Matrix index must be positive.");
    }
    return mat + idx * N;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    if (m1.N != m2.N) {
        throw new std::logic_error("Matrix sizes must match.");
    }

    Matrix mt(m1.N);
    size_t N = mt.N;
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            elem_t cell = 0;
            for (size_t k = 1; k <= N; k++) {
                cell += m1[i][k] * m2[k][j];
            }
            mt[i][j] = cell;
        }
    }
    return mt;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if (m1.N != m2.N) {
        throw new std::logic_error("Matrix sizes must match.");
    }

    Matrix mt(m1.N);
    size_t N = mt.N;
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            mt = m1[i][j] + m2[i][j];
        }
    }
    return mt;
}

Matrix operator-(const Matrix &m1, const Matrix &m2) {
    if (m1.N != m2.N) {
        throw new std::logic_error("Matrix sizes must match.");
    }

    Matrix mt(m1.N);
    size_t N = mt.N;
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            mt = m1[i][j] - m2[i][j];
        }
    }
    return mt;
}

Matrix operator*(elem_t alpha, const Matrix &mt) {
    Matrix m(mt.N);
    for (size_t i = 1; i <= mt.N; i++) {
        for (size_t j = 1; j <= mt.N; j++) {
            m[i][j] = mt[i][j] * alpha;
        }
    }
    return m;
}

std::ostream &operator<<(std::ostream &o, const Matrix &mt) {
    for (size_t i = 1; i <= mt.N; i++) {
        for (size_t j = 1; j <= mt.N; j++) {
            
        }
    }
    return o;
}

void Matrix::print() const {
    for (size_t i = 1; i <= N; i++) {
        for (size_t j = 1; j <= N; j++) {
            printf("%*.*lf ", PRINT_WIDTH, PRINT_PRECISION, (*this)[i][j]);
        }
        printf("\n");
    }
    printf("***********************************\n");
}
/*
void Matrix::fill_diagonals(elem_t lower, elem_t central, elem_t upper) {
    Matrix &A = *this;
    for (size_t i = 0; i < N; i++) {
        A[i][i] = central;
        if (i > 0) {
            A[i][i - 1] = lower;
        }
        if (i < N - 1) {
            A[i][i + 1] = upper;
        }
    }
}

void Matrix::load_from_blocks(const Matrix &m_lower, const Matrix &m_center,
                              const Matrix &m_upper, elem_t alpha) {
    if (N != (m_lower.N * m_lower.N) || N != (m_center.N * m_center.N) ||
        N != (m_upper.N * m_upper.N)) {
        throw new std::logic_error("Matrix sizes must match.");
    }
    size_t n = m_lower.N;
    Matrix &A = *this;
    for (size_t i = 0; i < n; i++) {
        for (size_t ii = 0; ii < n; ii++) {
            for (size_t jj = 0; jj < n; jj++) {
                A[i * n + ii][i * n + jj] = m_center[ii][jj] * alpha;
                if (i > 0) {
                    A[i * n + ii][(i - 1) * n + jj] = m_lower[ii][jj] * alpha;
                }
                if (i < n - 1) {
                    A[i * n + ii][(i + 1) * n + jj] = m_upper[ii][jj] * alpha;
                }
            }
        }
    }
}
*/
Matrix::~Matrix() {
    delete [] mat;
}