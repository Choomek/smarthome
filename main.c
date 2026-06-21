#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentyWywolaniaProgramu.h"
#include "obslugaPokoi.h"
#include "rolety.h"
#include "swiatla.h"
#include "okna.h"
#include "temperatura.h"
#include "szafa.h"
#include "planPokoju.h"
int main(int argc, char *argv[])
{
    /*
    Witam w kodzie zrodlowym programu smathome, przed zaczeciem analizy polecam zapoznac sie z README

    Zmienne:

    zaczytany - wskaznik na strukture z pokojem ktory jest obecnie obslugiwany przez program

    kod - kazde wywolanie funkcji z modulow zwraca kod bledu lub 0, zmienna kod pozwala na zaawansowana obsluge bledow,
    weryfikujemy kazde wywolanie zewnetrznych funkcji i sprawdzamy czy zwraca cos innego niz 0 (blad) jezeli tak to
    informujemy uzytkownika i zakanczamy program z odpowiednim kodem

    zmiennaPrzelaczajaca - zmienna pomocnicza w instrukcji switch

    nazwa - nazwa pliku z ktorego zaczytujemy dane pokoju

    t - struktura zwierajaca informacje ktore opcje sa uzyte podczas wywolania

    tablica - tablica zawierajaca plan pokoju
    */
    pokoj *zaczytany=NULL;
    int kod, zmiennaPrzelaczajaca;
    char *nazwa = NULL;
    tryby t;
    char** tablica = NULL;
    /*
    W linijkach 19-43 dokonujemy analizy opcji programu i dostosowywujemu jego dzialanie do oczekiwan uzytkownika
    */
    kod=opcje(argc, argv, &t, &nazwa);
    if(kod != 0)
    {
        return kod;
    }
    if(t.trybRejestracji)
    {
        kod=rejestracja(nazwa);
        if (kod != 0)
        {
            return kod;
        }
    }
    if(t.trybLogowania)
    {

        kod=logowanie(nazwa, &zaczytany);
        if (kod != 0)
        {
            return kod;
        }
        kod=wczytajPlan(zaczytany, &tablica, nazwa);
        if (kod != 0)
        {
            utworzPlan(zaczytany, &tablica);
        }  
    }
    if(t.trybLogowania == 0)
    {
        return 0;
    }
    /*
    W linijkach 47-90 wyswietlamy glowny interfejs programu
    */
    start:
    printf("\033[2J\033[H"); 
    printf("                                 ----- Obecnie obslugujesz pokoj: %s -----\n", nazwa);
    printf("###################################################################################################################\n");
    printf("#                                 Witam bardzo serdecznie w programie smarthome!                                  #\n");
    printf("###################################################################################################################\n");
    printf("                                 ----- Informacje o twoim pokoju: -----\n");
    printf("                                 1. Rozmiar:               %d m^2\n", (*zaczytany).powierzchnia);
    printf("                                 2. Temperatura grzejnika: %f *C\n", (*zaczytany).temperaturaGrzejnika);
    printf("                                 3. Temperatura pokoju:    %f *C\n", (*zaczytany).temperaturaPokoju);
    if((*zaczytany).swiatla == 1)
    {
        printf("                                 4. Stan swiatla:          zapalone\n");
    }
    else
    {
        printf("                                 4. Stan swiatla:          zgaszone\n");
    }
    if((*zaczytany).rolety == 0)
    {
        printf("                                 5. Stan rolet:            odsloniete\n");
    }
    else
    {
        printf("                                 5. Stan rolet:            zasloniete\n");
    }
    if((*zaczytany).czujnikOkna == 1)
    {
        printf("                                 6. Stan okna:             otwarte\n");
    }
    else
    {
        printf("                                 6. Stan okna:             zamkniete\n");
    }
    printf("###################################################################################################################\n");
    printf("#                                               Plan pokoju                                                       #\n");
    printf("###################################################################################################################\n");
    wyswietlPlan(zaczytany, tablica);
    printf("###################################################################################################################\n");
    printf("#                                  Wybierz co chcesz zrobic:                                                      #\n");
    printf("#                                   1.Usun pokoj                                                                  #\n");
    printf("#                                   2.Dostosuj temperature                                                        #\n");
    printf("#                                   3.Wlacz/wylacz swiatla                                                        #\n");
    printf("#                                   4.Podnies/opusc rolety                                                        #\n");
    printf("#                                   5.Otworz/zamknij okno                                                         #\n");
    printf("#                                   6.Szafa                                                                       #\n");
    printf("#                                   7.Plan pokoju                                                                 #\n");
    printf("#                                   8.Zakoncz dzialanie                                                           #\n");
    printf("###################################################################################################################\n");
    printf("Twoja opcja: ");
    scanf("%d", &zmiennaPrzelaczajaca);
    /*
    W linijkach 94-220 bedziemy poruszac sie po roznych mozliwosciach programu
    */
    switch (zmiennaPrzelaczajaca)
    {
    case 1:
    {
        char weryfikacja[32];
        printf("Potwierdz usuniecie wpisujac: potwierdzam (by powrocic do glownego panelu wpisz bledny ciag znakow)\n");
        if (scanf("%31s", weryfikacja) != 1) 
        {
            goto start;
        }
        if(strcmp(weryfikacja, "potwierdzam") == 0)
        {
            kod = usunPokoj(nazwa);
            if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }
        }
        else
        {
            goto start;
        }
        break;
    }
    case 2:
        kod = temperatura(zaczytany);
        if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }
        goto start;
    case 3:
        kod = swiatla(zaczytany);
        if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }
        goto start;
        break;
    case 4:
        kod = rolety(zaczytany);
        if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }
        goto start;
        break;
    case 5:
        kod = okna(zaczytany);
        if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }
        goto start;
        break;
    case 6:
        kod = szafa(nazwa);
        if (kod != 0)
        {
            free(zaczytany);
            return kod;
        }
        goto start;
        break;
    case 7:
        kod = plan(zaczytany, &tablica, nazwa);
        if (kod != 0)
        {
            free(zaczytany);
            return kod;
        }
        goto start;
        break;
    case 8:
        kod = zapisywanie(nazwa, zaczytany);;
            if (kod != 0)
            {
                free(zaczytany);
                return kod;
            }        
        zapiszPlan(zaczytany, tablica, nazwa);
        free(zaczytany);
        free(tablica);
        return 0;
    default:
        fprintf(stderr, "Blad opcji do przemieszczania sie po programie\n");
        free(zaczytany);
        return 10;
    }
}