from urllib.request import urlopen
from tkinter import *
from tkinter.ttk import *
from PIL import ImageTk, Image
import cv2
import socket
import sys


 
# function for video streaming
def video_stream():
    cap = cv2.VideoCapture('http://192.168.3.170:8080/?action=stream')
    _, frame = cap.read()
    cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)
    img = Image.fromarray(cv2image)
    imgtk = ImageTk.PhotoImage(image=img)
    label_video.imgtk = imgtk
    label_video.configure(image=imgtk)
    label_video.after(1, video_stream) 

def socket_send(msg):
    s = socket.socket() 
    host ='192.168.3.170'
    port = 11451
    s.connect((host, port))
    s.send(msg.encode('utf-8'))
    s.close()
    pass

class Command:
    def __init__(self):
        self.__mode = 0 #模式选择
        self.__speed_M1 = 0
        self.__speed_M2 = 0

    def set_mode(self,mode):
        self.__mode = mode
        print (self.__mode)

    def toward(self,event):
        self.__speed_M1 = 50
        self.__speed_M2 = 50 
        fmt_M1 = '{:+}'.format(self.__speed_M1).zfill(4)
        fmt_M2 = '{:+}'.format(self.__speed_M2).zfill(4)
        send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        socket_send(send_msg)
        print(send_msg)

    def left(self,event):
        self.__speed_M1 = -50
        self.__speed_M2 = 50
        fmt_M1 = '{:+}'.format(self.__speed_M1).zfill(4)
        fmt_M2 = '{:+}'.format(self.__speed_M2).zfill(4)
        send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        socket_send(send_msg)
        print(send_msg)

    def right(self,event):
        self.__speed_M1 = 50
        self.__speed_M2 = -50 
        fmt_M1 = '{:+}'.format(self.__speed_M1).zfill(4)
        fmt_M2 = '{:+}'.format(self.__speed_M2).zfill(4)
        send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        socket_send(send_msg)
        print(send_msg)

    def back(self,event):
        self.__speed_M1 = -50
        self.__speed_M2 = -50
        fmt_M1 = '{:+}'.format(self.__speed_M1).zfill(4)
        fmt_M2 = '{:+}'.format(self.__speed_M2).zfill(4)
        send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        socket_send(send_msg)
        print(send_msg)
    def stop(self,event):
        self.__speed_M1 = 0
        self.__speed_M2 = 0 
        fmt_M1 = '{:+}'.format(self.__speed_M1).zfill(4)
        fmt_M2 = '{:+}'.format(self.__speed_M2).zfill(4)
        send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        socket_send(send_msg)
        print(send_msg)
       
    def print(self):
        print("mode:",self.__mode)
if __name__ == "__main__":
    
    
    cmd = Command()
    cmd.set_mode(1)

    root = Tk()
    root.geometry("1300x1000")
    root.title("Star.Pt")

    main_notebook = Notebook(root,height = 900,width = 1440)

    label_video = Label(root)
    label_video.pack(anchor = 'nw')
    
    frame_direct_command = Frame(root)

    label_direct_01 = Label(frame_direct_command,text="电机1:")
    label_direct_01.pack(anchor = "nw")
    label_direct_02 = Label(frame_direct_command,text="电机2:")
    label_direct_02.pack(anchor = "nw")
    label_direct_03 = Label(frame_direct_command,text="电机3:")
    label_direct_03.pack(anchor = "nw")
    label_direct_04 = Label(frame_direct_command,text="电机4:")
    label_direct_04.pack(anchor = "nw")
    label_direct_05 = Label(frame_direct_command,text="舵机1:")
    label_direct_05.pack(anchor = "nw")
    label_direct_06 = Label(frame_direct_command,text="舵机2:")
    label_direct_06.pack(anchor = "nw")
    label_direct_07 = Label(frame_direct_command,text="舵机3:")
    label_direct_07.pack(anchor = "nw")
    label_direct_08 = Label(frame_direct_command,text="舵机4:")
    label_direct_08.pack(anchor = "nw")

    button_direct_mode_change = Button(frame_direct_command,text = '切换模式')
    def button_direct_mode_change_event(event):
        global cmd
        cmd.set_mode(0)
    button_direct_mode_change.bind('<ButtonRelease-1>',button_direct_mode_change_event)
    button_direct_mode_change.pack(anchor = "se")

    frame_tank = Frame(root)

    button_tank_mode_change = Button(frame_tank,text = '切换模式')
    def button_tank_mode_change_event(event):
        global cmd
        cmd.set_mode(1)
    button_tank_mode_change.bind('<ButtonRelease-1>',button_tank_mode_change_event)
    button_tank_mode_change.pack(anchor = "se")


    main_notebook.add(frame_direct_command,text = "直接指令")
    main_notebook.add(frame_tank,text = "小车测试")
    main_notebook.pack()

    video_stream()
    root.bind("<w>",cmd.toward)
    root.bind("<a>",cmd.left)
    root.bind("<s>",cmd.back)
    root.bind("<d>",cmd.right)
    root.bind("<r>",cmd.stop)
    root.mainloop()

