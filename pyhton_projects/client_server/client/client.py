
import socket
import os


print ("Client starting... ")
TCP_IP = 'localhost'
TCP_PORT = 9001
BUFFER_SIZE = 1024

dir_path = os.path.dirname(os.path.realpath(__file__))
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

while True:
    order = input("Please choose List,Get or Put. What is your order? ")
    type(order)
    print('order is...' + order)
    if order == "list":
        s.send(order.encode())
        print('receiving size...')
        size = s.recv(16)
        if not size:
            break
        size = int(size)
        print(size)        
        while(size > 0):
            data = s.recv(BUFFER_SIZE)
            file_name = data.decode()
            size -= len(file_name)
            print(file_name)
            if not data:
                break
        print('Successfully get the file')
    elif order == "get":
        s.send(order.encode())
        data = s.recv(BUFFER_SIZE)
        print(data)
        file_name = input("File name please?")
        type(file_name)
        print('You request for file:' + file_name)
        s.send(file_name.encode())
        print('receiving file...')
        with open(file_name, 'wb') as ff:
            data = s.recv(BUFFER_SIZE)
            ff.write(data)
            while(data):
                print(data)
                if not data:
                    ff.close()
                    print ("file close()")
                    break
                data = s.recv(BUFFER_SIZE)
                ff.write(data)
            print('Successfully get the file')
        ff.close()
    elif order == "put":
        s.send(order.encode())
        data = s.recv(BUFFER_SIZE)
        print(data)
        file_name = input("File name please?")
        type(file_name)
        print('You putting file:' + file_name)
        s.send(file_name.encode())
        data = s.recv(BUFFER_SIZE)
        print(data)
        print('sending file...')
        f = open(dir_path + "/" + file_name, 'rb')
        while True:
            l = f.read(BUFFER_SIZE)
            while (l):
                s.send(l)
                l = f.read(BUFFER_SIZE)
            if not l:
                f.close()
                break
        
    elif order == "exit":
        print('Exiting...')
        s.close()
        break

print('connection closed')