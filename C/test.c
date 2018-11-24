#include"matrix.h"
#include"CodCov.h"
int main()
{
    double *X0=zeros(3,1);
    double alpha,beta,gamma;
	double *X1;
	X0[0]=5000;
    X0[1]=5000;
    X0[2]=100;
	alpha=deg2rad(120);beta=deg2rad(30);gamma=deg2rad(40);
    X1=CoordinateConversion(X0,alpha,beta,gamma);
    printf("%*s%s%*s%s%*s%s\n",18,"","X",18,"","Y",18,"","Z");
    printf("original   %18.6f%18.6f%18.6f\n",X0[0],X0[1],X0[2]);
    printf("transformed%18.6f%18.6f%18.6f\n",X1[0],X1[1],X1[2]);
    return 0;
}
