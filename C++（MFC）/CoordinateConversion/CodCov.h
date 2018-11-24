#pragma once

#include "MAT.h"
#include <math.h>

class CodCov
{
public:
	double alpha,beta,gamma;
	MAT Rx,Ry,Rz;
	MAT X0,X1;

	CodCov();
	~CodCov();
	MAT RotationMatrixRx();
	MAT RotationMatrixRy();
	MAT RotationMatrixRz();
	MAT RotationMatrix();
	void CoordinateConversion();

};

CodCov::CodCov()
{
	alpha=beta=gamma=0;
	Rx.SetRow(3);Rx.SetRank(3);Rx.Set0();
	Ry.SetRow(3);Ry.SetRank(3);Ry.Set0();
	Rz.SetRow(3);Rz.SetRank(3);Rz.Set0();
	X0.SetRow(3);X0.SetRank(1);X0.Set0();
	X1.SetRow(3);X1.SetRank(1);X1.Set0();
}

CodCov::~CodCov()
{
}

MAT CodCov::RotationMatrixRx()
{
	Rx.SetElem(0,0,1);
	Rx.SetElem(1,1,cos(alpha));
	Rx.SetElem(1,2,sin(alpha));
	Rx.SetElem(2,1,-sin(alpha));
	Rx.SetElem(2,2,cos(alpha));
	return Rx;
}

MAT CodCov::RotationMatrixRy()
{
	Ry.SetElem(1,1,1);
	Ry.SetElem(0,0,cos(beta));
	Ry.SetElem(2,0,sin(beta));
	Ry.SetElem(0,2,-sin(beta));
	Ry.SetElem(2,2,cos(beta));
	return Ry;
}

MAT CodCov::RotationMatrixRz()
{
	Rz.SetElem(2,2,1);
	Rz.SetElem(1,1,cos(gamma));
	Rz.SetElem(0,1,sin(gamma));
	Rz.SetElem(1,0,-sin(gamma));
	Rz.SetElem(0,0,cos(gamma));
	return Rz;
}

MAT CodCov::RotationMatrix()
{
	//return (RotationMatrixRx().T()*RotationMatrixRy())*(RotationMatrixRy().T()*RotationMatrixRz());
	return (RotationMatrixRz()*RotationMatrixRy()*RotationMatrixRx());
}

void CodCov::CoordinateConversion()
{
	X1=RotationMatrix()*X0;   //cout<<X0<<endl;cout<<X1<<endl;
}

double deg2rad(double angle)
{
	return PI*angle/180;
}