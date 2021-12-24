from socket_mf import *

class Command:
    def __init__(self):
        self.__mode = 0 #模式选择
        self.__speed_M1 = 0
        self.__speed_M2 = 0
        self.__speed_M3 = 0
        self.__speed_M4 = 0

        self.__angle_S1 = 0
        self.__angle_S2 = 0
        self.__angle_S3 = 0
        self.__angle_S4 = 0
        self.mainframe_debugging = False

    def set_mode(self,mode):
        self.__mode = mode
        print (self.__mode)
    def set_mainframe_debug_mode(self,mode):
        self.mainframe_debugging = mode
        print("Mainframe Debugging:",self.mainframe_debugging)
    def get_mainframe_debug_mode(self):
        return self.mainframe_debugging

    def set_speed_M1(self, speed):
        self.__speed_M1 = speed
    def set_speed_M2(self,speed):
        self.__speed_M2 = speed
    def set_speed_M3(self,speed):
        self.__speed_M3 = speed
    def set_speed_M4(self,speed):
        self.__speed_M4 = speed
    
    def set_angle_S1(self, angle):
        self.__angle_S1 = angle
    def set_angle_S2(self, angle):
        self.__angle_S2 = angle
    def set_angle_S3(self, angle):
        self.__angle_S3 = angle
    def set_angle_S4(self, angle):
        self.__angle_S4 = angle
    
    def send_cmd(self):
        if self.__mode == 0:
            fmt_M1 = '{:+X}'.format(self.__speed_M1).zfill(4)
            fmt_M2 = '{:+X}'.format(self.__speed_M2).zfill(4)
            fmt_M3 = '{:+X}'.format(self.__speed_M3).zfill(4)
            fmt_M4 = '{:+X}'.format(self.__speed_M4).zfill(4)

            fmt_S1 = '{:+X}'.format(self.__angle_S1).zfill(4)
            fmt_S2 = '{:+X}'.format(self.__angle_S2).zfill(4)
            fmt_S3 = '{:+X}'.format(self.__angle_S3).zfill(4)
            fmt_S4 = '{:+X}'.format(self.__angle_S4).zfill(4)
            send_msg ='SS{:1d}{}{}{}{}{}{}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2,fmt_M3,fmt_M4,fmt_S1,fmt_S2,fmt_S3,fmt_S4)

        if self.__mode == 1:
            fmt_M1 = '{:+X}'.format(self.__speed_M1).zfill(4)
            fmt_M2 = '{:+X}'.format(self.__speed_M2).zfill(4)
            send_msg ='SS{:1d}{}{}EE'.format(self.__mode,fmt_M1,fmt_M2)
        if self.mainframe_debugging == False:
            socket_send(send_msg)
        print(send_msg)

    