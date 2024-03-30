import socket
HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
def running():
    client.connect((HOST,PORT))
    print("connectd sucssefully!!")
    while True:
        y=0
        y=y+1

running()