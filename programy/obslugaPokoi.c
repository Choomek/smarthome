#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "obslugaPokoi.h"
#include "strukturaPokoju.h"
int rejestracja(char *nazwa)
/*
##########################################################################################################################################
PRE:
Nazwa pokoju zaczerpnieta z argumentow wywolania programu.
POST:
Tworzy plik ktory bedzie zawieral informacje o danym pokoju, kod bledu.
CEL:
Funkcja bazujac na napisie podanym przez uzytkownika tworzy plik .txt ktory bedzie zawieral dane jego pokoju i przekazuje go do folderu 
~/smarthome/pokoje.
OPIS DZIALANIA:
Najpierw tworzymy sciezke do pliku z danymi pokoju potem sprawdzamy czy pokoj o podanej nazwie istnieje jezeli nie tworzymy plik kotry
bedzie przechowywac jego dane. Za pomoca strumieni wejscia i wyjscia uzytkownik jest wstanie wprowadzic dane do utworzonego pokoju. Kazda
zaczytana informacja jest weryfikownana.
OBSLUGA BLEDOW:
Kod 4 - blad otwarcia pliku.
Kod 5 - proba utworzenia pokoju ktore juz istnieje.
##########################################################################################################################################
*/
{
    char c;
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    FILE *f = fopen(sciezka, "r");
    if (f != NULL)
    {
        fclose(f);
        fprintf(stderr, "Pokoj o takiej nazwie juz istnieje\n");
        return 5;
    }
    f = fopen(sciezka, "w");
    if (f == NULL)
    {
        fprintf(stderr, "Blad otwarcia plik\n");
        return 4;
    }
    float tempG, tempP;
    int pow, x, y, swiatla, rolety, okna;
    printf("Pierwszy przyblizony wymiar pokoju (liczba calkowita do 10): \n");
    scanf("%d", &x);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "x : %d\n", x);
    printf("Drugi przyblizony wymiar pokoju (liczba calkowita do 10): \n");
    scanf("%d", &y);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "y : %d\n", y);
    pow=x*y;
    fprintf(f, "powierzchnia : %d\n", pow);
    printf("Temperatura grzejnika (od 0 do 55 [*C]): \n");
    scanf("%f", &tempG);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "temperatura grzejnika : %8.6f\n", tempG);
    tempP=tempG/(1+0.01*pow);
    fprintf(f, "temperatura pokoju : %8.6f\n", tempP);
    printf("Status swiatla (0 - off, 1 - on): \n");
    scanf("%d", &swiatla);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "swiatla : %d\n", swiatla);
    printf("Status rolet (0 - gora, 1 - dol): \n");
    scanf("%d", &rolety);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "rolety : %d\n", rolety);
    printf("Status okien (0 - zamkniete, 1 - otwarte): \n");
    scanf("%d", &okna);
    c=getchar();
    if(c!='\n')
    {
        fprintf(stderr, "Blad przypisania danych pokoju\n");
        fclose(f);
        return 8;
    }
    fprintf(f, "okna : %d\n", okna);
    fprintf(f, "szafa :\n");
    fclose(f);
    return 0;
}
int logowanie(char *nazwa, pokoj **dodawany)
/*
##########################################################################################################################################
PRE:
Nazwa pokoju z awp, adres wskaznika na strukture ktore bedzie przechowywac pokoj na ktorym bedziemy przeprowadzac operacje.
POST:
Alokacja i przypisanie do wskaznika struktury na bazie pliku .txt, kod bledu.
CEL:
Z poziomu terminala chcemy uzyskac nazwe pokoju ktorego plik tekstowy bedziemy obrabiac. Funkcja ta wyszukuje pokoju i jezeli go znajdzie
to za pomoca kolejnego modulu alokuje dynamicznie strukture z danymi z pliku.
OPIS DZIALANIA:
Zapisujemy do bufora sciezke pliku za pomoca snprintf by go nie przepelnic oraz by zbudowac "stringa" ktorego przekazujemy do fopen.
Jezeli otwarcie sie nie uda zwracamy informacje i kod bledu. Jezeli sie uda wykonujemy funkjce zaczytajPokoj ktora w skrocie na
podstawie pliku tworzy dynamiczna strukture. W przypadku gdy nie wystapily zadne bledy to podstawiamy za wartosc adresu utworzony wskaznik
na strukture.
OBSLUGA BLEDOW:
Kod 9 - proba logowania do nieistniejacego pokoju.
##########################################################################################################################################
*/
{
    pokoj *alokowany=NULL;
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    FILE *f = fopen(sciezka, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Pokoj o takiej nazwie nie istnieje\n");
        return 9;
    }
    int kod = zaczytajPokoj(f, &alokowany, nazwa);
    fclose(f);
    if (kod != 0)
    {
        return kod;
    }
    *dodawany = alokowany;
    return 0;
}
int zapisywanie(char* nazwa, pokoj *zapisywany)
/*
##########################################################################################################################################
PRE:
Nazwa pliku z informacjami o pokoju ktory jest obslugiwany, wskaznik do struktury z pokojem.
POST:
Kod bledu badz 0 oraz modyfikacja pliku.
CEL:
Zaczytanie do pliku zmian dokonanych w programie by po wylaczeniu programu nie utracic informacji o pokoju.
OPIS DZIALANIA:
Definiujemy sicezke by za jej pomoca otworzyc plik sprawdzamy czy to sie udalo. Jezeli tak zapisujemy obecne informacje ze struktury
do pliku a na koniec go zamykamy.
OBSLUGA BLEDOW:
Kod 4 - blad otwarcia pliku.
##########################################################################################################################################
*/
{
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    FILE *f = fopen(sciezka, "r+");
    if (f == NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku\n");
        return 4;
    }
    fprintf(f, "x : %d\n", (*zapisywany).x);
    fprintf(f, "y : %d\n", (*zapisywany).y);
    fprintf(f, "powierzchnia : %d\n", (*zapisywany).powierzchnia);
    fprintf(f, "temperatura grzejnika : %8.6f\n", (*zapisywany).temperaturaGrzejnika);
    fprintf(f, "temperatura pokoju : %8.6f\n", (*zapisywany).temperaturaPokoju);
    fprintf(f, "swiatla : %d\n", (*zapisywany).swiatla);
    fprintf(f, "rolety : %d\n", (*zapisywany).rolety);
    fprintf(f, "okna : %d\n", (*zapisywany).czujnikOkna);
    fprintf(f, "szafa :\n");
    fclose(f);
    return 0;
}
int zaczytajPokoj(FILE *source, pokoj **ptr, char *nazwa)
/*
##########################################################################################################################################
PRE:
Zrodlo z ktoreg zaczytywane beda informacje do struktury, zewnetrzny wskaznk ktory zapamieta nowy pokoj.
POST:
Dynamiczna struktura zawierajaca informacje o pokoju, kod bledu.
CEL:
Funkcja dynamicznie tworzy strukture ktora bedzie zaczytywac z pliku uzytkownika informacje o pokoju.
OPIS DZIALANIA:
Deklarujemy wskaznik na dynamiczna strukture oraz sparwdzamy czy allokacja sie udala. Jezeli nie zwracamy kod bledu i usuwamy uszkodzony
plik. Nastepnie kazda wartosc jest zaczytywana kolejnymi instrukcjami fscanf. Na koniec do wartosci wskazywanej przez wskaznik zaczytany 
do funkcji podstawiamy utworzona strukture.
OBSLUGA BLEDOW:
Kod 7 - blad przypisania pamieci dynamicznej.
Kod 8 - blad przypisania danych pokoju.
##########################################################################################################################################
*/
{
    *ptr = NULL;
    pokoj *p = malloc(sizeof(pokoj));
    if(p==NULL)
    {
        fprintf(stderr, "Blad przypisania pamieci dynamicznej\n");
        return 7;
    }
    if (fscanf(source, " x : %d", &(*p).x)!=1 || (*p).x < 0 || (*p).x > 10)
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " y : %d", &(*p).y)!=1 || (*p).y < 0 || (*p).y > 10)
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " powierzchnia : %d", &(*p).powierzchnia)!=1 || (*p).powierzchnia < 0 || (*p).powierzchnia > 100)
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " temperatura grzejnika : %f", &(*p).temperaturaGrzejnika) != 1 || (*p).temperaturaGrzejnika < 0.0f || (*p).temperaturaGrzejnika > 55.0f)
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " temperatura pokoju : %f", &(*p).temperaturaPokoju) != 1)
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " swiatla : %d", &(*p).swiatla) != 1 || ((*p).swiatla != 0 && (*p).swiatla != 1))
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " rolety : %d", &(*p).rolety) != 1 || ((*p).rolety != 0 && (*p).rolety != 1))
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    if (fscanf(source, " okna : %d", &(*p).czujnikOkna) != 1 || ((*p).czujnikOkna != 0 && (*p).czujnikOkna != 1))
    {
        fprintf(stderr, "Blad przypisania danych pokoju (plik jest uszkodzony i zostanie usuniety)\n");
        usunPokoj(nazwa);
        free(p);
        p=NULL;
        return 8;
    }
    *ptr = p;
    return 0;
}
int usunPokoj(char *nazwa)
/*
##########################################################################################################################################
PRE:
Nazwa uzytkownika zaczerpnieta z argumentow wywolania programu
POST:
Usuwa plik ktory zawieral informacje o danym uzytkowniku
CEL:
Funkcja bazujac na napisie podanym przez uzytkownika usuwa plik .txt ktory zawieral jego dane
OPIS DZIALANIA
Najpierw tworzymy sciezke do pliku z danymi uzytkowniak potem wykonujemy instrukcje usuwania pliku i sprawdzamy czy zakonczyla sie 
sukcesem jezeli tak zwracamy 0 jezeli nie informujemy o tym oraz zwracamy kod bledu
OBSLUGA BLEDOW:
Kod 6 - blad usuniecia pliku
##########################################################################################################################################
*/
{
    char sciezka[ROZMIAR];
    snprintf(sciezka, sizeof(sciezka), "pokoje/%s.txt", nazwa);
    if (remove(sciezka) == 0)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "Blad usuwania pokoju\n");
        return 6;
    }
}