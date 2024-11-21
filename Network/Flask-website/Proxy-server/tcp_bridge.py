import select
import socket
import threading
from scapy.all import *
from scapy.layers.http import *
from scapy.layers.inet import *
counter=0

def threaded(fn):
    def wrapper(*args, **kwargs):
        _thread = threading.Thread(target=fn, args=args, kwargs=kwargs)
        _thread.start()
        return _thread

    return wrapper

def get_substring_from_end(s):
    index=s.rfind('/')
    if index !=-1:
        substring=s[index+1:]
        remaining_part=s[:index]
    else:
        substring=s
        remaining_part=""

    return substring,remaining_part


#note that in this approach we dont need to remove or do anything for the header we are just reading the header


def analyz(packet_to_be_read:Packet):
    method=packet_to_be_read.Path.decode('utf-8')
    last_part,proxy_added=get_substring_from_end(method)
    
    if(packet_to_be_read.Host.decode('utf-8')=="192.168.113.132"):
        print("this packet is forwarding to the server")
        print("it is going to the "+last_part+" page")
        print("the proxy added "+proxy_added)
        print("\n")
        print(f"HTTP Method: {packet_to_be_read.Method.decode('utf-8')}")
        print(f"Host: {packet_to_be_read.Host.decode('utf-8')}")
        print(f"Path: {packet_to_be_read.Path.decode('utf-8')}")
        print(f"User-Agent: {packet_to_be_read.User_Agent.decode('utf-8')}")
        print("\n\n")



class TCPBridge(object):

    def __init__(self, host, port, dst_host, dst_port):
        self.host = host
        self.port = port
        self.dst_host = dst_host
        self.dst_port = dst_port

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.settimeout(1)
        self.server.bind((self.host, self.port))
        self.stop = False

    @threaded
    def tunnel(self, sock: socket.socket, sock2: socket.socket, chunk_size=1024):
        try:
            while not self.stop:
                """this line is for raising exception when connection is broken"""
                sock.getpeername() and sock2.getpeername()
                r, w, x = select.select([sock, sock2], [], [], 1000)
                if sock in r:
                    #counter+=1
                    data = sock.recv(chunk_size)
                    packet_pot=HTTPRequest(data)
                    if(packet_pot.haslayer(HTTPRequest)):
                        analyz(packet_pot)
                    if len(data) == 0:
                        break
                    sock2.sendall(data)

                if sock2 in r:
                    data = sock2.recv(chunk_size)
                    if len(data) == 0:
                        break
                    sock.sendall(data)
        except:
            pass
        try:
            sock2.close()
        except:
            pass
        try:
            sock.close()
        except:
            pass

    def run(self) -> None:
        self.server.listen()

        while not self.stop:
            try:
                (sock, addr) = self.server.accept()
                if sock is None:
                    continue
                client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                client_socket.connect((self.dst_host, self.dst_port))
                self.tunnel(sock, client_socket)
            except KeyboardInterrupt:
                self.stop = True
            except TimeoutError as exp:
                pass
            except Exception as exp:
                print("Exception:", exp)


if __name__ == "__main__":
    tcp_bridge = TCPBridge("0.0.0.0", 8082, "192.168.113.132", 80) #TODO:change destonation ip 
    tcp_bridge.run()
