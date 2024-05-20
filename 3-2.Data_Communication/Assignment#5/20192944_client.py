from socket import socket
from socket import AF_INET
from socket import SOCK_STREAM
HOST = '127.0.0.1'
PORT=8080

def main():
    # Create socket
    s=socket(AF_INET, SOCK_STREAM)
    # Connect to socket ({HOST}, {PORT})
    s.connect( (HOST,PORT) )
    while True:
        # Receive from msg server
        response=s.recv(1024).decode("utf-8")
        print("[*] Received from ({}, {}): {}".format(HOST, PORT, response))
        
        if "축하합니다" in response:
            break

        # Send encoded msg(byte stream)
        msg = input("숫자를 입력하세요: ")
        s.send(msg.encode("utf-8"))
        print("[*] Send to ({}, {}): {}" .format(HOST, PORT, msg))
    s.close()

if __name__ == "__main__":
    main()
