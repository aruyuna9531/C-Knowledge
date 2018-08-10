/*
类中的常成员变量的初始化必须在初始化列表中进行，不能在函数体里。非常成员变量可以在函数体内
不能以任何方式修改常成员变量
不能在常成员函数内修改任何成员变量（包括非常成员变量）

输出结果：
14
*/
#include<iostream>
using namespace std;
class R{
 public:
 R(int r1,int r2):R1(r1){
 //R1=r1;               //error C2758: 'R1' : must be initialized in constructor base/member initializer list
 R2=r2;
 }
 void print();
 void a() const{
	//R2=3;           //error C2166: l-value specifies const object
 }
 private:
 const int R1;
 int R2;
};
void R::print(){
 //R1=3;          //error C2166: l-value specifies const object
 cout<<R1+R2<<endl;
}
 
 
int main(){
 R a(6,8);
 a.print();
 return 0;
}
