#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"
#include "pliki.h"
#include "interfejs.h"

void obsluga_dodawania(Archiwum* arch) {
    Artefakt a;
    wczytaj_tekst("Nazwa (ID): ", a.nazwa, MAX_NAZWA);
    wczytaj_tekst("Pochodzenie: ", a.pochodzenie, MAX_POCHODZENIE);
    wczytaj_tekst("Cywilizacja Tworcow: ", a.cywilizacja, MAX_CYWILIZACJA);
    a.poziom_zagrozenia = wczytaj_int("Poziom zagrozenia (0-10): ", 0, 10);
    a.rok_odkrycia = wczytaj_int("Rok odkrycia (2000-3000): ", 2000, 3000);
    a.status = wczytaj_status();

    int wynik = dodaj_artefakt(arch, a);
    if (wynik == 0) printf("Artefakt zarejestrowany.\n");
    else if (wynik == -2) printf("BLAD: Nazwa zajeta!\n");
    else printf("BLAD: Pamiec.\n");
}

void obsluga_edycji(Archiwum* arch) {
    char nazwa[MAX_NAZWA + 1];
    wczytaj_tekst("Podaj nazwe artefaktu: ", nazwa, MAX_NAZWA);
    int idx = znajdz_indeks_po_nazwie(arch, nazwa);
    
    if (idx == -1) {
        printf("Nie znaleziono.\n");
        return;
    }

    printf("Edytujesz: %s\n", arch->tablica[idx].nazwa);
    Artefakt a;
    wczytaj_tekst("Nowe pochodzenie: ", a.pochodzenie, MAX_POCHODZENIE);
    wczytaj_tekst("Nowa cywilizacja: ", a.cywilizacja, MAX_CYWILIZACJA);
    a.poziom_zagrozenia = wczytaj_int("Nowy poziom zagrozenia (0-10): ", 0, 10);
    a.rok_odkrycia = wczytaj_int("Nowy rok odkrycia: ", 2000, 3000);
    a.status = wczytaj_status();

    edytuj_artefakt(arch, idx, a);
    printf("Zaktualizowano.\n");
}

void obsluga_usuwania(Archiwum* arch) {
    char nazwa[MAX_NAZWA + 1];
    wczytaj_tekst("Podaj nazwe do usuniecia: ", nazwa, MAX_NAZWA);
    int idx = znajdz_indeks_po_nazwie(arch, nazwa);
    
    if (idx == -1) {
        printf("Nie znaleziono.\n");
        return;
    }

    int wynik = usun_artefakt(arch, idx);
    if (wynik == 0) printf("Usunieto.\n");
    else if (wynik == -3) printf("BLAD: Zbyt wysokie zagrozenie (>=8). Odmowa.\n");
    else printf("BLAD.\n");
}

void obsluga_wyszukiwania(Archiwum* arch) {
    printf("1. Wg tekstu (nazwa/pochodzenie/tworca)\n");
    printf("2. Wg poziomu zagrozenia\n");
    int opcja = wczytaj_int("Wybor: ", 1, 2);

    if (opcja == 1) {
        char fraza[50];
        wczytaj_tekst("Szukana fraza: ", fraza, 49);
        wyszukaj_tekstowo(arch, fraza);
    } else {
        int min = wczytaj_int("Min zagrozenie: ", 0, 10);
        int max = wczytaj_int("Max zagrozenie: ", 0, 10);
        wyszukaj_zagrozenie(arch, min, max);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uzycie: %s <plik_bazy>\n", argv[0]);
        return 1;
    }

    char* nazwa_pliku = argv[1];
    Archiwum archiwum;
    inicjalizuj_archiwum(&archiwum);

    wczytaj_z_pliku(&archiwum, nazwa_pliku);

    int running = 1;
    while (running) {
        wyswietl_menu();
        int wybor = wczytaj_int("", 1, 7);

        switch (wybor) {
            case 1: obsluga_dodawania(&archiwum); break;
            case 2: 
                wyswietl_naglowek();
                for(int i=0; i<archiwum.rozmiar; i++) wyswietl_wiersz(&archiwum.tablica[i]);
                break;
            case 3: obsluga_wyszukiwania(&archiwum); break;
            case 4: 
                printf("1. Nazwa, 2. Zagrozenie\n");
                int k = wczytaj_int("Kryterium: ", 1, 2);
                sortuj_i_wyswietl(&archiwum, k == 1 ? 0 : 1);
                break;
            case 5: obsluga_edycji(&archiwum); break;
            case 6: obsluga_usuwania(&archiwum); break;
            case 7: running = 0; break;
        }
        if (running) pauza();
    }

    zapisz_do_pliku(&archiwum, nazwa_pliku);
    zwolnij_archiwum(&archiwum);
    return 0;
}