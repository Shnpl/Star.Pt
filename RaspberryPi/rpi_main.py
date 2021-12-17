import socket
import sys
import serial

serial_port = '/dev/ttyAMA0'
bps = 115200
ser = serial.Serial(serial_port,bps,timeout = 0.5)
# 创建 socket 对象
server = socket.socket()
# 主机名
host = '192.168.3.170'
# 设置端口号
port = 11451

# 连接服务，指定主机和端口
server.bind((host,port))
server.listen(5)
while 1:
	# 接收小于 1024 字节的数据
	conn,addr = server.accept()
	#print(conn,addr)

	msg_bytes = conn.recv(1024)
	received_msg= msg_bytes.decode('utf-8')
	print(received_msg)
	# ser_send_data = '0'+received_msg+'\r\n'
	# ser.write(ser_send_data.encode('ascii'))
	

	if  received_msg[0] == 'S' and\
		received_msg[1] == 'S' and\
		received_msg[-1]== 'E' and\
		received_msg[-2]== 'E':
		#ser.write(received_msg.encode('ASCII'))

		# 格式
		# SS开头
		# EE结尾
		# SS+1Bit模式+由模式决定的控制代码+EE		
		mode_msg = received_msg[2]
		data_msg = received_msg[3:-2]
		print(mode_msg)
		print(data_msg)
		
		# 直接指令模式0:(单个电机)
		# 格式(跟在模式代码后):
		# 1Bit电机1速度
		# Bit 0 方向 Bit 1~3 速度(Hex)
		if mode_msg == '0':
			Motor_1_speed = data_msg[:4]
			print("Motor1_spd:"+str(Motor_1_speed))

		# 直接指令模式1:(两个电机)
		# 格式(跟在模式代码后):
		# 1Bit电机1速度
		# Bit 0 方向
		# Bit 1~3 电机1速度(Hex)
		# Bit 4~6 电机2速度(Hex)	
		elif mode_msg == '1':
			Motor_1_speed = data_msg[:4]
			Motor_2_speed = data_msg[4:8]
			print("Motor1_spd:"+str(Motor_1_speed))
			print("Motor2_spd:"+str(Motor_2_speed))
		else:
			print("mode error")
	#

	#else:
	#	print('error')
	#	print(repr(received_msg))









# 4B电机2速度
# 4B电机3速度
# 4B电机4速度
# 4B舵机1角度
# 4B舵机2角度
# 16B摄像头指令
# 16B陀螺仪指令
# 32B保留
# 共
