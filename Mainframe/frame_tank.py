from tkinter import *
from tkinter.ttk import *

from socket_mf import *
from command import *
def toward(command):
        command.set_speed_M1(50)
        command.set_speed_M2(50)
        command.send_cmd()
    
def left(command):
    command.set_speed_M1(-50)
    command.set_speed_M2(50)
    command.send_cmd()

def right(command):
    command.set_speed_M1(50)
    command.set_speed_M2(-50)
    command.send_cmd()

def back(command):
    command.set_speed_M1(-50)
    command.set_speed_M2(-50)
    command.send_cmd()

def stop(command):
    command.set_speed_M1(0)
    command.set_speed_M2(0)
    command.send_cmd()

def InitFrameTank(master,command):
    frame_tank = Frame(master)

    button_tank_mode_change = Button(frame_tank,text = '切换模式')
    button_tank_mode_change.bind('<ButtonRelease-1>',lambda event: (command.set_mode(1),frame_tank.focus_set()))
    button_tank_mode_change.place(x = 1100,y =0)

    frame_tank.bind("<w>",lambda event:toward(command))
    frame_tank.bind("<a>",lambda event:left(command))
    frame_tank.bind("<s>",lambda event:back(command))
    frame_tank.bind("<d>",lambda event:right(command))
    frame_tank.bind("<r>",lambda event:stop(command))

    frame_tank.pack()
    
    return frame_tank