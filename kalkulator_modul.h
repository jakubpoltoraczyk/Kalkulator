/****************************************************/ 
/* Plik naglowkowy do programu pt. "Kalkulator RPN" */
/****************************************************/		     

#define SIZE 9  // stala okreslajaca wielkosc mozliwej liczby do podania dla kalkulatora
/* Struktura sluzaca do stworzenia listy obslugujacej stos */
typedef struct elem{
  int dana;  // wartosc argumentu
  struct elem* nastepny;  // wskaznik na nastepny element stosu
}t_elem;
int dodaj_element(t_elem**, t_elem*, int, int);  // funkcja dodajaca elementy do stosu
int usun_element(t_elem**, t_elem*, int);  // funkcja usuwajaca elementy ze stosu
int zamiana_miejsc(t_elem**, t_elem*, int*);  // zamiana kolejnosci dwoch pierwszych arg stosu
int wyswietl(t_elem*, t_elem*, int);  // funkcja wyswietlajaca zawartosc stosu
void zeruj(char*);  // funkcja zerujaca tablice 
int dzialanie(t_elem**, t_elem*, int*, int);  // funkcja wykonujaca podane dzialanie na stosie
void menu();  // funkcja wyswietlajaca menu programu
void wypisz_komunikat(int);  // funkcja wypisujaca komunikaty o bledach
void aktualizuj(int, t_elem**, t_elem**, t_elem**, t_elem**);// aktualizuje wskazniki na poszczegolne stosy
