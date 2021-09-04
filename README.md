# projet-M5StickC
Repo du projet de montre connectée avec un M5StickC et un capteur de pouls

### Objectifs

- Lire les données du capteur de pouls
- Détécter la chute de l'appareil
- Envoyer un mail quand on appuye sur le bouton
- Jouer du son sur le haut parleur

### Fichiers Projet Arduino

- projet.ino: contient le code source
- credentials_example.h: exemple de fichier credentials.h, contenant des données sensibles
- credentials.h (**A CREER**): fichier contenant les données sensibles (mot de passes et identifiants de connexion)

### Librairies utilisées (a.k.a: triche)

Voici la liste des librairies utilisées dans le code source (à installer avant de build)

- Librairie M5StickC: Librairie contenant les fonctions permettant d'utiliser les diverses parties du M5StickC ([Lien](https://github.com/m5stack/M5StickC))
- ESP32 Email client: Wrapper permettant d'envoyer des E-Mails à l'aide de l'ESP32 ([Lien](https://github.com/mobizt/ESP32-Mail-Client))
- WiFi.h et WiFiMulti.h: Librairies permettant de faciliter la connexion à un réseau WiFi

# Build le projet

## Prérequis

- L'IDE Arduino (ou autre IDE compatible avec les librairies et gestionnaire de cartes Arduino)
- M5StickC (pas modèle plus)

## Installation du driver (Windows)

Lors de la première connexion avec un ordinateur Windows, il faut installer les drivers nécéssaires à la reconnaisance de la carte par l'IDE. 

1. Télécharger les drivers avec ce [lien](https://ftdichip.com/drivers/vcp-drivers/) et extraire les fichiers dans un dossier 
2. Brancher la carte à l'ordinateur
3. Ouvrir le gestionnaire de périphériques
4. Dans la catégorie "Autres Appareils", repérer la carte, normalement nommée ```M5Stack``` ou ```USB Serial``` 
5. Clic Droit -> Mettre à jour le pilote
![Image Périphérique](https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/minicore/m5stickc/ftdi_01.webp "Image")
6. Cliquer sur "Parcourir mon poste de travail pour rechercher des pilotes"
7. Cliquer sur "Parcourir" puis sélectionner le dossier dans lequel les pilotes ont été extraits à l'étape n°1
8. Cliquer sur Suivant, puis une fois la procédure terminée, cliquer sur Fermer

Dans le cas où la carte se trouve toujours dans la catégorie "Autres Appareils", répéter les étapes 5 à 8 une deuxième fois pour terminer l'installation des pilotes. ([Plus d'infos](https://docs.m5stack.com/en/core/m5stickc))

Lorsque le pilote sera correctement installé, la carte s'affichera dans la catégorie "Ports (COM et LTP)" et contiendra l'identifiant du port sur lequel la carte est branchée (qu'il faut reternir par la suite), comme "COM3" par exemple.

## Installation des librairies et des cartes M5Stack

Avant de pouvoir build le projet, il faut installer les différentes librairies et cartes nécessaires.

### Librairies

Dans le gestionnaire de librairies de votre IDE (sous Arduino IDE: Croquis -> Inclure une bibliothèque -> Gérer les bibliothèques), rechercher les bibliothèques suivantes et les installer:

- M5StickC
- ESP32 Mail Client

### Cartes

Pour installer les cartes M5Stack, il faut d'abord ajouter le lien officiel d'installation dans l'IDE (sous Arduino IDE: Fichier -> Préférences -> URL de gestionnaire de cartes supplémentaires). Il faut y ajouter le lien:
 `https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json`

 Ensuite, se rendre dans le gestionnaire de cartes de votre IDE (sous Arduino IDE: Outils -> Type de carte -> Gestionnaire de carte) puis chercher et installer `M5Stack`

 ## Compiler et transférer le projet

 Dans un répertoire choisi pour stocker le code, exécuter la commande:
 `git clone https://github.com/titouan-loiseau/projet-M5StickC.git .`

 Ensuite, ouvrir le projet nommé "projet" dans l'IDE. Créer un nouveau fichier header nommé `credentials.h`, puis y coller le contenu du fichier `credentials_example.h` en remplacant les valeurs par les votre. 

 Avant de compiler et de transférer le projet, vérifer que le type de carte est bien réglé sur `M5Stick-C`, et le port sur l'identifiant du port vu lors de l'installation des pilotes. Ensuite, cliquer sur le bouton "Transférer" (sous Arduino IDE). Une fois le transfer effectué, la console affichera `Hard resetting via RTS pin...` et la carte se réinitialisera avec son nouveau code. 