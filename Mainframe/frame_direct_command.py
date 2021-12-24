from tkinter import *
from tkinter.ttk import *    
import re

from socket_mf import *
from command import *

def direct_send(command,M1_spd,M2_spd,M3_spd,M4_spd,S1_angle,S2_angle,S3_angle,S4_angle):
    command.set_mode(0)
    pattern = re.compile(r'(\-)?[0-9]{1,3}$')
    if  re.match(pattern, M1_spd) and\
        re.match(pattern, M2_spd) and\
        re.match(pattern, M3_spd) and\
        re.match(pattern, M4_spd) and\
        re.match(pattern, S1_angle) and\
        re.match(pattern, S2_angle) and\
        re.match(pattern, S3_angle) and\
        re.match(pattern, S4_angle) :
        
        command.set_speed_M1(int(M1_spd))
        command.set_speed_M2(int(M2_spd))
        command.set_speed_M3(int(M3_spd))
        command.set_speed_M4(int(M4_spd))
        command.set_angle_S1(int(S1_angle))
        command.set_angle_S2(int(S2_angle))
        command.set_angle_S3(int(S3_angle))
        command.set_angle_S4(int(S4_angle))
        command.send_cmd()
    else:
        print('Input Error')



def InitFrameDirect(master,command):
    frame_direct_command = Frame(master)

    label_M1_0 = Label(frame_direct_command,text="电机1:")
    label_M1_0.place(x = 0,y =0)
    label_M2_0 = Label(frame_direct_command,text="电机2:")
    label_M2_0.place(x = 0,y =30)
    label_M3_0 = Label(frame_direct_command,text="电机3:")
    label_M3_0.place(x = 0,y =60)
    label_M4_0 = Label(frame_direct_command,text="电机4:")
    label_M4_0.place(x = 0,y =90)

    label_S1_0 = Label(frame_direct_command,text="舵机1:")
    label_S1_0.place(x = 0,y =120)
    label_S2_0 = Label(frame_direct_command,text="舵机2:")
    label_S2_0.place(x = 0,y =150)
    label_S3_0 = Label(frame_direct_command,text="舵机3:")
    label_S3_0.place(x = 0,y =180)
    label_S4_0 = Label(frame_direct_command,text="舵机4:")
    label_S4_0.place(x = 0,y =210)

    M1_spd = StringVar()
    M1_spd.set('0')
    entry_M1_0 = Entry(frame_direct_command,textvariable = M1_spd,width = 5)
    entry_M1_0.place(x =75,y = 0)

    M2_spd = StringVar()
    M2_spd.set('0')
    entry_M2_0 = Entry(frame_direct_command,textvariable = M2_spd,width = 5)
    entry_M2_0.place(x =75,y = 30)

    M3_spd = StringVar()
    M3_spd.set('0')
    entry_M3_0 = Entry(frame_direct_command,textvariable = M3_spd,width = 5)
    entry_M3_0.place(x =75,y = 60)

    M4_spd = StringVar()
    M4_spd.set('0')
    entry_M4_0 = Entry(frame_direct_command,textvariable = M4_spd,width = 5)
    entry_M4_0.place(x =75,y = 90)

    S1_angle = StringVar()
    S1_angle.set('0')
    entry_S1_0 = Entry(frame_direct_command,textvariable = S1_angle,width = 5)
    entry_S1_0.place(x =75,y = 120)

    S2_angle = StringVar()
    S2_angle.set('0')
    entry_S2_0 = Entry(frame_direct_command,textvariable = S2_angle,width = 5)
    entry_S2_0.place(x =75,y = 150)

    S3_angle = StringVar()
    S3_angle.set('0')
    entry_S3_0 = Entry(frame_direct_command,textvariable = S3_angle,width = 5)
    entry_S3_0.place(x =75,y = 180)

    S4_angle = StringVar()
    S4_angle.set('0')
    entry_S4_0 = Entry(frame_direct_command,textvariable = S4_angle,width = 5)
    entry_S4_0.place(x =75,y = 210)

    
    button_direct_mode_change = Button(frame_direct_command,text = '发送指令')        
    button_direct_mode_change.bind('<ButtonRelease-1>',lambda event: direct_send(command,str(M1_spd.get()),str(M2_spd.get()),str(M3_spd.get()),str(M4_spd.get()),str(S1_angle.get()),str(S2_angle.get()),str(S3_angle.get()),str(S4_angle.get())))
    button_direct_mode_change.place(x = 1100,y =0)

    

    frame_direct_command.pack()
    return frame_direct_command
