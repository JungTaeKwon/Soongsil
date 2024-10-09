rm kjt*.*
sudo rm /etc/ssl/certs/kjtRoot.pem
sudo rm /usr/local/share/ca-certificates/kjtRoot.crt

sudo ls /etc/ssl/certs/ | grep kjt
sudo ls /usr/local/share/ca-certificates/ | grep kjt