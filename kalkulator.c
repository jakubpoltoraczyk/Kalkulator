#include <stdio.h>
#include <stdlib.h>
#include "kalkulator_modul.h"

/****************************************************/
/* Program pt. "Kalkulator RPN"                     */
/* Autor: Jakub Poltoraczyk                         */
/* Data wykonania:                                  */
/*                                                  */
/* Charakterystyka programu:                        */
/* Program ma na celu obslugiwac czterodzialaniowy  */
/* kalkulator RPN oparty w swojej konstrukcji na    */
/* stosie, obslugiwanym przez liste jednokierunkowa */
/* Oprocz podstawowych operacji arytmetycznych      */
/* zostaly tez dodane dodatkowe operacje sluzace    */
/* latwiejszej obsludze kalkulatora. Do dyspozycji  */
/* uzytkownika sa dwa stosy, miedzy ktorymi mozna   */
/* sie z latwoscia przelaczac, a takze przesylac    */
/* poczatkowe elementy stosow.                      */
/****************************************************/

int main(void){
  char tab[SIZE];  // tablica sluzaca do przechowywania znakow liczby wielocyfrowej
  /* zmienna 'znak' sluzy do wczytywania normalnych znakow, zmienna 'znak_minus' sluzy do wczytywania znakow w przypadku natkniecia sie na minus, jest to zmienna pomocnicza, zmienna i sluzy do obslugi petli w programie, zmienna liczba sluzy do przechowywania aktualnej wartosci pierwszego elementu stosu, zmienna komunikat sluzy do przyjmowania wartosci, od ktorych zalezy wyswietlenie odpowiedniego komunikatu o bledzie, zmienna rodzaj wskazuje, na rodzaj stosu obecnie dostepnego, wskaznik lista jest to wskaznik glowny na obecnie obslugiwany stos, wskaznik pom jest to wskaznik pomocniczy, wskaznik lista1 jest wskaznikiem do zapamietywania stosu nr 1, a wskaznik lista2 jest wskaznikiem do zapamietywania stosu nr 2 */
  int znak,liczba,i,znak_minus,komunikat,rodzaj=1;
  t_elem *lista,*pom,*lista1,*lista2;  // wskazniki na poszczegolne elementy listy
  lista=NULL,lista1=NULL,lista2=NULL;  // ustawienie wskaznikow na NULL
  printf("\nKALKULATOR RPN\n");
  menu();
  for(;;){ // petla dzialajaca w nieskonczonosc lub do momentu podania argumentu wyjscia z programu
    printf("Wprowadz dzialanie[%d]: ",rodzaj);
    while((znak=getc(stdin))!='\n'){  // petla pobierajaca kolejne znaki ze strumienia wejsciowego
      zeruj(tab);  // wyzerowanie tablicy 
      switch(znak){  // rozpoznawanie znaku
      case 'x':  // w przypadku zmiany stosu
	if(rodzaj==1){  // jesli obecny jest stos nr 1
	  rodzaj=2;  // zmienna wskazuje na stos nr 2
	  lista=lista2;  // zmiana glownego wskaznika na stos nr 2
	  pom=lista;}  // ustawienie wskaznika pomocniczego na stos nr 2
	else{  // jesli obecny jest stos nr 2
	  rodzaj=1;  // zmienna wskazuje na stos nr 1
	  lista=lista1;  // zmiana glownego wskaznika na stos nr 1
	  pom=lista;}  // ustawienie wskaznika pomocniczego na stos nr 1
	break;
      case 't':  // w przypadku transportowania wartosci
	if(rodzaj==1){  // jesli obecnie jest stos nr 1
	  if(lista1!=NULL){  // jesli stos nr 1 nie jest pusty
	    pom=lista2;  // ustawienie wskaznika pomocniczego na stos nr 2
	    dodaj_element(&lista2,pom,liczba,0);  // dodanie szczytu stosu nr 1 do stosu nr 2
	    pom=lista1;}  // ustawienie ponowne wskaznika pomocniczego na stos nr 1
	  else{  // jesli stos nr 1 jest pusty 
	    komunikat=7;  // nadanie zmiennej wartosci kodu bledu
	    wypisz_komunikat(komunikat);}}
	else{  // jesli obecnie jest stos nr 2
	  if(lista2!=NULL){  // jesli stos nr 2 nie jest pusty
	    pom=lista1;  // ustawienie wskaznika pomocniczego na stos nr 1
	    dodaj_element(&lista1,pom,liczba,0);  // dodanie szczytu stosu nr 2 do stosu nr 1
	    pom=lista2;}  // ustawienie ponowne wskaznika pomocniczego na stos nr 2
	  else{  // jesli  stos nr 2 jest pusty
	    komunikat=7;  // nadanie zmiennej wartosci kodu bledu
	    wypisz_komunikat(komunikat);}}
	break;
      case 'm':  // w przypadku wywolania menu
	menu(); break;
      case 'q':  // w przypadku wyjscia z programu
	if(lista1!=NULL){  // jesli stos nr 1 nie jest pusty
	  pom=lista1;  // ustawienie wskaznika pomocniczego na stos nr 1
	  usun_element(&lista1,pom,1);}  // usuniecie zawartosci stosu nr 1
	if(lista2!=NULL){  // jesli stos nr 2 nie jest pusty
	  pom=lista2;  // ustawienie wskaznika pomocniczego na stos nr 2
	  usun_element(&lista2,pom,1);}  // usuniecie zawartosci stosu nr 2
	lista=NULL;  // wskaznik glowny na NULL
	pom=NULL;  // wskaznik pomocniczy na NULL
	printf("\nWyjscie z programu\n"); 
        exit(0); break;  // wyjscie z programu
      case 'f':  // w przypadku wyswietlenie calego stosu
        komunikat=wyswietl(lista,pom,0); // argument zero wskazujacy na odpowiednia galaz w funkcji
	if(komunikat!=0)  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat);
	break;
      case 'p':  // w przypadku wyswietlenie szczytu stosu
        komunikat=wyswietl(lista,pom,1);// argument jeden wskazujacy na odpowiednia galaz w funkcji
	if(komunikat!=0)  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat);
	break;
      case 'd':  // w przypadku zduplikowania szczytu stosu
        komunikat=dodaj_element(&lista,pom,liczba,1);// jeden by wybrac odpowiednia galaz w funckji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
	aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case 'r':  // w przypadku zamiany miejsc dwoch pierwszych elementow stosu
        komunikat=zamiana_miejsc(&lista,pom,&liczba);
	if(komunikat!=0){// gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case 'P':  // w przypadku usuniecia pierwszego elementu stosu
        komunikat=usun_element(&lista,pom,0);// argument zero by wybrac odpowiednia galaz w funkcji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
	if(lista!=NULL)  // jesli usuniety element nie byl ostatnim w stosie
	  liczba=lista->dana;  // ustawienie liczby na aktualna wartosc
	break;
      case 'c':  // w przypadku usuniecia calej zawartosci stosu
	komunikat=usun_element(&lista,pom,1); // argument jeden by wybrac odpowiednia galaz funkcji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case '+':  // w przypadku dodania dwoch elementow
	komunikat=dzialanie(&lista,pom,&liczba,znak);  // przekazywany rowniez znak operacji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case '*':  // w przypadku mnozenia dwoch elementow
	komunikat=dzialanie(&lista,pom,&liczba,znak);  // przekazywany rowniez znak operacji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case '/':  // w przypadku dzielenia calkowitoliczbowego dwoch elementow
	komunikat=dzialanie(&lista,pom,&liczba,znak);  // przekazywany rowniez znak operacji
	if(komunikat!=0){  // gdy wykryto blad lub cos wyjatkowego
	  wypisz_komunikat(komunikat); break;}
        aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;  // aktualizacja wskaznikow
      case '-':  // w przypadku pojawienia sie znaku minus
	/* Ponizsze operacje sluza rozpoznaniu czy minus oznacza odejmowanie czy wprowadzenie liczby ujemnej */
	znak_minus=getc(stdin);  // wczytanie kolejnego znaku
	if(znak_minus<'0'||znak_minus>'9'){  // jesli nie jest on cyfra
	  komunikat=dzialanie(&lista,pom,&liczba,znak); // operacja odejmowanie, przy podaniu znaku
	  if(komunikat!=0)  // gdy wykryto blad lub cos wyjatkowego
	    wypisz_komunikat(komunikat);
          aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); // aktualizacja wskaznikow
	  ungetc(znak_minus,stdin);}  // zwrocenie wczytanego znaku innego od cyfry
	else{  // jesli jest to cyfra
	  tab[0]=(char)znak_minus;  // wczytanie znaku do tablicy
	  for(i=1;i<SIZE;++i){  // petla wczytujaca kolejne znaki
	    znak_minus=getc(stdin);
	    if(znak_minus<'0'||znak_minus>'9'){  // az do napotkania znaku innego od cyfry
	      ungetc(znak_minus,stdin);  // zwrocenie tego znaku
	      i=SIZE;}  // zakonczenie dzialania petli
	    else
	      tab[i]=(char)znak_minus;}  // gdy wczytywany znak jest znowu cyfra
	  liczba=0-atoi(tab);  // konwersja napisu na odpowiednia wartosc calkowita za pomoca atoi
	  dodaj_element(&lista,pom,liczba,0);   // dodanie powstalego elementu do stosu
	  aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom);} break;  // aktualizacja wskaznikow 
      default:  // gdy inny znak od wymienionych
        if(znak>='0'&&znak<='9'){  // gdy jest on cyfra
	  /* Petla identyczna z petla z 'case '-'' */
	  tab[0]=(char)znak;  
	  for(i=1;i<SIZE;++i){
	    znak=getc(stdin);
	    if(znak<'0'||znak>'9'){
	      ungetc(znak,stdin);
	      i=SIZE;}
	    else
	      tab[i]=(char)znak;}
	  liczba=atoi(tab);  // tu jedyna roznica gdyz ta liczba nie jest ujemna
	  dodaj_element(&lista,pom,liczba,0);}
	aktualizuj(rodzaj,&lista,&lista1,&lista2,&pom); break;}}} // aktualizacja wskaznikow
  return (0);  // zwrocenie zera w przypadku poprawnego zakonczenia dzialania programu
}
