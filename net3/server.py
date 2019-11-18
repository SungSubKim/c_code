from socket import *
ip_rcv = input("Enter the IP address of a receiver")
t_out = input("Enter the timeout")
w_size = input("Enter the window size")
    
serverSock = socket(AF_INET,SOCK_DGRAM)
serverSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
serverSock.bind(('',10080))
print('my ip is '+gethostbyname(getfqdn()))
while True:
    message, clientAddress = serverSocket.recvfrom(1024)
    newMsg = message.decode().upper()
    serverSocket.sendto(newMsg.encode(),ip_rcv)
serverSock.close()
print('Program ended.')
