#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include<unistd.h>

#define LENGTH_CONSOLE 120

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct score{
    int id;
    int score;
    char name[20];
}score_t;


void jeux_1VS1(char grille[][3],int tourJ1,int tourJ2);
void jeux_1VSordi(char grille[][3],int tourJ,int tour_Ordi);
void init_grille();
void aff_grille(int n,int p,char symbole,char grid[][3]);
int win(int joueur);
void centrer(const char *str);
int est_complete(char grille[][3]);
int est_horizontale(char grille[][3],char sym);
int est_verticale(char grille[][3],char sym);
int est_diagonale(char grille[][3],char sym);
void egalite();
int est_occupee(int n,int p,char grille[][3]);

char grid[3][3]={   {' ',' ',' '},
                    {' ',' ',' '},
                    {' ',' ',' '}   };


int est_complete(char grille[][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            if(grille[i][j]==' '){
                return 1;
            }
        }
    }
    return 0;
}

void egalite(){
    printf("egalité.\n");
    return ;
}

int win(int joueur){
        return joueur;
}

void init_grille(){

    printf("\n-+---+---+---+-\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf(" | %c",grid[i][j]);
        }
        printf(" |");
        printf("\n-+---+---+---+-\n");
    }
}

int est_occupee(int n,int p,char grille[][3]){
    if(grille[n][p]!=' '){
        return 1;
    }
    else{
        return 0;
    }
}

void centrer(const char *str){
    for(int count=0;count<(LENGTH_CONSOLE-strlen(str))/2;count++){
        putchar(' ');
    }
    printf("%s",str);
}

void aff_grille(int n,int p,char symbole,char grid[][3]){
    int a,b;
    if(grid[n][p] == ' '){
        grid[n][p]=symbole;
    }
    else{
        printf("place occupee !!\n");
        printf("entrer des cordonnee valables: ");
        scanf("%d %d",&a,&b);
        aff_grille(a,b,symbole,grid);
    }

    printf("\n-+---+---+---+-\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf(" | %c",grid[i][j]);
        }
        printf(" |");
        printf("\n-+---+---+---+-\n");
    }
}

void jeux_1VS1(char grille[][3],int tourJ1,int tourJ2){
    int n,p;
    int win_J1=0,win_j2=0;
    int egal=0;

    int sym_choisi;
    char symX='X';
    char symO='O';
    char symJ1,symJ2;
    centrer("bienvenue dans le mode joueur vs Ordinateur ;)\n\n");
    puts("grille vide :");
    printf("\n");

    init_grille();
    printf("\n");

    printf("vous choisissez vos symboles..\n");
    printf("J1-veuillez choisir entre X & O ..\n");
    printf("1- X\n");
    printf("2- O\n");

    scanf("%d",&sym_choisi);

    assert(sym_choisi==1 || sym_choisi==2);

    if(sym_choisi == 1){
        printf("J1- vous jouez avec %c\n",symX);
        symJ1=symX;
    }
    else{
        printf("J1- vous jouez avec %c\n",symO);
        symJ1=symO;
    }

    if(sym_choisi == 2){
        printf("J2- vous jouez avec %c\n",symX);
        symJ2=symX;
    }
    else{
        printf("J2- vous jouez avec %c\n",symO);
        symJ2=symO;
    }
    
    do{
        if(tourJ1 == tourJ2){
            printf("J1- c est votre tour de jouer ..\n");
            printf("choisir l'emplacement de votre symbole:\n");
            scanf("%d %d",&n,&p);

            assert((n>=0 && n<3) && (p>=0 && p<5));

            aff_grille(n,p,symJ1,grille);
            tourJ1++;
            if(est_verticale(grille,symJ1) == 0 || est_horizontale(grille,symJ1)==0 || est_diagonale(grille,symJ1)==0){
                printf(ANSI_COLOR_GREEN"felicitation Joueur %d vous avez gagné. :)\n"ANSI_COLOR_RESET,win(1));
                win_J1=1;
            }
            else if(est_complete(grille)==0){
                egalite();
                egal=1;
            }
        }
        else{
            printf("J2- c est votre tour de jouer ..\n");
            printf("choisir l'emplacement de votre symbole:\n");
            scanf("%d %d",&n,&p);
            aff_grille(n,p,symJ2,grille);
            tourJ2++; 
            if(est_verticale(grille,symJ2) == 0 || est_horizontale(grille,symJ2)==0 || est_diagonale(grille,symJ2)==0){
                printf(ANSI_COLOR_GREEN"felicitation Joueur %d vous avez gagné. :)\n"ANSI_COLOR_RESET,win(2));
                win_j2=1;
            }
            else if(est_complete(grille)==0){
                egalite();
                egal=1;
            }
        }
    }while((!win_J1 && !win_j2) && !egal);
}

