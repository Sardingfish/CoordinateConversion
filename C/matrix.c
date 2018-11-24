/*------------------------------------------------------------------------------
* matrix.c : matrix compute functions
*
*          Copyright (C) 2018 by DING Junsheng, All rights reserved.
*
* version : $Revision: 1.1 $ $Date: 2018/10/23 21:48:06 $
* history : 2018/10/23  1.0  new
*-----------------------------------------------------------------------------*/
#include "matrix.h"

/* new matrix -----------------------------------------------------------------*/
double *mat(int n, int m)
{
    double *p;
    if (n<=0||m<=0) return NULL;
    p=(double *)malloc(sizeof(double)*n*m);
    return p;
}
/* new zero matrix ------------------------------------------------------------*/
double *zeros(int n, int m)
{
    double *p;
    if ((p=mat(n,m))) for (n=n*m-1; n>=0; n--) p[n]=0.0;
    return p;
}
/* multiply matrix -----------------------------------------------------------*/
/* multiply matrix by matrix (C=alpha*A*B+beta*C)
* args   : char   *tr       I  transpose flags ("N":normal,"T":transpose)
*          int    n,k,m     I  size of (transposed) matrix A,B
*          double alpha     I  alpha
*          double *A,*B     I  (transposed) matrix A (n x m), B (m x k)
*          double beta      I  beta
*          double *C        IO matrix C (n x k)
* return : none
*-----------------------------------------------------------------------------*/
void matmul(const char *tr, int n, int k, int m, double alpha,
                   const double *A, const double *B, double beta, double *C)
{
    double d;
    int i,j,x,f=tr[0]=='N'?(tr[1]=='N'?1:2):(tr[1]=='N'?3:4);

    for (i=0; i<n; i++) for (j=0; j<k; j++)
        {
            d=0.0;
            switch (f)
            {
            case 1:
                for (x=0; x<m; x++) d+=A[i+x*n]*B[x+j*m];
                break;
            case 2:
                for (x=0; x<m; x++) d+=A[i+x*n]*B[j+x*k];
                break;
            case 3:
                for (x=0; x<m; x++) d+=A[x+i*m]*B[x+j*m];
                break;
            case 4:
                for (x=0; x<m; x++) d+=A[x+i*m]*B[j+x*k];
                break;
            }
            if (beta==0.0) C[i+j*n]=alpha*d;
            else C[i+j*n]=alpha*d+beta*C[i+j*n];
        }
}
