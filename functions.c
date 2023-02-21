#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>    /* Biblioteka matematyczna posluzyla do utworzenia wartosci bezwzglednej */
#include"structure.h"

/* **** Funkcja odpowiedzialna za operacje negatywu **** */
int negatyw(t_obraz *obraz_roboczy){
  int i,j;

  int (*piksele_robocze)[obraz_roboczy->wymx];    /* Zmienna pomocnicza do pracy na tablicy dynamicznej */
  piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;



  if(obraz_roboczy->kolor == 0){ /* Przetwarzanie czarno-biale */

  for(i=0; i<obraz_roboczy-> wymy; i++){
    for(j=0; j<obraz_roboczy->wymx; j++){
      piksele_robocze[i][j] = obraz_roboczy->odcieni - piksele_robocze[i][j];
    }
  }

  }

  if(obraz_roboczy->kolor == 1){  /* Przetwarzanie czerwieni */
    for(i=0; i<obraz_roboczy-> wymy; i++){
      for(j=0; j<obraz_roboczy->wymx; j+=3){
        piksele_robocze[i][j] = obraz_roboczy->odcieni - piksele_robocze[i][j];
      }
    }
  }

  if(obraz_roboczy->kolor == 2){  /* Przetwarzanie zieleni */
    for(i=0; i<obraz_roboczy-> wymy; i++){
      for(j=1; j<obraz_roboczy->wymx; j+=3){
        piksele_robocze[i][j] = obraz_roboczy->odcieni - piksele_robocze[i][j];
      }
    }

  }

  if(obraz_roboczy->kolor == 3){ /* Przetwarzanie niebieskiego */
    for(i=0; i<obraz_roboczy-> wymy; i++){
      for(j=2; j<obraz_roboczy->wymx; j+=3){
        piksele_robocze[i][j] = obraz_roboczy->odcieni - piksele_robocze[i][j];
      }
    }

  }



  return 1;
}

/* **** Funkcja odpowiedzialna za operacje progowania zwyklego **** */
int progowanie(t_obraz *obraz_roboczy, int procent){
  int i, j, prog;
  int (*piksele_robocze)[obraz_roboczy->wymx];
    piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  if(procent < 0 || procent > 100){ /* Zabezpieczenie przed podaniem zlego zakresu */
    fprintf(stderr,"Blad: Podano prog spoza zakresu\n");
    return 0;
  }

  prog = obraz_roboczy->odcieni * procent / 100;         /* Wartosc sluzaca do klasyfikacji pikseli do czarnych i bialych */

  
  if(obraz_roboczy->kolor == 0){
    for(i=0; i<obraz_roboczy->wymy; i++){                   /* Petla wykonujaca progowanie */
      for(j=0; j<obraz_roboczy->wymx; j++){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
        else
          piksele_robocze[i][j] = obraz_roboczy->odcieni;
      }
    }
  }

  if(obraz_roboczy->kolor == 1){
    for(i=0; i<obraz_roboczy->wymy; i++){                   
      for(j=0; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
        else
          piksele_robocze[i][j] = obraz_roboczy->odcieni;
      }
    }
  }

  if(obraz_roboczy->kolor == 2){
    for(i=0; i<obraz_roboczy->wymy; i++){                   
      for(j=1; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
        else
          piksele_robocze[i][j] = obraz_roboczy->odcieni;
      }
    }
  }

  if(obraz_roboczy->kolor == 3){
    for(i=0; i<obraz_roboczy->wymy; i++){                   
      for(j=3; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
        else
          piksele_robocze[i][j] = obraz_roboczy->odcieni;
      }
    }
  }


  return 1;
}


