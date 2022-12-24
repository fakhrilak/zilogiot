import socketio
import socket
import os
class SOCKET_IO():
    sio = socketio.Client()
    def __init__(self):
        self.message = ""
        self.sensor = ""
        self.datasensor = ""
        self.state = False
        pass
    def setup(self):
        self.call_backs()
        try:
            self.sio.connect("http://192.168.100.39:4009",namespaces=['/'])
        except BaseException as err:
            print(str(err),"============= SOCKET")
    def SocketOnCheck(self):
        self.sio.emit("connection",{"message":"Connected"})
    
    def SendCommand(self,data):
        self.sio.emit("sendto-controlles",data)
        print(" ======================= kirim perubahan")

    def getSensorState(self,data):
        self.sio.emit("sendto-sendsors",{"io":data})
        self.sensor = str(data)
        @self.sio.on("sensors-state"+self.sensor)
        def stateSensor(data):
            if int(data["data"]) != self.datasensor:
                self.state = True
            else:
                self.state = False
            self.datasensor = int(data["data"])

    def call_backs(self):
        @self.sio.on("sensors-state"+self.sensor)
        def stateSensor(data):
            print(data,self.sio.eio.sid)
            

