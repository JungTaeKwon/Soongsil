# 20192944 JungTaeKwon 03_2
from Crypto.Hash import HMAC


def hash_file(filename, key):
    with open(filename, "rb") as byte_infile:
        h = HMAC.new(key.encode())
        file_content = byte_infile.read()
        h.update(file_content)
        return file_content, h.hexdigest()


def save_hmac(filename, file_content, hashed_value):
    with open(filename, "wb") as new_file:
        new_file.write(file_content)
        new_file.write(hashed_value.encode())


print("===== 2a.py =====")
print("===== INPUT KEY OF HMAC =====")
key = input()

print("===== KEY =====")
print(key)

print("===== HASHED HMAC =====")
file_content, hashed_value = hash_file("./2.txt", key)
print(hashed_value)

print("===== SAVE H.txt =====")
save_hmac("H.txt", file_content, hashed_value)
