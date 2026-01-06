/*
* Code du serveur
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string.h>

/* Port local du serveur */
#define PORT 9600



int main(int argc, char *argv[]){

    int sockfd; //sockfd : descripteur de socket
    struct sockaddr_in server_addr, client_addr; //serveur_addr : structure d'adresse locale du serveur, client_addr : structure d'adresse du client
    socklen_t adr_len; //adr_len : taille de l'adresse du client

    //Ouverture du socket du serveur et vérification de la bonne ouverture du socket
    sockfd = socket(PF_INET,SOCK_DGRAM, 0);
    if(sockfd < 0) {
        perror("Erreur Socket");
        exit(1);
    }

    //Remplissage de la structure d'adresse locale du serveur
    server_addr.sin_family = PF_INET; 
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //On bind et on vérifie qu'il n'y a pas d'erreurs
    if( bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("Erreur binding");
        exit(1);
    }

    /*
    * Boucle générale du serveur (infinie)
    */
    while(1){
        /*
        * Code de l'intérieur de la boucle
        */
       adr_len = sizeof(client_addr);
       char buffer[21];
       int client_struct_length = sizeof(client_addr);
        int n = recvfrom(sockfd, buffer, 21, 0, (struct sockaddr*)&client_addr, &adr_len);
        if(n < 0) {
            perror("erreur réception");
        }
        write(1, "Message Reçu : ", 15);
        write(1, buffer, n);
        write(1, "\n", 1);
        
    }
    close(sockfd);
    

    return 0;


}
