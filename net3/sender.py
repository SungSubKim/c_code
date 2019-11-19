from socket import *
import time
#ip = raw_input("Enter the IP address of a receiver: ")
ip = '192.168.0.8'
filename = raw_input("Enter the filename: ")
senderSock = socket(AF_INET,SOCK_DGRAM)
senderSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
senderSock.bind(('',10080))
senderSock.sendto('hi'.encode(),(ip,10080))
sum_content = b''
with open(filename,"rb") as f1:
    while 1:
        content = f1.read(2)
        if not content:
            break
        sum_content += content
        senderSock.sendto(content,(ip,10080))
time.sleep(15)
print(sum_content.decode())                   
senderSock.close()
print('Program ended.')

