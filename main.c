/*

**********************************************************************
*    Przy kompilacji programu nalezy dodac biblioteke matematyczna:  *
*   -lm                                                              *
**********************************************************************


*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>      /* Biblioteka matematyczna posluzyla do utworzenia wartosci bezwzglednej */
#include"structure.h"


int main(int argc, char ** argv){
  t_obraz *obraz, *obraz_roboczy, *obraz_pom;            /* Struktury przechowujace dane o obrazach */
  t_opcje *opcje;                                        /* Struktura przechowujaca argumenty wywolania obrazu */
  int odczytano = 0, zapisano = 0, neg = 0, prog = 0, kont = 0, rozm = 0; /* Zmienne sluzace do sprawdzania poprawnosci wywolania funkcji*/                                         

  opcje = (t_opcje *) malloc(sizeof(t_opcje));
  obraz = (t_obraz *) malloc(sizeof(t_obraz));                    /* Alokowanie pamieci dla struktur dynamicznych */
  obraz_roboczy = (t_obraz *) malloc(sizeof(t_obraz));
  obraz_pom = (t_obraz *) malloc(sizeof(t_obraz));

  switch(przetwarzaj_opcje(argc,argv,opcje)){       /*  Warunki poprawnosci wywolania programu  */
    case 0: {                                       /* Przypadek prawidlowego wywolania programu */
      odczytano = czytaj(opcje->plik_we,obraz);
      fclose(opcje->plik_we);

      if(opcje->r)                  
        obraz->kolor = 1;
      else if(opcje->g)
        obraz->kolor = 2;           /* Przypisanie wartosci koloru dla ktorego maja sie wykonywac operacje */ 
      else if(opcje->b)             /* czerwony - 1, zielony - 2, niebieski - 3  */
        obraz->kolor = 3;
      else
        obraz->kolor = 0;
        
      if(odczytano)
        tworz_obraz(obraz_roboczy,obraz);
      else{                     /* W przypadku podania zlej nazwy pojawia sie odpowiedni komunikat */
            printf("Nie ma takiego pliku\n");
      }

      if(obraz->kolor!=0 && strcmp(obraz->numer_mag,"P2")){   /* Zabezpieczenie przed wybraniem koloru dla obrazu .pgm */
        fprintf(stderr,"Blad: Nie mozna wybrac koloru dla obrazu czarno-bialego. Wpisz ./program aby otzrymac pomoc\n");
        return 0;
      }

      if(opcje->rozm_pion == 1  && opcje->rozm_poz == 1){   /* Zabezpieczenie przed wyborem roznych rozmyc jednoczescie*/
        fprintf(stderr,"Blad: Wybierz jeden rodzaj rozmycia\n");
        usun(opcje->nazwa_wy);
        return 0;
      }



      if((opcje->progowanie == 1 && opcje->prog_czerni == 1) || (opcje->progowanie ==1 && opcje->prog_bieli == 1) || (opcje->prog_bieli == 1 && opcje->prog_czerni == 1) ){
        fprintf(stderr,"Blad: Prosze wybrac jeden sposob progowania\n");  /* Zabezpieczenie przed wyborem wielu progowan */
        usun(opcje->nazwa_wy);
        return 0;
      }


      if(opcje->konwersja_szar){
        obraz_roboczy = konwersja(obraz_roboczy);
      }

      if(opcje->negatyw){
        neg= negatyw(obraz_roboczy);
        if(neg)
          printf("Wykonano negatyw\n");
      }
      
      if(opcje->progowanie){
        if(opcje->w_progu < 0 || opcje->w_progu > 100){
          fprintf(stderr,"Blad: Wybrano prog spoza zakresu. Wpisz ./program aby otrzymac pomoc\n"); /* Zabezpieczenie przed podaniem progu mniejszego niz 0 i wiekszego niz 100 */
          usun(opcje->nazwa_wy);  /* Usuwanie pustego pliku powstalego podczas blednego dzialania programu */
          return 0;
        }
        prog = progowanie(obraz_roboczy,opcje->w_progu);
        if(prog)
          printf("Wykonano progowanie\n");
      }

      if(opcje->prog_bieli){  /* Analogicznie jak w progowaniu */
        if(opcje->w_progu < 0 || opcje->w_progu > 100){
          fprintf(stderr,"Blad: Wybrano prog spoza zakresu. Wpisz ./program aby otrzymac pomoc\n");
          usun(opcje->nazwa_wy);
          return 0;
        }
        prog = polprog_bieli(obraz_roboczy,opcje->w_progu);
        if(prog)
          printf("Wykonano polprogowanie bieli\n");
      }

      if(opcje->prog_czerni){ /* Analogicznie jak w progowaniu */
        if(opcje->w_progu < 0 || opcje->w_progu > 100){
          fprintf(stderr,"Blad: Wybrano prog spoza zakresu. Wpisz ./program aby otrzymac pomoc\n");
          usun(opcje->nazwa_wy);
          return 0;
        }
        prog = polprog_czerni(obraz_roboczy,opcje->w_progu);
        if(prog)
          printf("Wykonano polprogowanie czerni\n");
      }

      if(opcje->konturowanie){
        kont = konturowanie(obraz_roboczy);
        if(kont)
          printf("Wykonano konturowanie\n");
      }
      
      if(opcje->rozm_pion){
        tworz_obraz(obraz_pom,obraz_roboczy);
        rozm = rozmycie_pion(obraz_roboczy,obraz_pom);
        if(rozm)
          printf("Wykonano rozmycie pionowe\n");
        free(obraz_pom);
      }

      if(opcje->rozm_poz){
        tworz_obraz(obraz_pom,obraz_roboczy);
        rozm = rozmycie_poz(obraz_roboczy,obraz_pom);
        if(rozm)
          printf("Wykonano rozmycie poziome\n");
        free(obraz_pom);
      }


      zapisano = zapisz(opcje->plik_wy,obraz_roboczy);

      if(zapisano == 1) 
          printf("Zapisano plik lub zostal on wyswietlony na standardowym wyjsciu\n");

      if(opcje->wyswietlenie && strcmp(opcje->nazwa_wy,"-")) /* Wyswietlenie obrazu za pomoca zewnetrznego programu */
        wyswietl(opcje->nazwa_wy);

      
      fclose(opcje->plik_wy);

      break;
    }

    case 1: {   /* Wywolanie programu bez parametrow powoduje wyswietlenie pomocy */
      printf("Wybrano pomoc:\n");
      printf("usage: ./program [-i plik_wej] [-p wart] [-pb wart] [-pc wart] [-k] [-n] [-m wart] [-rx] [-ry] [-o plik_wyj]\n\n");
      printf("\t-i plik_wej : wczytywanie obrazu, plik_wej to nazwa pliku, w wypadku podania '-' wczytywanie odbywa sie ze standardowego wejscia\n");
      printf("\t-p wart : progowanie, wartosc procentowa podawana jako liczba calkowita\n");
      printf("\t-pb wart : polprogowanie bieli, wartosc procentowa podawana jako liczba calkowita\n");
      printf("\t-pc wart : polprogowanie czerni, wartosc procentowa podawana jako liczba calkowita\n");
      printf("\t-k : konturowanie\n");
      printf("\t-n : negatyw\n");
      printf("\t-m wart : wybor koloru, r - czerwony, g - zielony, b - niebieski, s - konwersja do szarosci (tylko dla obrazow kolorowych)\n");
      printf("\t-rx : rozmycie poziome\n");
      printf("\t-ry : rozmycie pionowe\n");
      printf("\t-o plik_wyj : zapisywanie obrazu, plik_wyj to nazwa pliku, w wypadku podania '-' zapis odbywa sie na standardowe wyjscie(nie mozna podawac tej samej nazwy)\n");
      break;
    }

    case -1:{
      fprintf(stderr,"Blad: Wybrano niepoprawna opcje. Wpisz ./program aby wyswietlic pomoc.\n");
    
      break;
    }

    case -2:{
      fprintf(stderr,"Blad: Brak nazwy pliku. Wpisz ./program aby wyswietlic pomoc.\n");
      
      break;
    }

    case -3:{
      fprintf(stderr,"Blad: Brak wartosci. Wpisz ./program aby wyswietlic pomoc.\n");
      
      break;
    }

    case -4:{
      fprintf(stderr,"Blad: Plik nie istnieje. Wpisz ./program aby wyswietlic pomoc.\n");
      
      break;
    }

    case -5:{
      fprintf(stderr,"Blad: Nie uzyto opcji -i. Wpisz ./program aby wyswietlic pomoc.\n");
      
      break;
    }

    case -6:{
      fprintf(stderr,"Blad: Nie uzyto opcji -o. Wpisz ./program aby wyswietlic pomoc.\n");
      break;
    }

  }


  return 0;

}





