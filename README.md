Program smarthome2 to program sluzacy do zaawansowanej obslugi domu.

### 1. AUTOR ###

Adam Olkiewicz, 292778

### 2. OGOLNE INFORMACJE O OBSLUDZE PROGRAMU ###

By uruchomic program nalezy to zrobic z poziomu terminala znajdujac sie w katalogu ./smarthome2 i uzyc komendy
./smarthome.out wykorzystujac conajmniej jedna z 2 opcji bez nich program nie zadziala.

Tymi opcjami sa:
-r <"Nazwa"> - "tryb rejestracji" czyli utworzenie pokoju o podanej nazwie i podanej jego podstawowych parametrow
-l <"Nazwa"> - "tryb logowania" czyli otworzenie pokoju o podanej nazwie i wywietlenie interfejsu programu

Oczywiscie opcje mozna laczyc w dowolnej konfiguracji takiej jak inne polecenia unixowe by za pomoca jednego
polecenia stworzyc i otworzyc plik.

### 3. KOMPILACJA ###

gcc -I./moduly -o smarthome.out main.c programy/*.c

### 4. ZASADA DZIALANIA PRACY Z PLIKIEM PRZEZ PROGRAM ###

rejestracja() - zaczytuje dane od uzytkownika i tworzy z nich plik.
logowanie() - zaczytuje dane z pliku i tworzy z nich strukture.
zapisywnie() - zaczytuje dane ze struktury i tworzy z nich plik.

Rejestracja kazdego pokoju dokonuje sie tylko raz i tworzy pierwsza wersje pliku .txt. Kazde otworzenie pliku w
programie tworzy z niego strukture, a kazde kontrolowane zamkniecie (takie ktore nie konczy sie kodem bledu)
zaczytuje dane ze struktury i nadpisuje istniejacy plik by przechwowywac dane podczas gdy program jest wylaczony.

### 5. OPIS FUNKCJI PROGRAMU ###

Temperatura - pozwala na regulacje temperatury grzejnika, na ktorej podstawie szacowana jest temperatura pokoju.
Zaczytywana jest obecna temperatura grzejnika natomiast potem mozna regulowac zarowno bezposrednio ta temperature
jak i podac oczekiwana temperature pokoju na podstawie ktorej program za pomoca rownania ustawi szacowana wartosc
temperatury grzejnika.

Swiatla, Rolety, Okna - za pomoca logicznych wartosci {0, 1} opisanych przy ich podawaniu mozna zadecydowac o dwoch
stanach tych elementow pokoju. Podobnie jak z temperatura trzeba zaczytac obecne stany a nastepnie za pomoca
programu je zmieniac.

Szafa - zbior funkcji do zapamietywania przedmiotow znajdujacych sie w szafie. Uzytkownik na liscie tworzy baze
danych ktora po kazdym wyjeciu/wlozeniu przedmiotu do szafy powinien aktualizowac. Uzytkownik moze wpisac nazwe 
przedmiotu i dowiedziec sie czy znajduje sie on w szafie.

Plan - fragment programu posiwecony rozkladowi mebli w pokoju. Dziala na bazie tablicy dwuwymiarowej oraz pozwala na
rozklad mebli wedle zyczenia uzytkownika. W obecnej wersji dostepne sa 4 rodzaje mebli ktore zajmuja odpowiednia
liczbe pol. Uzytkownik moze je rozkladac w dowolnej orientacji i we wybranych miejscach. Tablica jest zapisywana w 
osobnym pliku.

### 6. OBLSUGA BLEDOW ###

Program posiada bogata obsluge bledow kazdy przypadek ma swoj kod zwracany przez program oraz komunikat na strumieniu
bledow. Od poczatku przyjeta jest zasade; jezeli uzytkownik popelni blad program zakancza swoje dzialanie, zwraca kod
bledu oraz komunikat natomiast jezeli plik jest niekompatybilny program zakancza dzialanie, zwraca kod bledu, informacje
oraz usuwa plik. Dodatkowo informacje o kodach sa w pliku kodyBledu.txt oraz dokumentacji poszczegolnych funkcji.

### 7. DOKUMENTACJA ###

Kazda funkcja w programie jest dokumentowana wedlug wzoru okreslonego w templateDokumentacji.txt oraz funkcja main
posiada dodatkowe opisy pomagajace zrozumiec dzialanie programu jako calosci.