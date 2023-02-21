#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include"structure.h"

/********************************************************************/
/* W programie zostala uzyta i zmodyfikowana:                       */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2020 KCiR  */
/********************************************************************/


/************************************************************************************
 * Funkcja wczytuje obraz PGM lub PPM z pliku do struktury       	       	       *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM lub PPM			    *
 * \param[out] obraz[piksele]  tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] obraz[wymx] szerokosc obrazka						    *
 * \param[out] obraz[wymy] wysokosc obrazka						    *
 * \param[out] obraz[odcieni] liczba odcieni szarosci	lub nasycenia koloru				    *
 * \param[out] obraz[numer_mag] numer magiczny pliku z obrazem	  *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/



int czytaj(FILE *plik_we,t_obraz * obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]=='P') && (buf[1]=='2') ){    /* Przypisanie numeru magicznego do struktury */
    obraz->numer_mag = "P2";
  }
  else if( (buf[0]=='P') && (buf[1]=='3') ){
    obraz->numer_mag = "P3";
  }
  else{
    fprintf(stderr,"Blad: Podano bledny plik\n");
    return(0);
  }  
  

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
    fscanf(plik_we,"%i", &(obraz->wymx));
    fscanf(plik_we,"%i", &(obraz->wymy));
    fscanf(plik_we,"%i",&(obraz->odcieni));

    if(strcmp(obraz->numer_mag,"P3")==0)  /* Jezeli plik to ppm wtedy jego szerokosc jest 3 razy wieksza, bo kazdy piksel charakteryzuja 3 liczby */
      obraz->wymx *= 3;

    obraz->piksele = malloc(obraz->wymx*obraz->wymy*sizeof(int)); /* Przypisanie pamieci dla tablicy dynamicznej, w ktorej znajdowac sie beda piksele */

    int (*piksele)[obraz->wymx];                    /* Zmienna pomocnicza do obslugi tablicy dynamicznej */
    piksele=(int(*)[obraz->wymx]) obraz->piksele;


  /* Pobranie obrazu i zapisanie w tablicy */
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(plik_we,"%d",&(piksele[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  } 
  return obraz->wymx * obraz->wymy;  /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* **** 
* Funkcja odpowiedzialna za stworzenie drugiej struktury, na ktorej beda wykonywane wszelkie operacje 
* t_obraz *obraz_roboczy - struktura, na ktorej bedziemy pracowac
**** */
void tworz_obraz(t_obraz *obraz_roboczy, t_obraz *obraz){
  int i,j;

  obraz_roboczy->numer_mag = obraz->numer_mag;  /* Przepisanie wartosci miedzy strukturami */
  obraz_roboczy->wymx = obraz ->wymx;
  obraz_roboczy->wymy = obraz ->wymy;
  obraz_roboczy->odcieni = obraz ->odcieni;
  obraz_roboczy->kolor = obraz->kolor;

  obraz_roboczy->piksele = malloc(obraz_roboczy->wymx*obraz_roboczy->wymy*sizeof(int));

  int (*piksele)[obraz->wymx];
  piksele=(int(*)[obraz->wymx]) obraz->piksele;

  int (*piksele_rob)[obraz_roboczy->wymx];
  piksele_rob=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;


  for (i=0;i<obraz_roboczy-> wymy;i++) {                      /* Petla przepisuje wartosci tablicy z obrazem do tablicy roboczej */ 
    for (j=0;j<obraz_roboczy->wymx;j++) {
      piksele_rob[i][j] = piksele[i][j];    
    }
  }

}

/* **** Funkcja odpowiedzialna za zapisywanie nowego pliku lub wyswietlenie na standardowym wyjsciu **** */
int zapisz(FILE *plik_wy, t_obraz *obraz_roboczy){
  int i,j;

  int (*piksele)[obraz_roboczy->wymx];
    piksele=(int(*)[obraz_roboczy->wymx]) obraz_roboczy->piksele;

  if (plik_wy==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  fprintf(plik_wy,"%s\n",obraz_roboczy->numer_mag);

  if(strcmp(obraz_roboczy->numer_mag,"P3")==0) /* Dla obrazow PPM nalezy zmniejszyc docelowa szerokosc trzykrotnie */
    fprintf(plik_wy,"%d %d %d\n", obraz_roboczy->wymx /3 , obraz_roboczy-> wymy, obraz_roboczy-> odcieni);
  else{
    fprintf(plik_wy,"%d %d %d\n", obraz_roboczy->wymx , obraz_roboczy-> wymy, obraz_roboczy-> odcieni);
  }


  for (i=0;i<obraz_roboczy->wymy;i++) {
    for (j=0;j<obraz_roboczy->wymx;j++) {
      fprintf(plik_wy,"%i ",piksele[i][j]);
    }
    fprintf(plik_wy,"\n");
  }

  return 1;
}


/* **** Funkcja odpowiedzialna za wyswietlanie pliku */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}


/* **** Funkcja odpowiedzialna za usuwanie plikow pomocniczych lub blednych */
void usun(char *n_pliku){
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"rm ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* rm "nazwa_pliku" &       */
  strcat(polecenie," &");
  system(polecenie);             /* wykonanie polecenia        */

}

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->nazwa_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
  wybor->prog_bieli=0;
  wybor->prog_czerni=0;
  wybor->rozm_pion=0;
  wybor->rozm_poz=0;
  wybor->konwersja_szar=0;
}


/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-d] [-k]    */
/*                  [-pb liczba] [-pc liczba] [-rx] [ry] [-m znak] }    */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wyb�r, do tego ustawia na 1 pola dla opcji, ktore  */
/*	poprawnie wystapily w linii wywolania programu,                     */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;         */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                         */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor) {
  int i, prog, a, b ;
  char *nazwa_pliku_we, *nazwa_pliku_wy, *kolor;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  if(argc == 1) /* Wywolanie programu bez opcji*/
    return 1;

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      a = 1;
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	  wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	else                               /* otwieramy wskazany plik   */
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      b = 1;
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else{                              /* otwieramy wskazany plik    */
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
    wybor->nazwa_wy = nazwa_pliku_wy;
  }
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if(argv[i][2]=='b'){
        if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	      if (sscanf(argv[i],"%d",&prog)==1) {
	      wybor->prog_bieli=1;
	      wybor->w_progu=prog;
	      } else
	      return B_BRAKWARTOSCI;
        } else 
	      return B_BRAKWARTOSCI; 
      }
      else if(argv[i][2]=='c'){
        if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	      if (sscanf(argv[i],"%d",&prog)==1) {
	      wybor->prog_czerni=1;
	      wybor->w_progu=prog;
	    } else
	      return B_BRAKWARTOSCI;
      } else 
	      return B_BRAKWARTOSCI; 
      } 
      else{
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	    if (sscanf(argv[i],"%d",&prog)==1) {
	      wybor->progowanie=1;
	      wybor->w_progu=prog;
	    } else
	      return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else 
	      return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      }

      break;
    }
    case 'n': {                 /* mamy wykonac negatyw */
      wybor->negatyw=1;
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      wybor->konturowanie=1;
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
      break;
    }
    case 'r':{
      if(argv[i][2] == 'x')   /* mamy wykonac rozmycie poziome */
        wybor->rozm_poz=1;
      else if(argv[i][2] == 'y')  /* mamy wykonac rozmycie pionowe */
        wybor->rozm_pion=1;
      else
      {
        return B_NIEPOPRAWNAOPCJA;
      }
      break;
    }
    case 'm':{            /* Wybor koloru */
         
        kolor = argv[++i];
      
      if (strcmp(kolor,"r")==0)       /* Pracujemy na czerwonym */
        wybor->r = 1;
      else if (strcmp(kolor,"g")==0)  /* Pracujemy na zielonym */
        wybor->g = 1;
      else if (strcmp(kolor,"b")==0)  /* Pracujemy na niebieskim */
        wybor->b = 1;
      else if (strcmp(kolor,"s")==0)  /* Wykonujemy konwersje do szarosci */
        wybor->konwersja_szar = 1;
      else
        return B_NIEPOPRAWNAOPCJA;

      break;
    }

    case 'h':{    /* mamy wyswietlic pomoc */
      return HELP;
      break;
    }

    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

  if(a == 0)
    return -5;
  if(b == 0)
    return -6;

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}