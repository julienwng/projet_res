# Projet Réseau : Client/Serveur UDP & TCP

##  Membres
- **Léandre LEMOINE**
- **Julien WENG**

## Description
Projet de programmation réseau en binôme dans le cadre de l'UE "Réseaux" de l'Université Paris-Saclay (LDD2 Mathématiques, Informatique).

Ce projet implémente deux types de communication en langage C :
1.  **Communication orientée datagramme** (Protocole UDP)
2.  **Communication orientée flux** (Protocole TCP/IP)

Un `Makefile` est fourni pour automatiser la compilation.

---

# Partie 1 : Communication orientée datagramme (UDP)

Le client envoie une chaîne de caractères au serveur, qui l'affiche sur sa sortie standard.
> **Note :** La taille des messages est limitée à **20 caractères**.

##  Compilation

Pour compiler uniquement la partie UDP :
```bash
make udp 
```
Pour clean :
```bash
make clean
```
## Exécution

Il faut ouvrir **deux terminaux** différents (un pour le serveur, un pour le client).

### 1. Démarrer le Serveur
Dans le premier terminal, lancez :
```bash
./serveur_udp
```
Si sur le terminal du serveur il y a une erreur de binding, alors le serveur est déjà utilisé, il faut donc soit utiliser le terminal où le serveur a déjà été lancé ou bien quitter dans l'autre terminal avec CTRL + C au clavier et puis relancer la commande dans le terminal.

### 2. Pour le Client
Dans un deuxième terminal, lancez : 
```bash
./client_udp localhost
```
### Exemple d'utilisation 
Pour envoyer un message au serveur il faut écrire le message après avoir lancé le client, par exemple :
```bash
$./client_udp localhost
Entrez un message : abc
Envoyé
```

Puis l'on va recevoir sur le serveur
```bash
$./serveur_udp
Message reçu : abc
```
# Partie 2 : Communication orientée flux (TCP/IP)

Dans cette partie, une connexion stable est établie entre le client et le serveur.
Le serveur fonctionne en mode **"Écho"** : il renvoie au client exactement ce qu'il a reçu.

##  Compilation

Pour compiler uniquement la partie TCP :
```bash
make tcpip
```
Pour clean :
```bash
make clean
```

## Exécution

Il faut ouvrir **deux terminaux** différents (un pour le serveur, un pour le client).

### 1. Démarrer le Serveur
Dans le premier terminal, lancez :
```bash
./serveur_tcpip
```

### 2. Pour le Client
Dans un deuxième terminal, lancez : 
```bash
./client_tcpip localhost
```

### Exemple d'utilisation

Après que le client s'est connecté au serveur, on peut envoyer plusieurs messages à la suite.

```bash
$ ./client_tcpip localhost
Connecté au serveur localhost sur le port 9600
Entrez votre message: abc
Message reçu du serveur: abc

Entrez votre message: test
Message reçu du serveur: test
``` 
Pour déconnecter le client, entrer dans le terminal du client :

```bash
--quit
```
Puis le serveur se remettra à l'écoute pour un prochain client.
