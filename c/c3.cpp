//走迷宫
//采用四叉树递归遍历
#include <iostream>
#include <fstream>

using namespace std;
#define NOARRIVE 1000
#define ZHANGAI  1001
#define ROW 10
#define COL 10
int map[ROW][COL][3]={};//x[][]0|1表示前一个点的rc坐标，[][]2表示类型或者记录当前步数
int col=0;
int row=0;
int slw[2]={0,0};//起点坐标
int elw[2]={0,0};//终点坐标
void show(int x,int y){
    int row=0,col=0;
    system("clear");//ubtunu下清屏 windows下为 “clr”
    cout<<" 0123456789"<<endl;
    while (row!=ROW)
    {
        cout<<row;
        while(col!=COL)
        {
            if(row==x&&col==y)cout<<'n';//当前所在位置
            else if(map[row][col][2]==NOARRIVE)cout<<' ';//从未到达
            else if(map[row][col][2]==ZHANGAI)cout<<'#';//路障
            else cout<<'0';
            col++;
        }
        col=0;
        cout<<endl;
        row++;
    }
    cout<<endl;
}
void floodfill(int x,int y,int last_x,int last_y,int step_num)
{
    if(map[x][y][2]==ZHANGAI)return;//已经找到了当前位置最小路径,或者终点的最小路径
    if(map[x][y][2]>step_num){//有更短的路径
        cout<<x<<','<<y<<'#'<<last_x<<','<<last_y<<'#'<<step_num<<endl;
        map[x][y][0]=last_x;
        map[x][y][1]=last_y;
        map[x][y][2]=step_num;
        // //判断是否为最短路径,周围都是最短,后来发现无法判断
        // flag[x][y]=1;//假定现在是最短了
        // if(flag[max(x-1,0)][y]==1\
        // &&flag[min(x+1,ROW)][y]==1\
        // &&flag[x][max(y-1,0)]==1\
        // &&flag[x][min(y+1,9)]==1)
        // {        }//说名确实是最短
        // else{
        //     flag[x][y]=0;//不是最短
        // }
        show(x,y);
        floodfill(min(x+1,ROW),y,x,y,step_num+1);//下走
        show(x,y);
        floodfill(x,min(y+1,COL),x,y,step_num+1);
        show(x,y);
        floodfill(max(x-1,0),y,x,y,step_num+1);//
        show(x,y);
        floodfill(x,max(y-1,0),x,y,step_num+1);
        show(x,y);
    }
    else{
        return;
    }
    
    
}
void get_map()
{
    int temp;
    ifstream f("c3.txt");
    if(!f.is_open()){
        cout<<"error";
    }
    row=0;col=0;
    while (!f.eof())
    {
        temp=f.get();
        while (temp=='\n')
        {
            temp=f.get();
        }
        if(temp=='5')//起点
        {
            slw[0]=row;
            slw[1]=col;
            map[row][col][0]=slw[0];
            map[row][col][1]=slw[1];
            map[row][col][2]=NOARRIVE;//起点只要第一步
            
        }else if(temp=='8')//终点
        {
            elw[0]=row;
            elw[1]=col;
            map[row][col][2]=NOARRIVE;
        }else if(temp=='1')//障碍
        {
            map[row][col][2]=ZHANGAI;
            map[row][col][0]=ZHANGAI;
            map[row][col][1]=ZHANGAI;
        }else if(temp=='0')//路径
        {
            map[row][col][2]=NOARRIVE;
        }
        col++;
        if(col==COL){
            col=0;
            row++;
        }
    }
}
void show_way()
{
    int temp=0;
    row=elw[0];col=elw[1];
    cout<<row<<','<<col<<endl;
    do{
        temp=row;
        row=map[temp][col][0];
        col=map[temp][col][1];
        cout<<row<<','<<col<<endl;
    }while(map[row][col][0]!=slw[0]||map[row][col][1]!=slw[1]);
    cout<<slw[0]<<','<<slw[1]<<endl;
}
int main()
{    
    row=0;col=0;
    get_map();
    floodfill(slw[0],slw[1],slw[0],slw[1],0);
    show_way();
    return 0;
}