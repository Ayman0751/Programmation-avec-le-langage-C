// le programme ci dessous est une simulation du jeu démineur que j ai decide d ecrire en language C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<assert.h>

#define MAX_LENGTH 120
#define LIGNES 8
#define COLONNES 8
#define BOMBS 10

// les couleurs d'écriture 

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//  la grille ci dessous est celle a remplir par des bombes 
char grille[LIGNES][COLONNES] = {   {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},           
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '}   };
//  la grille ci dessous est celle qui sera afficher au joueur (et qui contient le nombre de bombes voisines)
char G_aff[LIGNES][COLONNES] =  {   {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '},
                                    {' ',' ',' ',' ',' ',' ',' ',' '}   };


void centrer(const char *str);
void Jouer(char grille[][COLONNES]);
void Principe();
void Credit();
void menu();
void init_grille(char grille[][COLONNES]);
void aff_grille( char grille[][COLONNES]);
int count_bombs(int n , int p , char grille[][COLONNES]);

void Jouer(char G_aff[][COLONNES]){
    int won = 1;
    int count = 0 ; 
    int choix_n , choix_p;
    system("clear");
    centrer("Jouer\n\n");
    init_grille(grille);
    aff_grille(G_aff);
    aff_grille(grille);
    do{
        printf("saisir une case : \n");
        scanf("%d %d",&choix_n,&choix_p);
        if (grille[choix_n][choix_p] == 'X'){
            won = 0;
        }
        else{
            G_aff[choix_n][choix_p] = 'O';
        }
        printf("le nombre de bombes voisines est : %d\n",count_bombs(choix_n,choix_p,grille));
        aff_grille(G_aff);
        count ++;
    } while (won && count < LIGNES*COLONNES - BOMBS);
    if (!won){
        printf("Vous avez perdu :(\n\n");
        aff_grille(grille);
        sleep(3);
        exit(EXIT_FAILURE);
    }
    else{
        printf("Félicitation vous avez Gagné :)\n\n");
        sleep(3);
        system("clear");
        menu();
    }
}

int count_bombs(int n , int p , char grille[][COLONNES]){
    int result = 0 ; 
    if (n==0 && p==0){
        if (grille[0][1]=='X'){result ++;}
        if (grille[1][0]=='X'){result ++;}
        if (grille[1][1]=='X'){result ++;}
    }
    if (n==0 && p==COLONNES-1){
        if (grille[0][COLONNES-2]=='X'){result ++;}
        if (grille[1][COLONNES-2]=='X'){result ++;}
        if (grille[1][COLONNES-1]=='X'){result ++;}
    }
    if (n==LIGNES-1 && p==0){
        if (grille[LIGNES-1][1]=='X'){result ++;}
        if (grille[LIGNES-2][0]=='X'){result ++;}
        if (grille[LIGNES-2][1]=='X'){result ++;}
    }
    if (n==LIGNES-1 && p==COLONNES-1){
        if (grille[LIGNES-1][COLONNES-2]=='X'){result ++;}
        if (grille[LIGNES-2][COLONNES-2]=='X'){result ++;}
        if (grille[LIGNES-2][COLONNES-1]=='X'){result ++;}
    }
    if(p == 0 && n>0 && n<LIGNES-1){
        if (grille[n-1][1]=='X'){result ++;}
        if (grille[n][1]=='X'){result ++;}
        if (grille[n+1][1]=='X'){result ++;} 
        if (grille[n-1][0]=='X'){result ++;}
        if (grille[n+1][0]=='X'){result ++;}
    }
    if(p == COLONNES-1 && n>0 && n<LIGNES-1){
        if (grille[n-1][COLONNES-2]=='X'){result ++;}
        if (grille[n][COLONNES-2]=='X'){result ++;}
        if (grille[n+1][COLONNES-2]=='X'){result ++;} 
        if (grille[n-1][COLONNES-1]=='X'){result ++;}
        if (grille[n+1][COLONNES-1]=='X'){result ++;}
    }
    if(n == 0 && p>0 && p<COLONNES-1){
        if (grille[0][p-1]=='X'){result ++;}
        if (grille[0][p+1]=='X'){result ++;}
        if (grille[1][p-1]=='X'){result ++;} 
        if (grille[1][p]=='X'){result ++;}
        if (grille[1][p+1]=='X'){result ++;}
    }
    if(n == LIGNES-1 && p>0 && p<COLONNES-1){
        if (grille[LIGNES-1][p-1]=='X'){result ++;}
        if (grille[LIGNES-1][p+1]=='X'){result ++;}
        if (grille[LIGNES-2][p-1]=='X'){result ++;} 
        if (grille[LIGNES-2][p]=='X'){result ++;}
        if (grille[LIGNES-2][p+1]=='X'){result ++;}
    }
    else{
        for(int i = n-1 ; i<n+2 ; i++){
            for(int j=p-1 ; j<p+2 ;j++){
                if ((i!= n || j!= p) && grille[i][j] == 'X'){
                    result ++;
                }
            }
        }
    }
    return result;
}

void aff_grille(char G_aff[LIGNES][COLONNES]){

   printf("\n+---+---+---+---+---+---+---+---+\n");
    for (int i = 0 ; i < LIGNES ; i++ ){
        printf("|");
        for(int j = 0 ; j < COLONNES ; j++ ){
            printf(" %c |",G_aff[i][j]);
        }
        printf("\n+---+---+---+---+---+---+---+---+\n");
    } 
    return ;
}

void init_grille( char grille[][COLONNES] ){

    int n_alea , p_alea ;
    int count = BOMBS ; 
    srand(time(NULL));
    while (count != 0){
        n_alea = rand()%8; 
        p_alea = rand()%8;
        count --;
        grille[n_alea][p_alea] = 'X';
    }

}

void centrer(const char *str){
    for (int count = 0; count < (MAX_LENGTH - strlen(str))/2 ; count ++){
        putchar(' ');
    }
    printf("%s",str);
}

void Principe(){
    int choix;
    system("clear");
    centrer("Principe de jeu\n\n");
    printf("Le jeu de démineur est un jeu de logique basé sur une grille de cases, certaines contenant des mines et d'autres non.\nLe but du jeu est de découvrir toutes les cases sans mines (gagner) tout en évitant de déclencher une mine (perdre).\nLe jeu commence par une grille cachée, et le joueur choisit une case pour la révéler.\nSi la case révélée contient une mine, le joueur perd immédiatement.\nSi la case est vide, elle affiche un nombre qui indique combien de mines se trouvent dans les cases voisines (horizontalement, verticalement et en diagonale).\nLe joueur peut utiliser ces indices pour déterminer l'emplacement des mines. Si le joueur révèle toutes les cases sans mines,\nil gagne la partie.Le démineur est un jeu de réflexion qui nécessite de la logique et de l'observation \npour éviter les mines et découvrir toutes les cases en toute sécurité.");
    printf("\n\n");
    puts("\t1• retour");
    puts("\t2• Exit");
    scanf("%d",&choix);
    switch(choix){
        case 1 : 
            menu();
            break;
        case 2 : 
            exit(EXIT_FAILURE);
            break;
        default: 
            system("clear");
            printf("assurer vous de saisir soit 1 soit 2 !\n");
            sleep(3);
            Principe();
    }
}

void Credit(){
    int choix;
    system("clear");
    centrer("Crédit:");
    printf("\n");
    printf("Ce jeu (démineur) à été développé par :\nAHMED BADI\nDate de 01/09/2023\nvoici mon mail:\npersonnel : ahmedbadi905@gmail.com\nscoalire : Ahmed.BADI@etu.uca.fr\nbon Journée/Soirée :)\n");
    printf("choisir:\n");
    puts("\t1• retour");
    puts("\t2• Exit");
    scanf("%d",&choix);
    switch(choix){
        case 1 : 
            menu();
            break;
        case 2 : 
            exit(EXIT_FAILURE);
            break;
        default: 
            system("clear");
            printf("assurer vous de saisir soit 1 soit 2 !\n");
            sleep(3);
            Credit();
    }
}

void menu(){
    int choix ;
    system("clear");
    printf("Veuillez choisir une options des 4 ci-dessous:\n\n");
    puts("\t1• Jouer");
    puts("\t2• Principe du jeu");
    puts("\t3• Credit");
    puts("\t4• Exit");

    scanf("%d",&choix);

    switch(choix){
        case 1 : 
            Jouer(G_aff);
            break;
        case 2 : 
            Principe();
            break;
        case 3 : 
            Credit();
            break;
        case 4 : 
            exit(EXIT_FAILURE);
            break;
        default : 
            system("clear");
            menu();
            break;
    }
}


/* ------------------  Le Programme Principale ------------------- */
int main(){

    system("clear");
    centrer("***********************************\n");
    centrer(" * Binevenue dans le jeu Démineur  *\n");
    centrer("***********************************\n");
    printf("\n");
    
    menu();

    return 0;
}