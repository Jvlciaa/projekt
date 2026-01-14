#ifndef FILE_IO_H
#define FILE_IO_H

#include "defs.h"

int zapisz_do_pliku(const Archiwum *arch, const char *nazwa_pliku);
int wczytaj_z_pliku(Archiwum *arch, const char *nazwa_pliku);

#endif