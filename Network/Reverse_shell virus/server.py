import socket
import threading

HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
FORMAT='UTF-8'
list_of_clients=[]
client_counter=0

def connectiona_accepter():
    global client_counter
    print("server is starting")
    server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server.bind((HOST,PORT))
    server.listen()
    print(f"server is running on ip {HOST}")
    while True:
        conn,addr=server.accept()
        print(f"the new client is {addr}")
        list_of_clients.append((conn,addr))
        client_counter+=1
        print(f"the number of active connection is {client_counter}")


def start():
    connection_thread=threading.Thread(target=connectiona_accepter)
    connection_thread.start()
    x=0
    while 1:
        x=x+1

    
start()