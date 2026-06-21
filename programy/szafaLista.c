#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include "szafaLista.h"

przedmiot* zainicjujPrzedmiot(char nazwa[ROZMIAR])
/*
##########################################################################################################################################
PRE:
Nazwa przedmiotu ktory chcemy umiescic w szafie
POST:
Utworzenie struktury tego przedmiotu
CEL:
Stworzyc element listy wchodzacy w sklad szafy
OPIS DZIALANIA:
Funkcja tworzy nowy elemnt i przydziela mu pamiec wielkosci przedmiotu. Nastepnie w pole nazwa wpisujemy zaczytana nazwe na ktorej koncu 
umieszczamy znak pusty oraz w pole kolejny wpisujemy wartosc NULL
OBSLUGA BLEDOW:
-
##########################################################################################################################################
*/
{
    przedmiot* wezel=malloc(sizeof(przedmiot));
    strncpy((*wezel).nazwa, nazwa, ROZMIAR-1);
    (*wezel).nazwa[ROZMIAR-1]='\0';
    (*wezel).kolejny=NULL;
    return wezel;
}

void odlozPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR])
/*
##########################################################################################################################################
PRE:
Wskaznik na liste, nazwa dodawanego przedmiotu
POST:
Dodaje przedmiot na liste
CEL:
Dodac przedmiot na liste
OPIS DZIALANIA:
Deklarujemy wskaznik na element listy. Sprawdzamy czy znajduje sie on juz na liscie. Nastepnie podstawiamy do niego adres utworzonego 
elementu listy. Rozpatrujemy dwa przypadki gdy lista jest pusta za pierwszy element wstawiamy zainicjowany przedmiot. W przeciwnym razie 
iterujemy po lisice w poszukiwaniu ostatniego elementu gdy uda sie go znalezc wychdzoimy z petli i za jego obecna warotsc podstawiamy nasz 
nowo utworzony wskaznik.
OBSLUGA BLEDOW:
-
##########################################################################################################################################
*/
{
    przedmiot* szukany=*glowa;
    for(; szukany != NULL; szukany=(*szukany).kolejny)
    {
        if (strcmp((*szukany).nazwa, nazwa) == 0)
        {
            return;
        }
    }
    przedmiot* nowy;
    nowy=zainicjujPrzedmiot(nazwa);
    if (*glowa == NULL)
    {
        *glowa = nowy;
        return;
    }
    przedmiot* ostatni;
    ostatni=*glowa;
    for(; (*ostatni).kolejny != NULL; ostatni=(*ostatni).kolejny);
    (*ostatni).kolejny=nowy;
}

void wyjmijPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR])
/*
##########################################################################################################################################
PRE:
Wskaznik na liste, nazwa usuwanego przedmiotu
POST:
Usuniecie przedmiotu z listy
CEL:
Usuniecie przedmiotu z listy
OPIS DZIALANIA:
Deklarujemy dwie zmienne pomocnicze. Nastepnie sprawdzamy czy lista i pierwszy element istenije w przeciwnym razie nie jestesmy w stanie
nic usunac. Nastepnie gdy przejdziemy ten test rozpatrujemy 2 przypadki. Wpierw sprawdzimy czy element ktory chcemy usunac jest pierwszym
elementem listy gdyz ten ptzypadek wykrzaczy nam petle. Jezeli tak usuwamy go i zwalniamy pamiec. Jezeli do usuniecia jest inny element
to iterujemy po lisicie w poszukiwaniu go. Sa 2 opcje albo go znajdziemy albo nie. Sprawdzamy czy po wykonaniu petli wskaznik sprawdzany
dalej na nic nie pokazuje jezeli tak oznacza to ze na lisie nie bylo szukanego elementu i zakanczamy dzialanie funkcji. W przeciwnym razie
wskaznik pomocniczy sprawdzany pokazuje na element poprzedzajacy element do usuniecia co oznacza ze jestesmy go w stanie bezpiecznie usunac
OBSLUGA BLEDOW:
-
##########################################################################################################################################
*/
{
    przedmiot* doUsuniecia;
    przedmiot* sprawdzany;
    sprawdzany=*glowa;
    if (glowa==NULL || *glowa==NULL)
    {
        return;
    }
    if (strcmp((**glowa).nazwa, nazwa) == 0)
    {
        doUsuniecia = *glowa;
        *glowa=(*doUsuniecia).kolejny;
        free(doUsuniecia);
        return;
    }
    while ((*sprawdzany).kolejny != NULL && strcmp((*(*sprawdzany).kolejny).nazwa, nazwa) != 0)
    {
        sprawdzany=(*sprawdzany).kolejny;
    }
    if ((*sprawdzany).kolejny==NULL)
    {
        return;
    }
    doUsuniecia = (*sprawdzany).kolejny;
    (*sprawdzany).kolejny=(*doUsuniecia).kolejny;
    free(doUsuniecia);
}

void znajdzPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR])
/*
##########################################################################################################################################
PRE:
Wskaznik na liste, nazwa szukanego przedmiotu
POST:
Wskaznik na literal napisowy z komunikatem
CEL:
Znalezc przedmiot w szafie
OPIS DZIALANIA:
Pod zmienna pomocnicza da przeszukiwania listy podstawiamy pierwszy element i sprawdzamy czy on istenieje. Nastepnie iterujemy po liscie
w poszukiwaniu przedmiotu o zaczytanej nazwie. W zaleznosci od tego czy uda sie znalezc zwracamy odpowiedni komunikat
OBSLUGA BLEDOW:
-
##########################################################################################################################################
*/
{
    przedmiot* szukany=*glowa;
    if (szukany == NULL)
    {
        printf("Przedmiotu nie ma w szafie\n");
        printf("Zaczekaj 5 sekund\n");
        sleep(5);
        return;
    }
    for(; szukany != NULL; szukany=(*szukany).kolejny)
    {
        if (strcmp((*szukany).nazwa, nazwa) == 0)
        {
            printf("Przedmiot w szafie\n");
            printf("Zaczekaj 5 sekund\n");
            sleep(5);
            return;
        }
    }
    printf("Przedmiotu nie ma w szafie\n");
    printf("Zaczekaj 5 sekund\n");
    sleep(5);
    return;
}