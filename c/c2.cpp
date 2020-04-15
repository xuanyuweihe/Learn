//floodfill算法
#include <fstream>
#include <iostream>

using namespace std;
char buff[10][10]={' '};
int col=0;
int row=0;
int xy[2]={6,3};//起点坐标
void show(){
    int row=0,col=0;
    system("clear");//ubtunu下清屏 windows下为 “clr”
    while (row!=10)
    {
        cout<<row;
        while(col!=10)
        {
            cout<<buff[row][col];
            col++;
        }
        col=0;
        cout<<endl;
        row++;
    }
    cout<<endl;
}
void floodfill(int x,int y)
{
    if(buff[x][y]!='X'&&buff[x][y]!='#')
    {   
        cout<<x<<','<<y<<','<<'X'<<endl;
        show();
        buff[x][y]='X';
        floodfill(max(x-1,0),y);
        floodfill(min(x+1,9),y);
        floodfill(x,max(y-1,0));
        floodfill(x,min(y+1,9));
    }
    else if (buff[x][y]=='X')//已经淹没
    {
        cout<<x<<','<<y<<','<<'X'<<endl;
        show();
    }
    else //墙壁
    {   
        cout<<x<<','<<y<<','<<'#'<<endl;
        show();
    }
    
}
int main(){
    cout<<"x0123456789:"<<endl;
    row=0;col=0;
    while (row!=10)
    {     
        while(col!=10)
        {
            buff[row][col]=' ';
            col++;
        }
        col=0;
        row++;
    }
    buff[0][3]='#';
    buff[1][4]='#';
    buff[2][5]='#';
    buff[3][6]='#';
    buff[2][7]='#';
    buff[1][8]='#';
    buff[0][9]='#';
    show();
    floodfill(xy[0],xy[1]);
    return 1;
}