from socket import socket
from socket import AF_INET
from socket import SOCK_STREAM
HOST=''
PORT=888

# Create socket
ss=socket(AF_INET, SOCK_STREAM)
# Bind
ss.bind( (HOST, PORT) )
# Listen on ss
ss.listen(5)
# Wait for connection request
conn,addr=ss.accept()

# Receive from client
data=conn.recv(1024).decode("utf-8")
print("[*] Received from %s: %s" %(addr, data))
data=data.upper()
# Send reply msg to client
conn.send(data.encode("utf-8"))
print("[*] Send to %s \"%s\"" %(addr, data))
conn.close()