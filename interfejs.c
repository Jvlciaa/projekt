#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfejs.h"

void wyczysc_bufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void wyswietl_menu() {
    printf("\n=== GALAKTYCZNE ARCHIWUM ARTEFAKTOW ===\n");
    printf("1. Zarejestruj nowy artefakt\n");
    printf("2. Wyswietl wszystkie artefakty\n");
    printf("3. Wyszukaj artefakty\n");
    printf("4. Sortuj liste\n");
    printf("5. Edytuj dane artefaktu\n");
    printf("6. Usun artefakt\n");
    printf("7. Zapisz i Wyjdz\n");
    printf("=======================================\n");
    printf("Wybierz opcje: ");
}

void wczytaj_tekst(const char* prompt, char* bufor, int max_len) {
    printf("%s", prompt);
    if (fgets(bufor, max_len + 1, stdin) != NULL) {
        size_t len = strlen(bufor);
        if (len > 0 && bufor[len - 1] == '\n') {
            bufor[len - 1] = '\0';
        } else {
            wyczysc_bufor();
        }
    }
}

int wczytaj_int(const char* prompt, int min, int max) {
    char bufor[50];
    int wartosc;
    while (1) {
        printf("%s", prompt);
        if (fgets(bufor, sizeof(bufor), stdin) != NULL) {
            char* koniec;
            wartosc = (int)strtol(bufor, &koniec, 10);
            
            if (koniec != bufor && (*koniec == '\n' || *koniec == '\0') && 
                wartosc >= min && wartosc <= max) {
                return wartosc;
            }
        }
        printf("BLAD: Podaj liczbe z zakresu %d-%d.\n", min, max);
    }
}

StatusArtefaktu wczytaj_status() {
    printf("\n0-Bezpieczny, 1-Niestabilny, 2-Zakazany, 3-Kwarantanna, 4-W trakcie badan\n");
    int s = wczytaj_int("Podaj kod statusu: ", 0, 4);
    return (StatusArtefaktu)s;
}

void pauza() {
    printf("\nNacisnij Enter, aby kontynuowac...");
    getchar(); 
}