#pragma once

#include<iostream>                                 // ����/�����
#include<fstream>                                  // �ļ���
using namespace std;

#if !defined PI
#define PI 3.14159265358979312                     // Բ����
#endif
#if !defined UNK
#define UNK (-PI*PI*PI)                            // ����δ֪��
#endif
#if !defined rou
#define rou (180.*60.*60./PI)                      // 1���ȶ�Ӧ������
#endif
//**********************************************************************
/*
double setf(double a, int t)                       // ����a��С��λ��Ϊt
{
   double b=fabs(a);                               // ����a�ľ���ֵ          
    for(int i=0;i<t;i++)
	   b*=10;                                      // ��b����10��t�η�
    if(b-floor(b)>0.5) b=floor(b)+1;               // ��b��С��ȡ��
    else b=floor(b);
    for(int i=0;i<t;i++)
	   b/=10;                                      // ��b����10��t�η�
    if(a<0) b=-b;                                  // aΪ�����Ĵ���
     return b;
}
*/
//******************************************************************** 
class MAT                                                    // ������        
{   
  public:                                       //���г�Ա����
	MAT();                                      //��ʼ��δ֪�������ľ���	
	MAT(int hang,int lie);                      //��ʼ����֪�������ľ���
    MAT( MAT &S);                               //�������캯��
	MAT(int hl);                                //���������ξ���  
	~MAT();                                     //��������	
	
	void SetRow(int h);                         //���þ�������   
	void SetRank(int l);                        //���þ������� 
	void SetRR(int h,int l);                    //���þ����С�����

	int GetRow();                               //���ؾ�������   
	int GetRank();                              //���ؾ�������   
    void GetRR(int &row,int &rank);             //���ؾ��������������

	void SetElem(int h,int l,double m);         //���þ���h,lλ�õ�Ԫ��
	double& GetElem(int h, int l);              //���ؾ���h,lλ�õ�Ԫ��

	void SetALL();                              //���������������Ԫ��ֵ
	void SetI();                                //���õ�ǰ����Ϊ��λ��
    void Set1();                                //���õ�ǰ��������Ԫ��Ϊ1
	void Set0();                                //���õ�ǰ��������Ԫ��Ϊ0
	bool CheckI();                              //�жϵ�ǰ�����Ƿ�Ϊ��λ��

    void print();                               //����Ļ��ʾ����

	MAT & operator = ( MAT &other);             //�þ���Ծ���ֵ	
	bool operator ==(MAT &A);                   //�ж����������Ƿ���ͬ
    MAT & operator +=(MAT &other);              //�������ĺ͵��ڲ���
	MAT operator + (MAT &B);                    //�����������
	MAT operator - (MAT &B);                    //�����������
    MAT operator * (MAT &B);                    //�����������
    friend MAT operator * (double A,MAT &B);    //���˾�������
    MAT operator * (double B);                  //�����������
    MAT operator / (double B);                  //�������������
    friend ostream & operator <<(ostream &ou,MAT &A);   //�������
    friend istream & operator >>(istream &in,MAT &A);   //�������
    double & operator () (int h,int l);                 //����h�С�l��λ�õ�Ԫ��	

	MAT inverse();                //���㷽������󣨼���ʧ�ܷ���0��0�ľ���
 	MAT T();                      //����ת��
    int R();                      //����������          
    double hl();                  //�����������ʽֵ   
	double Trace();               //�������ļ�

	MAT ChildMAT(int row1,int rank1,int row2,int rank2);  
	                              //����row1-row2��rank1-rank2���Ӿ���
	MAT ChildMAT(int row,int rank);
	                              //����(row,rank)Ԫ�ص��Ӿ���
    MAT _row(int i);              //ȥ����i�й����¾���
    MAT _rank(int i);             //ȥ����i�й����¾���
	MAT _row_rank(int i,int j);   //ȥ����i�к͵�j�й����¾���
	
  private:                        //˽�г�Ա���� 
    int row;                      //���������
	int rank;                     //���������
    double *elem;                 //����Ԫ�أ�һά��̬���飩
	
	MAT inverse1();               //������������ͨ�������ֱ�ӱ任��
	void SetRR();                 //����row��rank��ֵ���þ������������Ԫ�ظ�ֵΪ0
	bool exrow(int,int);          //�������������Ԫ��
	bool exrank(int,int);	      //�������������Ԫ��
};
