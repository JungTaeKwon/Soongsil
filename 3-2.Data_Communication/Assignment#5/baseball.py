###숫자 야구 게임

import random

def generate_number():
    # 0-9 사이의 숫자 중에서 중복되지 않는 3자리 숫자 생성
    digits = random.sample(range(10), 3)
    return ''.join(map(str, digits))

def get_strikes_and_balls(guess, answer):
    strikes = 0
    balls = 0
    
    for i in range(3):
        if guess[i] == answer[i]:
            strikes += 1
        elif guess[i] in answer:
            balls += 1
            
    return strikes, balls

def is_valid_guess(guess):
    # 입력이 3자리 숫자인지 확인하고 중복되지 않는지 확인
    if len(guess) != 3:
        return False
    if not guess.isdigit():
        return False
    if len(set(guess)) != 3:
        return False
    return True
