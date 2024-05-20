import baseball

from socket import socket
from socket import AF_INET
from socket import SOCK_STREAM
HOST=''
PORT=8080

def main():
    # Create socket
    ss=socket(AF_INET, SOCK_STREAM)
    # Bind
    ss.bind( (HOST, PORT) )
    # Listen on ss
    ss.listen(5)
    # Wait for connection request
    conn,addr=ss.accept()

    print(f"[*] {addr}에서 접속하였습니다.")
    
    answer = baseball.generate_number()
    attempts = 0
    
    # Send Introduction of baseball-game
    baseball_introduction_msg="3자리 숫자 야구 게임에 오신 것을 환영합니다!\n컴퓨터가 0에서 9까지의 숫자 중에서 중복되지 않는 3자리 숫자를 생성했습니다.\n"
    conn.send(baseball_introduction_msg.encode("utf-8"))

    # Print answer to server log
    print(f"[*] 정답: {answer}")
    while True:
        # Receive from client (request for answer)
        request = conn.recv(1024).decode("utf-8")
        
        # Use baseball module
        if not baseball.is_valid_guess(request):
            # Invalid request
            conn.send("잘못된 입력입니다. 3자리의 중복되지 않는 숫자를 입력하세요.".encode("utf-8"))
            continue
        
        # Check attempts
        attempts += 1
        strikes, balls = baseball.get_strikes_and_balls(request, answer)
        
        # Print server log
        print(f"Received \'{request}\': {strikes} 스트라이크, {balls} 볼")
        # Send result of the round to the connected client
        conn.send(f"{strikes} 스트라이크, {balls} 볼\n".encode("utf-8"))
        
        # Success
        if strikes == 3:
            conn.send(f"축하합니다! {attempts}번 만에 정답을 맞추셨습니다.".encode("utf-8"))
            break

    conn.close()
    ss.close()

if __name__ == "__main__":
    main()