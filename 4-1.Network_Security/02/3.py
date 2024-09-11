# 20192944 JungTae Kwon 02_3
# AES pycrypto package
from Crypto.Cipher import AES
from Crypto.Util import Counter

key = b'ABCDEF0123456789'  # 16 bytes key
mode = AES.MODE_CTR
ctr = Counter.new(128)

with open('enc2.txt', 'rb') as encrypted_file:
    ciphertext = encrypted_file.read()

ciphertext = ciphertext[4:]

decrypt_AES = AES.new(key, mode, counter=ctr)
message_decrypted =  decrypt_AES.decrypt(ciphertext)

print("Decrypted text: ",  message_decrypted.strip())