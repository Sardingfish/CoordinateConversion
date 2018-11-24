#include "MAT.h"

using namespace std;
//********************************************************************
//*************************矩阵类成员函数定义*************************
MAT & MAT:: operator +=(MAT &other)               //定义矩阵和等于操作
{
      *this=*this+other;               // 当前矩阵=当前矩阵+other矩阵
	  return *this;                    // 返回当前矩阵
}
//********************************************************************
MAT MAT::_row(int ii)                           //去掉第ii行构造新矩阵
{
	if(ii<0 || ii>row-1) 
	{
	  cout<<"MAT::_row(int ii)错误：给定的行数ii超出原矩阵阶数！"<<endl;
	  return MAT(0,0);
	}
    MAT C(row-1,rank);                                 //新矩阵行数减1
	for(int i=0;i<row;i++)
	  for(int j=0;j<rank;j++)
	  {
	    if(i<ii)
			C(i,j)=(*this)(i,j);
		else if(i==ii) 
			continue;                                 //删除第ii行元素 
		else
			C(i-1,j)=(*this)(i,j);
	  }
	return C;
}
//********************************************************************
MAT MAT::_rank(int ii)                          //去掉第ii列构造新矩阵
{
	if(ii<0 || ii>rank-1) 
	{
	  cout<<"MAT::_rank(int ii)错误：给定列数ii超出原矩阵阶数！"<<endl;
	  return MAT(0,0);
	}
     MAT C(row,rank-1);
	 for(int i=0;i<rank;i++)
	  for(int j=0;j<row;j++)
	  {
	    if(i<ii)
			C(j,i)=(*this)(j,i);
		else if(i==ii) 
			continue;                                 //删除第ii列元素
		else
			C(j,i-1)=(*this)(j,i);
	  }
	return C;
}
//********************************************************************
MAT MAT::_row_rank(int i,int j)           //去掉第i行、第j列构造新矩阵
{
   MAT C=_row(i);                         // 删除第i行元素                     
   return C._rank(j);                     // 删除第j列元素
}
//********************************************************************
ostream & operator<<(ostream &ou,MAT& A)// 矩阵插入符定义（用于流输出）
 {
     for(int i=0;i<A.row;i++)
	 {
		    ou<<"   ";
		   for(int j=0;j<A.rank;j++)
		    { 
			  if(fabs(A(i,j))>1E-10) 
			    ou<<" "<<A(i,j);                       // 输出一行元素
			  else 
			    ou<<" "<<0;  
		    }
		    ou<<endl;                                          // 换行  
	 }
	ou<<endl;
   return ou;                                      // 返回输出流对象
 }
//********************************************************************
 istream & operator >>(istream &in,MAT &A)               // 矩阵提取符
 {
    for(int i=0;i<A.GetRow();i++)
     for(int j=0;j<A.GetRank();j++)  
	   in>>A(i,j);                                      // 输入矩阵元素
	return in;                                          // 返回输入流
 }
