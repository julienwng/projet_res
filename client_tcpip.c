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
    /*Déclaration des variables du client*/
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[SIZE];
    int n;

    /*Vérification des arguments passés dans l'entrée standard*/
    if (argc < 2) { 
       fprintf(stderr,"Usage: %s nom_machine\n", argv[0]);
       exit(1);
    }

    /*Création du socket*/
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Erreur ouverture socket");
        exit(1);
    }

    /*Récupération des informations du serveur*/
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Erreur, aucun hôte trouvé\n");
        exit(0);
    }

    /*Configuration de l'adresse du serveur*/
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    /*Connexion au serveur*/
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur de connexion");
        exit(1);
    }

    printf("Connecté au serveur %s sur le port %d\n", argv[1], PORT);
    printf("Tapez '--quit' pour quitter.\n");

    /*Echange avec le serveur*/
    printf("Entrez votre message: ");
    while(1){
        printf("Entrez votre message: ");
        memset(buffer, 0, SIZE);
        fgets(buffer, SIZE-1, stdin);

        /*Envoi du message*/
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
             perror("Erreur écriture sur socket");
             exit(1);
        }

        /*Réception de la réponse*/
        memset(buffer, 0, SIZE);
        n = read(sockfd, buffer, SIZE-1);
        if (n < 0) {
             perror("Erreur lecture sur socket");
             exit(1);
        }

        /*Test si arrêt de l'échange*/
        if(strncmp(buffer, "--quit", 6) == 0) {
            printf("Déconnexion du serveur.\n");
            break;
        }

        printf("Message reçu du serveur: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
