# 20192944 JungTae Kwon 02_2
# AES pycrypto package
from Crypto.Cipher import AES

key = b'ABCDEF0123456789'  # 16 bytes key
iv = b'Netsec@Soongsil.'   # 16 bytes IV (Initialization Vector)
mode = AES.MODE_CBC

with open('enc1.txt', 'rb') as encrypted_file:
    ciphertext = encrypted_file.read()

ciphertext = ciphertext[4:]

decrypt_AES = AES.new(key, mode , iv)
message_decrypted =  decrypt_AES.decrypt(ciphertext)

print("Decrypted text: ",  message_decrypted.strip())