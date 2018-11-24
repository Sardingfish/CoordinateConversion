#pragma once

#include<iostream>                                 // 输入/输出流
#include<fstream>                                  // 文件流
using namespace std;

#if !defined PI
#define PI 3.14159265358979312                     // 圆周率
#endif
#if !defined UNK
#define UNK (-PI*PI*PI)                            // 定义未知数
#endif
#if !defined rou
#define rou (180.*60.*60./PI)                      // 1弧度对应的秒数
#endif
//**********************************************************************
/*
double setf(double a, int t)                       // 设置a的小数位数为t
{
   double b=fabs(a);                               // 计算a的绝对值          
    for(int i=0;i<t;i++)
	   b*=10;                                      // 对b乘以10的t次方
    if(b-floor(b)>0.5) b=floor(b)+1;               // 对b的小数取整
    else b=floor(b);
    for(int i=0;i<t;i++)
	   b/=10;                                      // 对b除以10的t次方
    if(a<0) b=-b;                                  // a为负数的处理
     return b;
}
*/
//******************************************************************** 
class MAT                                                    // 矩阵类        
{   
  public:                                       //公有成员声明
	MAT();                                      //初始化未知行列数的矩阵	
	MAT(int hang,int lie);                      //初始化已知行列数的矩阵
    MAT( MAT &S);                               //拷贝构造函数
	MAT(int hl);                                //定义正方形矩阵  
	~MAT();                                     //析构函数	
	
	void SetRow(int h);                         //设置矩阵行数   
	void SetRank(int l);                        //设置矩阵列数 
	void SetRR(int h,int l);                    //设置矩阵行、列数

	int GetRow();                               //返回矩阵行数   
	int GetRank();                              //返回矩阵列数   
    void GetRR(int &row,int &rank);             //返回矩阵的行数与列数

	void SetElem(int h,int l,double m);         //设置矩阵h,l位置的元素
	double& GetElem(int h, int l);              //返回矩阵h,l位置的元素

	void SetALL();                              //键盘输入矩阵所有元素值
	void SetI();                                //设置当前矩阵为单位阵
    void Set1();                                //设置当前矩阵所有元素为1
	void Set0();                                //设置当前矩阵所有元素为0
	bool CheckI();                              //判断当前矩阵是否为单位阵

    void print();                               //向屏幕显示矩阵

	MAT & operator = ( MAT &other);             //用矩阵对矩阵赋值	
	bool operator ==(MAT &A);                   //判断两个矩阵是否相同
    MAT & operator +=(MAT &other);              //定义矩阵的和等于操作
	MAT operator + (MAT &B);                    //矩阵相加运算
	MAT operator - (MAT &B);                    //矩阵相减运算
    MAT operator * (MAT &B);                    //矩阵相乘运算
    friend MAT operator * (double A,MAT &B);    //数乘矩阵运算
    MAT operator * (double B);                  //矩阵乘数运算
    MAT operator / (double B);                  //矩阵除以数运算
    friend ostream & operator <<(ostream &ou,MAT &A);   //输出矩阵
    friend istream & operator >>(istream &in,MAT &A);   //输入矩阵
    double & operator () (int h,int l);                 //返回h行、l列位置的元素	

	MAT inverse();                //计算方阵的逆阵（计算失败返回0×0的矩阵）
 	MAT T();                      //矩阵转置
    int R();                      //计算矩阵的秩          
    double hl();                  //计算矩阵行列式值   
	double Trace();               //计算矩阵的迹

	MAT ChildMAT(int row1,int rank1,int row2,int rank2);  
	                              //构造row1-row2、rank1-rank2的子矩阵
	MAT ChildMAT(int row,int rank);
	                              //构成(row,rank)元素的子矩阵
    MAT _row(int i);              //去掉第i行构造新矩阵
    MAT _rank(int i);             //去掉第i列构造新矩阵
	MAT _row_rank(int i,int j);   //去掉第i行和第j列构造新矩阵
	
  private:                        //私有成员声明 
    int row;                      //矩阵的行数
	int rank;                     //矩阵的列数
    double *elem;                 //矩阵元素（一维动态数组）
	
	MAT inverse1();               //计算矩阵的逆阵（通过矩阵的直接变换）
	void SetRR();                 //利用row和rank的值设置矩阵阶数，所有元素赋值为0
	bool exrow(int,int);          //交换矩阵的两行元素
	bool exrank(int,int);	      //交换矩阵的两列元素
};
