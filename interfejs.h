#ifndef INTERFEJS_H
#define INTERFEJS_H

#include "artefakt.h"

void wyswietl_menu();
void wczytaj_tekst(const char* prompt, char* bufor, int max_len);
int wczytaj_int(const char* prompt, int min, int max);
StatusArtefaktu wczytaj_status();
void wyczysc_bufor();
void pauza();

#endif