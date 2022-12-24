from module.socket import SOCKET_IO
from time import sleep
sockets = SOCKET_IO()
sockets.setup()

while True:
    sockets.getSensorState(4)
    if sockets.state:
        if sockets.datasensor == 1:
            sockets.SendCommand({
                "io": 2,
                "changestate" : 1
            })
        else:
            sockets.SendCommand({
                "io": 2,
                "changestate" : 0
            })
    sleep(0.3)
