#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<time.h>

#define CONSOLE_LENGTH 82

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char grille[6][7]={ {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '},
                    {' ',' ',' ',' ',' ',' ',' '}  };


void centrer(char *str);
void startGame_1VS1(int tourJ1,int tourJ2);
void startGame_1VSmachine(int tourJ,int tourOrdi);
void init_grille();
void aff_grille(int n,char grille[][7],char color);
int est_pleine_grille(char grille[][7]);
int est_pleine_colonne(char grille[][7],int p);
void egalite();
int est_4horizontales(char grille[][7],char color);
int est_4verticales(char grille[][7],char color);
int est_4diagonales(char grille[][7],char color);
void remplir_case_bas(int p,char grille[][7],char color);
int chaque_verticale(char grille[][7],int p,char color);
int chaque_horizontale(char grille[][7],int n,char color);

void centrer(char *str){
    for(int count=0;count<(CONSOLE_LENGTH-strlen(str))/2;count++){
        putchar(' ');
    }
    printf("%s",str);
}

int chaque_verticale(char grille[][7],int p,char color){
    if( (grille[0][p]==grille[1][p] && grille[0][p]==grille[2][p] && grille[0][p]==grille[3][p] && grille[0][p]==color) ||
        (grille[1][p]==grille[2][p] && grille[1][p]==grille[3][p] && grille[1][p]==grille[4][p] && grille[1][p]==color) ||
        (grille[2][p]==grille[3][p] && grille[2][p]==grille[4][p] && grille[2][p]==grille[5][p] && grille[2][p]==color) ){
            return 0;
    }
    return 1;
}

int chaque_horizontale(char grille[][7],int n,char color){
   if(  (grille[n][0]==grille[n][1] && grille[n][0]==grille[n][2] && grille[n][0]==grille[n][3] && grille[n][0]==color) ||
        (grille[n][1]==grille[n][2] && grille[n][1]==grille[n][3] && grille[n][1]==grille[n][4] && grille[n][1]==color) ||
        (grille[n][2]==grille[n][3] && grille[n][2]==grille[n][4] && grille[n][2]==grille[n][5] && grille[n][2]==color) ||
        (grille[n][3]==grille[n][4] && grille[n][3]==grille[n][5] && grille[n][3]==grille[n][6] && grille[n][3]==color)){
            return 0;
    }
    return 1; 
}

int est_4horizontales(char grille[][7],char color){
     for (int j=0;j<6;j++){
        if(chaque_verticale(grille,j,color) == 0){
            return 0;
        }
    }
    return 1;        // no four in raw (horizontalement)
}

int est_4verticales(char grille[][7],char color){
    for (int j=0;j<7;j++){
        if(chaque_verticale(grille,j,color) == 0){
            return 0;
        }
    }
    return 1;       // no four in raw (verticalement)
}

int est_4diagonales(char grille[][7],char color){
    int res=1;

   for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 3; j++) {
            if (grille[i][j] == color && grille[i+1][j+1] == color && grille[i+2][j+2] == color && grille[i+3][j+3] == color) {
                res=0;
            }
        }
    }

    
    for (int i = 0; i <= 2; i++) {
        for (int j = 3; j <= 6; j++) {
            if (grille[i][j] == color && grille[i+1][j-1] == color && grille[i+2][j-2] == color && grille[i+3][j-3] == color) {
                res=0;
            }
        }
    }
    return res;
}

void egalite(){
    printf("égalite :/\n");
    return;
}

void init_grille(){
   for(int i=0;i<6;i++){
        printf("-+---+---+---+---+---+---+---+-\n");
        for(int j=0;j<7;j++){
            printf(" | %c",grille[i][j]);
        }
        printf(" |");
        printf("\n");
    }
    printf("-+---+---+---+---+---+---+---+-\n");
}

void remplir_case_bas(int p,char grille[][7],char color){
    for(int i=6;i>=0;i--){
        if(grille[i][p] ==' '){
            grille[i][p]= color;
            break;
        }
    }
}

