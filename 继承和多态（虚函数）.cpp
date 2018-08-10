/*
类里可以定义虚函数（用关键字virtual修饰），表明子类在重载父类这个函数时，父类指针和子类指针调用函数时的选择

定义父类和子类的对象，从对象中直接调用时，不用考虑virtual，直接调用类自己的该名字函数

子类对象可以调用父类的自己未重载的函数，此时结果与父类直接调用一致

定义父类指针指向父类对象时，指针调用函数是直接调用父类自身的成员函数（没有什么变数）

定义子类指针指向子类对象时，指针调用函数也是直接调用子类自身的成员函数（没有什么变数）

但定义父类指针指向子类对象时，指针如果调用的函数在父类里没有virtual（不是虚函数），那么会调用父类（指针类型）的对应函数

如果在父类里有virtual，那么将调用子类（对象类型）的对应函数

应用方面，基本用于出现某些特殊例子时，这些特殊例子使用子类，一般例子使用父类

举例：

SIF的普通卡池我甩下100张单抽券，期望值是抽到1.00张UR

但特殊的box甩下100张单抽券，由于抽出UR可以重置，因此期望值有点复杂，反正大于1.00张UR

因此box卡池类继承普通卡池时，就要把普通卡池的抽卡概率计算函数设为virtual

这样我用卡池指针指向box卡池的对象时，调用的一定是box卡池的概率

*/
#include<cstdio>
class A
{
public:
	void FuncA()
	{
		printf( "A:FuncA()\n" );
	}
	virtual void FuncB()
	{
		printf( "A:FuncB()\n" );
	}
	void FuncC()
	{
		printf( "A:FuncC()\n" );
	}
};
class B : public A
{
public:
	void FuncA()
	{
		printf("B:FuncA()\n" );
	}
	void FuncB()
	{
		printf("B:FuncB()\n");
	}
	void FuncD()
	{
		printf("B:FuncD()\n");
	}
};
int main()
{
	A a;
	B b;
	A *pa_a=&a;
	A *pa_b=&b;
	//B *pb_a=&a;	//error C2440: 'initializing' : cannot convert from 'class A *' to 'class B *'
	B *pb_b=&b;

	printf("class a | FuncA="); //A:FuncA
	a.FuncA();
	printf("class a | FuncB="); //A:FuncB
	a.FuncB();
	printf("class a | FuncC="); //A:FuncC
	a.FuncC();
	printf("class b | FuncA="); //B:FuncA
	b.FuncA();
	printf("class b | FuncB="); //B:FuncB
	b.FuncB();
	printf("class b | FuncC="); //A:FuncC
	b.FuncC();
	printf("class b | FuncD="); //B:FundD
	b.FuncD();
	printf("pointer A class A | FuncA="); //A:FuncA
	pa_a->FuncA();
	printf("pointer A class A | FuncB="); //A:FuncB
	pa_a->FuncB(); 
	printf("pointer A class B | FuncA="); //A:FuncA
	pa_b->FuncA(); 
	printf("pointer A class B | FuncB="); //B:FuncB
	pa_b->FuncB();
	printf("pointer A class B | FuncC="); //A:FuncC
	pa_b->FuncC();
	//printf("pointer A class B | FuncD=");
	//pa_b->FuncD();		 //error C2039: 'FuncD' : is not a member of 'A'
	printf("pointer B class B | FuncA="); //B:FuncA
	pb_b->FuncA();
	printf("pointer B class B | FuncB="); //B:FuncB
	pb_b->FuncB();
	printf("pointer B class B | FuncC="); //A:FuncC
	pb_b->FuncC();
	printf("pointer B class B | FuncD="); //B:FuncD
	pb_b->FuncD();
	return 0;
}