/*
SPRAWOZDANIE
KAMIL ORLOWSKI



Testy programu

Poniewaz wynikiem dzialania programu jest utworzenie obrazu
testy funkcji zostaly przeprowadzone poprzez porownanie ich dzialania z 
dzialaniem komendy convert z odpowiednimi opcjami.

Test wywolania programu zostal przeprowadzony poprzez wybieranie odpowiednich opcji i sprawdzanie czy otrzymalismy odpowiedni wynik.

I
Testy wywolania:

Wywolywanie odpowiednich opcji powoduje wywolanie odpowiednich fubkcji.
Brak podania -i przy wywolaniu programu spowoduje pojawienie sie odpowiedniego komunikatu.
Brak podania -o przy wywolaniu programu spowoduje pojawienie sie odpowiednigo komunikatu.
Podanie '-' jako wartosci -o powoduje wyswietlenie pliku na standardowym wyjsciu.
Podanie '-' jako wartosci -i powoduje czytanie ze standardowego wejscia.
Bledne podanie progu dla progowania spowoduje pojawienie sie odpowiedniego komunikatu.
Podanie opcji, która nie istnieje powoduje pojawienie sie odpowiedniego komunikatu.
Wywolanie opcji -h powoduje pojawienie sie pomocy.
Wywolanie programu bez opcji powoduje pojawienie sie pomocy.

II
Testy funkcji

Odczyt:
Funkcja odczytuje obraz z rozszerzeniem .pgm lub .ppm i zapisuje go do dynamicznej tablicy dwuwymiarowej, przechowuje tez inne dane o obrazie.
W przypadku podania nieistniejacego pliku pojawi sie adekwatny komentarz.
Funkcja prawidlowo wczytywala obraz kubus.pgm oraz Lena.ppm.


Negatyw:
Funkcja odwraca poziomy szarosci pikseli.
Program prawidlowo zadzialal dla obrazow: Lena2.ppm, kubus.pgm, oko.pgm, CitroenC5.ppm i Claudia.pgm 

Wniosek
Funkcja dziala prawidlowo.

Progowania:
Funkcja klasyfikuje wybrane piksele i przypisuje im wartosci MAX lub 0.
Program prawidlowo zadzialal dla obrazow: Lena2.ppm, kubus.pgm, oko.pgm, CitroenC5.pgm i Claudia.ppm 

Wniosek
Funkcja dziala prawidlowo

Konturowanie:
Funkcja tworzy kontury obiektow znajdujacych sie na obrazie.
Program prawidlowo zadzialal dla obrazow: Lena2.ppm, kubus.pgm, oko.pgm, CitroenC5.pgm i Claudia.ppm 
Dla bardziej zlozonych obrazow kontury sa mniej wyrazne np. Lena2.pgm, nie jest to na tyle powazne aby stwierdzic wadliwosc funkcji.

Wniosek
Funkcja dziala prawidlowo

Rozmycia:
Funkcja usrednia wartosci pikseli z odpowiedniego zakresu.
Program prawidlowo zadzialal dla obrazow: Lena2.ppm, kubus.pgm, oko.pgm, CitroenC5.pgm i Claudia.ppm 
Zmiany przy rozmyciach kolorow sa znikome, dla calego obrazu jest juz bardziej widoczny.
Rozmycie poziome obrazu .ppm bez podania kolorow powoduje konwersje do szarosci.

Wniosek
Funkcja dziala prawidlowo

Wyswietlanie
Funkcja uruchamia zewnetrzny program.
Aby funkcja dzialala prawidlowo trzeba zainstalowac pakiet dispaly (imagesmagicks).

Wniosek
Funkcja dziala prawidlowo

Zapis
Funkcja korzysta z tablicy roboczej i zapisuje jej zawartosc do pliku tekstowego.
W ten sposob powstaje plik z obrazem, ktory mozna otwierac programami zewnetrznymi. ( Mozna zapisac plik bez rozszerzenia )

Wniosek
Funkcja dziala prawidlowo


**********************************************************************************
/ Wnioski ogolne dotyczace programu:

Program dziala prawidlowo. Opcje przetwarzania obrazow sa podobne lub identyczne
do wynikow dzialania komendy convert z odpowienimi opcjami.

Jezeli uzytkownik postepuje zgodnie z tym o co prosi go program
jego prawidlowe dzialanie jest zagwarantowane.

Przy wczytywaniu pliku ze standardowego wejscia nalezy zachowac szczegolna ostroznosc,
w razie popelnienia bledu dzialanie programu moze byc nieprzewidywalne.

***********************************************************************************

*/
