from urllib.request import urlopen
from tkinter import *
from PIL import ImageTk, Image
import cv2
import socket
import sys


 
# function for video streaming
def video_stream():
    _, frame = cap.read()
    cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)
    img = Image.fromarray(cv2image)
    imgtk = ImageTk.PhotoImage(image=img)
    label_video.imgtk = imgtk
    label_video.configure(image=imgtk)
    label_video.after(1, video_stream) 

def select_mode(x) :
    global mode
    mode = x

if __name__ == "__main__":
    
    
    mode = 0
    root = Tk()
    root.geometry("1440x900")
    root.title("Star.Pt")
    # Create a label in the frame
    label_video = Label(root)
    label_video.pack(side='top')

    command_entry = Entry(root)
    command_entry.pack(side = 'left')

    mode_select_menu = ['单电机调试模式','双电机调试模式']
    mode_select_var = StringVar()
    mode_select_var.set(mode_select_menu[0])
    mode_select = OptionMenu(root, mode_select_var,*mode_select_menu)
    mode_select.pack(side = 'right')    

    btn_send = Button(root)
    btn_send['text'] = 'send'
    btn_send.pack(side='left')

    def btn_send_event(event):
        s = socket.socket() 
        # 获取本地主机名
        host ='192.168.3.170'
        port = 11451
        s.connect((host, port))
        #print(command_entry.get())

        if mode_select_var.get() == '单电机调试模式' :
            msg = 'SS0'+command_entry.get()+'EE'
        elif mode_select_var.get() == '双电机调试模式':
            msg = 'SS1'+command_entry.get()+'EE'
        s.send(msg.encode('utf-8'))
        s.close()

    btn_send.bind('<ButtonRelease-1>', btn_send_event)
    # Capture from camera
    cap = cv2.VideoCapture('http://192.168.3.170:8080/?action=stream')
    video_stream()

    root.mainloop()
