#ifndef ARTEFAKT_H
#define ARTEFAKT_H

#define MAX_NAZWA 100
#define MAX_POCHODZENIE 50
#define MAX_CYWILIZACJA 50

typedef enum {
    BEZPIECZNY = 0,
    NIESTABILNY,
    ZAKAZANY,
    KWARANTANNA,
    W_TRAKCIE_BADAN,
    STATUS_UNKNOWN
} StatusArtefaktu;

typedef struct {
    char nazwa[MAX_NAZWA + 1];
    char pochodzenie[MAX_POCHODZENIE + 1];
    char cywilizacja[MAX_CYWILIZACJA + 1];
    int poziom_zagrozenia;
    int rok_odkrycia;
    StatusArtefaktu status;
} Artefakt;

typedef struct {
    Artefakt* tablica;
    int rozmiar;
    int pojemnosc;
} Archiwum;

const char* status_na_napis(StatusArtefaktu s);
StatusArtefaktu napis_na_status(const char* s);
void wyswietl_naglowek();
void wyswietl_wiersz(const Artefakt* art);

#endif