#动态归划 plt.sca(ax1)选择ax 
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
print(buff)
buff[0]=values[0]
buff[1]=values[1]
print(np.max(buff))