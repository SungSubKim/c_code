from socket import *
ip_snd = input("what's serverIP")
clientSocket = socket(AF_INET,SOCK_DGRAM)
clientSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
msg = input("Input lowercase sentence: ")
clientSocket.sendto(msg.encode(),(ip_snd,10080))