//********************************************************************
inline MAT::MAT()                                 //构造未知阶数的矩阵	
{
       row=rank=0;                                   //行列数均设置为0
       elem=new double;                              //定义为动态变量
	   *elem=0;                                      //该变量赋值为0
}
//********************************************************************
inline MAT::~MAT()                                          //析构函数	
{  
   if(row+rank>0)
   delete [] elem;                             // 释放矩阵元素动态数组
   else delete elem;
}
//********************************************************************
bool MAT::operator ==(MAT &A)                  // 两矩阵是否相等的判断 
{
  if(row!=A.row || rank!=A.rank)	
	 return false;                         // 行列数不相等则矩阵不相等
  for(int i=0;i<row;i++)
    for(int j=0;j<rank;j++)
	  if(fabs(GetElem(i,j)-A(i,j))>1E-12)
			  return false;                // 元素不相等则矩阵不相等
	  return true;                         // 否则，两矩阵相等
}
//********************************************************************
inline int MAT::GetRow()                                //返回矩阵行数   
{
	 return row;                                   // 返回当前矩阵行数
}
//********************************************************************
inline int MAT::GetRank()                               //返回矩阵列数   
{
   return rank;                                    // 返回当前矩阵列数
}
//********************************************************************
inline void MAT::GetRR(int &row,int &rank)         // 返回矩阵行、列数
{
    row=this->row;                                 // 得到当前矩阵行数
	rank=this->rank;                               // 得到当前矩阵列数
} 
//********************************************************************
double MAT::Trace()                                    // 计算矩阵的迹
{
    if( row!=rank ) return UNK;                  // 非方阵不做此项计算
	double S=0;                                  // 定义返回数据
	for(int i=0;i<row;i++)
	S+=GetElem(i,i);                             // 计算对角线元素之和
	return S;
}
//********************************************************************
void MAT::SetRR()                                      // 设置矩阵阶数
{
   delete [] elem;                             // 释放矩阵元素动态数组
   elem = new double[row*rank];                // 新开辟内存空间
   Set0();                                     // 新矩阵元素全部设为零
}  
//********************************************************************
void MAT::SetRow(int h)                                 //设置矩阵行数   
{
	row=h;                                              //行数赋值
	SetRR();                                            //重新分配空间
}
//********************************************************************
void MAT::SetRank(int l)                                //设置矩阵列数 
{
	rank=l;                                             //列数赋值
    SetRR();                                            //重新分配空间
}
//********************************************************************
void MAT::SetRR(int row,int rank)                   //设置矩阵行、列数
{
	this->row=row; 
	this->rank=rank;                                   // 设置行、列数
	SetRR();                                           // 分配内存空间
}
//********************************************************************	
class node{              //结点类（在矩阵逆阵计算函数inverse1()中使用）
     public:  
        int dat1;                                      //定义结点数据1 
		int dat2;                                      //定义结点数据2
        node * prev;                                   //前一结点地址 
		node(int d1,int d2,node *n);
};
// ********node类成员函数定义*****************************************
inline node::node(int d1,int d2,node *n)
{
	dat1=d1;
	dat2=d2;
	prev=n;
}
//********************************************************************	
class stack{               //栈类（在矩阵逆阵计算函数inverse1()中使用）
   public:
	node *top;                                      //定义栈顶结点指针                               
	stack(){top=0;}
	void push(int,int);                                 //定义压入函数
    node* pop();                                        //定义弹出函数
};
// ********stack类成员函数定义****************************************
void stack::push(int t1,int t2)
{
	node * n=new node(t1,t2,top);                      // 定义新节点
	top=n;                                             // 新节点压入栈
}
//********************************************************************
node* stack::pop()
{
	node * t=top;                                    
	if(top)
	{
	  top=top->prev;
	  return t;                                      // 弹出最后的节点
	}
	return 0;                                        // 无节点可以弹出
}
//********************************************************************	
double & MAT::GetElem(int h,int l)                 // 返回矩阵元素的值
{
    if(h>row-1 || h<0 )
	{
	  cout<<" MAT::GetElem(int h, int l)错误: 矩阵行数h超限！"<<endl;
	  exit(1);	
	}
	if(l>rank-1 || l<0 )
	{
	  cout<<" MAT::GetElem(int h, int l)错误: 矩阵列数l超限！"<<endl;
	  exit(1);
	}
	return elem[l+h*rank];  
}
//**********************************************************************	
double & MAT:: operator () (int h,int l)          //返回矩阵对应位置元素 
{
    return GetElem(h,l);                         // 返回h、l对应位置元素
}
//**********************************************************************
void MAT::SetElem(int h,int l,double m)                   //设置矩阵元素
{   
    GetElem(h,l)=m;                              // h、l对应位置元素赋值
}
//**********************************************************************	
void MAT::SetALL()                                //键盘输入矩阵所有元素
{
    cout<<"输入("<<row<<"*"<<rank<<")矩阵元素:"<<endl;
    for(int i=0;i<row*rank;i++)
     cin>>elem[i];                              //从屏幕逐一输入矩阵元素
}
//**********************************************************************	
bool MAT::CheckI()                                  //判断矩阵是否单位阵 
{ 
	if(row!=rank)
		return false;                                      // 非方阵判断            
	for(int i=0;i<row;i++)
     for(int j=0;j<rank;j++)
	 { 
	   if(i==j && fabs(GetElem(i,j)-1)>1E-10) 
		   return false;                               // 非主元非零判断
	   if(i!=j && fabs(GetElem(i,j))>1E-10) 
		   return false;                                  // 主元非1判断
	 } 
   return true;
}
//**********************************************************************	
MAT & MAT::operator = ( MAT &other)                    // 矩阵对矩阵赋值
{	
//1 检查自赋值
		if(this == &other)
			return *this;
//2 释放原有的内存资源
  if(row+rank>0)
    delete [] elem;                              // 释放矩阵元素动态数组
     else
     delete elem;                                      // 释放原内存空间
		row=other.row;
		rank=other.rank;
//3 分配新的内存资源，并复制数据
	elem = new double[row*rank];
		for(int i=0;i<row*rank;i++)
	    	elem[i]=other.elem[i];                      //矩阵元素值复制		
//4 返回当前矩阵
	return *this;
}	
//**********************************************************************	
void MAT::Set1()                                   //设置矩阵所有元素为1
{
	for(int i=0;i<row*rank;i++)
	  elem[i]=1;                                   //所有元素值均设置为1              
}
//**********************************************************************	
void MAT::Set0()                                   //设置矩阵所有元素为0
{
	for(int i=0;i<row*rank;i++)
	  elem[i]=0;
}
//**********************************************************************	
void MAT::SetI()                                      //设置矩阵为单位阵
{
	if(row!=rank)
	{
		cout<<"MAT::SetI()错误：当前矩阵非方阵！"<<endl;
	    exit(1);
	}
	for(int i=0;i<row;i++)
	  for(int j=0;j<rank;j++)
		if(i==j)
			SetElem(i,j,1);                            //对角线元素设为1
		else 
			SetElem(i,j,0);                          //非对角线元素设为0
}
//**********************************************************************	
void MAT::print()                                      // 矩阵的屏幕输出
{
	cout<<endl;                                                  // 换行
		for(int i=0;i<row;i++)
		{
		    cout<<"   ";
		   for(int j=0;j<rank;j++)
		   	{ 
			  if(fabs(GetElem(i,j))>1E-10) 
			    cout<<" "<<GetElem(i,j);                  // 输出一行元素
			  else 
			    cout<<" "<<0;  
		    }
		    cout<<endl;                                          // 换行  
		}
	cout<<endl;
}
//**********************************************************************	
MAT::MAT( MAT &S)                                   //拷贝初始化构造函数
{
     row=S.row;
     rank=S.rank;                                        // 阶数相等赋值
       elem=new double[row*rank];                      // 开辟新内存空间
        for(int i=0;i<row*rank;i++)
	     elem[i]=S.elem[i];                              // 矩阵元素赋值
}		
//**********************************************************************	
MAT::MAT(int hang,int lie)                        //构造确定行列数的矩阵
{
   	row=hang;
   	rank=lie;                                                // 确定阶数
	elem=new double[hang*lie];                       // 定义元素动态数组
    Set0();                                          // 矩阵元素赋值为0
}
//**********************************************************************	
MAT::MAT(int hl)                                             // 定义方阵
{
    elem=new double[hl*hl]; 
  	SetRR(hl,hl);
}
//**********************************************************************	
bool MAT::exrow(int row1,int row2)                  //交换矩阵的两行元素
{   
	if(row1<0 || row1>row)
    { 
	  cout<<"MAT::exrow(int row1,int row2) 错误::给定行row1超限！"<<endl;
	  return false;
	}
    if(row2<0 || row2>row) 
	{
	  cout<<"MAT::exrow(int row1,int row2) 错误::给定行row2超限！"<<endl;
      return false;
	}
	if(row1==row2) 
	  return true;
    for(int i=0;i<rank;i++) 
	{ 
	  double ex=GetElem(row1,i); 
      SetElem(row1,i,GetElem(row2,i));      
      SetElem(row2,i,ex);
   }
  return true;
}
//**********************************************************************	
bool MAT::exrank(int rank1,int rank2)               //交换矩阵的两列元素
{
	if(rank1<0 || rank1>rank)
	{
	  cout<<"MAT::exrank() 错误::列数rank1超限！"<<endl;
	  exit(1);
	}
 	if(rank2<0 || rank2>rank) 
	{
	  cout<<"MAT::exrank() 错误::列数rank2超限！"<<endl;
	  exit(1);
	}
	if(rank1==rank2) 
		return true;
    for(int i=0;i<row;i++) 
   {
	  double ex=GetElem(i,rank1);
      SetElem(i,rank1,GetElem(i,rank2));      
      SetElem(i,rank2,ex);
   }
    return true;
}
//**********************************************************************	
MAT MAT::T()                             //矩阵转置（返回值为转置后矩阵）
{
	MAT C(rank,row);                                 // 构造转置结果矩阵
	 for(int i=0;i<row;i++)
       for(int j=0;j<rank;j++)
	  	 C(j,i)=GetElem(i,j);                        // 设置转置矩阵的值
	   return C;
}
//**********************************************************************	
MAT MAT::operator + (MAT &B)                      //矩阵求和，返回和矩阵
{   
    if(row!=B.GetRow() || rank!=B.GetRank())
	{ 
		cout<<"MAT::矩阵相加计算错误：两矩阵阶数不同!"<<endl;
		return MAT(0,0);
	}
	MAT C(row,rank);                             //定义计算结果矩阵
	for(int i=0;i<row*rank;i++)
	{
		C.elem[i]=this->elem[i]+B.elem[i];       //矩阵对应元素求和
	}
	return C;                                    //返回结果矩阵
}
//**********************************************************************	
MAT MAT::operator - (MAT &B)          // 计算两矩阵的差矩阵（返回差矩阵）
{
	if(row!=B.GetRow() || rank!=B.GetRank())
	{ 
		cout<<"MAT::矩阵相减函数错误：两矩阵阶数不同!"<<endl;
		return MAT(0,0);
	}
	MAT C(row,rank);                              //定义计算结果矩阵
	for(int i=0;i<row*rank;i++)
	{
			C.elem[i]=this->elem[i]-B.elem[i];    //元素求差
	}
	return C;                                     //返回计算结果
}
//**********************************************************************	
MAT MAT::operator * (MAT &B)               // 矩阵相乘计算，返回积矩阵
{ 
   if(this->rank!=B.GetRow()) 
   {
	 cout<<"MAT::矩阵相乘错误:两矩阵阶数不满足相乘条件! "<<endl;
     return MAT(0,0);
   }
	int Crow=this->row;
	int Crank=B.GetRank();
	int Brow=B.GetRow();
	MAT C(Crow,Crank);                                //定义计算结果矩阵
 	C.Set0();
	for(int i=0;i<Crow;i++)
	 for(int j=0;j<Crank;j++)
	  for(int k=0;k<Brow;k++)
	  {
		C(i,j)+=this->GetElem(i,k)*B(k,j);            //计算乘积矩阵元素
	  }                                       	     
	return C;                                             //返回结果矩阵
}
//**********************************************************************	
MAT operator * (double A,MAT &B)           // 数乘矩阵计算，返回结果矩阵
{ 
	int Crow=B.GetRow();
	int Crank=B.GetRank();
	MAT C(Crow,Crank); 
	for(int i=0;i<(Crow*Crank);i++) 
	{
		C.elem[i]=A*B.elem[i];
	}
	return C;
}
//**********************************************************************	
MAT MAT::operator * (double B)              //矩阵乘数计算，返回结果矩阵
{   
	 MAT A(row,rank);
  	 A=B*(*this); 
	 return A;
}
//**********************************************************************	
MAT MAT::operator / (double B)           // 矩阵除以数计算，返回结果矩阵
{   
	if(B==0) 
	{
		cout<<"MAT::矩阵除以数函数数据错误 :除数为0！"<<endl;
	    return MAT(0,0);
	}
 	MAT C(row,rank); 
	 for(int i=0;i<(row*rank);i++) 
	 {
		C.elem[i]=this->elem[i]/B;
	 }
	 return C;
}
//**********************************************************************	
MAT MAT::inverse()                      //行列变换矩阵求逆计算，返回逆阵
{
  if(row!=rank || row==0)                             //判断矩阵是否方阵
   { 
	 cout<<" MAT::inverse() 错误: 求逆矩阵不是方阵！ "<<endl;
	 return MAT(0,0);             // 不可求逆，返回0阵
   }
   if(row>5)                         
    return inverse1();            //如果矩阵较大，采用矩阵直接变换法计算
    MAT C(row,row);             
    C.SetI();	                  //定义单位阵
	MAT A=*this;                  //定义变换矩阵
	double MAXX,b;
	int h,m;
	m=row;
	for(int i=0;i<m;i++)
	{  
		MAXX=0;
		   h=0;
		  if(fabs(A(i,i))<1E-10 && i<m-1)           // 矩阵主元为零的处理
		  {
			  for(int l=i+1;l<m;l++)
			 if(fabs(A(l,i))>MAXX) 
			 { 
				 MAXX=fabs(A(l,i));       
                 h=l;                      // 找到主元对应列最大元素行数
			 }
			 if(h!=i)
			  for(int k1=0;k1<m;k1++)
			  {
                A(i,k1)+=A(h,k1);
			    C(i,k1)+=C(h,k1);
			  }
		  }
	       if(fabs(A(i,i))<1E-16)                    // 主元为零
		   {
		     cout<<" MAT::inverse()错误: 求逆矩阵不满秩 ! "<<endl;
		     return MAT(0,0);                        // 不可求逆，返回0阵
		   }
		b=A(i,i);	                       
		for(int j=0;j<m;j++)                             // 矩阵行变换法求逆
		{
			A(i,j)/=b;
			C(i,j)/=b;
        }
		for(int j=0;j<m;j++)	   
		{  
			b=A(j,i);
			for(int k=0;k<m;k++)
			if(i!=j) 
			{
				A(j,k)-=b*A(i,k);
				C(j,k)-=b*C(i,k);
			}
		}
	} 
    return C; 
}
//**********************************************************************	
MAT MAT::inverse1()                  // 矩阵直接变换法求逆，计算速度较快
{
    MAT C=*this;                                     // 定义求逆结果矩阵
	stack exrow;
	for(int i=0;i<row;i++)
	{ 
	  int h=i;
	  double b=fabs(C(i,i));
		if(i<row-1)
		{
		  for(int j=i;j<row;j++)
		   if(fabs(C(j,i))>b)
		   {
		       h=j;
			   b=fabs(C(j,i));
		   }
		  if(h!=i)
		  {
			  C.exrow(h,i);
			  exrow.push(h,i);
		  }
		}  
    	if(fabs(C(i,i))<1E-16) 
		{
			cout<<"MAT::inverse1()错误: 求逆矩阵不满秩 !  \n";
			return MAT(0,0);          // 不可求逆，返回0阵
		}
		double a=1/C(i,i);
		C(i,i)=a;
	   for(int j=0;j<row;j++)
        if(j!=i)
		{
			C(j,i)=-a*C(j,i);
		}
	   for(int j=0;j<row;j++)
		for(int k=0;k<row;k++)
		 if(i!=k && j!=i)
		 {				
		   C(j,k)=C(j,k)+C(j,i)*C(i,k);			
		 }
  		for(int j=0;j<row;j++)
         if(j!=i)
		 {
			C(i,j)=a*C(i,j);
		 }
	} 
	node * p=exrow.top;
   if(p)
	do 
    {
		p=exrow.pop();
		C.exrank(p->dat1,p->dat2);
	}while(p->prev!=0);
 	return C;
}
//**********************************************************************
int MAT::R()                                  //计算矩阵的秩，返回秩的值          
{    // 方法：将矩阵通过行变换变为对角线形式，然后计算对角线元素非零个数
   MAT C;
  if(row>rank) C=this->T();
   else C=*this;
   int row=C.GetRow();   
   int rank=C.GetRank();
  
   double b,js(0);
   int h,Z(row);
	for(int i=0;i<row;i++)
     {
		h=i;
		b=fabs(C(i,i));

		  if(b<1E-8)                                 //对主元为零的处理
		    for(int l=i+1;l<row;l++)
			 if(fabs(C(l,i))>b)
			 {
		        h=l;
				b=fabs(C(l,i));
             }
			if(h!=i) C.exrow(h,i);
	       	if(fabs(C(i,i))<1E-12) 
			{ 
				Z--;
				continue;
			} 
	        for(int j=i+1;j<row;j++)
			{
			   b=C(j,i)/C(i,i);
	           for(int k=0;k<rank;k++) 
			   {
			     C(j,k)-=b*C(i,k);                         // 矩阵行变换
			   }
			}
	  }
	return Z;	 
}	  
//**********************************************************************	
double MAT::hl()                        //计算矩阵行列式，返回行列式的值  
{      // 方法：将矩阵通过行变换变为对角线形式，然后计算对角线元素的乘积
  if(row!=rank) 
  { 
	  cout<<"行列式计算函数MAT::hl(MAT &A)错误：计算矩阵非方阵！"<<endl;
      return UNK;
  }
  MAT C=(*this);
  double b;
 	for(int i=0;i<row;i++)
      for(int j=i+1;j<row;j++)
      { 
		  if(fabs(C(i,i))<1E-8)               //对主元为零的处理：
		    for(int l=i+1;l<row;l++)          //主元为零时，将本列主元下
			 if(C(l,i)!=0)                    //非零元素对应行加于主元行
			 {
				 for(int k1=0;k1<rank;k1++)
                   C(i,k1)+=C(l,k1);
			        break;
			 }
		   if(fabs(C(i,i))<1E-12)             //处理后主元仍为零
		   {  
			  return 0;						  //则行列式值为零			  
		   }
		    b=C.GetElem(j,i)/C(i,i);          //计算j行对主元的倍数
	        for(int k=0;k<rank;k++) 
			if(i!=j) 
			{
			  C(j,k)-=b*C(i,k);               //列数据非主元位置变为零
			}
	  }
	  b=1.0;
	  for(int i=0;i<row;i++) b*=C(i,i);           //计算对角线元素乘积
      return b;
}
//**********************************************************************
MAT MAT::ChildMAT(int row1,int rank1,int row2,int rank2)    
// 用B(row1,rank1)~rank(row2,rank2)构成新矩阵
{
    if(row1<0 || row1>row)
	{
		cout<<"MAT::ChildMAT() 错误 : 起始行数row1超限！ "<<endl;
	    return MAT(0,0);
	}
    if(row2<0 || row2>row) 
	{
		cout<<"MAT::ChildMAT() 错误 : 终止行数row2超限！ "<<endl;
	    return MAT(0,0);
	}
    if(rank1<0 || rank1>rank) 
	{
		cout<<"MAT::ChildMAT() 错误 : 起始列数rank1超限！ "<<endl;
	    return MAT(0,0);
	}
    if(rank2<0 || rank2>rank) 
	{
		cout<<"MAT::ChildMAT() 错误 : 终止列数rank2超限！ "<<endl;
	    return MAT(0,0);
	}
    if(row1>row2) 
	{
		cout<<"MAT::ChildMAT() 错误 : 起始行数row1>终止行数row2！"<<endl;
		return MAT(0,0);
	}
    if(rank1>rank2) 
	{
		cout<<"MAT::ChildMAT() 错误 : 起始列数rank1>终止列数rank2！"<<endl;
		return MAT(0,0);
	}
	int row;
	row=row2-row1+1;
	int rank;
	rank=rank2-rank1+1;
	MAT C(row,rank);
	for(int i=row1;i<row+row1;i++)
		for(int j=rank1;j<rank+rank1;j++)
			C.SetElem(i-row1,j-rank1,GetElem(i,j));
	return C;
}

