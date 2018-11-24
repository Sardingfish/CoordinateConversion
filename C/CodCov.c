/*------------------------------------------------------------------------------
* CodCov.c : compute Coordinate Conversion
*
*          Copyright (C) 2018 by DING Junsheng, All rights reserved.
*
* version : $Revision: 1.1 $ $Date: 2018/10/23 21:48:06 $
* history : 2018/10/23  1.0  new
*-----------------------------------------------------------------------------*/
#include "CodCov.h"

/* Rotation matrix around the X-axis ----------------------------------*/
double *RotationMatrixRx(double *Rx,double alpha)
{
    Rx[(1-1)*3+(1-1)]=1;
    Rx[(2-1)*3+(2-1)]=cos(alpha);
    Rx[(2-1)*3+(3-1)]=sin(alpha);
    Rx[(3-1)*3+(2-1)]=-sin(alpha);
    Rx[(3-1)*3+(3-1)]=cos(alpha);
    return Rx;
}
/* Rotation matrix around the Y-axis ----------------------------------*/
double *RotationMatrixRy(double *Ry,double beta)
{
    Ry[(1-1)*3+(1-1)]=cos(beta);
    Ry[(1-1)*3+(3-1)]=-sin(beta);
    Ry[(2-1)*3+(2-1)]=1;
    Ry[(3-1)*3+(1-1)]=sin(beta);
    Ry[(3-1)*3+(3-1)]=cos(beta);
    return Ry;
}
/* Rotation matrix around the Z-axis ----------------------------------*/
double *RotationMatrixRz(double *Rz,double gamma)
{
    Rz[(1-1)*3+(1-1)]=cos(gamma);
    Rz[(1-1)*3+(2-1)]=sin(gamma);
    Rz[(2-1)*3+(1-1)]=-sin(gamma);
    Rz[(2-1)*3+(2-1)]=cos(gamma);
    Rz[(3-1)*3+(3-1)]=1;
    return Rz;
}
/* Rotation matrix ----------------------------------------------------*/
double *RotationMatrix(double alpha,double beta,double gamma)
{
    double *Rx,*Ry,*Rz,*R1,*R2,*R;
	Rx=zeros(3,3);Ry=zeros(3,3);Rz=zeros(3,3);
	R1=zeros(3,3);R2=zeros(3,3);R=zeros(3,3);
    Rx=RotationMatrixRx(Rx,alpha);
    Ry=RotationMatrixRy(Ry,beta);
    Rz=RotationMatrixRz(Rz,gamma);
    matmul("NN",3,3,3,1.0,Rx,Ry,0.0,R1);
    //matmul("NN",3,3,3,1.0,Ry,Rz,0.0,R2);
    matmul("NN",3,3,3,1.0,R1,Rz,0.0,R);
    return R;
}
/* Coordinate Conversion ----------------------------------------------*/
double *CoordinateConversion(double *X0,double alpha,double beta,double gamma)
{
    double *X1=zeros(3,1);
    double *R=RotationMatrix(alpha,beta,gamma);
    matmul("NN",3,1,3,1.0,R,X0,0.0,X1);
    return X1;
}
/* Degrees to Radians -------------------------------------------------*/
double deg2rad(double angle)
{
    return PI*angle/180;
}
/* Radians to Degrees -------------------------------------------------*/
double rad2deg(double angle)
{
    return angle*180/PI;
}
