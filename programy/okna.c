#include <stdio.h>
#include "okna.h"
#include "strukturaPokoju.h"
int okna(pokoj *zaczytany)
/*
##########################################################################################################################################
PRE:
Wskaznik do struktury z pokojem.
POST:
Zmiana bitu ktory informowal o stanie okna oraz kod bledu lub informacja o sukcesie.
CEL:
Przelaczyc stan okna wedlug zyczenia uzytkownika.
OPIS DZIALANIA:
Wyswietlamy interfejsy do obslugi zmian warunkowo czyli zaleznie od obecnego stanu potem dajemy uzytkownikowi opcje by zmienic stan 
okna z pomoca switcha.
OBSLUGA BLEDOW:
Kod 10 - blad przemieszczania sie po programie.
##########################################################################################################################################
*/
{
    int zmiennaPrzelaczajaca;
    printf("###################################################################################################################\n");
    if((*zaczytany).czujnikOkna == 0)
    {
        printf("#                                 Okna zamkniete czy chcesz je otworzyc?                                          #\n");
        printf("#                                 1. Tak                                                                          #\n");
        printf("#                                 2. Nie                                                                          #\n");
        printf("###################################################################################################################\n");
        printf("Twoja opcja: ");
        scanf("%d", &zmiennaPrzelaczajaca);
        switch (zmiennaPrzelaczajaca)
        {
        case 1:
            (*zaczytany).czujnikOkna = 1;
            break;
        case 2:
            return 0;
        default:
            fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
            return 10;
        }
    }
    else
    {
        printf("#                                 Okna otwarte czy chcesz je zamknac?                                             #\n");
        printf("#                                 1. Tak                                                                          #\n");
        printf("#                                 2. Nie                                                                          #\n");
        printf("###################################################################################################################\n");
        printf("Twoja opcja: ");
        scanf("%d", &zmiennaPrzelaczajaca);
        switch (zmiennaPrzelaczajaca)
        {
        case 1:
            (*zaczytany).czujnikOkna = 0;
            break;
        case 2:
            return 0;
        default:
            fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
            return 10;
        }
    }
    return 0;
}