/* **** 
* Funkcja odpowiedzialna za progowanie czerni ( zastepuje tylko piksele biale )
* int procent - procent progowania podany przez uzytkownika
**** */
int polprog_czerni(t_obraz *obraz_roboczy, int procent){
  int i, j, prog;
  int (*piksele_robocze)[obraz_roboczy->wymx];
    piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;


  if(procent < 0 || procent > 100){
    fprintf(stderr,"Blad: Podano prog spoza zakresu\n");
    return 0;
  }

  prog = obraz_roboczy->odcieni * procent / 100;        /* Wartosc sluzaca do klasyfikacji pikseli do czarnych i bialych */


  if(obraz_roboczy->kolor ==0){
    for(i=0; i<obraz_roboczy->wymy; i++){                  /* Petla wykonujaca progowanie */
      for(j=0; j<obraz_roboczy->wymx; j++){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
      }
    }
  }
  if(obraz_roboczy->kolor ==1){
    for(i=0; i<obraz_roboczy->wymy; i++){                  /* Petla wykonujaca progowanie */
      for(j=0; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
      }
    }
  }
  if(obraz_roboczy->kolor ==2){
    for(i=0; i<obraz_roboczy->wymy; i++){                  /* Petla wykonujaca progowanie */
      for(j=1; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
      }
    }
  }
  if(obraz_roboczy->kolor ==3){
    for(i=0; i<obraz_roboczy->wymy; i++){                  /* Petla wykonujaca progowanie */
      for(j=3; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] <= prog)
          piksele_robocze[i][j] = 0;
      }
    }
  }

  return 1;
}


/* **** Funkcja odpowiedzialna za progowanie bieli ( zastepuje tylko piksele czarne )  **** */
int polprog_bieli(t_obraz *obraz_roboczy, int procent){
  int i, j, prog;
  int (*piksele_robocze)[obraz_roboczy->wymx];
    piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  if(procent < 0 || procent > 100){                         /* Zabezpieczenie przed podaniem zlego zakresu */
    fprintf(stderr,"Blad: Podano prog spoza zakresu\n");
    return 0;
  }

  prog = obraz_roboczy->odcieni * procent / 100;            /* Wartosc sluzaca do klasyfikacji pikseli do czarnych i bialych */


  if(obraz_roboczy->kolor == 0){
    for(i=0; i<obraz_roboczy->wymy; i++){                      /* Petla wykonujaca progowanie */
      for(j=0; j<obraz_roboczy->wymx; j++){
        if(piksele_robocze[i][j] > prog)
          piksele_robocze[i][j] = obraz_roboczy->odcieni;

      }
    }
  }
  if(obraz_roboczy->kolor == 1){
    for(i=0; i<obraz_roboczy->wymy; i++){                      /* Petla wykonujaca progowanie */
      for(j=0; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] > prog)
          piksele_robocze[i][j] = obraz_roboczy->odcieni;

      }
    }
  }
  if(obraz_roboczy->kolor == 2){
    for(i=0; i<obraz_roboczy->wymy; i++){                      /* Petla wykonujaca progowanie */
      for(j=1; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] > prog)
          piksele_robocze[i][j] = obraz_roboczy->odcieni;

      }
    }
  }
  if(obraz_roboczy->kolor == 3){
    for(i=0; i<obraz_roboczy->wymy; i++){                      /* Petla wykonujaca progowanie */
      for(j=2; j<obraz_roboczy->wymx; j+=3){
        if(piksele_robocze[i][j] > prog)
          piksele_robocze[i][j] = obraz_roboczy->odcieni;

      }
    }
  }

  return 1;
}



