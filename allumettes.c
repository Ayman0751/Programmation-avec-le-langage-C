#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LARGEUR_CONSOLE 80

void jeu1vs1(int n, int cpj1, int cpj2, int N);
void jeu1vsordi(int n, int cpj1, int cpj2, int N, int nv);
int win(int jgagnant, int nbjoueurs, int n, int nv);
int menu();
void menuall();
void menuj(int n);
void centrer (const char* str);
int regles();
int credits();

int main ()
{
    menu();
    return 0;
}

int menu()
{
    int choix;
    system("clear");
    printf("\n\n");
    centrer("**********************\n");
    centrer("* Jeu des allumettes *\n");
    centrer("**********************\n");
    printf("\n\n");
    centrer("Bonjour et bienvenue dans le jeu des allumettes\n");
    printf("\nVous allez avoir 3 menus.\nVous choisirez d'abord si vous voulez voir les regles du jeu ou non, puis le\nnombre d'allumettes a utiliser, et enfin le nombre de joueurs.\n\n");
    system("pause");
    system("clear");
    printf("\n    Que faire ?\n\n");
    printf("1 - Jouer\n");
    printf("2 - Voir les regles du jeu\n");
    printf("3 - Voir les credits\n");
    printf("4 - Quitter");
    printf("\n\nVotre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : menuall(); break;
        case 2 : regles(); break;
        case 3 : credits(); break;
        case 4 : return 0; break;
        default : printf("\nJe n'ai pas compris votre demande....");system("pause");menu();
    }
    return 0;
}

void menuall()
{
    system("clear");
    int n; int choix;
    printf("\n    Que faire ?\n\n");
    printf("1 - Utiliser un nombre aleatoire d'alumettes\n");
    printf("2 - Utiliser le nombre d'alumettes predefini (20)\n");
    printf("3 - Choisir le nombre d'allumettes\n");
    printf("\nVotre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : do{n=rand()%30;}while (n<11); break;
        case 2 : n=20 ; break;
        case 3 : printf("\nNombre d'allumettes a utliser : ");
                 scanf("%d", &n) ;
                 while (n<=10) {printf("IMPOSSIBLE ! \nNombre d'allumettes a utliser : ");scanf("%d", &n) ;} ;
                 break;
        default : system("clear");
                  printf("\nJe n'ai pas compris...\n\n");
                  menuall() ; break;
    }
    menuj(n);
}

void menuj(int n)
{
    system("clear");
    int choix, nv;
    printf("\n    Que faire maintenant ?\n\n");
    printf("1 - Jeu 2 joueurs\n");
    printf("2 - Humain VS ordinateur\n");
    printf("\nVotre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : jeu1vs1(n,0,0,n); break;
        case 2 :
            printf("\nChoisir entre 3 niveaux de difficulte\nNiveau : ");
            do {scanf("%d", &nv);} while ((nv<0)||(nv>3));
            system("clear");
            printf("Jeu contre l'ordinateur, niveau %d, avec %d allumettes au depart.\n\n", nv, n);
            if ((nv==3)&&(n==11)) printf("Bon, en fait t'as perdu d'avance, la, mais bon, essaye quand meme :P\n\n");
            jeu1vsordi(n,0,0,n, nv); break;
        default : system("clear");
                  printf("\nJe n'ai pas compris...\n\n");
                  menuj(n) ; break;
    }
}

void jeu1vs1(int n, int cpj1, int cpj2, int N)
{
    int j1, j2; int i;
    printf("\n");
    for (i=1;i<=n;i++) {printf("| ");}
    printf("     Il reste %d allumettes\n\n", n);
    if (cpj1==cpj2)
    {
        printf("J1 - Nombre d'allumettes a enlever : ");
        scanf("%d", &j1);
        if ((j1<0)||j1>3) {printf("\nOn ne peut pas faire ca... :/\n\n");jeu1vs1(n, cpj1, cpj2, N);}
        n=n-j1; cpj1++;
        if (n==1) {win(1,2,N, 0);}
        else {jeu1vs1(n, cpj1, cpj2, N);}
    }
    else
    {
        printf("J2 - Nombre d'allumettes a enlever : ");
        scanf("%d", &j2);
        if ((j2<0)||j2>3) {printf("\nOn ne peut pas faire ca... :/\n\n");jeu1vs1(n, cpj1, cpj2, N);}
        n=n-j2; cpj2++;
        if (n==1) {win(2,2,N, 0);}
        else {jeu1vs1(n, cpj1, cpj2, N);}
    }
}

