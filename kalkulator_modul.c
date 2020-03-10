/*************************************************************************/
/* Plik z definicjami funkcji zawartymi w programie pt. "Kalkulator RPN" */
/*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "kalkulator_modul.h"

/***************************************************************************/
/* Funkcja ma na celu dodawac nowe elementy do stosu lub                   */
/* duplikowac elementy ze szczytu stosu                                    */
/* Argumenty funkcji:                                                      */
/*                   - lista - wskaznik na adres wskaznika wskazujacego na */
/*                             poczatkowy element obecnego stosu (praca na */
/*                             orginale)                                   */
/*                   - pom - wskaznik na wskaznik zmiennej pomocniczej     */
/*                   - liczba - wartosc elementu do dodania na stos        */
/*                   - check - zmienna sluzaca rozroznieniu, czy           */
/*                             nalezy wykonac duplikacje czy dodanie       */
/*                             nowego elementu na poczatek stosu           */
/* PRE:                                                                    */
/*      W przypadku wywolania funkcji w celu zduplikowania                 */
/*      podanego elementu stosu stos nie moze byc pusty.                   */
/* POST:                                                                   */
/*      Dodanie elementu na poczatek stosu, a w przypadku                  */
/*      opcji duplikacji, zduplikowanie elementu, badz zwrocenie wartosci  */
/*      o kodzie bledu, w normalnym przypadku zwrocenie zera. Ponadto w obu*/
/*      przypadkach ustawienie zmiennej lista na poczatek nowego stosu.    */
/***************************************************************************/

int dodaj_element(t_elem **lista,t_elem *pom,int liczba,int check){
  if(check==0||(check==1&&*lista!=NULL)){ // warunek wykonania duplikacji i dodania nowego elementu
    pom=(t_elem*)malloc(sizeof(t_elem));  // przydzielenie nowego obszaru pamieci
    pom->dana=liczba;  // ustawienie wartosci nowego elementu na podana wartosc
    pom->nastepny=*lista;  // ustawienie nowego elementu na poczatku listy
    *lista=pom;}  // zapamietanie nowego ukladu listy
  else  // gdy poproszono o duplikacje, jednak brak elementow na stosie
    return (6);  // zwrocenie wartosci o kodzie bledu
  return (0);  // zwrocenie zera w przypadku poprawnego wykonania funkcji
}

/***************************************************************************/
/* Funkcja ma na celu usuwanie poczatkowego elementu stosu lub             */
/* usuwanie zawartosci calego stosu, w obu przypadkach wraz ze             */
/* zwolnieniem zajmowanej pamieci                                          */
/* Argumenty funkcji:                                                      */
/*                   - lista - wskaznik na adres wskaznika wskazujacego na */
/*                             poczatkowy element obecnego stosu (praca na */
/*                             orginale                                    */
/*                   - pom - wskaznik na wskaznik zmiennej pomocniczej     */
/*                   - liczba - zmienna sluzaca rozpoznaniu czy nalezy     */
/*                              usunac elementu na szczycie stosu, czy     */
/*                              zawartosc calego stosu                     */
/* PRE:                                                                    */
/*      Stos nie moze byc pusty.                                           */
/* POST:                                                                   */
/*      Usuniecie pierwszego elementu stosu, badz tez usuniecie zawartosci */
/*      calego stosu, w obu przypadkach ze zwolnieniem zajmowanej pamieci. */
/*      W zaleznosci od przypadku ustawienie zmiennej lista na NULL lub    */
/*      poczatek nowego stosu, natomiast w przypadku proby usuniecia       */
/*      elementu z pustego stosu zwrocenie wartosci o kodzie bledu,        */
/*      w normalnym przypadku zwrocenie zera                               */
/***************************************************************************/
                                                           
int usun_element(t_elem **lista,t_elem *pom,int liczba){
  if(*lista!=NULL){  // gdy stos nie jest pusty
    if(liczba==0){  // przypadek gdy chcemy usunac pierwszy element
      *lista=pom->nastepny;  // ustawienie lista na element nastepny
      free(pom);  // zwolnienie pamieci dla elementu wczesniejszego
      pom=NULL;}  // ustawienie wskaznika pomocniczego na NULL
    if(liczba==1){  // przypadek gdy chcemy usunac caly stos
      for(pom=*lista;pom!=NULL;pom=*lista){  // petla sluzaca usunieciu calego stosu
	*lista=pom->nastepny;  // ustawienie lista na element nastepny
	free(pom);  // zwolenienie pamieci dla elementu wczesniejszego
	pom=NULL;}}}  // ustawienie wskaznika pomocniczego na NULL
  else  // gdy stos jest pusty
    return (5);  // zwrocenie wartosci o kodzie bledu
  return (0);  // zwrocenie zera gdy poprawnie wykonano funkcje
}

