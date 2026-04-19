# Epollaris (C-Chatter) 🚀

Un petit projet de chat client/serveur codé en C de A à Z ! 

L'objectif ici n'est pas de réinventer Discord, mais de comprendre ce qui se passe vraiment "sous le capot" d'un serveur réseau. Pour ça, le serveur utilise l'architecture événementielle (avec `select()`) pour gérer jusqu'à 30 connexions simultanées sur un seul thread, sans jamais bloquer.

## 🛠️ Comment l'essayer ?

Pas besoin de configuration complexe, il suffit d'un Mac ou d'un système Linux avec `make`.

1. **Compilez le projet :**

    make

2. **Lancez le serveur :**

    ./chat_server

3. **Connectez-vous :**
   Le serveur utilise désormais un **protocole binaire strict**. Seul un client parlant ce "langage" peut communiquer avec lui (Netcat ne fonctionnera plus pour envoyer du texte brut). Le client C complet arrive très bientôt !

## 📍 Où en est-on ?

- [x] Un serveur robuste (sockets non-bloquantes, multiplexage I/O).
- [x] Gestion des clients (connexion, déconnexion).
- [x] Protocole binaire (Header + Payload) pour des échanges sécurisés.
- [x] Client lourd C (Multithreadé).
- [x] Le "Broadcast" : le serveur relaie les messages à tous les utilisateurs.
- [x] Interface terminal (UI) avec `ncurses` pour le client.
- [x] **Bonus : Notifications système (X a rejoint/quitté le chat).**

## 💡 Le petit plus
Le code respecte le coding style d'Epitech.