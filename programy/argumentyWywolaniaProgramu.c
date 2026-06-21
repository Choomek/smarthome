#include <stdio.h>
#include "argumentyWywolaniaProgramu.h"
int opcje(int argc, char *argv[], tryby *t, char **nazwa)
/*
##########################################################################################################################################
PRE:
Argumenty wywolania programu, struktura zawierajaca informacje o trybach.
POST:
Zmiana wartosci logicznych w strukturze, przypisanie nazwy, kod bledu.
CEL:
Funkcja operuje na argumentach wywolania programu by na ich podstawie rozroznic 2 opcje; logowanie oraz rejestracje. Pozwala to na
zapamietywanie danych uzytkownikow w plikach tekstowych by moc operowac na nich wielokrotnie.
OPIS DZIALANIA:
Pierwsza petla iteruje po kolejnych awp w poszukiwaniu znaku "-" na ich poczatku. Gdy na takowy natrafi przechodzi do 2 petli ktora
iteruje po kolejnych zmiennych char napotkanej opcji w by zrealizowac wszystkie oczekiwane przez uzytkownika operacje kazdy znak 
rozpatrywany jest przez switch by ustawic wartosci trybow w strukturze. Na koniec funkcja przypisuje pod zmienna podana w arguemncie
jako nazwa nazwe uzytkownika zaczerpnieta z argv.
OBSLUGA BLEDOW:
Kod 1 - program sprawdza w instrukcji switch czy wybrana opcja istnieje, jezeli nie poprzez default zwraca komunikat i kod bledu.
Kod 2 - program sprawdza czy do ktoregos z trybow zostala przypisana wartosc 1 jezeli nie zwraca komunikat i kod bledu.
Kod 3 - program sprawdza czy po iteracji argc wyzerowalo sie jezeli tak oznacza to ze uzytkownik nie podal nazwy po opcji, program
zwraca komunikat i kod bledu.
##########################################################################################################################################
*/
{
    (*t).trybLogowania=0;
    (*t).trybRejestracji=0;
    int c;
    *nazwa = NULL;
    while(--argc>0 && (*++argv)[0]=='-')
    {
        while(c=*++argv[0])
        {
            switch (c)
            {
            case 'l':
                (*t).trybLogowania=1;
                break;
            case 'r':
                (*t).trybRejestracji=1;
                break;
            default:
                fprintf(stderr, "Nieznana opcja\n");
                return 1;
            }
        }
    }
    if((*t).trybLogowania==0 && (*t).trybRejestracji==0)
    {
        fprintf(stderr, "Program wywolany bez opcji\n");
        return 2;
    }
    if(argc<=0)
    {
        fprintf(stderr, "Niepodano nazwy pokoju\n");
        return 3;
    }
    *nazwa = *argv;
    for(int i=0; (*nazwa)[i] != '\0'; i++)
    {
        if((((*nazwa)[i] >= 65 && (*nazwa)[i]<=90) || ((*nazwa)[i] >= 97 && (*nazwa)[i]<=122) || ((*nazwa)[i] >= 48 && (*nazwa)[i]<=57))==0)
        {
            fprintf(stderr, "Niepoprawny format nazwy pokoju\n");
            return 14;
        }
    }
    return 0;
}