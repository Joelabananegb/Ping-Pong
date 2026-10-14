#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#include "Canon.h"
#include "Affichage.h"
#include "Flechette.h"
#include "Canar.h"

// Liste des évènements possibles
enum evenement
{
  CONTINUE,
  ECHAP
};
    // CONTINUE: le jeu debute ou continue
    // ECHAP: la touche ESC a été utilisée
    // (on peut en ajouter d'autres (victoire etc)

/* Coeur du jeu contenant la boucle événementielle */
void MainLoop(int, int, int);
bool ChechColision(Canar *, Flechette *);
void SpawnCanar(ListeCanar *, int, int);
/***************************************/

int main(int argv, char **argc)
{
  srand(time(NULL));
  if (argv!=4)
  {
     printf("Usage: %s <largeur> <hauteur> <niveau de difficulté>\n", argc[0]);
     exit(2);
  }
  srand(time(NULL));
  MainLoop(atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));
  return EXIT_SUCCESS;
}

/***************************************/


void SpawnCanar(ListeCanar *canars, int largeur, int hauteur)
{
  int x = largeur - 2;                 // côté droit
  int y = rand() % (hauteur - 2) + 1;  // aléatoire dans écran

  AjouterCanar(canars, x, y);
}

void Interaction_Flechette_Canard(ListeFlechette *Lflech, ListeCanar *Lcanard)
{
    Flechette *f = Lflech->head;
    Flechette *prevF = NULL;

    while (f != NULL)
    {
        Canar *c = Lcanard->head;
        Canar *prevC = NULL;

        int collision = 0;

        while (c != NULL)
        {
            if (f->x == c->x && f->y == c->y)
            {
                // 🔥 supprimer le canard
                if (prevC == NULL)
                    Lcanard->head = c->next;
                else
                    prevC->next = c->next;

                Canar *tmpC = c;
                c = c->next;
                free(tmpC);

                collision = 1;
                break;
            }
            else
            {
                prevC = c;
                c = c->next;
            }
        }

        if (collision)
        {
            // 🔥 supprimer la fléchette
            if (prevF == NULL)
                Lflech->head = f->next;
            else
                prevF->next = f->next;

            Flechette *tmpF = f;
            f = f->next;
            free(tmpF);
        }
        else
        {
            prevF = f;
            f = f->next;
        }
    }
}

void MainLoop(int tailleL, int tailleH, int nivdiff){

  int ch;   /* Récupération de la saisie clavier, valeur # pour fin de jeu */
  enum evenement KeyEvent; /* Retour des évènements  */

  /* Initialisation de ncurses et du clavier(4*/
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  halfdelay(1);  /* Temps d'exécution max de getch à 1/10ème de seconde */
  int spawnCanarCompteur = 0;
  int spawnInterval = 15; // plus petit = plus rapide
  
  /* Initialisation des éléments du jeu */
  
  KeyEvent = CONTINUE;
  
  Affichage *grille = AffichageInitialiser(tailleL, tailleH);
  Canon *canon = CanonInitialiser(0, tailleL, tailleH);
  ListeFlechette *Flechettes = ListeFlechetteInit(tailleH, nivdiff);
  ListeCanar *Canars = ListeCanarInit(nivdiff);

  enum action_canon actionCanon;


  /* Boucle événementielle du jeu */ 
  do
  {
    spawnCanarCompteur++; 
    ch = getch(); /* Si aucune touche utilisée, getch renvoie -1 */   

    AffichageVider(grille);
    AffichageCadre(grille);
    CanonAfficher(canon, grille);    
    // Autre affichage
    AfficherCanar(Canars, grille);
    FlechetteAction(Flechettes);
    AfficherFlechette(Flechettes, grille);
    CanarAction(Canars);
    Interaction_Flechette_Canard(Flechettes, Canars);

    if (spawnCanarCompteur >= spawnInterval)
    {
      SpawnCanar(Canars, tailleH - 20, tailleL - 10);
      spawnCanarCompteur = 0;
      if (spawnInterval > 5) spawnInterval--;
    }

    AffichageDessiner(grille);
    printf("Pour jouer: utiliser les flèches, SPACE pour tirer (ESC pour Sortir)\33[1E\33[1E");
    fflush(stdout);  /* Force l'affichage complet	 */

    
      
    if (ch != -1)
    { /* Si une touche a été appuyée */

     switch(ch) 
      {  
        case 27:  /* Code ASCII de la touche ESC-Echap */
           KeyEvent = ECHAP;
           break;                  
        case KEY_LEFT: 
           actionCanon = Gauche_canon;
           break; 
        case KEY_RIGHT: 
           actionCanon = Droite_canon;
           break;
        case 32:  /* Code ASCII de la touche ESPACE */
           actionCanon = Tir;
           break;        
        default:
           break;           
       }
       if (KeyEvent != ECHAP)
      { // Zone des actions dirigeant un élément
          CanonAction(canon, actionCanon, Flechettes);      
      }
     }
     
     // Zone des actions d'éléments agissant automatiquement
     // Comme les fléchettes et les canards

  }while (KeyEvent == CONTINUE);
  
     
  if (KeyEvent == ECHAP)
  {
      printf("\n\nVous avez taper ESC pour sortir. \33[1E\n");
  }

  printf("\33[1EAppuyez sur une touche pour sortir\33[1E\n");          

  do
  {
      ch = getch();
  }while( ch == -1);
  
  endwin(); /* Doit obligatoirement etre mis en fin de programme pour remettre le terminal en etat */  
  AffichageDesallouer(&grille);  
  CanarDesallouer(&Canars);
  FlechetteDesallouer(&Flechettes);
  CanonDesallouer(&canon);
 }