void aff_grille(int p,char grille[][7],char color){
    int nv_p;
    if(est_pleine_colonne(grille,p) != 0){
        printf("place invalide !\n");
        puts("essayer autre emplacement.\n");
        scanf("%d",&nv_p);
        aff_grille(nv_p,grille,color);
    }
    else{
        remplir_case_bas(p,grille,color);
    }

    for(int i=0;i<6;i++){
        printf("-+---+---+---+---+---+---+---+-\n");
        for(int j=0;j<7;j++){
            if(color == 'J'){
                printf(" | "ANSI_COLOR_YELLOW"%c"ANSI_COLOR_RESET,grille[i][j]);
            }
            else{
                printf(" | "ANSI_COLOR_RED"%c"ANSI_COLOR_RESET,grille[i][j]);
            }
        }
        printf(" |");
        printf("\n");
    }
    printf("-+---+---+---+---+---+---+---+-\n");
}

int est_pleine_colonne(char grille[][7],int p){
    for(int i=0;i<6;i++){
        if(grille[i][p] == ' '){
            return 0;
        }
    }
    return 1;                 // la colonne selectionnee est pleine
}

int est_pleine_grille(char grille[][7]){
    for(int j=0;j<7;j++){
        if(est_pleine_colonne(grille,j)==0){
            return 0;
        }
    }
    return 1;              // grille toute pleine
}

void startGame_1VS1(int tourJ1,int tourJ2){
    int color_choice;
    int n;
    char colorJ1,colorJ2;
    int won=0,tie=0;

    centrer("bienvenue dans le mode 1 VS 1\n");
    printf("choisir une des deux couleurs :\n\n");
    puts("1-Jaune");
    puts("2-Rouge");

    scanf("%d",&color_choice);
    assert(color_choice == 1 || color_choice == 2);
    system("clear");

    if(color_choice == 1){
        printf("Joueur 1: vous etes le "ANSI_COLOR_YELLOW "Jaune.\n" ANSI_COLOR_RESET);
        colorJ1='J';
        printf("Joueur 2: vous etes le "ANSI_COLOR_RED "Rouge.\n"ANSI_COLOR_RESET);
        colorJ2='R';
    }
    else{
        printf("Joueur 1: vous etes le "ANSI_COLOR_RED "Rouge.\n"ANSI_COLOR_RESET);
        colorJ1='R';
        printf("Joueur 2: vous etes le "ANSI_COLOR_YELLOW "Jaune.\n"ANSI_COLOR_RESET); 
        colorJ2='J';
    }
    printf("\n");
    do{
        if(tourJ1 == tourJ2){
            printf("Joueur 1: c est votre tour..\n");
            printf("choisir ou voulez vous insrez votre piece\n");
            scanf("%d",&n);
            assert(n>=1 && n<=7);

            aff_grille(n-1,grille,colorJ1);
            tourJ1++;

            if(est_4horizontales(grille,colorJ1)==0  || est_4verticales(grille,colorJ1)==0  || est_4diagonales(grille,colorJ1)==0){
                printf(ANSI_COLOR_GREEN"falicitation Joueur 1, vous avez gagne :)\n"ANSI_COLOR_RESET);
                won=1;
            }
            else if(est_pleine_grille(grille) == 1){
                egalite();
                tie=1;
            }
        }
        else{
            printf("Joueur 2: c est votre tour..\n");
            printf("choisir ou voulez vous insrez votre piece\n");
            scanf("%d",&n);
            assert(n>=1 && n<=7);

            aff_grille(n-1,grille,colorJ2);
            tourJ2++;
            
            if(est_4horizontales(grille,colorJ2)==0  || est_4verticales(grille,colorJ2)==0  || est_4diagonales(grille,colorJ2)==0){
                printf(ANSI_COLOR_GREEN"falicitation Joueur 2, vous avez gagne :)\n"ANSI_COLOR_RESET);
                won=1;
            }
            else if(est_pleine_grille(grille) == 1){
                egalite();
                tie=1;
            }
        }
    }while( !won && !tie);
    
}

