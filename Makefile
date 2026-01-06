CC = gcc

all: serveur client

# UDP
serveur_udp: serveur_udp.c
	$(CC) serveur_udp.c -o serveur_udp

client_udp: client_udp.c
	$(CC) client_udp.c -o client_udp

udp: serveur_udp client_udp

# TCP
serveur_tcpip: serveur_tcpip.c
	$(CC) serveur_tcpip.c -o serveur_tcpip
client_tcpip: client_tcpip.c 
	$(CC) client_tcpip.c -o client_tcpip
tcpip: serveur_tcpip client_tcpip

clean:
	rm -f serveur_udp client_udp serveur_tcpip client_tcpip
