#include <stdio.h>
#include "swiatla.h"
#include "strukturaPokoju.h"
int swiatla(pokoj *zaczytany)
/*
##########################################################################################################################################
PRE:
Wskaznik do struktury z pokojem.
POST:
Zmiana bitu ktory informowal o stanie swiatla oraz kod bledu lub informacja o sukcesie.
CEL:
Przelaczyc stan swiatla wedlug zyczenia uzytkownika.
OPIS DZIALANIA:
Wyswietlamy interfejsy do obslugi zmian warunkowo czyli zaleznie od obecnego stanu potem dajemy uzytkownikowi opcje by zmienic stan 
swiatla z pomoca switcha.
OBSLUGA BLEDOW:
Kod 10 - blad przemieszczania sie po programie.
##########################################################################################################################################
*/
{
    int zmiennaPrzelaczajaca;
    printf("###################################################################################################################\n");
    if((*zaczytany).swiatla == 0)
    {
        printf("#                                 Swiatla zgaszone czy chcesz je zapalic?                                         #\n");
        printf("#                                 1. Tak                                                                          #\n");
        printf("#                                 2. Nie                                                                          #\n");
        printf("###################################################################################################################\n");
        printf("Twoja opcja: ");
        scanf("%d", &zmiennaPrzelaczajaca);
        switch (zmiennaPrzelaczajaca)
        {
        case 1:
            (*zaczytany).swiatla = 1;
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
        printf("#                                 Swiatla zapalone czy chcesz je zgasic?                                          #\n");
        printf("#                                 1. Tak                                                                          #\n");
        printf("#                                 2. Nie                                                                          #\n");
        printf("###################################################################################################################\n");
        printf("Twoja opcja: ");
        scanf("%d", &zmiennaPrzelaczajaca);
        switch (zmiennaPrzelaczajaca)
        {
        case 1:
            (*zaczytany).swiatla = 0;
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