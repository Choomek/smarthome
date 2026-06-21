#include "temperatura.h"
#include <stdio.h>
int temperatura(pokoj *zaczytany)
/*
##########################################################################################################################################
PRE:
Wskaznik do struktury z pokojem.
POST:
Zmiana wartosci temperatury grzejnika, kod bledu.
CEL:
Zmienic wartosc temperatury grzejnika bezposrednio lub dostosowac ja automatycznie podajc oczekiwana temperature pokoju.
OPIS DZIALANIA:
Wyswietlamy menu funkcji i wchodzimy w instrukcje switch dajac mozliwosc uzytkownikowi dostosowania temperatur pokoju i grzejnika tak by
byly ze soba powiazane wg wzoru szacujacego zaleznosc tych temperatur.
OBSLUGA BLEDOW:
Kod 10 - blad przemieszczania sie po programie.
##########################################################################################################################################
*/
{
    int zmiennaPrzelaczajaca;
    float tmp;
    printf("###################################################################################################################\n");
    printf("#                                  Wybierz jak chcesz zmienic temperature:                                        #\n");
    printf("#                                   1.Ustawic temperature grzejnika                                               #\n");
    printf("#                                   2.Ustawic temperature pokoju                                                  #\n");
    printf("###################################################################################################################\n");
    printf("Twoja opcja: ");
    scanf("%d", &zmiennaPrzelaczajaca);
    switch (zmiennaPrzelaczajaca)
    {
    case 1:
        printf("Podaj nowa temperature grzejnika: ");
        scanf("%f", &((*zaczytany).temperaturaGrzejnika));
        if((*zaczytany).temperaturaGrzejnika < 0.0f || (*zaczytany).temperaturaGrzejnika > 55.0f)
        {
            fprintf(stderr, "Blad przypisania danych pokoju\n");
            return 8;
        }
        (*zaczytany).temperaturaPokoju=(*zaczytany).temperaturaGrzejnika/(1+0.01*(*zaczytany).powierzchnia);
        break;
    case 2:
        printf("Podaj nowa temperature pokoju: ");
        scanf("%f", &((*zaczytany).temperaturaPokoju));
        tmp = (*zaczytany).temperaturaPokoju*(1+0.01*(*zaczytany).powierzchnia);
        if((*zaczytany).temperaturaPokoju < 0.0f || (*zaczytany).temperaturaPokoju > 55.0f || tmp < 0.0f || tmp > 55.0f)
        {
            fprintf(stderr, "Blad przypisania danych pokoju\n");
            return 8;
        }
        (*zaczytany).temperaturaGrzejnika=(*zaczytany).temperaturaPokoju*(1+0.01*(*zaczytany).powierzchnia);
        break;
    default:
        fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
        return 10;
    }
    return 0;
}