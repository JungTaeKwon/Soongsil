# 20192944 JungTae Kwon 02_1
# AES pycrypto package
from Crypto.Cipher import AES

while(True):
    # key has to be 16, 24 or 32 bytes long
    encrypt_AES = AES.new(b'secret-key-01234', AES.MODE_CFB, b'IV-0123456789ABC')

    # Fill with spaces the user until 32 characters
    # Fill with spaces until 32 characters
    message = input("Enter the message to encrypt (max 32 characters): ")
    message = message.encode('utf-8')
    print ("message length: ", len(message) )

    ciphertext = encrypt_AES.encrypt(message)
    print("Cipher text: " , ciphertext)

    # key must be identical
    decrypt_AES = AES.new(b'secret-key-01234', AES.MODE_CFB, b'IV-0123456789ABC')
    message_decrypted =  decrypt_AES.decrypt(ciphertext)

    print("Decrypted text: ",  message_decrypted.strip())