/* **** Funkcja odpowiedzialna za konturowanie **** */
int konturowanie(t_obraz *obraz_roboczy){
  int i, j;
  int (*piksele_robocze)[obraz_roboczy->wymx];
    piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  if(obraz_roboczy->kolor == 0){ /* Konturowanie czarno-biale */
    for(i=0; i<obraz_roboczy->wymy; i++){                    /* Petla wykonujaca konturowanie */
      for(j=0; j<obraz_roboczy->wymx; j++){
        if(i+1 != obraz_roboczy->wymy && j+1 != obraz_roboczy->wymx)
          piksele_robocze[i][j] = sqrt(pow(piksele_robocze[i+1][j] - piksele_robocze[i][j], 2 )) + sqrt(pow(piksele_robocze[i][j+1] - piksele_robocze[i][j], 2 )); /* Uzycie funkcji matematycznych */
        if(piksele_robocze[i][j] > obraz_roboczy->odcieni)                                                                                                               /* do stworzenia wartosci bezwzgl */       
          piksele_robocze[i][j] = obraz_roboczy->odcieni;     /* Przypisanie max wartosci szarosci w wypadku gdy wartosc wyjdzie poza dozwolony przedzial */
      }
    }
  }

  if(obraz_roboczy->kolor == 1){ /* Konturowanie czerwieni */
    for(i=0; i<obraz_roboczy->wymy; i++){                    /* Petla wykonujaca konturowanie */
      for(j=0; j<obraz_roboczy->wymx; j+=3){
        if(i+1 != obraz_roboczy->wymy && j+3 != obraz_roboczy->wymx)
          piksele_robocze[i][j] = sqrt(pow(piksele_robocze[i+1][j] - piksele_robocze[i][j], 2 )) + sqrt(pow(piksele_robocze[i][j+3] - piksele_robocze[i][j], 2 )); /* Uzycie funkcji matematycznych */
        if(piksele_robocze[i][j] > obraz_roboczy->odcieni)                                                                                                               /* do stworzenia wartosci bezwzgl */       
          piksele_robocze[i][j] = obraz_roboczy->odcieni;     /* Przypisanie max wartosci szarosci w wypadku gdy wartosc wyjdzie poza dozwolony przedzial */
      }
    }
  }

  if(obraz_roboczy->kolor == 2){ /* Konturowanie zieleni */
    for(i=0; i<obraz_roboczy->wymy; i++){                    /* Petla wykonujaca konturowanie */
      for(j=1; j<obraz_roboczy->wymx; j+=3){
        if(i+1 != obraz_roboczy->wymy && j+3 != obraz_roboczy->wymx)
          piksele_robocze[i][j] = sqrt(pow(piksele_robocze[i+1][j] - piksele_robocze[i][j], 2 )) + sqrt(pow(piksele_robocze[i][j+3] - piksele_robocze[i][j], 2 )); /* Uzycie funkcji matematycznych */
        if(piksele_robocze[i][j] > obraz_roboczy->odcieni)                                                                                                               /* do stworzenia wartosci bezwzgl */       
          piksele_robocze[i][j] = obraz_roboczy->odcieni;     /* Przypisanie max wartosci szarosci w wypadku gdy wartosc wyjdzie poza dozwolony przedzial */
      }
    }
  }

  if(obraz_roboczy->kolor == 3){ /* Konturowanie niebieskiego */
    for(i=0; i<obraz_roboczy->wymy; i++){                    /* Petla wykonujaca konturowanie */
      for(j=2; j<obraz_roboczy->wymx; j+=3){
        if(i+1 != obraz_roboczy->wymy && j+3 != obraz_roboczy->wymx)
          piksele_robocze[i][j] = sqrt(pow(piksele_robocze[i+1][j] - piksele_robocze[i][j], 2 )) + sqrt(pow(piksele_robocze[i][j+3] - piksele_robocze[i][j], 2 )); /* Uzycie funkcji matematycznych */
        if(piksele_robocze[i][j] > obraz_roboczy->odcieni)                                                                                                               /* do stworzenia wartosci bezwzgl */       
          piksele_robocze[i][j] = obraz_roboczy->odcieni;     /* Przypisanie max wartosci szarosci w wypadku gdy wartosc wyjdzie poza dozwolony przedzial */
      }
    }
  }





  return 1;
}


