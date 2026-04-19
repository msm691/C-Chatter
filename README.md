# Epollaris (C-Chatter)

> Un système de chat Client/Serveur haute performance en C, basé sur l'architecture événementielle (I/O Multiplexing).

Epollaris est un projet de programmation système et réseau démontrant la création d'une architecture client-serveur robuste. Développé en C pur, ce projet illustre la maîtrise des sockets POSIX, de la gestion de la mémoire, et du multiplexage avec `select()` pour gérer de multiples connexions simultanées sans recourir à un modèle lourd basé sur les threads (C10k problem approach).

Ce projet respecte strictement la **Norme de codage Epitech** (C Coding Style).

## 🚀 Fonctionnalités Actuelles

### Serveur (`chat_server`)
- **I/O Multiplexing :** Utilisation de `select()` pour gérer les I/O de manière asynchrone sur un seul thread.
- **Sockets Non-Bloquantes :** Configuration via `fcntl()` pour garantir qu'aucune opération réseau ne fige le serveur.
- **Gestion des Clients :** Capacité d'accepter et de maintenir jusqu'à 30 connexions TCP simultanées.
- **Lecture en Temps Réel :** Réception et affichage en temps réel des messages envoyés par les clients.
- **Gestion des Déconnexions :** Détection propre des clients qui quittent le serveur et libération des ressources (`File Descriptors`).

### Client (`chat_client`)
- *L'architecture est en place, mais le client C est actuellement en cours de développement (voir la section Avancement).*

## 🛠️ Installation & Compilation

### Prérequis
- Un compilateur C (`gcc` ou `clang`)
- `make`
- Un environnement type UNIX (Linux, macOS)

### Compilation
Cloner le dépôt et compiler le projet à l'aide du `Makefile` fourni :

```bash
git clone [https://github.com/VOTRE_PSEUDO/C-Chatter.git](https://github.com/VOTRE_PSEUDO/C-Chatter.git)
cd C-Chatter
make
```

Le `Makefile` génère deux exécutables distincts :
- `chat_server`
- `chat_client`

**Autres commandes Make disponibles :**
- `make clean` : Supprime les fichiers objets (`.o`).
- `make fclean` : Supprime les fichiers objets et les exécutables.
- `make re` : Recompile entièrement le projet.

## 💻 Utilisation

### 1. Démarrer le serveur
Lancez simplement l'exécutable du serveur. Par défaut, il écoute sur le port **8080**.

```bash
./chat_server
```

### 2. Se connecter en tant que client
Le client C (`chat_client`) étant en phase de construction de son interface utilisateur, vous pouvez tester le serveur en utilisant l'outil standard `nc` (Netcat). Ouvrez un ou plusieurs nouveaux terminaux et tapez :

```bash
nc localhost 8080
```
Vous pouvez maintenant taper vos messages dans Netcat, ils seront reçus et affichés instantanément par le serveur !

## 📊 État d'Avancement (Roadmap)

- [x] **Étape 1 :** Architecture du projet, Makefiles et conformité stricte au C Coding Style.
- [x] **Étape 2 :** Cœur du serveur (Sockets POSIX, `select()`, connexions non-bloquantes).
- [x] **Étape 3 :** Gestion de la concurrence (suivi des FD multiples, lecture des messages entrants).
- [ ] **Étape 4 :** Implémentation du protocole binaire (Header + Payload) pour structurer les paquets réseau.
- [ ] **Étape 5 :** Logique de Broadcast (le serveur renvoie les messages aux autres clients connectés).
- [ ] **Étape 6 :** Développement du client lourd C avec interface terminal (`ncurses`) et multithreading (lecture/écriture simultanées).

## 📝 Norme de Codage (C Coding Style)
Ce projet est écrit en respectant des règles de formatage strictes pour garantir une lisibilité et une maintenabilité professionnelles :
- Maximum 80 colonnes par ligne.
- Maximum 20 lignes par fonction.
- Maximum 5 fonctions par fichier.
- Pas de variables globales.
- Indentation stricte à 4 espaces.