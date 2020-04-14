#include <iostream>// cin,cout
#include <fstream>//getline(myfile,string)，读入string中
#include <algorithm>//min_element 找数组中最大、最小 distance找对应值的位置
#include <list>
using namespace std;

int main()
{
  int nums[]={1,2,3,4,2,3};
  int num_to_find=3;
  int start=0;
  int end=5;
  start=distance(nums,find(nums+start,nums+end,num_to_find));
  cout<<start<<endl;
}