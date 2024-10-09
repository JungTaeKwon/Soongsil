#!/bin/bash

# 1. Root CA 개인 키 생성
openssl genrsa -out kjtRoot.key 2048

# 2. Root CA 인증서 생성 (self-signed)
openssl req -x509 -new -key kjtRoot.key -days 3650 -out kjtRoot.pem -subj "/C=KR/ST=Seoul/L=Dongjak/O=SSU/OU=SW/CN=kjtROOT/emailAddress=liku99@soongsil.ac.kr"

# 3. 중간 CA 개인 키 생성
openssl genrsa -out kjtCA.key 2048

# 4. 중간 CA 인증서 서명 요청 (CSR) 생성
openssl req -new -key kjtCA.key -out kjtCA.csr -subj "/C=KR/ST=Seoul/L=Dongjak/O=SSU/OU=SW/CN=kjtCA/emailAddress=liku99@soongsil.ac.kr"

# 5. 확장 파일 생성 (중간 CA에 대한 설정)
cat > kjtCA.ext <<EOF
authorityKeyIdentifier=keyid,issuer
basicConstraints=critical,CA:TRUE
keyUsage = digitalSignature, keyCertSign, cRLSign
EOF

# 6. 중간 CA 인증서 생성 (Root CA로 서명)
openssl x509 -req -in kjtCA.csr -CA kjtRoot.pem -CAkey kjtRoot.key -CAcreateserial -out kjtCA.pem -days 3650 -extfile kjtCA.ext

# 7. 사용자 개인 키 생성
openssl genrsa -out kjt.key 2048

# 8. 사용자 인증서 서명 요청 (CSR) 생성
openssl req -new -key kjt.key -out kjt.csr -subj "/C=KR/ST=Seoul/L=Dongjak/O=SSU/OU=SW/CN=kjt/emailAddress=liku99@soongsil.ac.kr"

# 9. 사용자 인증서 생성 (중간 CA로 서명)
openssl x509 -req -in kjt.csr -CA kjtCA.pem -CAkey kjtCA.key -CAcreateserial -out kjt.pem -days 365

# 10. Root CA를 시스템에 추가 및 인증서 업데이트
sudo cp kjtRoot.pem /usr/local/share/ca-certificates/kjtRoot.crt
sudo update-ca-certificates
