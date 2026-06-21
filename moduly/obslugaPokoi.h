#include "strukturaPokoju.h"
int rejestracja(char *nazwa);
int logowanie(char *nazwa, pokoj **dodawany);
int zapisywanie(char* nazwa, pokoj *zapisywany);
int zaczytajPokoj(FILE *source, pokoj **ptr, char *nazwa);
int usunPokoj(char *nazwa);