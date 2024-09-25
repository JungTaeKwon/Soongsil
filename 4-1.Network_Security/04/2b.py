# 20192944 JungTaeKwon 04_2
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import base64

with open("public.der", "rb") as p:
    pubKeyDER = p.read()

with open("sig.txt", "rb") as s:
    sig = s.read()

with open("1.txt", "rb") as f:
    plaintext = f.read()

# generate pubKey
pubKey = RSA.import_key(pubKeyDER)

# generate validator
verifier = PKCS1_OAEP.new(pubKey)

result = verifier.decrypt(base64.b64decode(sig))
print("===== VERIFICATION RESULT =====")
if result == plaintext:
    print("verified")
else:
    print("not verified")
