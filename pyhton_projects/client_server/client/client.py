
import socket
import os
from time import sleep


print ("Client starting... ")
TCP_IP = 'localhost'
TCP_PORT = 9001
BUFFER_SIZE = 1024

dir_path = os.path.dirname(os.path.realpath(__file__))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

while True:
    input_cmd = input("Please choose List,Get or Put. What is your order? ")
    type(input_cmd)
    order = [str(x) for x in input_cmd.split(' ')]
    for x in order:
        print (x)
    print('order is...' + order[0])
    if order[0] == "list":
        s.send(order[0].encode())
        size = s.recv(16)
        if not size:
            break
        size = int(size, 2)
        while(size > 0):
            data = s.recv(BUFFER_SIZE)
            if not data:
                break
            file_name = data.decode()
            size -= len(file_name)
            for x in file_name.split(','):
                print(x)
    elif order[0] == "get":
        for file_name in order[1:]:
            print ("file_name")
            s.send((order[0]+ " " + file_name).encode())
            size = s.recv(32)
            if not size:
                break
            size = int(size, 2)
            print('receiving file...')
            with open(file_name, 'wb') as ff:
                while(size > 0):
                    data = s.recv(BUFFER_SIZE)
                    size -= len(data)
                    if not data:
                        break
                    ff.write(data)
            print('Successfully get the file' + file_name)
            ff.close()
    elif order[0] == "put":
        for file_name in order[1:]:
            print (file_name)
            if not (os.path.isfile(dir_path + "/" + file_name)):
                print ("The file " + file_name + " not exist, continue to next file...")
                continue
            filesize = os.path.getsize(dir_path + "/" + file_name)
            filesize = bin(filesize)[2:].zfill(32)
            s.send((order[0]+ " " + filesize + " " + file_name).encode())
            sleep(0.10)
            f = open(dir_path + "/" + file_name, 'rb')
            while True:
                l = f.read(BUFFER_SIZE)
                while (l):
                    s.send(l)
                    l = f.read(BUFFER_SIZE)
                if not l:
                    f.close()
                    break
            f.close()
    elif order[0] == "exit":
        print('Exiting...')
        break
    else:
        break

s.close()
print('connection closed')