#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "baza.h"

void inicjalizuj_archiwum(Archiwum* arch) {
    arch->rozmiar = 0;
    arch->pojemnosc = 10;
    arch->tablica = (Artefakt*)malloc(arch->pojemnosc * sizeof(Artefakt));
    if (!arch->tablica) {
        exit(1);
    }
}

void zwolnij_archiwum(Archiwum* arch) {
    if (arch->tablica) {
        free(arch->tablica);
        arch->tablica = NULL;
    }
    arch->rozmiar = 0;
    arch->pojemnosc = 0;
}

int dodaj_artefakt(Archiwum* arch, Artefakt nowy) {
    if (znajdz_indeks_po_nazwie(arch, nowy.nazwa) != -1) return -2;

    if (arch->rozmiar == arch->pojemnosc) {
        arch->pojemnosc *= 2;
        Artefakt* tmp = (Artefakt*)realloc(arch->tablica, arch->pojemnosc * sizeof(Artefakt));
        if (!tmp) return -1;
        arch->tablica = tmp;
    }
    arch->tablica[arch->rozmiar] = nowy;
    arch->rozmiar++;
    return 0;
}

int usun_artefakt(Archiwum* arch, int indeks) {
    if (indeks < 0 || indeks >= arch->rozmiar) return -1;

    if (arch->tablica[indeks].poziom_zagrozenia >= 8) {
        return -3;
    }

    for (int i = indeks; i < arch->rozmiar - 1; i++) {
        arch->tablica[i] = arch->tablica[i + 1];
    }
    arch->rozmiar--;
    return 0;
}

int edytuj_artefakt(Archiwum* arch, int indeks, Artefakt zaktualizowany) {
    if (indeks < 0 || indeks >= arch->rozmiar) return -1;
    strcpy(zaktualizowany.nazwa, arch->tablica[indeks].nazwa);
    arch->tablica[indeks] = zaktualizowany;
    return 0;
}

int znajdz_indeks_po_nazwie(Archiwum* arch, const char* nazwa) {
    for (int i = 0; i < arch->rozmiar; i++) {
        if (strcmp(arch->tablica[i].nazwa, nazwa) == 0) return i;
    }
    return -1;
}

int zawiera_fraze(const char* tekst, const char* fraza) {
    char t[MAX_NAZWA], f[MAX_NAZWA];
    int i = 0;
    while(tekst[i] && i < MAX_NAZWA) { t[i] = tolower(tekst[i]); i++; } t[i] = 0;
    i = 0;
    while(fraza[i] && i < MAX_NAZWA) { f[i] = tolower(fraza[i]); i++; } f[i] = 0;
    return strstr(t, f) != NULL;
}

void wyszukaj_tekstowo(Archiwum* arch, const char* fraza) {
    wyswietl_naglowek();
    int znaleziono = 0;
    for (int i = 0; i < arch->rozmiar; i++) {
        if (zawiera_fraze(arch->tablica[i].nazwa, fraza) ||
            zawiera_fraze(arch->tablica[i].pochodzenie, fraza) ||
            zawiera_fraze(arch->tablica[i].cywilizacja, fraza)) {
            wyswietl_wiersz(&arch->tablica[i]);
            znaleziono++;
        }
    }
    if (znaleziono == 0) printf("Brak wynikow.\n");
}

void wyszukaj_zagrozenie(Archiwum* arch, int min, int max) {
    wyswietl_naglowek();
    int znaleziono = 0;
    for (int i = 0; i < arch->rozmiar; i++) {
        if (arch->tablica[i].poziom_zagrozenia >= min && 
            arch->tablica[i].poziom_zagrozenia <= max) {
            wyswietl_wiersz(&arch->tablica[i]);
            znaleziono++;
        }
    }
    if (znaleziono == 0) printf("Brak wynikow.\n");
}

int porownaj_nazwy(const void* a, const void* b) {
    Artefakt* artA = *(Artefakt**)a;
    Artefakt* artB = *(Artefakt**)b;
    return strcmp(artA->nazwa, artB->nazwa);
}

int porownaj_zagrozenie(const void* a, const void* b) {
    Artefakt* artA = *(Artefakt**)a;
    Artefakt* artB = *(Artefakt**)b;
    return artB->poziom_zagrozenia - artA->poziom_zagrozenia;
}

void sortuj_i_wyswietl(Archiwum* arch, int kryterium) {
    if (arch->rozmiar == 0) return;

    Artefakt** wskazniki = malloc(arch->rozmiar * sizeof(Artefakt*));
    if (!wskazniki) return;

    for(int i = 0; i < arch->rozmiar; i++) {
        wskazniki[i] = &arch->tablica[i];
    }

    if (kryterium == 0)
        qsort(wskazniki, arch->rozmiar, sizeof(Artefakt*), porownaj_nazwy);
    else
        qsort(wskazniki, arch->rozmiar, sizeof(Artefakt*), porownaj_zagrozenie);

    wyswietl_naglowek();
    for(int i = 0; i < arch->rozmiar; i++) {
        wyswietl_wiersz(wskazniki[i]);
    }
    free(wskazniki);
}