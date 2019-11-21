from socket import *
import time

def make_header(port,seq,ack):
    header = [int(port/256), port%256, int(port/256), port%256,255,255,255,255]
    header += [int(seq/256), seq%256, int(ack/256), ack%256]
    return header #len is 8+4, 12
def make_pkt(header, content):
    pkt_len= len(header)+len(content)
    header[4]=int(pkt_len/256)
    header[5]=pkt_len%256
    pkt = bytes(header)+ content
    return pkt
#ip = raw_input("Enter the IP address of a receiver: ")
ip = '192.168.0.8'
#ip = raw_input("Enter the IP address of a receiver: ")
timeout=10
#ip = raw_input("Enter the IP address of a receiver: ")
w_size=4
port=10080
f_name = raw_input("Enter the filename: ")
senderSock = socket(AF_INET,SOCK_DGRAM)
senderSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
senderSock.bind(('',port))
seq=0
ack=1<<16
senderSock.sendto(f_name.encode(),(ip,10080)) 
with open(f_name,"rb") as f1:
    while True:
        header = make_header(port,seq,ack,f_name)
        content = f1.read(1400-len(header)) #1400-12=1388
        if not content:
            break
        pkt = make_pkt(header, content)
        senderSock.sendto(pkt,(ip,10080))
senderSock.close()
print('Program ended.')

