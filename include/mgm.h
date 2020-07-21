#ifndef MGM_H
#define MGM_H

#include "includes.h"
#include "matrix.h"

#define NPRE 1
#define NPOST 1
#define NGMAX 15

Matrix MGM(const Matrix &rhs, size_t ng, size_t ncycle);

#endif