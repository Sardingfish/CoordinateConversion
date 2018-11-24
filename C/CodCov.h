#include "matrix.h"

extern double *RotationMatrixRx(double *Rx,double alpha);
extern double *RotationMatrixRy(double *Ry,double beta);
extern double *RotationMatrixRz(double *Rz,double gamma);
extern double *RotationMatrix(double alpha,double beta,double gamma);
extern double *CoordinateConversion(double *X0,double alpha,double beta,double gamma);
extern double deg2rad(double angle);