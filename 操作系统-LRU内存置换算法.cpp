#include<vector>
#include<iostream>
using namespace std;

int existPage(const vector<int> &pages, int _p){
	for(int i=0;i<pages.size();i++)if(pages[i]==_p)return i;
	return -1;
}

int main(){
	vector<int> pages;
	int p_size;
	cin>>p_size;
	int p;
	int pageFault=0;
	while(cin>>p){
		if(p<0)break;
		int index=existPage(pages, p);
		if(index!=-1){
			cout<<"page "<<p<<" exists. index="<<index<<endl;
			pages.erase(pages.begin()+index);
			pages.push_back(p);
		}
		else if(pages.size()<p_size){
			pages.push_back(p);
			pageFault++;
			cout<<"page "<<p<<" pushed, page fault called."<<endl;
		}
		else{
			cout<<"page "<<pages[0]<<" out, page "<<p<<" in, page fault called."<<endl;
			pages.erase(pages.begin());
			pages.push_back(p);
			pageFault++;
		}
		cout<<"Now memory:";
		for(int i=0;i<pages.size();i++)cout<<pages[i]<<" ";
		cout<<endl;
	}
	return 0;
}
