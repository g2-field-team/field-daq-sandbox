sudo mkdir -p /usr/local/opt/galil
cd /usr/local/opt/galil
wget http://www.galil.com/sw/pub/rhel/6/galilrpm-2-1.noarch.rpm | sudo rpm -ivh

sudo yum install gclib