/***************************************************************************/
/* Funkcja ma na celu zamiane miejsc pierwszego elementu stosu             */
/* z jego drugim elementem                                                 */
/* Argumenty funkcji:                                                      */
/*                   - lista - wskaznik na adres wskaznika wskazujacego na */
/*                             poczatkowy element obecnego stosu (praca na */
/*                             orginale)                                   */
/*                   - pom - wskaznik na wskaznik zmiennej pomocniczej     */
/*                   - liczba - wskaznik na adres wartosci pierwszego      */
/*                              elementu stosu(praca na orginale)          */
/* PRE:                                                                    */
/*      Stos musi skladac sie co najmniej z dwoch elementow                */
/* POST:                                                                   */
/*      Zamiana miejscami dwoch pierwszych elementow stosu, a nastepnie    */
/*      ustawienie zmiennej lista na pocztek nowego stosu. W przypadku     */
/*      checi wykonania zamiany miejsc i braku odpowiedniej ilosc elementow*/
/*      stosu, zwrocenie wartosci o kodzie bledu, w normalnym przypadku    */
/*      zwrocenie zera                                                     */
/***************************************************************************/
                 
int zamiana_miejsc(t_elem **lista,t_elem *pom,int *liczba){
  t_elem *pom2;  // utworzenie dodatkowej lokalnej zmiennej wskaznikowej
  if(*lista!=NULL&&(*lista)->nastepny!=NULL){  // gdy istnieja dwa elementy na stosie
    *lista=pom->nastepny;  // lista ustawiona na poczatkowo drugi element stosu
    pom2=(*lista)->nastepny;  // lokalna zmienna wskaznikowa ustawiona na poczatkowo trzeci element stosu
    (*lista)->nastepny=pom;  // nastepny element listy ustawiony na poczatkowo pierwszy element stosu 
    (*lista)->nastepny->nastepny=pom2;  // nastepny element nastepnego elementu listy ustawiony na poczatkowo trzeci element stosu
    *liczba=(*lista)->dana;}  // aktualna wartosc poczatku stosu ustawiona zgodnie z nowym stosem
  else  // gdy brakuje elementow na stosie
    return (4);  // zwrocenie wartosci o kodzie bledu
  return (0);  // zwrocenie zera gdy poprawnie wykonano funkcje
}

/*****************************************************************************/
/* Funkcja ma na celu wyswietlac zawartosc calego stosu lub jego             */
/* pierwszego elementu                                                       */
/* Argumenty funkcji:                                                        */
/*                   - lista - wskaznik na adres wskaznika wskazujacego na   */
/*                             poczatkowy element obecnego stosu (praca na   */
/*                             orginale)                                     */
/*                   - pom - wskaznik na wskaznik zmiennej pomocniczej       */
/*                   - liczba - zmienna wskazujaca czy nalezy wykonac        */
/*                              usuniecie pierwszego elementu stosu, czy     */
/*                              nalezy usunac cala jego zawartosc            */
/* PRE:                                                                      */
/*      Stos nie moze byc pusty                                              */
/* POST:                                                                     */
/*      Usuniecie pierwszego elementu stosu oraz ustawienie zmiennej lista   */
/*      na pierwszy element nowego stosu(lub na na NULL gdy usunieto ostatni */
/*      jego element, lub usuniecie calej zawartosci stosu i ustawienie      */
/*      zmiennej lista na NULL. W przypadku bledu usuwania(brak elementow na */
/*      stosie) zwrocenie wartosci o kodzie bledu, w normalnym przypadku     */
/*      zwrocenie zera                                                       */
/*****************************************************************************/

