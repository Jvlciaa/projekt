#ifndef PLIKI_H
#define PLIKI_H

#include "artefakt.h"

int zapisz_do_pliku(const Archiwum* arch, const char* nazwa_pliku);
int wczytaj_z_pliku(Archiwum* arch, const char* nazwa_pliku);

#endif