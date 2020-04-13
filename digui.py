#动态归划 plt.sca(ax1)选择ax 
import numpy as np
import tkinter as tk
import matplotlib.pyplot as plt
from   matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
import threading

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


def max_value(end_time_now):
    global thing,start_times,end_times,values,min_end_time
    if start_times[num]<min_end_time
        return values[num]
    else:
        return values[num]+max_value[]
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
    
t = threading.Timer(1, interrupt)
t.start()
show()
root.mainloop()
