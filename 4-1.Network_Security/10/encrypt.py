from M2Crypto import BIO, Rand, SMIME, X509

def makebuf(text):
	return BIO.MemoryBuffer(text)

def encrypt(text, email):
	# Make a MemoryBuffer of the message.
	buf = makebuf(text.encode())

	# Seed the PRNG.
	Rand.load_file('randpool.dat', -1)

	# Instantiate an SMIME object.
	s = SMIME.SMIME()

	# Load target cert to encrypt to.
	x509 = X509.load_cert('recipient.pem')
	sk = X509.X509_Stack()
	sk.push(x509)
	s.set_x509_stack(sk)

	# Set cipher: AES_128 in CBC mode.
	s.set_cipher(SMIME.Cipher('aes_128_cbc'))

	# Encrypt the buffer.
	p7 = s.encrypt(buf)


	# Output p7 in mail-friendly format.
	out = BIO.MemoryBuffer()

	out.write('From: %s\n' %email)
	out.write('To: %s\n' %email)
	out.write('Subject: M2Crypto S/MIME testing\n')
	s.write(out, p7)

	# Save the PRNG's state.
	Rand.save_file('randpool.dat')
	return out.read()

if __name__ == '__main__':
	print(encrypt("test", "oxdjww@gmail.com").decode() )