/* **** 
* Funkcja odpowiedzialna za rozmycie poziome ( wedlug osi horyzontalnej ) 
**** */
int rozmycie_poz(t_obraz *obraz_roboczy,t_obraz *obraz_pom){
  int i, j;

  int (*piksele_robocze)[obraz_roboczy->wymx];
  piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;
  
  int (*piksele_pom)[obraz_pom->wymx];
  piksele_pom=(int(*)[obraz_pom->wymx]) obraz_pom->piksele;
  

  if(obraz_roboczy->kolor == 0){
    for(i=0; i<obraz_roboczy->wymy; i++){                /* Petla wykonujaca operacje*/
      for(j=0; j<obraz_roboczy->wymx; j++){
          if(j+1 != obraz_roboczy->wymx && j-1 > -1)     /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i][j-1] + piksele_pom[i][j] + piksele_pom[i][j+1])/3; /* Sytuacja dla pikseli z srodka obrazu*/
          if(j+1 == obraz_roboczy->wymx)
            piksele_robocze[i][j] = (piksele_pom[i][j-1] + piksele_pom[i][j])/2;    /* Sytuacja dla ostatnich pikseli w danym wierszu*/
          if(j-1 == -1)
            piksele_robocze[i][j] = (piksele_pom[i][j+1] + piksele_pom[i][j])/2;    /* Sytuacja dla pierwszych pikseli*/
      }
    }
  }

  if(obraz_roboczy->kolor == 1){
    for(i=0; i<obraz_roboczy->wymy; i++){                /* Petla wykonujaca operacje*/
      for(j=0; j<obraz_roboczy->wymx; j+=3){
          if(j+3 != obraz_roboczy->wymx && j-3 > -3)     /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j] + piksele_pom[i][j+3])/3; /* Sytuacja dla pikseli z srodka obrazu*/
          if(j+3 == obraz_roboczy->wymx)
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j])/2;    /* Sytuacja dla ostatnich pikseli w danym wierszu*/
          if(j-3 == -3)
            piksele_robocze[i][j] = (piksele_pom[i][j+3] + piksele_pom[i][j])/2;    /* Sytuacja dla pierwszych pikseli*/
      }
    }
  }

  if(obraz_roboczy->kolor == 2){
    for(i=0; i<obraz_roboczy->wymy; i++){                /* Petla wykonujaca operacje*/
      for(j=1; j<obraz_roboczy->wymx; j+=3){
          if(j+3 < obraz_roboczy->wymx && j-3 > -2)     /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j] + piksele_pom[i][j+3])/3; /* Sytuacja dla pikseli z srodka obrazu*/
          if(j+3 > obraz_roboczy->wymx + 1)
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j])/2;    /* Sytuacja dla ostatnich pikseli w danym wierszu*/
          if(j-3 == -2)
            piksele_robocze[i][j] = (piksele_pom[i][j+3] + piksele_pom[i][j])/2;    /* Sytuacja dla pierwszych pikseli*/
      }
    }
  }

  if(obraz_roboczy->kolor == 3){
    for(i=0; i<obraz_roboczy->wymy; i++){                /* Petla wykonujaca operacje*/
      for(j=2; j<obraz_roboczy->wymx; j+=3){
          if(j+3 < obraz_roboczy->wymx && j-3 > -1)     /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j] + piksele_pom[i][j+3])/3; /* Sytuacja dla pikseli z srodka obrazu*/
          if(j+3 > obraz_roboczy->wymx)
            piksele_robocze[i][j] = (piksele_pom[i][j-3] + piksele_pom[i][j])/2;    /* Sytuacja dla ostatnich pikseli w danym wierszu*/
          if(j-3 == -1)
            piksele_robocze[i][j] = (piksele_pom[i][j+3] + piksele_pom[i][j])/2;    /* Sytuacja dla pierwszych pikseli*/
      }
    }
  }


  return 1;
}

