/*
类中可以重载一个常成员函数（如下面的print），参数和返回值和非常成员函数一样，函数定义的后面带关键字const
调用时，如果该对象是非常对象，那么调用非常成员函数，无视常成员函数
如果对象是常对象，那么调用常成员函数
函数定义只有常成员函数（下面的pp），没有非常时，常对象和非常对象调用该名称时都会调用这个常函数
而函数定义只有非常时（下面的p2），没有常函数，那么常对象是不能调用这个函数的，否则报错

运行结果：
14（6+8）
48（6*8）
28（(6+8)*2）
-32（56-88）
4928（56*88）

*/
#include<iostream>
using namespace std;
class R{
 public:
 R(int r1,int r2){
 R1=r1;
 R2=r2;
 }
 void print();
 void print() const;
 void pp() const;
 void p2();
 private:
 int R1,R2;
};
void R::print(){
 cout<<R1+R2<<endl;
}
void R::print() const{
 cout<<R1-R2<<endl;
}
void R::pp() const{
 cout<<R1*R2<<endl;
}
void R::p2(){
 cout<<(R1+R2)*2<<endl;
}
 
 
int main(){
 R a(6,8);
 const R b(56,88);
 a.print();
 a.pp();
 a.p2();
 b.print();
 b.pp();
 //b.p2();    //该行报错
 return 0;
}
