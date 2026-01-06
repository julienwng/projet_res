/*
* Code du Client
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100
#define PORT 9600

int main(int argc, char *argv[]){

    int sockfd, lenstr; //sockfd : descripteur de socket, lenstr : taille de la chaine à envoyer
    char buffer[SIZE]; //buffer : zone de mémoire pour accueillir la chaîne entrée du clavier
    struct sockaddr_in serveur_addr; //servaddr : structure d'addresse du serveur 
    struct hostent *host; //host : pointeur vers la structure descriptive de la machine
    

   //Ouverture du socket du client et vérification de la bonne ouverture du socket
   sockfd = socket(PF_INET, SOCK_DGRAM, 0);
   if(sockfd < 0){
    perror("Erruer socket");
    exit(1);
   }

   //On vérifie qu'il y a bien un argument rentré 
   if(argc != 2){ 
    printf("Erreur, il n'y a pas le bon nombre d'arguments");
    exit(1);
   }

   //On récupère l'adresse IP du serveur à partir de son nom donné en ligne de commande et on vérifie que l'adresse existe
   host = gethostbyname(argv[1]); 
   if(host == NULL){
    herror("Serveur Inconnu");
    exit(1);
   }

   //Remplissage de la structure d'adresse du serveur
   serveur_addr.sin_family = PF_INET;   
   serveur_addr.sin_port = htons(PORT);
   serveur_addr.sin_addr = *(struct in_addr*) host->h_addr_list[0];

   printf("Entrez un message :");
   
   //On récupère le message du client lu dans l'entrée standard en vérifiant qu'il n'y a pas d'erreur
   if(fgets(buffer, 21, stdin) != NULL){
        lenstr = strlen(buffer) + 1;

        //On envoie ce message au serveur et on vérifie qu'il n'y a pas d'erreur, s'il n'y en a pas, on confirme l'envoi du message
        if(sendto(sockfd, buffer, lenstr, 0, (struct sockaddr*) &serveur_addr, sizeof(serveur_addr)) < 0){
            perror("Erreur sendto");
            exit(1);
        }
        else{
            printf("Message envoyé\n");
        }
   }
   close(sockfd);

    return 0;
}