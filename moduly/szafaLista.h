#define ROZMIAR 64
#ifndef STRUKTURA_SZAFY_H
#define STRUKTURA_SZAFY_H
typedef struct przedmiot
{
    char nazwa[ROZMIAR];
    struct przedmiot* kolejny;
}przedmiot;
#endif

przedmiot* zainicjujPrzedmiot(char nazwa[ROZMIAR]);
void odlozPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR]);
void wyjmijPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR]);
void znajdzPrzedmiot(przedmiot** glowa, char nazwa[ROZMIAR]);