from urllib.request import urlopen
from PIL import ImageTk, Image
import cv2
import socket
import sys
import ctypes

 
# function for video streaming
def GetVideoStream(url):
    cap = cv2.VideoCapture(url)
    _, frame = cap.read()
    cv2image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)
    img = Image.fromarray(cv2image)
    imgtk = ImageTk.PhotoImage(image=img)
    return imgtk

def socket_send(msg):
    s = socket.socket() 
    host ='192.168.3.233'
    #host = '192.168.43.86'
    port = 1919
    s.connect((host, port))
    s.send(msg.encode('utf-8'))
    s.close()