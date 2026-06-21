#include "strukturaPokoju.h"
int plan(pokoj *zaczytany, char*** tablica, char* nazwaPokoju);
int utworzPlan(pokoj *zaczytany, char*** tablica);
int wyswietlPlan(pokoj *zaczytany, char** tablica);
int wstawMebel(pokoj* zaczytany, int rodzajMebla, char*** tablica);
int wczytajPlan(pokoj *zaczytany, char*** tablica, char* nazwaPokoju);
int zapiszPlan(pokoj* zaczytany, char** tablica, char* nazwaPokoju);