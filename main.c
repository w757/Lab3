#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pion (char tab[3][3], int y, char znak){            //Funkcjcje sprawdzające czy nikt nie wygrał
    int l=0;                                            //sumują czy dany znak wystąpił 3 razy w danej lini
    for(int i=0; i<3; i++){
            if(tab[i][y]==znak) l++;
        }
        return l;
}

int poziom (char tab[3][3], int x, char znak){
    int l=0;
    for(int i=0; i<3; i++){
            if(tab[x][i]==znak) l++;
        }
        return l;
}

int ukos1 (char tab[3][3], char znak){
    int l=0;
    for(int i=0; i<3; i++){
        if(tab[i][i]==znak)l++;
    }
    return l;
}

int ukos2 (char tab[3][3], char znak){
    int l=0;
    for(int i=2; i>=0; i--){
        if(tab[i][2-i]==znak)l++;
    }
   return l;
}

int losowanie_ruchu (char plansza[3][3]){       //Komputer spawdza czy nie ma sytuaci zwiększającej szanse na jego wygraną

    int pion=0,  poziom=0, ukos_1=0, ukos_2=0, z;

    for (int i=0; i<3; i++){                    //Sprawdzenie czy nie ma ruchu, który pozwoli mu wygrać
         pion=0,  poziom=0;
         for (int j=0; j<3; j++){

             if (plansza[i][j]=='X'){
                   poziom++;
                   if(poziom==2) {

                       z=0;
                       while (plansza[i][z]!='-' && z<3){
                       z++;
                   }
                   if(plansza[i][z]=='-') return (10*i)+z;}
                }
             if (plansza[j][i]=='X'){
                   pion++;
                   if(pion==2) {

                       z=0;
                       while (plansza[z][i]!='-' && z<3){
                       z++;
                  }
                  if(plansza[z][i]=='-') return (10*z)+i;}


            }
         }
    }

    for(int i=0; i<3; i++){
        if(plansza[i][i]=='X')ukos_1++;
        if(ukos_1==2){
            z=0;
            while(plansza[z][z]!='-' && z<3){
                z++;
            }
            if(plansza[z][z]=='-') return (10*z)+z;
        }
    }
    for(int i=0; i<3; i++){
        if(plansza[i][2-i]=='X')ukos_2++;
        if(ukos_2==2){
            z=0;
            while(plansza[z][2-z]!='-' && z<3){
                z++;
            }
            if(plansza[z][2-z]=='-') return (10*z)+(2-z);
        }
    }


    for (int i=0; i<3; i++){                    //Sprawdzanie czy nie ma ruchu który uniemożliwi wygraną przeciwnikowi
          pion=0,  poziom=0;
          for (int j=0; j<3; j++){

              if (plansza[i][j]=='O'){          //Szukanie lini w której występują dwa takie same znaki (dla 3 gra się już zakończyła)
                    poziom++;                   //jeśli w którejś lini są dwa takie same znaki szukamy wolnego miejsca jeśli je znajdziemy
                    if(poziom==2) {             //kończymy funkcje (analogiczny proces dla wszystkiego w funkkcji)

                        z=0;
                        while (plansza[i][z]!='-' && z<3){
                        z++;
                     }
                     if(plansza[i][z]=='-')return (10*i)+z;}
                }
               if (plansza[j][i]=='O'){
                       pion++;
                       if(pion==2) {

                            z=0;
                            while (plansza[z][i]!='-' && z<3){
                            z++;
                     }
                     if(plansza[z][i]=='-')return (10*z)+i;}
                  }
              }
     }

    for(int i=0; i<3; i++){
        if(plansza[i][i]=='O')ukos_1++;
        if(ukos_1==2){
            z=0;
            while(plansza[z][z]!='-' && z<3){
                z++;
            }
            if(plansza[z][z]=='-') return (10*z)+z;
        }
    }

    for(int i=0; i<3; i++){
        if(plansza[i][2-i]=='O')ukos_2++;
        if(ukos_2==2){
            z=0;
            while(plansza[z][2-z]!='-' && z<3){
                z++;
            }
            if(plansza[z][2-z]=='-') return (10*z)+(2-z);
        }
    }


     return 5;
}

void wyswietlanie_planszy(char plansza[3][3])
{
    printf("\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%c ", plansza[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    srand(time(NULL));
    int x, y;
    char plansza[3][3];
    char znak='O';

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++)
        plansza[i][j]='-';
    }

    for (int i=0; i<9; i++){

        if(znak=='O'){
            printf("Twój ruch. Podaj dwie wspólrzedne (pion, poziom): \n");
            scanf("%i  %i", &x, &y);
            x=x-1;
            y=y-1;
        }

        else
        {    //Wygląda to dziwnie ale narzaie potrafie zwrócić z funkcji tylko jedną zmienną :)
            if(losowanie_ruchu(plansza)!=5) {y=losowanie_ruchu(plansza)%10; x=(losowanie_ruchu(plansza)-y)/10;}

            //Losowanie miejsca w funkcji kiedy zastosowanie funkcji nie zwiększa szans na wygraną
            else{
                 while(plansza[x][y]!='-'){
                    x=rand()%3;
                    y=rand()%3;
                    }
            }
        }

        if (plansza[x][y]!='-'){
            printf("Wybrano błędne miejsce, powtórz ruch! \n");
            --i;
        }
        //Jeśli ruch nie był błędny sprawdzamy czy ktoś nie wygrał
        else {
            plansza[x][y]=znak;
            wyswietlanie_planszy(plansza);

            if(pion(plansza, y, znak)==3 || poziom(plansza, x, znak)==3 || ukos1(plansza, znak)==3 || ukos2(plansza, znak)==3){
                    printf("Wygrana dla %c \n", znak);
                    return 0;
            }

            //Zamiana znaku jeśli nie zakończyliśmy gry
            if(znak=='O') znak='X';
            else znak='O';

            }

    }
        printf("R1emis :(  \n");
        return 0;
}
