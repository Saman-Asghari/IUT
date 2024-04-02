import socket
import threading
import tkinter as tk



HOST=socket.gethostbyname(socket.gethostname())
PORT=12345
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)


def background():
    client.connect((HOST,PORT))
    print("connectd sucssefully!!")
    while True:
        request=client.recv(1024).decode('UTF-8')
        print(request)

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
    while 1:
        pass


start()