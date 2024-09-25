# 20192944 JungTaeKwon 04_2
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import base64

# generate keypair
keyPair = RSA.generate(2048)

pubKeyPEM = keyPair.export_key(format="DER")
pubKey = RSA.importKey(pubKeyPEM)

# save pub key
print("===== GENERATE RSA PUBLIC KEY =====")

with open("public.der", "wb") as f:
    f.write(pubKeyPEM)
    print("===== SAVE RSA PUBLIC KEY =====")

# sign
encryptor = PKCS1_OAEP.new(keyPair)

with open("./1.txt", "rb") as f:
    plaintext = f.read()
ciphertext = encryptor.encrypt(plaintext)

sig = base64.b64encode(ciphertext)

with open("sig.txt", "wb") as f:
    f.write(sig)
    print("===== SAVE SIGNED FILE WITH PRIVATE KEY =====")