int wyswietl(t_elem *lista,t_elem *pom,int liczba){
  if(lista!=NULL){  // Gdy stos nie jest pusty
    if(liczba==0){  // przypadek gdy nalezy pokazac cala zawartosc stosu
      for(pom=lista;pom->nastepny!=NULL;pom=pom->nastepny)  // petla obchodzaca caly stos
        printf("%d ",pom->dana);
      printf("%d ",pom->dana);}
    if(liczba==1){  // przypadek gdy nalezy pokazac pierwszy element stosu
      printf("%d",pom->dana);}}
  else  // gdy stos jest pusty
    return (3);  // zwrocenie wartosci o kodzie bledu
  printf("\n");
  return (0);  // zwrocenie zera w przypadku poprawnego wykonania funkcji
}

/*****************************************************************/
/* Funkcja ma na celu zerowac elemnty tablicy typu char          */
/* Argumenty funkcji:                                            */
/*                   - tab - wskaznik na adres pierwszego        */
/*                           elementu tablicy(praca na orginale) */
/* PRE:                                                          */
/*      Poprawnie zaincjowany wskaznik na tablice                */
/* POST:                                                         */
/*      Wyzerowanie poszczegolnych elementow tablicy             */
/*****************************************************************/

void zeruj(char *tab){
  int i;
  if(tab!=NULL){
    for(i=0;i<SIZE;++i)
      tab[i]=0;}
}

/******************************************************************************/
/* Funkcja wykonuje wskazane przez uzytkownika dzialanie na poczatkowych      */
/* elemntach stosu, a po jego wykonaniu aktualizuje zawartosc stosu - usuwa   */
/* elementy stare i dodaje nowe                                               */
/* Argumenty funkcji:                                                         */
/*                   - lista - wskaznik na adres wskaznika wskazujacego na    */
/*                             poczatkowy element obecnego stosu (praca na    */
/*                             orginale)                                      */
/*                   - pom - wskaznik na wskaznik zmiennej pomocniczej        */
/*                   - wynik - aktualna wartosc pierwszego elementu stosu     */
/*                   - znak - kod znaku sluzacego do rozpoznania rodzaju      */
/*                            dzialania do wykonania                          */
/* PRE:                                                                       */
/*      Stos musi skladac sie z co najmniej dwoch elementow                   */
/* POST:                                                                      */
/*      Wykonanie dzialania na dwoch poczatkowych elementach stosu, usuniecie */
/*      ich obu, a nastepnie dodanie nowego elementu o wartosci z wykonanego  */
/*      dzialania na starych elementach stosu, w przypadku braku co najmniej  */
/*      dwoch elemntow na stosie zwrocenie wartosci o kodzie bledu, normalnie */
/*      zwrocenie zera                                                        */
/******************************************************************************/

int dzialanie(t_elem **lista,t_elem *pom,int *wynik,int znak){
  if(*lista!=NULL&&(*lista)->nastepny!=NULL){  // gdy stos sklada sie z co najmniej dwoch elementow
    switch(znak){  // rozpoznanie rodzaju operacji
    case '+':  // dodawanie
      *wynik=(*lista)->dana+(((*lista)->nastepny)->dana); break;
    case '-':  // odejmowanie
      *wynik=(*lista)->dana-(((*lista)->nastepny)->dana); break;
    case '*':  // mnozenie
      *wynik=(*lista)->dana*(((*lista)->nastepny)->dana); break;
    case '/':  // dzielenie
      if(((*lista)->nastepny)->dana!=0)  // gdy dzielnik rozny od zera
        *wynik=(*lista)->dana/(((*lista)->nastepny)->dana);
      else  // gdy proba dzielenia przez zero
	return (1);  // zwrocenie wartosci o kodzie bledu
      break;
    default: break;}
    usun_element(lista,pom,0);  // usuniecie pierwszego elementu listy
    pom=*lista;  // wskaznik pomocniczy ustawiony na nowy poczatek listy
    usun_element(lista,pom,0);  // usuniecie drugiego elementu listy
    dodaj_element(lista,pom,*wynik,0);}  // dodanie nowego elementu do listy
  else  // gdy stos sklada sie z mniej niz dwoch elementow
    return (2);  // zwrocenie wartosci o kodzie bledu
  return (0);  // zwrocenie zera w przypadku poprawnego wykonania funkcji
}