//**********************************************************************	
MAT MAT::ChildMAT(int row,int rank)        // 构成(row,rank)元素的子矩阵
{
	MAT B=*this;
    if(row<0 || row>B.GetRow()) 
	{
	  cout<<"MAT::ChildMAT(int row,int rank)错误：行数row超限！"<<endl;
		 return MAT(0,0);
	}
    if(rank<0 || rank>B.GetRank()) 
	{
	 cout<<"MAT::ChildMAT(int row,int rank)错误：列数rank超限！"<<endl;
		 return MAT(0,0);
	}
 	MAT C((B.GetRow()-1),(B.GetRank()-1)); 
	for(int i=0;i<row;i++)
	 for(int j=0;j<rank;j++)
	   C.SetElem(i,j,B(i,j));
	for(int i=row+1;i<B.GetRow();i++)
	 for(int j=rank+1;j<B.GetRank();j++)
	  C.SetElem(i-1,j-1,B(i,j));
    for(int i=0;i<row;i++)
	 for(int j=rank+1;j<B.GetRank();j++)
	  C.SetElem(i,j-1,B(i,j));
	for(int i=row+1;i<B.GetRow();i++)
	 for(int j=0;j<rank;j++)
	  C.SetElem(i-1,j,B(i,j));
	return C;		
}
//**********************************************************************
