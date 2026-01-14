#ifndef DEFS_H
#define DEFS_H

#include <stddef.h>

#define MAX_NAME 100
#define MAX_TEXT 50
#define MAX_PATH 256

// Struktura pojedynczego artefaktu
typedef struct {
    char nazwa[MAX_NAME + 1];           // Unikalny identyfikator
    char pochodzenie[MAX_TEXT + 1];
    char cywilizacja[MAX_TEXT + 1];
    int poziom_zagrozenia;              // 0-10
    int rok_odkrycia;
    char status[MAX_TEXT + 1];
} Artefakt;

// Struktura kolekcji (sterta)
typedef struct {
    Artefakt *tablica;  // Wskaźnik do dynamicznej tablicy
    size_t licznik;     // Aktualna liczba elementów
    size_t pojemnosc;   // Zaalokowana pojemność
} Archiwum;

#endif