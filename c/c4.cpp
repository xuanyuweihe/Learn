//用迪克斯特拉算法完成c3中的迷宫
//思路：将路障变成一个带花费的空格，存在map里面
#include <iostream>
#include <fstream>

using namespace std;
#define START_FALG '5'
#define END_FLAG   '8'
#define ZHANGAI_FLAG '1'
#define WAY_FLAG '0'
#define FIND_SHORTEST_FLAG 1//找到了最短路径相当于将这个变为路障
#define WAY_PAY 1 //空白方格花费
#define ZHANGAI_PAY 1000//经过路障花费
int ROW,COL;//地图大小
// #define ROW_ 10
// #define COL_ 10
int row,col;
int slw[2]={0,0};//起点坐标
int elw[2]={0,0};//终点坐标
int **map;//记录经过这个方格的花费
int **pay;//当前的花费
int **rl;//记录地图中去对应位置的前一个位置的x
int **cl;//记录地图中去对应位置的前一个位置的x
int **fl;//记录到地图对应位置是否已经是最短距离

    // int map[ROW_][COL_];
    // int pay[ROW_][COL_];
    // int rl[ROW_][COL_];
    // int cl[ROW_][COL_];
    // int fl[ROW_][COL_];
void get_ROW_COL(){//获取地图的大小  
    //得到行列数
    ifstream f("c4.txt");
    while (!f.eof())
    {
        if(f.get()=='\n')
            ROW+=1;
        else//不计算'\n'
            COL+=1;
    }
    f.close();
    ROW+=1;//最后一行无'\n'
    COL=COL/ROW;
    cout<<ROW<<','<<COL<<endl;
}
void data_init(){
    get_ROW_COL();
    //内存申请
    map = new int*[ROW];
    pay =new int*[ROW];
    rl = new int*[ROW];
    cl = new int*[ROW];
    fl = new int*[ROW];
    for(row=0;row<ROW;row++)
    {
        map[row]=new int[COL];
        pay[row]=new int[COL];
        rl[row]=new int[COL];
        cl[row]=new int[COL];
        fl[row]=new int[COL];
    }
    //给map赋值
    int temp;
    ifstream f("c4.txt");
    if(!f.is_open()){
        cout<<"error";
    }
    row=0;col=0;
    while (!f.eof())
    {
        temp=f.get();
        if(temp==-1)break;
        while (temp=='\n')
        {
            temp=f.get();
        }

        fl[row][col]=temp-'0';
        if(temp==START_FALG){
            slw[0]=row;slw[1]=col;
            temp=WAY_PAY;

        }
        else if(temp==END_FLAG){
            elw[0]=row;elw[1]=col;
            temp=WAY_PAY;
        }
        else if(temp==WAY_FLAG){
            temp=WAY_PAY;
        }
        else if(temp==ZHANGAI_FLAG){
            temp=ZHANGAI_PAY;
        }
        map[row][col]=temp;
        pay[row][col]=ZHANGAI_PAY;
        rl[row][col]=0;
        cl[row][col]=0;
        col++;
        if(col==COL){
            col=0;
            row++;
        }
    }
    f.close();
}
void min_now_last(int rn,int cn,int rlast,int clast)//
{
    if(fl[rn][cn]==1)return;//已经是最小值了
    if(pay[rlast][clast]+map[rn][cn]<pay[rn][cn]){
        pay[rn][cn]=pay[rlast][clast]+map[rn][cn];
        rl[rn][cn]=rlast;
        cl[rn][cn]=clast;
    }
}
void show_flag(int x,int y){
    int row=0,col=0;
    system("clear");//ubtunu下清屏 windows下为 “clr”
    cout<<" 0123456789"<<endl;
    while (row!=ROW)
    {
        cout<<row;
        while(col!=COL)
        {
            if(x==row&&y==col)
                cout<<'n';
            else
            {
                cout<<fl[row][col];
            }
            col++;
        }
        col=0;
        cout<<endl;
        row++;
    }
    cout<<endl;
}
void show_way(){    
    int temp=0;
    row=elw[0];col=elw[1];
    cout<<row<<','<<col<<endl;
    do{
        temp=row;
        row=rl[temp][col];
        col=cl[temp][col];
        cout<<row<<','<<col<<endl;
    }while(rl[row][col]!=slw[0]||cl[row][col]!=slw[1]);
    cout<<slw[0]<<','<<slw[1]<<endl;
}
void show_map(){
    int temp=0;
    row=elw[0];col=elw[1];
    map[row][col]=8;
    do{
        temp=row;
        row=rl[temp][col];
        col=cl[temp][col];
    map[row][col]=8;
    }while(rl[row][col]!=slw[0]||cl[row][col]!=slw[1]);
    map[row][col]=8;
    row=0,col=0;
    system("clear");//ubtunu下清屏 windows下为 “clr”
    cout<<" 0123456789abcdefghijk"<<endl;
    while (row!=ROW)
    {
        cout<<char('0'+row);
        while(col!=COL)
        {
            if(map[row][col]==8)cout<<'+';
            if(map[row][col]==ZHANGAI_PAY)cout<<'#';
            if(map[row][col]==WAY_PAY)cout<<' ';
            col++;
        }
        col=0;
        cout<<endl;
        row++;
    }
    cout<<endl;
}
void dkstl(){
    int rn=slw[0],cn=slw[1];
    int r_min,r_max,c_min,c_max;//激活周围9点用
    int temp,noflag_minpay;//寻找下一个最小值位置用
    pay[rn][cn]=0;//起点花费为0；
    fl[rn][cn]=0;
    fl[elw[0]][elw[1]]=0;
    while(fl[elw[0]][elw[1]]!=FIND_SHORTEST_FLAG)//未找到最短一直循环
    {
        r_min=min(rn+1,ROW-1);
        r_max=max(rn-1,0);
        c_min=min(cn+1,COL-1);
        c_max=max(cn-1,0);
        min_now_last(r_min,cn,rn,cn);
        min_now_last(rn,c_min,rn,cn);
        min_now_last(rn,c_max,rn,cn);
        min_now_last(r_max,cn,rn,cn);
        min_now_last(r_min,c_min,rn,cn);//计算周围8个点的情况
        min_now_last(r_min,c_max,rn,cn);
        min_now_last(r_max,c_min,rn,cn);
        min_now_last(r_max,c_max,rn,cn);
        noflag_minpay=ZHANGAI_PAY;
        for(row=0;row<ROW;row++){
            for(col=0;col<COL;col++){
                temp=fl[row][col]*ZHANGAI_PAY+pay[row][col];
                if(noflag_minpay>temp)
                {
                    rn=row;
                    cn=col;
                    noflag_minpay=temp;//找到下一个最小值
                }
            }
        }
        fl[rn][cn]=1;
        show_flag(rn,cn);
    }

}
int main(){
    data_init();
    dkstl();
    show_way();
    show_map();
    return 0;
}
