# Epollaris (C-Chatter) 🚀

Epollaris est un système de messagerie complet et hybride, alliant la performance du **C** (système) à la flexibilité du **Web** (Node.js/HTML5). Le projet démontre la mise en œuvre d'une architecture client-serveur asynchrone capable de faire dialoguer des terminaux et des navigateurs web en temps réel.

## 🏗️ Architecture du Projet

Le projet se divise en trois composants majeurs qui communiquent en harmonie :

1.  **Le Serveur (C)** : Le cœur du système. Il utilise le multiplexage d'E/S avec `select()` pour gérer les connexions de manière non-bloquante.
2.  **Le Client Lourd (C)** : Une application terminale multithreadée utilisant `ncurses` pour une interface utilisateur scindée entre la lecture et l'écriture.
3.  **Le Pont Web (Node.js)** : Un proxy agissant comme traducteur entre les **WebSockets** (navigateur) et le **TCP Binaire** (serveur C).

## 🛠️ Installation et Lancement

### 1. Le Serveur et le Client C
Assurez-vous d'avoir `clang` et la bibliothèque `ncurses` installés sur votre système.

```bash
# Compilation du serveur et du client
make re

# Lancement du serveur (port 8080 par défaut)
./chat_server

# Lancement du client terminal (dans un autre terminal)
./chat_client
```

### 2. L'Interface Web
Nécessite [Node.js](https://nodejs.org/) installé.

```bash
cd web_client
npm install
node server.js
```
Ouvrez ensuite `web_client/index.html` dans votre navigateur.

## 📡 Protocole Réseau

Le système repose sur un protocole binaire strict défini dans `protocol.h` :
* **Packet Header** : Définit le type de message (`LOGIN_REQ`, `MSG_REQ`) et la taille du payload.
* **Msg Payload** : Contient le nom de l'expéditeur et le texte brut.

Cette structure garantit que les données sont transmises de manière compacte et rapide.

## 📍 État d'avancement (Roadmap)

- [x] **Serveur robuste** : Sockets non-bloquantes et multiplexage `select()`.
- [x] **Gestion des clients** : Connexion, déconnexion et nettoyage des ressources.
- [x] **Protocole binaire** : Header + Payload pour des échanges sécurisés.
- [x] **Client lourd C** : Architecture multithreadée (Threads d'envoi et de réception séparés).
- [x] **Broadcast** : Relais en temps réel des messages à tous les connectés.
- [x] **Interface Ncurses** : UI terminale propre avec fenêtres scindées.
- [x] **Notifications Système** : Annonces automatiques des arrivées et départs.
- [x] **Extension Web** : Proxy Node.js et interface HTML5/WebSocket.

## 💡 Concepts Techniques Abordés

* **Multiplexage I/O** : Gestion de plusieurs descripteurs de fichiers sans threads côté serveur via `select()`.
* **Multithreading** : Utilisation de `pthread` pour gérer l'interface utilisateur et le réseau simultanément côté client.
* **Protocoles Hybrides** : Conversion de données entre flux TCP binaires et messages JSON WebSockets.
* **Norme Epitech** : Code structuré, modulaire et respectant le coding style.
