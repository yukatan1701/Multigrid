#include <cmath>
#include "mgm.h"

double f(double x, double y) {
    return -1;
	return -2 * sin(x * y) * exp(x * y);
}

int main(int argc, char **argv) {
    size_t ng = 2; // ng is a maximal grid level
    size_t ncycles = 2;
    if (argc > 2) {
        ng = atoi(argv[1]);
        ncycles = atoi(argv[2]);
    }
    if (ng > NGMAX) {
        std::cout << "Too large ng value. (NGMAX is " << NGMAX << ")."
                  << std::endl;
    }
    size_t n = (1L << ng) + 1;
    Matrix rhs(n);
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            rhs[i][j] = f(i / double(n), j / double(n));
        }
    }
    Matrix u = MGM(rhs, ng, ncycles);
    #ifndef DEBUG
    printf("# X, Y, Z\n");
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            printf("%lu %lu %lf\n", i, j, u[i][j]);
        }
    }
    #endif
    #ifdef DEBUG
        u.print();
    #endif
    return 0;
}