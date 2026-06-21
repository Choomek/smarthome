#include "szafa.h"
#include <stdio.h>
#include <string.h>
#include "szafaLista.h"

int szafa(char *nazwa)
/*
##########################################################################################################################################
PRE:
Nazwa pokoju ktory jest teraz obslugiwany.
POST:
Zeedytowany plik, kod bledu.
CEL:
Edycja pliku by zachowac informacje o przedmiotach w szafie korzystajac z listy.
OPIS DZIALANIA:
Funkcja deklaruje wskaznik na szafe> Nastepnie zaczytuje z pliku informacje i przypisuje pod wskaznik liste. Potem Wyswietla menu szafy
i w zaleznosci od wyboru uzytkownika wykonuje wybrana operacje na liscie. Po wykonaniu operacji zaczytujemy szafe do pliku.
OBSLUGA BLEDOW:
Kod 10 - blad przemieszczania sie po programie.
##########################################################################################################################################
*/
{
    przedmiot* szafa=NULL;
    char nazwaPrzedmiotu[ROZMIAR];
    int zmiennaPrzelaczajaca, kod;
    kod = wczytajSzafe(&szafa, nazwa);
    if (kod != 0)
    {
        return kod;
    }
    printf("###################################################################################################################\n");
    printf("#                                  Wybierz jakiej funkcji chcesz uzyc:                                            #\n");
    printf("#                                   1.Usun wyjety przedmiot z bazy danych                                         #\n");
    printf("#                                   2.Dodaj wlozony przedmiot do bazy danych                                      #\n");
    printf("#                                   3.Poszukaj przedmiotu w szafie                                                #\n");
    printf("#                                   4.Wyjdz z szafy                                                               #\n");
    printf("###################################################################################################################\n");
    printf("Twoja opcja: ");
    scanf("%d", &zmiennaPrzelaczajaca);
    switch (zmiennaPrzelaczajaca)
    {
    case 1:
        printf("Co wyjmujesz z szafy?: ");
        scanf("%63s", nazwaPrzedmiotu);
        wyjmijPrzedmiot(&szafa, nazwaPrzedmiotu);
        kod = zapiszSzafe(&szafa, nazwa);
        if (kod != 0)
        {
            return kod;
        }
        break;
    case 2:
        printf("Co wkladasz do szafy?: ");
        scanf("%63s", nazwaPrzedmiotu);
        odlozPrzedmiot(&szafa, nazwaPrzedmiotu);
        kod = zapiszSzafe(&szafa, nazwa);
        if (kod != 0)
        {
            return kod;
        }
        break;
    case 3:
        printf("Czego szukasz w szafie?: ");
        scanf("%63s", nazwaPrzedmiotu);
        znajdzPrzedmiot(&szafa, nazwaPrzedmiotu);
        kod = zapiszSzafe(&szafa, nazwa);
        if (kod != 0)
        {
            return kod;
        }
        break;
    case 4:
        kod = zapiszSzafe(&szafa, nazwa);
        if (kod != 0)
        {
            return kod;
        }
        return 0;
    default:
        fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
        return 10;
    }
    return 0;
}

int wczytajSzafe(przedmiot** szafa, char* nazwa)
/*
##########################################################################################################################################
PRE:
Wskaznik do listy, nazwa pokoju
POST:
Dodanie danych do listy, kod bledu
CEL:
Zaczytac z pliku pokojowego informacje do listy szafa
OPIS DZIALANIA:
Otwieramy plik z danymi pokoju a nastepnie wykonujemy iteracje dopoki nie znajdziemy linijki "szafa : " lub plik okaze sie uszkodzony i
nieczytelny przez program. W kolejnej petli kolejne linijki pliku pokojowego uzupelniamydanymi z listy.
OBSLUGA BLEDOW:
Kod 4 - Blad otwarcia pliku
Kod 8 - Blad przypisania danych pokoju
##########################################################################################################################################
*/
{
    char sciezka[ROZMIAR], linia[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    FILE *f = fopen(sciezka, "r");
    if (f==NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    do
    {
        if (fgets(linia, ROZMIAR, f) == NULL)
        {
            fprintf(stderr, "Blad przypisania danych pokoju\n");
            fclose(f);
            return 8;
        }
        if (strstr(linia, "szafa :") != NULL)
        {
            break;
        }
    }while(1);
    while (fgets(linia, ROZMIAR, f) != NULL)
    {
        linia[strcspn(linia, "\n")] = '\0';
        odlozPrzedmiot(szafa, linia);
    }
    fclose(f);
    return 0;
}

int zapiszSzafe(przedmiot** szafa, char* nazwa)
/*
##########################################################################################################################################
PRE:
Wskaznik na liste, nazwa pokoju
POST:
Tworzy plik z utworzona szafa, kod bledu
CEL:
Dopisac do istniejacego pliku zawartosc szafy
OPIS DZIALANIA:
Otwieramy 2 pliki; tj. obslugiwanego pokoju oraz pomocniczy. Nastepnie iterujemy po pliku obslugiwanego pokoju dopoki nie dojedziemy do
konca lub cos sie popsuje lub znajdziemy linijke "szafa: ". Kazda linijke petla for przepisujemy by na koncu zamiast \n miala \0 i
zapisujemy do pliku pomocniczego gdy znajdziemy "szafa: " to oznacza ze znalezlismy sie w momencie gdzie przepisalismy do tmp caly pokoj
bez zawartosci szafy. Wychodzimy z petli i zawartosc szafy przepisujemy z listy na koniec podmieniamy pliki tmp z pokojowym i usuwamy
stary plik.
OBSLUGA BLEDOW:
Kod 4 - Blad otwarcia pliku
##########################################################################################################################################
*/
{
    int znalezione=0;
    char sciezka[ROZMIAR], linia[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    FILE *f = fopen(sciezka, "r");
    if (f==NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    FILE *tmp = fopen("temp.txt", "w");
    if (tmp==NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    while (fgets(linia, sizeof(linia), f) != NULL && znalezione != 1)
    {
        for (int i=0; linia[i]!='\0'; i++)
        {
            if (linia[i] == '\n')
            {
                linia[i]='\0';
                break;
            }
        }
        fprintf(tmp, "%s\n", linia);
        if (strstr(linia, "szafa :") != NULL)
        {
            znalezione = 1;
        }
    }
    przedmiot* zapisywany=*szafa;
    for(; zapisywany!= NULL; zapisywany=(*zapisywany).kolejny)
    {
        fprintf(tmp, "%s\n", (*zapisywany).nazwa);
    }
    fclose(f);
    fclose(tmp);
    remove(sciezka);
    rename("temp.txt", sciezka);
    return 0;
}