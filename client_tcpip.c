/*
* Code du client
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100
#define PORT 9600
#define h_addr h_addr_list[0]

int main(int argc, char *argv[]){
    
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[SIZE];
    int n;

    if (argc < 2) {
       fprintf(stderr,"Usage: %s nom_machine\n", argv[0]);
       exit(1);
    }


    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Erreur ouverture socket");
        exit(1);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Erreur, aucun hôte trouvé\n");
        exit(0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur connexion");
        exit(1);
    }

    printf("Connecté au serveur %s sur le port %d\n", argv[1], PORT);

    while(1){
        printf("Entrez votre message: ");
        memset(buffer, 0, SIZE);
        fgets(buffer, SIZE-1, stdin);

        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
             perror("Erreur écriture sur socket");
             exit(1);
        }

        memset(buffer, 0, SIZE);
        n = read(sockfd, buffer, SIZE-1);
        if (n < 0) {
             perror("Erreur lecture sur socket");
             exit(1);
        }

        if(strncmp(buffer, "--quit", 4) == 0) {
            printf("Déconnexion du serveur.\n");
            break;
        }

        printf("Message reçu du serveur: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}