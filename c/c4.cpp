//用迪克斯特拉算法完成c3中的迷宫
#include <iostream>
#include <fstream>

using namespace std;

int ROW;
int COL;
int row,col;
int **map;//指向地图中位置的类型，障碍，空白
int **xl;//指向地图中去对应位置的前一个位置的x
int **yl;//指向地图中去对应位置的前一个位置的x
int **fl;//记录到地图对应位置是否已经是最短距离
void get_ROW_COL()//获取地图的大小
{   
    //得到行列数
    ifstream f("c4.txt");
    while (!f.eof())
    {
        if(f.get()=='\n')
            ROW+=1;
        else//不计算'\n'
            COL+=1;
    }
    f.close()
    ROW+=1;//最后一行无'\n'
    COL=COL/ROW;
    cout<<ROW<<','<<COL<<endl;
    //内存申请
    map = new int*[ROW];
    xl = new int*[ROW];
    yl = new int*[ROW];
    fl = new int*[ROW];
    for(row=0;row<ROW;row++)
    {
        map[row]=new int[COL];
        xl[row]=new int[COL];
        yl[row]=new int[COL];
        fl[row]=new int[COL];
    }
    for
    
}
void dkstl()
{

}
int main()
{
    get_ROW_COL();

    return 0;
}