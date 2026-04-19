# Epollaris (C-Chatter) 🚀

Un petit projet de chat client/serveur codé en C de A à Z ! 

L'objectif ici n'est pas de réinventer Discord, mais de comprendre ce qui se passe vraiment "sous le capot" d'un serveur réseau. Pour ça, le serveur utilise l'architecture événementielle (avec `select()`) pour gérer jusqu'à 30 connexions simultanées sur un seul thread, sans jamais bloquer.

## 🛠️ Comment l'essayer ?

Pas besoin de configuration complexe, il suffit d'un Mac ou d'un système Linux avec `make`.

1. **Compilez le projet :**

    make

2. **Lancez le serveur :**

    ./chat_server

3. **Connectez-vous (en tant que client) :**
   Le vrai client C est encore en construction. Pour l'instant, on utilise l'outil natif Netcat pour discuter avec le serveur. Ouvrez plusieurs terminaux et tapez :

    nc localhost 8080

   *Envoyez des messages depuis vos différents terminaux et regardez le serveur réagir en temps réel !*

## 📍 Où en est-on ?

- [x] Un serveur robuste (sockets non-bloquantes, multiplexage I/O).
- [x] Gestion des clients (connexion, déconnexion) et lecture des messages.
- [ ] Le "Broadcast" : le serveur renvoie les messages aux autres utilisateurs.
- [ ] Un vrai client C avec une belle interface terminal (ncurses).

## 💡 Le petit plus
Le code respecte la norme Epitech