#include "matrix.h"
#include "vector.h"
#include <array>
#include <cmath>

#define NPRE 1
#define NPOST 1
#define NGMAX 15

double f(double x, double y) {
	return 1;
}

Matrix *rstrct(const Matrix &uf, size_t nc) {
    Matrix *UC = new Matrix(uf.size() / 2 + 1);
    Matrix &uc = *UC;
    //int nc = uc.size();
    size_t ncc = 2 * nc - 1;

    size_t ic,iif,jc,jf;

    for (jf=3,jc=2;jc<nc;jc++,jf+=2) {
		for (iif=3,ic=2;ic<nc;ic++,iif+=2) {
			uc[ic][jc]=0.5*uf[iif][jf]+0.125*(uf[iif+1][jf]+uf[iif-1][jf]
					+uf[iif][jf+1]+uf[iif][jf-1]);
		}
	}
	for (jc=1,ic=1;ic<=nc;ic++,jc+=2) {
		uc[ic][1]=uf[jc][1];
		uc[ic][nc]=uf[jc][ncc];
	}
	for (jc=1,ic=1;ic<=nc;ic++,jc+=2) {
		uc[1][ic]=uf[1][jc];
		uc[nc][ic]=uf[ncc][jc];
	}

    return UC;
}

Matrix *interp(const Matrix &uc, size_t nf) {
    Matrix *UF = new Matrix(nf);
    Matrix &uf = *UF;
    //int nf = uf.size();
	size_t nc = nf/2+1;
	size_t ic,iif,jc,jf,nc;

	for (jc=1,jf=1;jc<=nc;jc++,jf+=2)
		for (ic=1;ic<=nc;ic++)
            uf[2*ic-1][jf]=uc[ic][jc];
	for (jf=1;jf<=nf;jf+=2)
		for (iif=2;iif<nf;iif+=2)
			uf[iif][jf]=0.5*(uf[iif+1][jf]+uf[iif-1][jf]);

	for (jf=2;jf<nf;jf+=2)
		for (iif=1;iif <= nf;iif++)
			uf[iif][jf]=0.5*(uf[iif][jf+1]+uf[iif][jf-1]);

    return UF;
}

Matrix *addint(const Matrix &uc, const Matrix &res, size_t nf) {
    Matrix *uf = interp(uc, nf);
    *uf += res;
    return uf;
}

Matrix *slvsml(const Matrix &rhs) {
    Matrix *u = new Matrix(3);
    double h = 0.5;
    *u[2][2] = -h * h * rhs[2][2] / 4.0;
    return u;
}

void relax(Matrix &u, const Matrix &rhs, size_t n) {
    double h = 1.0 / double(n - 1);
    double h2 = h * h;

    int i,ipass,isw,j,jsw=1;

	for (ipass=1;ipass<=2;ipass++,jsw=3-jsw) {
		isw=jsw;
		for (j=2;j<n;j++,isw=3-isw)
			for (i=isw+1;i<n;i+=2)
				u[i][j]=0.25*(u[i+1][j]+u[i-1][j]+u[i][j+1]
					+u[i][j-1]-h2*rhs[i][j]);
	}
}

Matrix *resid(const Matrix &u, const Matrix &rhs)
{
    size_t n = u.size();
    Matrix *RES = new Matrix(n);
    Matrix &res = *RES;
	int i,j;
	double h,h2i;

	h=1.0/(n-1);
	h2i=1.0/(h*h);
	for (j=2;j<n;j++)
		for (i=2;i<n;i++)
			res[i][j] = -h2i*(u[i+1][j]+u[i-1][j]+u[i][j+1]+u[i][j-1]-
					4.0*u[i][j])+rhs[i][j];
	for (i=1;i<=n;i++)
		res[i][1]=res[i][n]=res[1][i]=res[n][i]=0.0;
    return RES;
}

Matrix MGM(const Matrix &rhs, size_t ng, int ncycle) {
    
    Matrix *ires[NGMAX + 1], *irho[NGMAX + 1], *irhs[NGMAX + 1], *iu[NGMAX + 1];

    const size_t n = rhs.size();
    size_t nn = n / 2 + 1;
    size_t ngrid = ng - 1;
    irho[ngrid] = new Matrix(nn);
    while (nn > 3) {
		nn = nn / 2 + 1;
		irho[--ngrid] = rstrct(*irho[ngrid+1], nn);
	}

    nn = 3;
    iu[1] = slvsml(*irho[1]);
    irhs[1] = new Matrix(nn);

    ngrid = ng;
    for (size_t j = 2; j <= ngrid; j++) {
		nn = 2 * nn - 1;
		iu[j] = interp(*iu[j-1], nn);
		irhs[j] = new Matrix(nn);
        if (j != ngrid) {
            *irhs[j] = *irho[j];
        } else {
            *irhs[j] = rhs;
        }
		for (size_t jcycle = 1; jcycle <= ncycle; jcycle++) {
			size_t nf = nn;
			for (size_t jj = j; jj >= 2; jj--) {
                for (size_t jpre = 1; jpre <= NPRE; jpre++)
                    relax(*iu[jj], *irhs[jj], nf);
                ires[jj] = resid(*iu[jj], *irhs[jj]);
                nf = nf / 2 + 1;
                irhs[jj-1] = rstrct(*ires[jj], nf);
                iu[jj-1]->clear();
			}
			iu[1] = slvsml(*irhs[1]);
			nf = 3;
			for (size_t jj=2;jj<=j;jj++) {
                nf = 2 * nf - 1;
                iu[jj] = addint(*iu[jj-1], *ires[jj], nf);
                for (size_t jpost = 1; jpost <= NPOST; jpost++)
                    relax(*iu[jj], *irhs[jj], nf);
			}
		}
	}
    Matrix u(n);
    u = *iu[ngrid];
    for (size_t i = 1; i < NGMAX + 1; i++) {

    }
    return u;
}



int main(int argc, char **argv) {
    int ng = 2; // m is a maximal grid level
    if (argc > 1) {
        ng = atoi(argv[1]);
    }
    size_t n = (1 << ng) + 1;
    Matrix rhs(n);
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            rhs[i][j] = f(i, j);
        }
    }
    Matrix u = MGM(rhs, ng, 2);
    u.print();
    return 0;
}