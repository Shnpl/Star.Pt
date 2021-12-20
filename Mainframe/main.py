from tkinter import *
from tkinter.ttk import *

from socket_mf import *
from command import *
from frame_direct_command import *
from frame_tank import *



def root_timer():
        video_img = GetVideoStream('http://192.168.43.86:8080/?action=stream')
        label_video.imgtk = video_img
        label_video.configure(image=video_img)
        
        root.after(1,root_timer)

if __name__ == "__main__":

    cmd = Command()
    cmd.set_mode(1)

    root = Tk()
    root.geometry("1300x1200")
    root.title("Star.Pt")

    ctypes.windll.shcore.SetProcessDpiAwareness(1)
    #调用api获得当前的缩放因子
    ScaleFactor=ctypes.windll.shcore.GetScaleFactorForDevice(0)
    #设置缩放因子
    root.tk.call('tk', 'scaling', ScaleFactor/75)

    main_notebook = Notebook(root,height = 900,width = 1440)

    label_video = Label(root)
    label_video.pack(anchor = 'nw')
    
    frame_direct_command = InitFrameDirect(root,cmd)
    frame_tank = InitFrameTank(root,cmd)

    main_notebook.add(frame_direct_command,text = "直接指令")
    main_notebook.add(frame_tank,text = "小车测试")
    main_notebook.pack()

    
    frame_tank.after(1,root_timer)
    
    root.mainloop()

