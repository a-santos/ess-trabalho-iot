// INFO

# PASTAS NO SERVER
$ /var/www/html   							(plataforma web)
$ /home/pi/ess_trab_server  				(scripts do server: broker MQTT, sockets, envia IFTTT)
$ /home/pi/ess_trab_data  					(onde são guardados enviados pelos sensores)
$ /home/pi/ess_trab_server/twitter_post  	(portar no Twitter)

# NETWORKS
SSID: droid_wlan / WlanDr01d16

# SITES
URL da plataforma: http://192.168.1.78/index.html         (rede Afonso)
Repositório: https://github.com/a-santos/ess-trabalho-iot
** Twitter: https://twitter.com/desmondd_io  

# INTERFACES
MAC wlan0: ?
MAC eth0: b8:27:eb:69:b2:d3

# USERS 
root, afonso, pi
VNC
phpmyadmin 
MySQL

# CRONTAB:
$ crontab -e

____________________________________________________________________________
// CONFIGS + PACKAGES INSTALADOS

teclado PT
time-zone Lisboa
$ sudo apt-get update && apt-get upgrade	

pass alterada: user & root

bloquear acesso SSH pelo root:
	$ cd /etc/ssh
	$ sudo nano sshd_config
		PermitRootLogin no
		Control + O  (gravar alteração)
	$ sudo service ssh restart

ativar serviço SSH no arranque
$ sudo systemctl enable ssh.socket

tightvncserver (só configurei password)

samba (ñ configurei)

Apache2 + PHP + MySQL

post no twitter
$ sudo apt-get install python-setuptools
$ sudo easy_install pip
$ sudo pip install twython