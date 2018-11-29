# server2.py
import socket
import glob
import os
from time import sleep

from threading import Thread
from socketserver import ThreadingMixIn

TCP_IP = 'localhost'
TCP_PORT = 9001
BUFFER_SIZE = 1024

dir_path = os.path.dirname(os.path.realpath(__file__))


class ClientThread(Thread):

    def __init__(self,ip,port,sock):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.sock = sock
        print (" New thread started for ", ip, ":", str(port))

    def run(self):
        while True:
            input_cmd = self.sock.recv(BUFFER_SIZE)
            input_cmd = input_cmd.decode()
            order = [str(x) for x in input_cmd.split(' ')]
            if order[0] == "list":
                print("this is List operation!")
                files_list_init = glob.glob(dir_path + '/*.txt')
                print(files_list_init)
                files_list = []
                files_name_len = 0
                for file in files_list_init:
                    file_name = file[file.rfind("\\")+1:] + ","
                    files_list.append(file_name)
                    files_name_len += len(file_name)
                files_name_len = bin(files_name_len)[2:].zfill(16)
                self.sock.send(files_name_len.encode())
                for file in files_list:
                    self.sock.send(file.encode())
            elif order[0] == "get":
                file_name = order[1]
                filesize = os.path.getsize(dir_path + "/" + file_name)
                filesize = bin(filesize)[2:].zfill(32)
                self.sock.send(filesize.encode())
                f = open(dir_path + "/" + file_name, 'rb')
                while True:
                    l = f.read(BUFFER_SIZE)
                    while (l):
                        self.sock.send(l)
                        l = f.read(BUFFER_SIZE)
                    if not l:
                        f.close()
                        break
                f.close()
            elif order[0] == "put":
                file_name = order[2]
                size = order[1]
                if not size:
                    break
                size = int(size, 2)
                with open(dir_path + "/" + file_name, 'wb') as ff:
                    while(size > 0):
                        data = self.sock.recv(BUFFER_SIZE)
                        size -= len(data)
                        if not data:
                            break
                        ff.write(data)
                ff.close()
            elif order[0] == 'exit':
                self.sock.close()
tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcpsock.bind((TCP_IP, TCP_PORT))
threads = []

while True:
    tcpsock.listen(5)
    print ("Waiting for incoming connections...")
    (conn, (ip,port)) = tcpsock.accept()
    print ("Got connection from ", (ip,port))
    newthread = ClientThread(ip,port,conn)
    newthread.start()
    threads.append(newthread)

for t in threads:
    t.join()
