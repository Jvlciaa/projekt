#include <stdio.h>
#include <string.h>
#include "artefakt.h"

const char* status_na_napis(StatusArtefaktu s) {
    switch (s) {
        case BEZPIECZNY: return "Bezpieczny";
        case NIESTABILNY: return "Niestabilny";
        case ZAKAZANY: return "Zakazany";
        case KWARANTANNA: return "Kwarantanna";
        case W_TRAKCIE_BADAN: return "W trakcie badan";
        default: return "Nieznany";
    }
}

StatusArtefaktu napis_na_status(const char* s) {
    if (strcmp(s, "Bezpieczny") == 0) return BEZPIECZNY;
    if (strcmp(s, "Niestabilny") == 0) return NIESTABILNY;
    if (strcmp(s, "Zakazany") == 0) return ZAKAZANY;
    if (strcmp(s, "Kwarantanna") == 0) return KWARANTANNA;
    if (strcmp(s, "W trakcie badan") == 0) return W_TRAKCIE_BADAN;
    return STATUS_UNKNOWN;
}

void wyswietl_naglowek() {
    printf("\n%-20s | %-15s | %-15s | %-5s | %-6s | %s\n",
           "NAZWA", "POCHODZENIE", "CYWILIZACJA", "ZAGR", "ROK", "STATUS");
    printf("--------------------------------------------------------------------------------------\n");
}

void wyswietl_wiersz(const Artefakt* art) {
    printf("%-20.20s | %-15.15s | %-15.15s | %-5d | %-6d | %s\n",
           art->nazwa, art->pochodzenie, art->cywilizacja,
           art->poziom_zagrozenia, art->rok_odkrycia, status_na_napis(art->status));
}