void jeu1vsordi(int n, int cpj1, int cpj2, int N, int nv) // n=nbre allumettes en cours, cpj1, cpj2 = nbre de coups des joueurs, N = nbre allumettes au départ, nv=niveau
{
    int j1, j2; int i,k;
    printf("\n");
    for (i=1;i<=n;i++) {printf("| ");}
    if (n<=24) {k=48-2*n;}
    else {k=3;}
    for(i=1;i<=k;i++) {printf(" ");}
    printf("Il reste %d allumettes\n\n", n);
    if (cpj1==cpj2)
    {
        printf("J1 - Nombre d'allumettes a enlever : ");
        scanf("%d", &j1);
        if ((j1<=0)||j1>3) {printf("\nOn ne peut pas faire ca... :/\n\n");jeu1vsordi(n, cpj1, cpj2, N, nv);}
        n=n-j1; cpj1++;
        if (n==1) {win(1,1,N, nv);}
        else {jeu1vsordi(n, cpj1, cpj2, N, nv);}
    }
    else
    {
        if (nv==3)
        {
            if (n<=4) {j2=n-1;}
            else if ((n>5)&&(n<=8)) {j2=n-5;}
            else if (n%4==0) {j2=3;}
            else if (n%4==2) {j2=1;}
            else if (n%4==3) {j2=2;}
            else {do {j2=rand()%3;}while (j2==0);}
        }
        else if (nv==2)
        {
            if (n<=4) {j2=n-1;}
            else if (n%4==0) {j2=3;}
            else if (n%4==2) {j2=1;}
            else if (n%4==3) {j2=2;}
            else {do {j2=rand()%3;}while (j2==0);}
        }
        else
        {
            if (n==3) {do {j2=rand()%2;}while (j2==0);}
            if (n==2) {j2=1;}
            else {do {j2=rand()%3;}while (j2==0);}
        }
        printf("Ordi enleve %d allumettes\n", j2);
        n=n-j2; cpj2++;
        if (n==1) {win(3,1,N, nv);}
        else {jeu1vsordi(n, cpj1, cpj2, N, nv);}
    }
}

int win(int jgagnant, int nbjoueurs, int n, int nv)
{
    int choix;
    switch(jgagnant)
    {
        case 1 :
        case 2 : printf("\nBravo J%d, tu as gagne !", jgagnant); break;
        default : printf("\nOrdi a gagne !");
    }
    printf("\nQue faire?\n");
    printf("1 - Rejouer avec les memes parametres\n");
    printf("2 - Revenir au menu initial\n");
    printf("3 - Quitter");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 :
            if (nbjoueurs==2) {jeu1vs1(n,0,0,n);}
            else {jeu1vsordi(n,0,0,n, nv);}
            break;
        case 2 : menuall(); break;
        case 3 : return EXIT_SUCCESS; break;
        default : printf("\nJe n'ai pas compris...\n"); win(jgagnant, nbjoueurs, n, nv);
    }
    return 0;
}

void centrer (const char* str)
{
    unsigned int n;
    for (n = 0; n < (LARGEUR_CONSOLE-strlen(str)) / 2; n++)
    {
        putchar(' ');
    }
    printf("%s", str);
}

int regles()
{
    int choix;
    centrer("\n\nLe but du jeu est simple:");
    printf("\n\nCe jeu se joue a deux. Vous avez un nombre n d'allumettes.\n");
    printf("A tour de role, chacun des deux joueurs enleve entre 1 et 3 allumettes selon ce qu'il souhaite. Le perdant est celui qui doit enlever la derniere allumette.\n");
    printf("\nAttention, il existe 3 niveaux de difficulte en version humain vs ordi.\n");
    printf("Le 1er est plutot simple a battre, donc pour les debutants. Mais le dernier.....\n");
    printf("Contactez-moi si vous avez reussi (screenshot evidemment^^), mon e-mail est dans les credits !\n\n");
    printf("\n    Que faire ?\n\n");
    printf("1 - Jouer\n");
    printf("2 - Quitter");
    printf("\nVotre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : menuall(); break;
        case 2 : return 0; break;
        default : printf("\nJe n'ai pas compris votre demande....");system("pause");regles();
    }
    return 0;
}

int credits()
{
    int choix;
    centrer("\n\nCe jeu a ete realise par Virginie LE GUEN - BERTHEAUME");
    printf("\n\nPour me contacter : devtuto@gmail.com :D   Bon jeu !\n\n");
    printf("\n    Que faire ?\n\n");
    printf("1 - Jouer\n");
    printf("2 - Quitter");
    printf("\nVotre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1 : menuall(); break;
        case 2 : return 0; break;
        default : printf("\nJe n'ai pas compris votre demande....");system("pause");regles();
    }
    return 0;
}