/*******************************************************************/
/* Funkcja aktualizuje wskaznik na konkretny stos w zaleznosci     */
/* od stosu, na ktorym obecnie przeprowadzane sa operacje,         */
/* a takze ustawia zmienna pomocnicza na obecny stos               */
/* Argumenty funkcji:                                              */
/*                   - rodzaj - zmienna wskazujaca na stos,        */
/*                              na ktorym sa obecnie wykonywane    */
/*                              operacje                           */
/*                   - lista - wskaznik na adres wskaznika         */
/*                             wskazujacego na poczatkowy element  */
/*                             obecnego stosu(praca na orginale)   */
/*                   - lista1 - wskaznik na adres wskaznika        */
/*                              wskazujacego na poczatkowy element */
/*                              stosu nr 1(praca na orginale)      */
/*                   - lista2 - wskaznik na adres wskaznika        */
/*                              wskazujacego na poczatkowy element */
/*                              stosu nr 2(praca na orginale)      */
/*                   - pom - wskaznik pomocniczy na adres wskaznika*/
/*                           wskazujacego na poczatkowy element    */
/*                           obecnego stosu(praca na orginale)     */
/* PRE:                                                            */
/*      brak                                                       */
/* POST:                                                           */
/*      zaktualizowanie wskaznika na konretny stos w zaleznosci    */
/*      od stosu, na ktorym obecnie przeprowadzane sa operacje,    */
/*      a takze ustawienie wskaznika pomocniczego na obecny stos   */
/*******************************************************************/

void aktualizuj(int rodzaj,t_elem **lista, t_elem **lista1, t_elem **lista2,t_elem **pom){
  if(rodzaj==1)  // jesli obecnie jest stos nr 1
    *lista1=*lista;  // zaktualizowanie wskaznika na stos
  else  // jesli obecnie jest stos nr 2
    *lista2=*lista;  // zaktualizowanie wskaznika na stos
  *pom=*lista;  // zaktualizowanie wskaznika pomocniczego
}

/**************************************************/
/* Funkcja wyswietla menu napisowe programu       */
/* PRE:                                           */
/*      brak                                      */
/* POST:                                          */
/*      brak                                      */
/**************************************************/

void menu(){
  printf("\nMenu obslugi kalkulatora:\n");
  printf("[p] - Wyswietl pierwszy element stosu\n[f] - Wyswietl zawartosc calego stosu\n");
  printf("[P] - Usun pierwszy element stosu\n[c] - Wyczysc zawartosc calego stosu\n");
  printf("[d] - Duplikuj pierwszy element stosu\n");
  printf("[r] - Zamien kolejnoscia pierwszy z drugim elementem stosu\n[q] - Wyjscie z programu\n");
  printf("[+] - Dodaj dwa pierwsze elementy stosu\n[-] - Odejmij dwa pierwsze elementy stosu\n");
  printf("[*] - Pomnoz dwa pierwsze elementy stosu\n[/] - Podziel dwa pierwsze elementy stosu\n");
  printf("[m] - Wyswietl menu programu\n");
  printf("[x] - Zmiana stosu\n");
  printf("[t] - Transportowanie wartosci ze szczytu obecnego stosu do drugiego stosu\n");
  printf("Uwaga! Po komunikacie: 'Wprowadz dzialanie' wyswietlony w nawiasie jest numer stosu");
  printf(", ktory obecnie jest obslugiwany\n\n");
}

/**********************************************************/
/* Funkcja wypisuje komunikaty o bledach lub o sytuacjach */
/* wyjatkowych w programie na standardowy strumien        */
/* diagnostyczny                                          */
/* Argumenty funkcji:                                     */
/*                    - liczba - wartosc kodu bledu       */
/* PRE:                                                   */
/*      brak                                              */
/* POST:                                                  */
/*      wyswietlenie komunikatu o bledzie                 */
/**********************************************************/

void wypisz_komunikat(int liczba){
  switch(liczba){  // instrukcja sluzaca wybrania odpowiedniego komunikatu
  case 1:
    fprintf(stderr,"Blad dzialania - nie mozna dzielic przez zero\n"); break;
  case 2:
    fprintf(stderr,"Blad dzialania - zbyt mala liczba elementow stosu\n"); break;
  case 3:
    fprintf(stderr,"Stos jest pusty\n"); break;
  case 4:
    fprintf(stderr,"Nie mozna zamienic miejscami - zbyt mala liczba elementow stosu\n"); break;
  case 5:
    fprintf(stderr,"Nie mozna usunac - stos jest pusty\n"); break;
  case 6:
    fprintf(stderr,"Nie mozna zduplikowac - stos jest pusty\n"); break;
  case 7:
    fprintf(stderr,"Nie mozna transportowac - stos jest pusty\n"); break;
  default: break;}
}
