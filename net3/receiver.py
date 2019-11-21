from socket import *

receiverSock = socket(AF_INET,SOCK_DGRAM)
receiverSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
receiverSock.bind(('',10080))
print("receiverSock is created.")
content_sum = b''
while 1:
    content,serverAddress=receiverSock.recvfrom(1400)
    header = content[:32]
    header2 = header[12:].decode()
    f_name = ''
    for i in header2:
        if i is not '\x00':
            f_name+=i
    #content_sum += content[32:]
    with open(f_name,"ab") as f1:
        f1.write(content[32:])
print("received!")

receiverSock.close()    
