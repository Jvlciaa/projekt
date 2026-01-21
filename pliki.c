#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pliki.h"
#include "baza.h"

int zapisz_do_pliku(const Archiwum* arch, const char* nazwa_pliku) {
    FILE* plik = fopen(nazwa_pliku, "w");
    if (!plik) return -1;

    for (int i = 0; i < arch->rozmiar; i++) {
        Artefakt* a = &arch->tablica[i];
        fprintf(plik, "%s|%s|%s|%d|%d|%s\n",
                a->nazwa,
                a->pochodzenie,
                a->cywilizacja,
                a->poziom_zagrozenia,
                a->rok_odkrycia,
                status_na_napis(a->status));
    }
    fclose(plik);
    return 0;
}

int wczytaj_z_pliku(Archiwum* arch, const char* nazwa_pliku) {
    FILE* plik = fopen(nazwa_pliku, "r");
    if (!plik) return -1;

    char bufor[512];
    int licznik = 0;

    while (fgets(bufor, sizeof(bufor), plik)) {
        Artefakt a;
        char status_str[50];

        if (sscanf(bufor, "%[^|]|%[^|]|%[^|]|%d|%d|%[^\n]",
                   a.nazwa, a.pochodzenie, a.cywilizacja,
                   &a.poziom_zagrozenia, &a.rok_odkrycia, status_str) == 6) {
            
            a.status = napis_na_status(status_str);
            dodaj_artefakt(arch, a);
            licznik++;
        }
    }
    fclose(plik);
    return licznik;
}