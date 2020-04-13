import tkinter
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

root = tkinter.Tk()  # 创建tkinter的主窗口
root.title("在tkinter中使用matplotlib")

f = Figure(figsize=(5, 4), dpi=100)
a = f.add_subplot(111)  # 添加子图:1行1列第1个

# 生成用于绘sin图的数据
x = np.arange(0, 3, 0.01)
y = np.sin(2 * np.pi * x)

# 在前面得到的子图上绘图
a.plot(x, y)

# 将绘制的图形显示到tkinter:创建属于root的canvas画布,并将图f置于画布上
canvas = FigureCanvasTkAgg(f, master=root)
canvas.draw()  # 注意show方法已经过时了,这里改用draw
canvas.get_tk_widget().pack(side=tkinter.TOP,  # 上对齐
                            fill=tkinter.BOTH,  # 填充方式
                            expand=tkinter.YES)  # 随窗口大小调整而调整

# matplotlib的导航工具栏显示上来(默认是不会显示它的)

# 主循环
root.mainloop()