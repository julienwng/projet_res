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

#define PORT 9600
#define SIZE 100

int main(int argc, char *argv[]){
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t adr_len;
    char buffer[SIZE];
    int n;
    int opt = 1;

    sockfd = socket(PF_INET,SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Erreur Socket");
        exit(1);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = PF_INET; 
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("Erreur binding");
        exit(1);
    }

    if (listen(sockfd, 4) < 0){
        perror("Erreur listen");
        exit(1);
    }

    printf("Serveur en attente de connexion sur le port %d...\n", PORT);

    while(1){

        adr_len = sizeof(client_addr);
        newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &adr_len);
        if(newsockfd < 0){
            perror("Erreur accept");
        }

        printf("Client connecté.\n");

        while(1){
            memset(buffer, 0, SIZE);
            n = read(newsockfd, buffer, SIZE - 1);
            if (n < 0) {
                perror("Erreur lecture");
                break;
            }
            if (n == 0) {
                printf("Client déconnecté.\n");
                break;
            }
            printf("Message reçu: %s\n", buffer);
            write(newsockfd, buffer, n);
        }
        
        close(newsockfd);
        break;
    }
    close(sockfd);
    printf("Serveur arrêté.\n");
    return 0;

}
