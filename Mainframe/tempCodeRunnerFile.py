s = socket.socket() 
    host ='192.168.3.170'
    port = 11451
    s.connect((host, port))
    s.send(msg.encode('utf-8'))
    s.close()