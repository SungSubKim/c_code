from socket import *

receiverSock = socket(AF_INET,SOCK_DGRAM)
receiverSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
receiverSock.bind(('',10080))
print("receiverSock is created.")
content = b''
new_content,serverAddress=receiverSock.recvfrom(1024)
print(new_content.decode())
while 1:
    new_content,serverAddress=receiverSock.recvfrom(2)
    #if not new_content:
    #    break
    content+=new_content
    print(new_content.decode())
    with open("client.py","wb") as f1:
        f1.write(content)
        #f1.write(new_content)
print("received!")

receiverSock.close()    