/* **** Funkcja odpowiedzialna za rozmycie pionowe ( wedlug osi wertykalnej ) **** */
int rozmycie_pion(t_obraz *obraz_roboczy,t_obraz *obraz_pom){
  int i, j;

  int (*piksele_robocze)[obraz_roboczy->wymx];
  piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  int (*piksele_pom)[obraz_pom->wymx];
  piksele_pom=(int(*)[obraz_pom->wymx]) obraz_pom->piksele;

  if(obraz_roboczy->kolor == 0 ){
    for(j=0; j<obraz_roboczy->wymx; j++){              /* Petla wykonujaca operacje */
      for(i=0; i<obraz_roboczy->wymy; i++){
          if(i+1 != obraz_roboczy->wymy && i-1 > -1)   /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j] + piksele_pom[i+1][j])/3;    /* Sytuacja dla pikseli z srodka obrazu*/
          if(i+1 == obraz_roboczy->wymy)
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j])/2;   /* Sytuacja dla pierwszych pikseli w kolumnie */
          if(i-1 == -1)
            piksele_robocze[i][j] = (piksele_pom[i+1][j] + piksele_pom[i][j])/2;  /* Sytuacja dla ostatnich pikseli w kolumnie */
      }
    }
  }
  if(obraz_roboczy->kolor == 1 ){
    for(j=0; j<obraz_roboczy->wymx; j+=3){              /* Petla wykonujaca operacje */
      for(i=0; i<obraz_roboczy->wymy; i++){
          if(i+1 != obraz_roboczy->wymy && i-1 > -1)   /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j] + piksele_pom[i+1][j])/3;    /* Sytuacja dla pikseli z srodka obrazu*/
          if(i+1 == obraz_roboczy->wymy)
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j])/2;   /* Sytuacja dla pierwszych pikseli w kolumnie */
          if(i-1 == -1)
            piksele_robocze[i][j] = (piksele_pom[i+1][j] + piksele_pom[i][j])/2;  /* Sytuacja dla ostatnich pikseli w kolumnie */
      }
    }
  }if(obraz_roboczy->kolor == 2 ){
    for(j=1; j<obraz_roboczy->wymx; j+=3){              /* Petla wykonujaca operacje */
      for(i=0; i<obraz_roboczy->wymy; i++){
          if(i+1 != obraz_roboczy->wymy && i-1 > -1)   /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j] + piksele_pom[i+1][j])/3;    /* Sytuacja dla pikseli z srodka obrazu*/
          if(i+1 == obraz_roboczy->wymy)
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j])/2;   /* Sytuacja dla pierwszych pikseli w kolumnie */
          if(i-1 == -1)
            piksele_robocze[i][j] = (piksele_pom[i+1][j] + piksele_pom[i][j])/2;  /* Sytuacja dla ostatnich pikseli w kolumnie */
      }
    }
  }
  if(obraz_roboczy->kolor == 3 ){
    for(j=2; j<obraz_roboczy->wymx; j+=3){              /* Petla wykonujaca operacje */
      for(i=0; i<obraz_roboczy->wymy; i++){
          if(i+1 != obraz_roboczy->wymy && i-1 > -1)   /* Zabezpieczenie przed bledem pamieci ( uzycie wartosci spoza tablicy) */
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j] + piksele_pom[i+1][j])/3;    /* Sytuacja dla pikseli z srodka obrazu*/
          if(i+1 == obraz_roboczy->wymy)
            piksele_robocze[i][j] = (piksele_pom[i-1][j] + piksele_pom[i][j])/2;   /* Sytuacja dla pierwszych pikseli w kolumnie */
          if(i-1 == -1)
            piksele_robocze[i][j] = (piksele_pom[i+1][j] + piksele_pom[i][j])/2;  /* Sytuacja dla ostatnich pikseli w kolumnie */
      }
    }
  }
  return 1;

}


/* Funkcja odpowiedzialna za operacje konwersji do szarosci */
/* \param[in] struktura przechowujaca obraz kolorowy        */
/* \param[out] struktura przechowujaca obraz czarno-bialy   */
t_obraz* konwersja(t_obraz *obraz_roboczy){
  int i, j, k;
  t_obraz *obraz_konwersja; /* nowa struktura */

  obraz_konwersja = (t_obraz *) malloc(sizeof(t_obraz));  /* Przydzial pamieci */
  obraz_konwersja->numer_mag = "P2";                      /* Zmiana do pliku PGM */
  obraz_konwersja->wymy = obraz_roboczy->wymy;
  obraz_konwersja->wymx = obraz_roboczy->wymx/3;
  obraz_konwersja->odcieni = obraz_roboczy->odcieni;

  obraz_konwersja->piksele = malloc(obraz_konwersja->wymx*obraz_konwersja->wymy*sizeof(int));

  int (*piksele_konw)[obraz_konwersja->wymx];
  piksele_konw=(int(*)[obraz_konwersja->wymx]) obraz_konwersja->piksele;

  int (*piksele_robocze)[obraz_roboczy->wymx];
  piksele_robocze=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  
  for(i=0;i<obraz_roboczy->wymy;i++){ /* Konwersja polegajaca na urednianiu wszystkich pikseli na podstawie ich skladowych r,g,b*/
    k=0;
    for(j=1;j<obraz_roboczy->wymx;j+=3){
        piksele_konw[i][k] = (piksele_robocze[i][j-1] + piksele_robocze[i][j] + piksele_robocze[i][j+1])/3;
        k++;
    }
  }

  return obraz_konwersja;

}

