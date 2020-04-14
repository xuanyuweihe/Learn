/*******************************************************************
 * 问题描述：有8件事可以选择完成，求获得的最大价值
 *  01234567890a   价值  m--n表示开始事件点为m，结束时间点为n
 * 0 1--4			5
 * 1   3-5			1
 * 20-----6			8
 * 3    4--7		4
 * 4   3-----8		6
 * 5     5----9		3
 * 6      6----10	2
 * 7        8---11	4
*******************************************************************/
#include <iostream>// cin,cout
#include <fstream>//getline(myfile,string)，读入string中
#include <algorithm>//min_element 找数组中最大、最小 distance找对应值的位置

using namespace std;

#define THING_NUM 8
#define THING_SIZE 3

int start_times[THING_NUM];
int values[THING_NUM];
int end_times[THING_NUM];
int time_first_end=0;
int pos;
int sort_start_times[THING_NUM];
int sort_end_times[THING_NUM];
int max_value(int num)
{
	int te,tv,ts;//在找上一个位置时用
	int tpf,tpn;//tpf：完成num的情况下的上一个位置,tpn:不完成num的情况下上一个位置
	int tvf,tvn;//tvf：完成num的value,tvn:不完成num的alue
	if(num==pos){//只能做num事件
		tvf=values[num];
		tvn=0;
		cout<<num<<endl;
	} 
	else if(start_times[num]<time_first_end)
	{//做num事件&不做num事件
		tvf=values[num];
	//不做num
		tv=distance(sort_end_times,find(sort_end_times,sort_end_times+THING_NUM,end_times[num]));//返回在sort中的位置
		te=sort_end_times[tv-1];//在num end前最迟end的那个事件的end时间
		tpn=distance(end_times,find(end_times,end_times+THING_NUM,te));//num end前面的那个事件位置
		cout<<num<<" # "<<"x"<<" # "<<tpn<<endl;
		tvn=max_value(tpn);
		cout<<" # "<<num<<" # "<<"x"<<" # "<<tpn<<endl;
	}
	else{
	//做num事件
		tv=distance(sort_end_times,find(sort_end_times,sort_end_times+THING_NUM,start_times[num]));//num start前面的那个事件位置,返回在sort中的位置
		tpf=start_times[num];//暂存这个量，因为start_times[num]在end_times可能不存在
		while(tv==THING_NUM){
			tpf=tpf-1;
			tv=distance(sort_end_times,find(sort_end_times,sort_end_times+THING_NUM,tpf));
		}
		te=sort_end_times[tv];
		tpf=distance(end_times,find(end_times,end_times+THING_NUM,te));//num end前面的那个事件位置
	//不做num
		tv=distance(sort_end_times,find(sort_end_times,sort_end_times+THING_NUM,end_times[num]));//返回在sort中的位置
		te=sort_end_times[tv-1];//在num end前最迟end的那个事件的end时间
		tpn=distance(end_times,find(end_times,end_times+THING_NUM,te));//num end前面的那个事件位置
		cout<<num<<" # "<<tpf<<" # "<<tpn<<endl;
		tvf=max_value(tpf)+values[num];
		cout<<" # "<<num<<" # "<<tpf<<" # "<<tpn<<endl;
		tvn=max_value(tpn);
		cout<<" # "<<num<<" # "<<tpf<<" # "<<tpn<<endl;
	}
	return tvf>tvn?tvf:tvn;
}
int main()
{
	int cnt=0;//计数
	ifstream infile; //c++文件流 >>是一次读取一行
	infile.open("1.txt",ios::in);
	if(!infile.is_open())
		cout << "Open file failure" << endl;
	cnt=0;
	while (!infile.eof())            // 若未到文件结束一直循环
	{
		infile >> start_times[cnt] >>values[cnt] >>end_times[cnt];
		sort_start_times[cnt]=start_times[cnt];
		sort_end_times[cnt]=end_times[cnt];
		cnt++;
	}
	infile.close();   //关闭文件
	time_first_end=(*min_element(end_times,end_times+THING_NUM));
	pos=distance(end_times,min_element(end_times,end_times+THING_NUM));
	sort(sort_start_times,sort_start_times+THING_NUM);
	sort(sort_end_times,sort_end_times+THING_NUM);
	cout<<sort_end_times[7]<<endl;
	cout<<"开始"<<endl;
	cout<<max_value(7)<<endl;
	return 0;
}
