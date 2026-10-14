Titre: Déplacement du canon
Auteur: Pierre Fouilhoux

Affiche un écran de jeux et permet le déplacement d'un canon dans la fenêtre d'un terminal en utilisant un affichage ASCII

Installation: Utiliser la commance make pour utiliser le Makefile

Usage: Lancer ./main_jeu <largeur> <hauteur> <niveau de difficulté>
  <largeur> largeur de l'écran de jeu (au moins 20)
  <hauteur> hauteur de l'écran de jeu (au moins 20)
  <niveau de difficulté> permet de régler la difficulté du jeu (1 niveau le plus bas)

Important: pour jouer sur un grand écran, par ex (200, 100), il faut agrandir la fenêtre du terminal et réduire la police du terminal (CTRL-)


Ce programme consiste à faire afficher sur une partie du terminal une zone délimitée par un rectangle, appelé écran de jeu, ainsi qu'un canon en bas de l'écran.
Le canon peut être déplacé à gauche et à droite en utilisant les flèches du clavier.
Quand le canon arrive sur le bord de l'écran, il ne peut continuer dans cette direction.

Le niveau de difficulté est ici inutilisé.

Fin du jeu: touche ESC


Exercice 0 

Q 0.2

La boucle principale du jeu ce trouve dans MainLoop et c'est notament là que on se charge d'afficher les 
element du jeu et changer la variable KeyEvent  qui nous informe sur l'etat du jeu si elle est arreter 
ou continue et la bouble principale a pour condition tant que cette variable vaut CONTINUE le jeu est en cours.


Q 0.3 

La valeur -1 correspond a une absence de  presion 

Q 0.4 

Le champs pas est la vitess de deplacement du cannon sur la gauche et sur la gauche

c'est cette condition qui se charge de faire en sorte que le cannon reste bien dans les limites du jeu 
if ((canon->ypos < canon->pos_min) || (canon->ypos > canon->pos_max - canon->largeur)){
   canon->ypos = canon->ypos_old;
  }


Q 0.5
  on utiliser une chaine vide car le caractere vide n'est pas une chaine vide donc il va rien remplacer

Q 0.6
https://unicode.org/emoji/charts/full-emoji-list.html

Partie A fini 
Mtn je doit refaire le jeu avec un bibliotech graphic SDL
