#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godRod;
    struct Osoba* Next;
} Osoba;

typedef Osoba* Pozicija;

int UnosP(Pozicija P) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));
    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    printf("Unesite ime (max 49 znakova): ");
    scanf("%s", nova->ime);
    printf("Unesite prezime (max 49 znakova): ");
    scanf("%s", nova->prezime);
    printf("Unesite godinu rodjenja: ");
    scanf("%d", &nova->godRod);

    nova->Next = P->Next;
    P->Next = nova;

    return 0;
}

void Ispis(Pozicija P) {
    Pozicija tren = P->Next;

    if (tren == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    printf("\n--- SADRZAJ LISTE ---\n");
    while (tren != NULL) {
        printf("%s %s (%d)\n", tren->ime, tren->prezime, tren->godRod);
        tren = tren->Next;
    }
    printf("---------------------\n");
}

int UnosK(Pozicija P) {
    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));
    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }

    printf("Unesite ime (max 49 znakova): ");
    scanf("%s", nova->ime);
    printf("Unesite prezime (max 49 znakova): ");
    scanf("%s", nova->prezime);
    printf("Unesite godinu rodjenja: ");
    scanf("%d", &nova->godRod);
    nova->Next = NULL;

    Pozicija tren = P;
    while (tren->Next != NULL) {
        tren = tren->Next;
    }

    tren->Next = nova;

    return 0;
}

Pozicija TraziPret(Pozicija P, const char* prez) {
    Pozicija tren = P;
    while (tren->Next != NULL) {
        if (strcmp(tren->Next->prezime, prez) == 0) {
            return tren;
        }
        tren = tren->Next;
    }
    return NULL;
}

void Trazi(Pozicija P, const char* prez) {
    Pozicija tren = P->Next;
    while (tren != NULL) {
        if (strcmp(tren->prezime, prez) == 0) {
            printf("\nPronadena osoba: %s %s (%d)\n", tren->ime, tren->prezime, tren->godRod);
            return;
        }
        tren = tren->Next;
    }
    printf("\nOsoba s prezimenom '%s' nije pronadena.\n", prez);
}

int Brisi(Pozicija P, const char* prez) {
    Pozicija pret = TraziPret(P, prez);

    if (pret == NULL) {
        printf("Osoba s prezimenom '%s' ne postoji u listi.\n", prez);
        return -1;
    }

    Pozicija zaBrisati = pret->Next;
    pret->Next = zaBrisati->Next;
    free(zaBrisati);
    printf("Osoba s prezimenom '%s' je uspjesno obrisana.\n", prez);

    return 0;
}

int main() {
    Osoba head;
    head.Next = NULL;

    int izbor;
    char prez[50];

    do {
        printf("\n--- MENI ---\n");
        printf("1. Dodaj na pocetak\n");
        printf("2. Ispis liste\n");
        printf("3. Dodaj na kraj\n");
        printf("4. Pronadi po prezimenu\n");
        printf("5. Obrisi po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            UnosP(&head);
            break;
        case 2:
            Ispis(&head);
            break;
        case 3:
            UnosK(&head);
            break;
        case 4:
            printf("Unesite prezime za pretragu (max 49 znakova): ");
            scanf("%s", prez);
            Trazi(&head, prez);
            break;
        case 5:
            printf("Unesite prezime za brisanje (max 49 znakova): ");
            scanf("%s", prez);
            Brisi(&head, prez);
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nepoznata opcija.\n");
        }
    } while (izbor != 0);

    Pozicija tren = head.Next;
    while (tren != NULL) {
        Pozicija temp = tren;
        tren = tren->Next;
        free(temp);
    }

    return 0;
}