# 20192944 JungTaeKwon 03_2
from Crypto.Hash import HMAC


def get_hmac(filename):
    with open(filename, "rb") as byte_infile:

        return byte_infile.read()[-32:]


def validate_file(filename, key, mac):
    with open(filename, "rb") as byte_infile:
        content = byte_infile.read()[:-32]
        h = HMAC.new(key.encode())

        if mac == h.update(content).hexdigest().encode():
            print("OK")
        else:
            print("NOK")


print("===== 2b.py =====")
print("===== INPUT KEY OF HMAC =====")
key = input()

print("===== KEY =====")
print(key)

filename = "./H.txt"

mac = get_hmac(filename)

print("===== HASHED HMAC =====")
print(mac)

print("===== VALIDATE FILE =====")
validate_file(filename, key, mac)