void jeux_1VSordi(char grille[][3],int tourJ,int tour_Ordi){
    srand(time(NULL));
    int n_alea,p_alea;
    int choix;
    char symbJ,symb_Ordi;
    char symbX='X';
    char symbO='O';
    int n,p;
    int woon=0,equal=0;

    centrer("bienvenue dans le mode joueur vs Ordinateur ;)\n");
    init_grille();

    printf("choisir le symbole:\n");
    puts("1- X");
    puts("2- O");
    scanf("%d",&choix);
    assert(choix == 1 || choix == 2);

    if(choix == 1){
        symbJ=symbX;
        symb_Ordi=symbO;
    }
    else{
        symbJ=symbO;
        symb_Ordi=symbX;
    }

    do{
        if(tourJ == tour_Ordi){
            printf("c est votre tour de jouer.\n");
            puts("donner l'emplacement de votre prochaine symbole.\n");
            scanf("%d %d",&n,&p);

            assert((n>=0 && n<3) && (p>=0 && p<5));
            aff_grille(n,p,symbJ,grille);

            tourJ++;
            if(est_diagonale(grille,symbJ)==0 || est_horizontale(grille,symbJ)==0 || est_verticale(grille,symbJ)==0){
                printf(ANSI_COLOR_GREEN"felicitation vous avez gagne :)\n"ANSI_COLOR_RESET);
                win(1);
                woon=1;
            }
            else if(est_complete(grille)==0){
                egalite();
                equal=1;
            }
        }
        else{
            printf("c est le tour de l ordi...\n");
            n_alea=rand()%3;
            do{
                p_alea=rand()%3;
            }while(est_occupee(n_alea,p_alea,grille)==1);

            aff_grille(n_alea,p_alea,symb_Ordi,grille);
            tour_Ordi++;
            if(est_diagonale(grille,symb_Ordi)==0 || est_horizontale(grille,symb_Ordi)==0 || est_verticale(grille,symb_Ordi)==0){
                printf(ANSI_COLOR_RED"malheureusement vous avez perdu :(\n"ANSI_COLOR_RESET);
                win(1);
                woon=1;
            }
            else if(est_complete(grille)==0){
                egalite();
                equal=1;
            }
        }
    }while(!woon && !equal);
}

int est_horizontale(char grille[][3],char symbole){
    return( !((grille[0][0] == grille[0][1] && grille[0][0] == grille[0][2] && grille[0][0]==symbole) ||
              (grille[1][0] == grille[1][1] && grille[1][0] == grille[1][2] && grille[1][0]==symbole) ||
              (grille[2][0] == grille[2][1] && grille[2][0] == grille[2][2] && grille[2][0]==symbole)   ));
}

int est_verticale(char grille[][3],char symbole){
    return ( !((grille[0][0] == grille[1][0] && grille[0][0] == grille[2][0]  && grille[0][0]==symbole) ||
          (grille[0][1] == grille[1][1] && grille[0][1] == grille[2][1]  && grille[0][1]==symbole) ||
          (grille[0][2] == grille[1][2] && grille[0][2] == grille[2][2]  && grille[0][2]==symbole)  ));
}

int est_diagonale(char grille[][3],char symbole){
    return ( !( (grille[0][0] == grille[1][1] && grille[0][0] == grille[2][2]  && grille[0][0]==symbole) ||
                (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0]  && grille[0][2]==symbole)   ));
}


int main(){
    int pre_choix;
    int sec_choix;
    system("clear");
    sleep(1);
    
    centrer("***************\n");
    centrer("* tic_tac_toe *\n");
    centrer("***************\n");
    sleep(1);

    printf("veuillez choisir l'une des options suivants:\n");
    printf("1-regles de jeux\n");
    printf("2-qui veux jouer\n");
    printf("3-credit\n");


    scanf("%d",&pre_choix);
    printf("\n");
    if(pre_choix == 1){
        system("clear");
        sleep(1);
        printf("******      regles      ******\n\n");
        printf("le jeux tic-tac-toe ou autrement XO est une jeux classique pour laquelle:\n");
        printf("$-soit vous jouez avec un autre amie\n");
        printf("$-soit avec votre ordinateur\n\n");
        printf("avant de commencer vous choisissez le symbole que vous allez a chaque fois placer.\n");
        printf("il y a deux symboles    X & O.\n");
        printf("le jeux est a tour de role\n");
        printf("le gagnat est celui qui pourra placer ces symboles:\n");
        printf("$-verticalement\n");
        printf("$-horizontalement\n");
        printf("$-diagonalement\n\n");
        printf("Il y a une possibilitee d egalitee !!!\n");
        printf("bon jeux ;)\n");
    }

    else if(pre_choix == 2){
        system("clear");
        sleep(1);
        printf("veuillez choisir l'une des options ci dessout:\n");
        printf("1-\t1 VS 1\n");
        printf("2-\t1 VS ordi\n");
        scanf("%d",&sec_choix);
        if(sec_choix == 1){
            jeux_1VS1(grid,0,0);
        }
        else{
            jeux_1VSordi(grid,0,0);
        }
    }

    else{
        system("clear");
        sleep(1);
        puts("ce version de jeux tic-tac-toe a ete cree par :\n\n");
        centrer(ANSI_COLOR_BLUE"BADI Ahmed\n\n"ANSI_COLOR_RESET);
        puts("vous trouvez ci dessout mon adresse mail pour toutes sorte de conseil,question,proposition...\n");
        puts(ANSI_COLOR_YELLOW"ahmedbadi905@gmail.com\n"ANSI_COLOR_RESET);
        printf("bon journéé :)\n");
    }

    return 0;
}