#define DL_LINII 1024
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define HELP 1                  /* kod pomocy */


/* Struktura przechowujaca informacje o obrazie */
typedef struct
{
    char *numer_mag;  /* numer magiczny */
    int wymx, wymy, odcieni, kolor; /*szerokosc, wysokosc, max_wartosc i kolor */
    void *piksele; /* tablica dynamiczna */
} t_obraz ;


/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,konturowanie,wyswietlenie,prog_bieli,prog_czerni,rozm_pion,rozm_poz,konwersja_szar;/* opcje */
  int w_progu;           
  char *nazwa_wy;
  int r, g, b ;
} t_opcje;


/* Prototypy uzywanych funkcji */
int czytaj(FILE *plik_we,t_obraz * obraz);
void tworz_obraz(t_obraz *obraz_roboczy, t_obraz *obraz);
int zapisz(FILE *plik_wy, t_obraz *obraz_roboczy);
void wyswietl(char *n_pliku);
void usun(char *n_pliku);

int negatyw(t_obraz *obraz_roboczy);
int progowanie(t_obraz *obraz_roboczy, int procent);
int polprog_czerni(t_obraz *obraz_roboczy, int procent);
int polprog_bieli(t_obraz *obraz_roboczy, int procent);
int konturowanie(t_obraz *obraz_roboczy);
int rozmycie_poz(t_obraz *obraz_roboczy,t_obraz *obraz_pom);
int rozmycie_pion(t_obraz *obraz_roboczy,t_obraz *obraz_pom);
t_obraz* konwersja(t_obraz *obraz_roboczy);


void wyzeruj_opcje(t_opcje * wybor);
int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor);