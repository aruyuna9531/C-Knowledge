/*
  关于C++标准库函数std::sort
  http://www.cplusplus.com/reference/algorithm/sort/

  对一个数组（随机迭代器）进行排序，可自己自定义规则，默认规则是从小到大。
  定义在头文件algorithm里。

  函数原型：
  （默认）
  template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);

  （扩展）
  template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

  first为排序的第一个内存地址块，last为最后一个地址块的之后一个位置（不包括last自己）
  comp是比较函数，可以自定义比较规则，此时可以对一个自定义的类定义排序规则，从而对类排序。
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<vector>
using namespace std;

class A{
public:
	int a;
	int b;
	int c;
	A(int aa=0, int bb=0, int cc=0){
		a=aa;
		b=bb;
		c=cc;
	}
	void print(){
		printf("a=%d,b=%d,c=%d\n",a,b,c);
	}
};

bool compare(A a, A b){
	//按每个类的a的10倍，b的5倍，c的2倍之和从大到小排序
	return a.a*10+a.b*5+a.c*2>b.a*10+b.b*5+b.c*2;
}

bool compare_string(string a, string b){
	//字符串字典序升序排列
	return strcmp(a.c_str(), b.c_str())<0;
}

int main(){
	int i;
	//1.整数数组排序
	int cp_int[100]={0};
	srand(time(NULL));
	for(i=0;i<100;i++)cp_int[i]=rand();
	for(i=0;i<100;i++)cout<<cp_int[i]<<",";
	cout<<endl;
	sort(cp_int, cp_int+100);		//100个数字全部排序，从小到大
	for(i=0;i<100;i++)cout<<cp_int[i]<<",";
	cout<<endl;

	//2.字符串排序（vector容器排序）
	vector<string> s;
	string s1("ajsdfoija");
	s.push_back(s1);
	string s2("babccslai");
	s.push_back(s2);
	string s3("ajsdaiwiwsa");
	s.push_back(s3);
	string s4("aiaiiwoakfffas");
	s.push_back(s4);
	string s5("aiblaiworiu");
	s.push_back(s5);
	for(i=0;i<s.size();i++)cout<<s[i].c_str()<<",";
	cout<<endl;
	sort(s.begin(), s.end(), compare_string);		//vector排序用begin和end，如果对部分排序用begin+i和begin+j（i和j是比较部分下标）
	//结果应为原s4,s5,s3,s1,s2
	for(i=0;i<s.size();i++)cout<<s[i].c_str()<<",";
	cout<<endl;

	//3.类的排序
	A a;		//0
	A b(2,3,4);	//2*10+3*5+4*2=43
	A c(3,1,3);	//3*10+1*5+3*2=41
	A d(4,2,5);	//4*10+2*5+5*2=60
	vector<A> x;
	x.push_back(a);
	x.push_back(b);
	x.push_back(c);
	x.push_back(d);
	for(i=0;i<x.size();i++)x[i].print();
	sort(x.begin(), x.end());
	for(i=0;i<x.size();i++)x[i].print();
	//结果：425,234,313,000

	return 0;
}
