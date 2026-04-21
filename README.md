# 🚀 TeleChat : Quand le bas niveau rencontre le Web

Salut ! 👋

---

## 🧠 L'Architecture

Le projet repose sur un trio de composants qui travaillent en parfaite harmonie :

1. **Le Cerveau (Serveur C)** 🧠 : C'est la source de vérité. Conçu autour du multiplexage d'E/S avec `select()`, il encaisse les connexions de manière non-bloquante. Il gère l'état des salons, les pseudos, et route les paquets à la vitesse de l'éclair.
2. **Le Puriste (Client C)** 💻 : Une interface terminale multithreadée construite avec `ncurses`. Parfait pour ceux qui aiment chatter sans quitter leur IDE.
3. **Le Traducteur (Proxy Node.js)** 🌐 : Un pont léger qui écoute les WebSockets du navigateur et les traduit en flux TCP binaires pour le serveur C. C'est lui qui permet d'avoir une belle interface Web dynamique !

---

## 🛠️ Installation

Pas besoin de configuration complexe. Si vous avez `clang`, `ncurses` et `node`, vous êtes prêt.

### 1. Lancer le projet
```bash
make re
./telechat_server  # Le serveur écoute sur le port 8080
```
*Ouvrez un autre terminal pour le client :*
```bash
./telechat_client
```

### 2. Rejoindre depuis le Web
```bash
cd web_client
npm install
node server.js
```
*Ouvrez simplement le fichier `web_client/index.html` dans Chrome, Firefox ou Safari !*

---

## 💬 Commandes Disponibles

Le serveur gère nativement plusieurs commandes pour pimenter vos discussions, que vous soyez sur le web ou le terminal :

* 🚪 `/join #nom_du_salon` : Marre du brouhaha de `#general` ? Créez ou rejoignez un salon privé.
* 🤫 `/msg <pseudo> <texte>` : Pour murmurer un secret à un utilisateur précis.
* 🕵️ `/users` : Affiche la liste des personnes en ligne (géré automatiquement par l'interface Web !).
* 🎭 `/nick <nouveau_nom>` : Envie d'une nouvelle identité ? Changez de pseudo à la volée.
* 🏃 `/quit` : Ferme proprement votre session (sur le terminal).

---

## 🗺️ La Roadmap

TeleChat est en constante évolution. Voici où nous en sommes :

**✅ Déjà implémenté :**
- Architecture réseau asynchrone non-bloquante.
- Protocole binaire strict (Header + Payload) ultra-léger.
- Interface Ncurses scindée et multithreadée.
- WebSockets et UI HTML5 avec barre latérale dynamique.
- Système de salons (Channels) et de messages privés.

**🚧 Prochaines étapes :**
- [ ] **Indicateur de frappe** : Voir quand vos amis sont en train d'écrire.
- [ ] **Historique (Catch-up)** : Ne ratez plus les messages envoyés avant votre connexion grâce à un Ring Buffer en mémoire.
- [ ] **Sécurité & Base de données** : Inscription et authentification avec SQLite et mots de passe hachés.

---