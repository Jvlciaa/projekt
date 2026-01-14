#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int zapisz_do_pliku(const Archiwum *arch, const char *nazwa_pliku) {
    FILE *fp = fopen(nazwa_pliku, "w");
    if (!fp) return 0;

    // Zapisujemy liczbę elementów na początku
    fprintf(fp, "%zu\n", arch->licznik);
    for (size_t i = 0; i < arch->licznik; i++) {
        Artefakt *a = &arch->tablica[i];
        // Używamy ; jako separatora
        fprintf(fp, "%s;%s;%s;%d;%d;%s\n",
                a->nazwa, a->pochodzenie, a->cywilizacja,
                a->poziom_zagrozenia, a->rok_odkrycia, a->status);
    }
    fclose(fp);
    return 1;
}

int wczytaj_z_pliku(Archiwum *arch, const char *nazwa_pliku) {
    FILE *fp = fopen(nazwa_pliku, "r");
    if (!fp) return 0;

    size_t ilosc = 0;
    if (fscanf(fp, "%zu\n", &ilosc) != 1) {
        fclose(fp);
        return -1; // Błąd formatu
    }

    // Alokacja pamięci
    zwolnij_archiwum(arch); // Czyścimy obecną pamięć
    if (ilosc > 0) {
        arch->tablica = malloc(ilosc * sizeof(Artefakt));
        if (!arch->tablica) { fclose(fp); return -2; } // Błąd pamięci
        arch->pojemnosc = ilosc;
    }

    char bufor[1024];
    size_t wczytane = 0;
    
    while (wczytane < ilosc && fgets(bufor, sizeof(bufor), fp)) {
        Artefakt *a = &arch->tablica[wczytane];
        // Parsowanie linii: nazwa;pochodzenie;cywilizacja;zagrozenie;rok;status
        // %[^\n] nie zadziała dobrze z sscanf przy delimiterach, użyjmy strtok lub manualnego skanu
        // Użyjemy prostej metody ze sscanf i zestawem znaków [^;]
        
        // Uwaga: sscanf jest wrażliwy. W realnym projekcie lepiej użyć strtok.
        // Tutaj dla czytelności użyjemy sscanf z formatem
        int res = sscanf(bufor, "%[^;];%[^;];%[^;];%d;%d;%[^\n]",
               a->nazwa, a->pochodzenie, a->cywilizacja,
               &a->poziom_zagrozenia, &a->rok_odkrycia, a->status);
               
        if (res == 6) {
            wczytane++;
        }
    }

    arch->licznik = wczytane;
    fclose(fp);
    return 1;
}