from socket import socket
from socket import AF_INET
from socket import SOCK_STREAM
HOST = '127.0.0.1'
PORT=888

# Create socket
s=socket(AF_INET, SOCK_STREAM)
# Connect to socket ({HOST}, {PORT})
s.connect( (HOST,PORT) )

# Send encoded msg(byte stream)
msg = "Hello world!"
s.send(msg.encode("utf-8"))
print("[*] Send to ({}, {}): {}" .format(HOST, PORT, msg))

# Receive from server
data=s.recv(1024)
print("[*] Received from ({}, {}): {}".format(HOST, PORT, data.decode("utf-8")))
s.close()