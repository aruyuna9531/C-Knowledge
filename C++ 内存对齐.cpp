#include<cstdio>
#include<iostream>
using namespace std;

const int strL=9;
const int strL_2=11;

#pragma pack(1)
class A{
	char a;	//8:8>[1] 0x00~0x07
	short b;		//4:4>[1] 0x08~0x0B
	int c;	//2:2>[1] 0x0C~0x0D
	char d;		//1:1=1 0x0E~0x0E
	short e[strL];	//3:3>[1] 0x0F~0x11
	int f[strL_2];	//3:3>[1] 0x0F~0x11
public:
	void print(){
		printf("a(size=1)内存偏移=%d-%d\n",int(&a)-int(&a),int(&a)-int(&a)+sizeof(a)-1);
		printf("b(size=2)内存偏移=%d-%d\n",int(&b)-int(&a),int(&b)-int(&a)+sizeof(b)-1);
		printf("c(size=4)内存偏移=%d-%d\n",int(&c)-int(&a),int(&c)-int(&a)+sizeof(c)-1);
		printf("d(size=1)内存偏移=%d-%d\n",int(&d)-int(&a),int(&d)-int(&a)+sizeof(d)-1);
		printf("e(size=%d×2)内存偏移=%d-%d\n",strL,int(&e)-int(&a),int(&e)-int(&a)+sizeof(e)-1);
		printf("f(size=%d×4)内存偏移=%d-%d\n",strL_2,int(&f)-int(&a),int(&f)-int(&a)+sizeof(f)-1);
	}
};//0x00~0x11(18 bytes)
#pragma pack()
#pragma pack(2)
class B{
	char a;	//8:8>[2] 0x00~0x07
	short b;		//4:4>[2] 0x08~0x0B
	int c;	//2:2=2 0x0C~0x0D
	char d;		//1:[1]<2 0x0E~0x0E
	short e[strL];	//3:3>[2] 0x0F~0x11
	int f[strL_2];	//3:3>[1] 0x0F~0x11
public:
	void print(){
		printf("a(size=1)内存偏移=%d-%d\n",int(&a)-int(&a),int(&a)-int(&a)+sizeof(a)-1);
		printf("b(size=2)内存偏移=%d-%d\n",int(&b)-int(&a),int(&b)-int(&a)+sizeof(b)-1);
		printf("c(size=4)内存偏移=%d-%d\n",int(&c)-int(&a),int(&c)-int(&a)+sizeof(c)-1);
		printf("d(size=1)内存偏移=%d-%d\n",int(&d)-int(&a),int(&d)-int(&a)+sizeof(d)-1);
		printf("e(size=%d×2)内存偏移=%d-%d\n",strL,int(&e)-int(&a),int(&e)-int(&a)+sizeof(e)-1);
		printf("f(size=%d×4)内存偏移=%d-%d\n",strL_2,int(&f)-int(&a),int(&f)-int(&a)+sizeof(f)-1);
	}
};//0x00~0x11(18 bytes)
#pragma pack()
#pragma pack(4)
class C{
	char a;	//8:8>[4] 0x00~0x07
	short b;		//4:4=4 0x08~0x0B
	int c;	//2:[2]<4 0x0C~0x0D
	char d;		//1:[1]<4 0x0E~0x0E
	short e[strL];	//3:[3]<4 0x10~0x12
	int f[strL_2];	//3:3>[1] 0x0F~0x11
public:
	void print(){
		printf("a(size=1)内存偏移=%d-%d\n",int(&a)-int(&a),int(&a)-int(&a)+sizeof(a)-1);
		printf("b(size=2)内存偏移=%d-%d\n",int(&b)-int(&a),int(&b)-int(&a)+sizeof(b)-1);
		printf("c(size=4)内存偏移=%d-%d\n",int(&c)-int(&a),int(&c)-int(&a)+sizeof(c)-1);
		printf("d(size=1)内存偏移=%d-%d\n",int(&d)-int(&a),int(&d)-int(&a)+sizeof(d)-1);
		printf("e(size=%d×2)内存偏移=%d-%d\n",strL,int(&e)-int(&a),int(&e)-int(&a)+sizeof(e)-1);
		printf("f(size=%d×4)内存偏移=%d-%d\n",strL_2,int(&f)-int(&a),int(&f)-int(&a)+sizeof(f)-1);
	}
};//0x10~0x13(20 bytes)
#pragma pack()
#pragma pack(8)
class D{
	char a;	//8
	short b;		//4
	int c;	//2
	char d;		//1
	short e[strL];	//3
	int f[strL_2];	//3:3>[1] 0x0F~0x11
public:
	void print(){
		printf("a(size=1)内存偏移=%d-%d\n",int(&a)-int(&a),int(&a)-int(&a)+sizeof(a)-1);
		printf("b(size=2)内存偏移=%d-%d\n",int(&b)-int(&a),int(&b)-int(&a)+sizeof(b)-1);
		printf("c(size=4)内存偏移=%d-%d\n",int(&c)-int(&a),int(&c)-int(&a)+sizeof(c)-1);
		printf("d(size=1)内存偏移=%d-%d\n",int(&d)-int(&a),int(&d)-int(&a)+sizeof(d)-1);
		printf("e(size=%d×2)内存偏移=%d-%d\n",strL,int(&e)-int(&a),int(&e)-int(&a)+sizeof(e)-1);
		printf("f(size=%d×4)内存偏移=%d-%d\n",strL_2,int(&f)-int(&a),int(&f)-int(&a)+sizeof(f)-1);
	}
};
#pragma pack()
#pragma pack(16)
class E{
	char a;	//8
	short b;		//4
	int c;	//2
	char d;		//1
	short e[strL];	//3
	int f[strL_2];	//3:3>[1] 0x0F~0x11
public:
	void print(){
		printf("a(size=1)内存偏移=%d-%d\n",int(&a)-int(&a),int(&a)-int(&a)+sizeof(a)-1);
		printf("b(size=2)内存偏移=%d-%d\n",int(&b)-int(&a),int(&b)-int(&a)+sizeof(b)-1);
		printf("c(size=4)内存偏移=%d-%d\n",int(&c)-int(&a),int(&c)-int(&a)+sizeof(c)-1);
		printf("d(size=1)内存偏移=%d-%d\n",int(&d)-int(&a),int(&d)-int(&a)+sizeof(d)-1);
		printf("e(size=%d×2)内存偏移=%d-%d\n",strL,int(&e)-int(&a),int(&e)-int(&a)+sizeof(e)-1);
		printf("f(size=%d×4)内存偏移=%d-%d\n",strL_2,int(&f)-int(&a),int(&f)-int(&a)+sizeof(f)-1);
	}
};
#pragma pack()

int main(){
	A a;
	B b;
	C c;
	D d;
	E e;
	printf("A size=%d,对齐标准=1\n",sizeof(a));	//26
	a.print();
	printf("B size=%d,对齐标准=2\n",sizeof(b));	//28
	b.print();
	printf("C size=%d,对齐标准=4\n",sizeof(c));	//32
	c.print();
	printf("D size=%d,对齐标准=8\n",sizeof(d));	//32
	d.print();
	printf("E size=%d,对齐标准=16\n",sizeof(e));	//32
	e.print();
	return 0;
}
