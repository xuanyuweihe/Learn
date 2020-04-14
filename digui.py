#动态归划 plt.sca(ax1)选择ax
'''*******************************************************************
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
*******************************************************************'''
import os 
import threading
import tkinter as tk

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,
                                               NavigationToolbar2Tk)

root = tk.Tk()
if 1:#数据部分
    start_time=0
    value=1
    end_time=2
    thing=np.zeros([8,3])#start_time value end_time
    thing[0]=[1,5,4]
    thing[1]=[3,1,5]
    thing[2]=[0,8,6]
    thing[3]=[4,4,7]
    thing[4]=[3,6,8]
    thing[5]=[5,3,9]
    thing[6]=[6,2,10]
    thing[7]=[8,4,11]
    start_times = thing[:,start_time]
    values=thing[:,value]
    end_times = thing[:,end_time]
    min_end_time=np.min(end_times)#最小结束时间

buff=np.zeros(2)
def max_value(num):
    global thing,start_times,end_times,values,min_end_time,buff
    if start_times[num]<min_end_time:
        '''有两个选择，一是完成第num个事件，
                     二是不完成第num事件，只完成num事件结束前的事件
                                       特例，第num事件是第一个结束的事件'''
        if end_times[num]==min_end_time:#只剩下num事件
            print(num)
            return np.array(values)[num]
        else:#不完成第num个事件
            tnums=np.where(end_times<end_times[num])#找到在第num个事件结束时已经结束的事件
            ttimes=end_times[tnums]#得到所有符合的列表
            tnfnum=np.where(end_times==np.max(ttimes))#找到最靠近第num个事件结束的前一个事件
            tfnum='cannot'
            print(str(num)+' # '+str(tfnum)+' # '+str(tnfnum))
            values_num=values[num]
            max_value_tnfnum=max_value(tnfnum)
            buff[0]=values_num
            buff[1]=max_value_tnfnum#np.max用法
            print(str(num)+' # '+str(tfnum)+' # '+str(tnfnum))
            tvalue=np.max(buff)
            return tvalue
    else:#有两个选择，一是完成第num个事件和第num个事件开始前的事件，二是不完成第num事件，只完成num事件结束前的事件'''
        #完成第num个事件
        tnums=np.where(end_times<=start_times[num])#找到在第num个事件开始时已经结束的事件
        ttimes=end_times[tnums]#得到所有符合的列表
        tfnum=np.where(end_times==np.max(ttimes))#找到最靠近第num个事件开始的前一个事件
        #不完成第num个事件
        tnums=np.where(end_times<end_times[num])#找到在第num个事件结束时已经结束的事件
        ttimes=end_times[tnums]#得到所有符合的列表
        tnfnum=np.where(end_times==np.max(ttimes))#找到最靠近第num个事件结束的前一个事件
        print(str(num)+' # '+str(tfnum)+' # '+str(tnfnum))
        values_num=values[num]
        max_value_tfnum =max_value(tfnum)
        max_value_tnfnum=max_value(tnfnum)
        print(str(num)+' # '+str(tfnum)+' # '+str(tnfnum))
        buff[0]=values_num+max_value_tfnum
        buff[1]=max_value_tnfnum
        tvalue=np.max(buff)
        return tvalue
def save_data():
    global thing
    if os.path.exists('1.txt') is False:
        open('1.txt','w+').close()
    with open('1.txt','w+') as f:
        data=np.reshape(thing,[thing.size])
        k=0
        while k<len(data):
            f.write(str(int(data[k]))+' ')
            k=k+1
            f.write(str(int(data[k]))+' ')
            k=k+1
            f.write(str(int(data[k])))
            k=k+1
            if k!= len(data):
                f.write('\n')
                
def show():#界面显示
    global thing,root,start_times,end_times,values
    ind = np.arange(len(start_times))    # the x locations for the groups
    width = 0.35       # the width of the bars: can also be len(x) sequence
    f,ax=plt.subplots()
    plt.sca(ax)#修改当前ax
    p1=plt.barh(ind, end_times, width, align='center')
    p2=plt.barh(ind, start_times, width, align='center')
    plt.title('np')
    plt.yticks(ind, ('1','2','3','4','5','6','7','8'))
    plt.xticks(np.arange(0, 11))
    plt.legend((p1[0], p2[0]), ('end_times','start_times'))
    
    canvas = FigureCanvasTkAgg(f, master=root)
    canvas.draw()
    canvas.get_tk_widget().pack()

def interrupt():#多线程
    t = threading.Timer(1, interrupt)
    print(1)
    t.start()
temp=max_value(7)
print(temp)
t = threading.Timer(1, interrupt)
t.start()
show()
root.mainloop()
