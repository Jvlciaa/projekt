#ifndef BAZA_H
#define BAZA_H

#include "artefakt.h"

void inicjalizuj_archiwum(Archiwum* arch);
void zwolnij_archiwum(Archiwum* arch);
int dodaj_artefakt(Archiwum* arch, Artefakt nowy);
int usun_artefakt(Archiwum* arch, int indeks);
int edytuj_artefakt(Archiwum* arch, int indeks, Artefakt zaktualizowany);
int znajdz_indeks_po_nazwie(Archiwum* arch, const char* nazwa);
void wyszukaj_tekstowo(Archiwum* arch, const char* fraza);
void wyszukaj_zagrozenie(Archiwum* arch, int min, int max);
void sortuj_i_wyswietl(Archiwum* arch, int kryterium);

#endif