void startGame_1VSmachine(int tourJ,int tourOrdi){
    srand(time(NULL));

    int color_choice;
    int n;
    char colorJ1,colorJ2;
    int won=0,tie=0;
    int alea;

    centrer("bienvenue dans le mode 1 VS machine\n");
    printf("choisir une des deux couleurs :\n");
    puts("1-Jaune");
    puts("2-Rouge");

    scanf("%d",&color_choice);
    assert(color_choice == 1 || color_choice == 2);
    system("clear");
    if(color_choice == 1){
        printf("Joueur 1(vous): vous etes le "ANSI_COLOR_YELLOW "Jaune.\n"ANSI_COLOR_RESET);
        colorJ1='J';
        printf("Joueur 2(ordi): vous etes le "ANSI_COLOR_RED "Rouge.\n"ANSI_COLOR_RESET);
        colorJ2='R';
    }
    else{
        printf("Joueur 1(vous): vous etes le "ANSI_COLOR_RED "Rouge.\n"ANSI_COLOR_RESET);
        colorJ1='R';
        printf("Joueur 2(ordi): vous etes le "ANSI_COLOR_YELLOW "Jaune.\n"ANSI_COLOR_RESET); 
        colorJ2='J';
    }

    do{
        if(tourJ == tourOrdi){
            printf(" c est votre tour..\n");
            printf("choisir ou voulez vous insrez votre piece\n");
            scanf("%d",&n);
            assert(n>=1 && n<=7);

            aff_grille(n-1,grille,colorJ1);
            tourJ++;

            if(est_4horizontales(grille,colorJ1)==0  || est_4verticales(grille,colorJ1)==0  || est_4diagonales(grille,colorJ1)==0){
                printf(ANSI_COLOR_GREEN"falicitation, vous avez gagne :)\n"ANSI_COLOR_RESET);
                won=1;
            }
            else if(est_pleine_grille(grille) == 1){
                egalite();
                tie=1;
            }
        }
        else{

            printf("c est le tour de l ordi..\n");

            alea=rand()%7;
            printf("l ordi a choisi le tube numero %d\n",alea);

            aff_grille(alea,grille,colorJ2);
            tourOrdi++;
            
            if(est_4horizontales(grille,colorJ2)==0  || est_4verticales(grille,colorJ2)==0  || est_4diagonales(grille,colorJ2)==0){
                printf(ANSI_COLOR_RED"vous avez perdu :(\n"ANSI_COLOR_RESET);
                won=1;
            }
            else if(est_pleine_grille(grille) == 1){
                egalite();
                tie=1;
            }
        }
    }while( !won && !tie); 
}

int main(){
    int choice;
    int mode;
    system("clear");
    sleep(1);
    centrer(ANSI_COLOR_BLUE"***********************\n"ANSI_COLOR_RESET);
    centrer(ANSI_COLOR_BLUE"          *"ANSI_COLOR_MAGENTA"     puissance 4     "ANSI_COLOR_BLUE"*\n"ANSI_COLOR_RESET);
    centrer(ANSI_COLOR_BLUE"***********************\n"ANSI_COLOR_RESET);  

    printf("\n");
    printf("\t\tBienvenue dans le jeux puissance 4.\n\n");
    puts("1-jouer");
    puts("2-principe du jeux");
    puts("3-credit");
    printf("\n");
    scanf("%d",&choice);
    
    assert(choice == 1 || choice == 2 || choice == 3);

    if(choice == 1){
        system("clear");
        sleep(1);
        printf("choisir une option:\n");
        puts("1- 1VS1");
        puts("2- 1VSmachine");
        printf("\n");
        scanf("%d",&mode);
        assert(mode == 1 || mode == 2);
        if(mode == 1){
            startGame_1VS1(0,0);
        }
        else{
            startGame_1VSmachine(0,0);
        }
    }
    else if(choice == 2){
        system("clear");
        sleep(2);
        puts("Le jeu Puissance 4 est un jeu de stratégie à deux joueurs.");
        puts("Le jeu se joue sur une grille de 6 lignes et 7 colonnes.");
        puts("Les joueurs alternent pour placer des jetons de leur couleur dans la colonne de leur choix.");
        puts("Le jeton tombe au bas de la colonne, à moins qu'il ne rencontre un autre jeton en descendant.");
        puts("L'objectif du jeu est d'aligner 4 jetons de sa couleur horizontalement, verticalement ou en diagonale.");
        puts("Le premier joueur qui y parvient gagne la partie.");
        printf("bon jeux :)\n");
    }
    else{
        system("clear");
        sleep(1);
        printf("Bonjour :)\n");
        puts("je m'appelle BADI Ahmed\n");
        puts("voici mon adresse mail pour me contacter pour toute sorte de conseil , aide ou propos ;)");
        puts("ahmedbadi905@gmail.com");
        puts("bon journéé :)");
        printf("\n");
    }

    return 0;
}