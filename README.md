# Author: Kadra Junior Gassama

# Partie A

## Exercice 0

### Q) 0.2

La boucle principale du jeu se trouve dans `MainLoop`. C’est notamment à cet endroit que l’on se charge d’afficher les éléments du jeu et de modifier la variable `KeyEvent`, qui nous informe sur l’état du jeu : arrêté ou en cours d’exécution.

La boucle principale fonctionne tant que cette variable vaut `CONTINUE`, ce qui signifie que le jeu est toujours en cours.

### Q) 0.3

La valeur `-1` correspond à une absence de pression.

### Q) 0.4

Le champ `pas` représente la vitesse de déplacement du canon vers la gauche et vers la droite.

Cette condition permet de s’assurer que le canon reste bien dans les limites du jeu :

```c
if ((canon->ypos < canon->pos_min) ||
    (canon->ypos > canon->pos_max - canon->largeur)) {
    canon->ypos = canon->ypos_old;
}
```

### Q) 0.5

On utilise une chaîne vide, car le caractère vide n’est pas une chaîne vide. Ainsi, rien ne sera remplacé.

### Q) 3.1

On place `Interaction_Flechette_Canard()` dans le `main` afin de pouvoir accéder aux structures de la fléchette et du canard en même temps.

# Partie B

Pour mon amélioration du jeu, je suis parti sur un projet inspiré de *Space Invaders*, car il fait partie de la liste des projets que je souhaite réaliser.

Ici, j’utilise SDL pour les graphismes, plus précisément `SDL2` avec `SDL2_image` et `SDL2_ttf`. Il faut donc installer SDL2 ainsi que les composants nécessaires au fonctionnement du jeu.

Pour lancer le jeu, il est conseillé d’utiliser la commande :

```bash
make run
```

Cela permet d’éviter certains faux positifs liés à SDL.

Une fois le jeu lancé, vous pouvez vous déplacer avec les touches directionnelles, utiliser la touche `Espace` pour tirer et la touche `Échap` pour mettre le jeu en pause.

## Détails du jeu

Pour l’instant, le jeu est jouable. Il contient un score ainsi que deux niveaux.

Dans le futur, il faudra :

- ajouter d’autres niveaux plus difficiles ;
- ajouter des animations ;
- permettre au joueur de réapparaître après un *Game Over*, ce qui n’est actuellement pas possible.


# Tutoriel : Installation SDL2

## Installation sous Linux Debian Based distro

Installer SDL2 ainsi que les bibliothèques nécessaires avec la commande suivante 
```bash
sudo apt update

sudo apt install libsdl2-dev \
libsdl2-image-dev \
libsdl2-ttf-dev
```
