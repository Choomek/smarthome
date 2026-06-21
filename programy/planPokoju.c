#include<stdio.h>
#include<stdlib.h>
#include "strukturaPokoju.h"
#include "planPokoju.h"
int plan(pokoj *zaczytany, char*** tablica, char* nazwaPokoju)
/*
##########################################################################################################################################
PRE:
Wskaznik na strukture pokoju, wskaznik na dynamicznie zaalokowana liste, naza pokoju
POST:
Edycja tablicy przekazanej przez wskaznik, kod bledu
CEL:
Obsluga planu pokoju
OPIS DZIALANIA:
Funkcja deklaruje wewnetrzne zmienne pomocnicze a nastepnie wyswietla interfejs obslugi oraz uruchamia instrukcje switch wywolujac funkcje
ze sprawdzeniem czy wykonaly sie poprawnie.
OBSLUGA BLEDOW:
Kod 10 - Blad opcji do przemieszczania sie po programie
##########################################################################################################################################
*/
{
    int zmiennaPrzelaczajaca, kod;
    printf("###################################################################################################################\n");
    printf("#                                        Wybierz mebel do wstawienia:                                             #\n");
    printf("#                                         1. Lozko (2x1)                                                          #\n");
    printf("#                                         2. Biurko (2x1)                                                         #\n");
    printf("#                                         3. Szafa (3x1)                                                          #\n");
    printf("#                                         4. Komoda (1x1)                                                         #\n");
    printf("#                                         5. Zresetuj plan                                                        #\n");
    printf("###################################################################################################################\n");
    printf("Twoja opcja: ");
    scanf("%d", &zmiennaPrzelaczajaca);
    switch(zmiennaPrzelaczajaca)
    {
    case 1:
        if((kod = wstawMebel(zaczytany, 1, tablica))!=0)
        {
            for(int i=0; i<(*zaczytany).y; i++)
            {
                free((*tablica)[i]);
            }
            free(*tablica);
            return kod;
        }
        break;
    case 2:
        if((kod = wstawMebel(zaczytany, 2, tablica))!=0)
        {
            for(int i=0; i<(*zaczytany).y; i++)
            {
                free((*tablica)[i]);
            }
            free(*tablica);
            return kod;
        }
        break;
    case 3:
        if((kod = wstawMebel(zaczytany, 3, tablica))!=0)
        {
            for(int i=0; i<(*zaczytany).y; i++)
            {
                free((*tablica)[i]);
            }
            free(*tablica);
            return kod;
        }
        break;
    case 4:
        if((kod = wstawMebel(zaczytany, 4, tablica))!=0)
        {
            for(int i=0; i<(*zaczytany).y; i++)
            {
                free((*tablica)[i]);
            }
            free(*tablica);
            return kod;
        }
        break;
    case 5:
        if((kod=utworzPlan(zaczytany, tablica))!=0)
        {
            for(int i=0; i<(*zaczytany).y; i++)
            {
                free((*tablica)[i]);
            }
            free(*tablica);
            return kod;
        }
        break;
    default:
        fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
        for(int i=0; i<(*zaczytany).y; i++)
        {
            free((*tablica)[i]);
        }
        free(*tablica);
        return 10;
    }
    zapiszPlan(zaczytany, *tablica, nazwaPokoju);
    return 0;
}
int utworzPlan(pokoj *zaczytany, char*** tablica)
/*
##########################################################################################################################################
PRE:
Wskaznik na struktur pokoju, wskaznik na tablice
POST:
Utworzenie tablicy dynamicznej 
CEL:
Zadeklarowac plansze
OPIS DZIALANIA:
Funkcja przypisuje wskaznikowi potrzebna ilosc pamiecie sprawdza czy przypisanie sie udalo, a nastepnie przechodzimy do alokacji kolejnych
kolumn przy ktorym rownierz sprawdzamy powowdzenie. Na koniec tablice wypelniamy znakiem pustym w naszym przypadku '.'.
OBSLUGA BLEDOW:
Kod 7 - Blad przypisania pamieci dynamicznej
##########################################################################################################################################
*/
{
    *tablica = malloc(sizeof(char*)*(*zaczytany).y);
    if (*tablica==NULL)
    {
        fprintf(stderr, "Blad przypisania pamieci dynamicznej\n");
        return 7;
    }
    for(int i=0; i<(*zaczytany).y; i++)
    {
        (*tablica)[i] = malloc(sizeof(char)*(*zaczytany).x);
        if ((*tablica)[i]==NULL)
        {
            for(int j=0; j<i; j++)
            {
                free((*tablica)[j]);
            }
            free(*tablica);
            fprintf(stderr, "Blad przypisania pamieci dynamicznej\n");
            return 7;
        }
    }
    for(int i=0; i<(*zaczytany).y; i++)
    {
        for(int j=0; j<(*zaczytany).x; j++)
        {
            (*tablica)[i][j]='.';
        }
    }
    return 0;
}
int wyswietlPlan(pokoj *zaczytany, char** tablica)
/*
##########################################################################################################################################
PRE:
Wskaznik na struktur pokoju, wskaznik na tablice
POST:
Kod bledu
CEL:
Wyswietlic tablice
OPIS DZIALANIA:
Program iteruje po kolejnych polach wyswietlajac jes
OBSLUGA BLEDOW:
-
##########################################################################################################################################
*/
{
    for(int i=0; i<(*zaczytany).y; i++)
    {
        for(int j=0; j<(*zaczytany).x; j++)
        {
            printf("%c", tablica[i][j]);
        }
        printf("\n");
    }
    return 0;
}
int wstawMebel(pokoj* zaczytany, int rodzajMebla, char*** tablica)
/*
##########################################################################################################################################
PRE:
Wskaznik do pokoju, kod mebla, wskaznik na tablice planu
POST:
Edycja tablicy w wybrany sposob, kod bledu
CEL:
Wstawic symbole mebla na plan
OPIS DZIALANIA:
Deklarujemy zmienne pomocnicze kotre posluza do komunikacji z uzytkownikiem. Nstepnie uzytkownik wybiera w jaki sposob i gdzie chce
wstawic meble. Zalaczamy instrukcej switch ktora ustawia parametry zaczytanego mebla. Sprawdzamy czy zaczytane dane spelniaja warunki
znalezienia sie na tablicy. Funkcja wchodzi do petli gdzie iteruje po i od pion do pion+wysokosc i j od poziom do poziom+szerokosc podczas
iteracji sprawdza czy nie nastapi kolizja mebli. Jezeli nie przechodzi do drugiej takiej samej petli i wypelnia wybrane pola.
OBSLUGA BLEDOW:
Kod 11 - Blad orientacji mebla
Kod 10 - Blad opcji do przemieszczania sie po programie
Kod 12 - Blad okreslenia wspolrzednych
Kod 13 - Kolizja mebli
##########################################################################################################################################
*/
{
    char symbol;
    int orientacja, poziom, pion, wysokosc, szerokosc;
    printf("Podaj orientacje mebla: (0-poziom, 1-pion): " );
    scanf("%d", &orientacja);
    if(orientacja!=0 && orientacja!=1)
    {
        fprintf(stderr, "Blad orientacji mebla\n");
        return 11;
    }
    printf("Podaj pozioma wspolrzedna mebla: ");
    scanf("%d", &poziom);
    printf("Podaj pionowa wspolrzedna mebla: ");
    scanf("%d", &pion);
    switch(rodzajMebla)
    {
    case 1:
        symbol='L';
        if(orientacja==0)
        {
            wysokosc=1;
            szerokosc=2;
        }
        else if(orientacja==1)
        {
            wysokosc=2;
            szerokosc=1;
        }
        else
        {
            fprintf(stderr, "Blad orientacji mebla\n");
            return 11;
        }
        break;
    case 2:
        symbol='B';
        if(orientacja==0)
        {
            wysokosc=1;
            szerokosc=2;
        }
        else if(orientacja==1)
        {
            wysokosc=2;
            szerokosc=1;
        }
        else
        {
            fprintf(stderr, "Blad orientacji mebla\n");
            return 11;
        }
        break;
    case 3:
         symbol='S';
        if(orientacja==0)
        {
            wysokosc=1;
            szerokosc=3;
        }
        else if(orientacja==1)
        {
            wysokosc=3;
            szerokosc=1;
        }
        else
        {
            fprintf(stderr, "Blad orientacji mebla\n");
            return 11;
        }
        break;
    case 4:
        symbol='K';
        if(orientacja==0)
        {
            wysokosc=1;
            szerokosc=1;
        }
        else if(orientacja==1)
        {
            wysokosc=1;
            szerokosc=1;
        }
        else
        {
            fprintf(stderr, "Blad orientacji mebla\n");
            return 11;
        }
        break;
    default:
        fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
        return 10;
    }
    if (poziom<0 || pion<0 || poziom+szerokosc > (*zaczytany).x || pion+wysokosc > (*zaczytany).y)
    {
        fprintf(stderr, "Blad okreslenia wspolrzednych (indeksy poza tablica)\n");
        return 12;
    }
    for(int i=pion; i<pion+wysokosc; i++)
    {
        for(int j=poziom; j<poziom+szerokosc; j++)
        {
            if((*tablica)[i][j]!='.')
            {
                fprintf(stderr, "Kolizja mebli\n");
                return 13;
            }
        }
    }
    for(int i=pion; i<pion+wysokosc; i++)
    {
        for(int j=poziom; j<poziom+szerokosc; j++)
        {
            (*tablica)[i][j]=symbol;
        }
    }
    return 0;
}
int wczytajPlan(pokoj *zaczytany, char*** tablica, char* nazwaPokoju)
/*
##########################################################################################################################################
PRE:
Wskaznik na strukture pokoju, wskaznik na tablice planu, wskaznik na litreal napisowy nazwy pokoju
POST:
Alokacja tablicy na podstawie danych z pliku
CEL:
Utworzyc plan z poprzedniego zapisu
OPIS DZIALANIA:
Deklarujemy zmienna sciezka kotra dziala tak samo jak w przypadku struktur pokoji. Otwieramuy plik o nazwie "<nazwaPokoju>_plan.txt" i z 
niego zaczytujemy informacje o obecnym stanie planie pokoju. Sprawdzamy czy to sie udalo a nastepnie alokujemy tablice dynamiczna 
sprawdzajac czy to sie udalo. Potem deklarujemy kolejne kolumny z ewentualna obsluga bledow. Po poprawnej alokacji wypelniamy tablice 
znak po znaku z obsluga konca pliku
OBSLUGA BLEDOW:
Kod 4 - Blad otwarcia pliku
Kod 7 - Blad przypisania pamieci dynamicznej
##########################################################################################################################################
*/
{
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s_plan.txt", nazwaPokoju);
    FILE* plik = fopen(sciezka, "r");
    if(plik == NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    *tablica = malloc(sizeof(char*)*(*zaczytany).y);
    if (*tablica==NULL)
    {
        fprintf(stderr, "Blad przypisania pamieci dynamicznej\n");
        fclose(plik);
        return 7;
    }
    for(int i=0; i<(*zaczytany).y; i++)
    {
        (*tablica)[i] = malloc(sizeof(char)*(*zaczytany).x);
        if ((*tablica)[i]==NULL)
        {
            for(int j=0; j<i; j++)
            {
                free((*tablica)[j]);
            }
            free(*tablica);
            fprintf(stderr, "Blad przypisania pamieci dynamicznej\n");
            fclose(plik);
            return 7;
        }
    }
    for(int i=0; i<(*zaczytany).y; i++)
    {
        for(int j=0; j<(*zaczytany).x; j++)
        {
            int c = fgetc(plik);
            if(c == EOF)
            {
                (*tablica)[i][j] = '.';
            }
            else
            {
                (*tablica)[i][j] = c;
            }
        }
        fgetc(plik);
    }
    fclose(plik);
    return 0;
}
int zapiszPlan(pokoj* zaczytany, char** tablica, char* nazwaPokoju)
/*
##########################################################################################################################################
PRE:
Wskaznik na strukture z pokojem, wskaznik na tablice z planem, wskaznik na literal napisowy z nazwa pokoju
POST:
Przekazanie tablicy do pliku
CEL:
Zapisanie informacji o obecnym rozkladzie mebli na planie pokoju
OPIS DZIALANIA:
Definiujem zmienna pomocnicza sciezka a nastepnie odpalamy plik sciezka do nadpisania. Jezeli sie nei otworzy zwracamy blad. Natmoiast w 
razie sukcesu zapisujemy znak po znaku plan w pliku.
OBSLUGA BLEDOW:
Kod 4 - Blad otwarcia pliku
##########################################################################################################################################
*/
{
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s_plan.txt", nazwaPokoju);
    FILE* plik = fopen(sciezka, "w");
    if(plik == NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    for(int i=0; i<(*zaczytany).y; i++)
    {
        for(int j=0; j<(*zaczytany).x; j++)
        {
            fputc(tablica[i][j], plik);
        }
        fputc('\n', plik);
    }
    fclose(plik);
    return 0;
}