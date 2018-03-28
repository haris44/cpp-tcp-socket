Cet exercice a pour but de démontrer l'usage de programmation en
multithread pour améliorer les performances d'un programme, et
d'explorer les compromis à faire.

En groupes de 2 à 4 personnes, vous travaillerez sur un client
et un serveur pour un protocole de messagerie.

## Fonctionnement du serveur

Le serveur fournit un salon de discussion commun à tous les clients
connectés. Tout message envoyé par un client sera envoyé à tous les
autres. Au démarrage de la connexion, le client enverra le nom
d'utilisateur par la commande `USER`. Le client pourra ensuite
recevoir les messages provenant d'autres utilisateurs, ainsi
qu'envoyer ses propres messages par la commande `MSG`.

**Explorez plusieurs solutions permettant de gérer de nombreux
clients en même temps**:

- solution naïve: le serveur passe en boucle sur toutes les sockets
pour vérifier si elles ont des messages (marquer la socket comme
"non bloquante" pour ce test)
- à chaque nouvelle connexion d'un client, créer un thread pour gérer
cette connexion. Comment gérer l'envoi des messages entre threads?
Combien de clients pouvez-vous gérer en même temps?
- même principe que la connexion précédente, mais cette fois en employant
un pool de threads déjà créés. Obtenez-vous un gain de performances par
rapport à la solution précédente?
- testez un serveur en single thread utilisant la fonction
[`poll()`](http://man7.org/linux/man-pages/man2/poll.2.html)
pour surveiller plusieurs sockets en même temps. Combien de clients
pouvez-vous gérer en même temps sur un seul thread?

## Fonctionnement du client

Le client attend au démarrage une première entrée de l'utilisateur
pour indiquer son nom. Le nom sera utilisé pour indiquer son
identité au server par la commande `USER`.
Après avoir indiqué le nom, le client pourra recevoir des messages
du serveur à tout moment, et l'utilisateur pourra envoyer des
messages à tout moment. Les messages seront affichés avec le nom
de l'utilisateur qui l'a envoyé.

**Trouvez une solution permettant d'afficher les messages reçus alors
que l'utilisateur peut être au milieu de l'écriture d'un message.**

## Code fourni

Pour démarrer l'exercice plus rapidement, des exemples de code pour
le client et le serveur sont fournis, ainsi qu'un fichier `Makefile`
permettant de tout compiler en même temps (lancez la compilation en
ligne de commande par la commande `make`).

## Protocole de communication

### Client vers serveur

`USER nom_d_utilisateur\n`: indique au serveur le nom d'utilisateur
choisi par le client. Le nom d'utilisateur ne doit pas contenir d'espace.
`MSG contenu_du_message\n`: envoie un message sur le salon de discussion.
Le message ne doit pas contenir de sauts de ligne

### Serveur vers client

`MSG nom_d_utilisateur contenu_du_message`: contient un message envoyé
par un autre utilisateur

## Debug et développement

Vous pouvez utiliser la commande [`netcat`](https://en.wikipedia.org/wiki/Netcat)
pour tester le client et le serveur, notamment sous une charge plus élevée.
