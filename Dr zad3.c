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
        return 0;
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
        return 0;
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
        return 0;
    }

    Pozicija zaBrisati = pret->Next;
    pret->Next = zaBrisati->Next;
    free(zaBrisati);
    printf("Osoba s prezimenom '%s' je uspjesno obrisana.\n", prez);

    return 0;
}

int UnosIza(Pozicija P, const char* prez) {
    Pozicija pret = TraziPret(P, prez);
    if (pret == NULL) {
        printf("Osoba s prezimenom '%s' ne postoji u listi.\n", prez);
        return 0;
    }

    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));
    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return 0;
    }

    printf("Unesite ime (max 49 znakova): ");
    scanf("%s", nova->ime);
    printf("Unesite prezime (max 49 znakova): ");
    scanf("%s", nova->prezime);
    printf("Unesite godinu rodjenja: ");
    scanf("%d", &nova->godRod);

    Pozicija cilj = pret->Next;
    nova->Next = cilj->Next;
    cilj->Next = nova;

    return 0;
}

int UnosIspred(Pozicija P, const char* prez) {
    Pozicija pret = TraziPret(P, prez);
    if (pret == NULL) {
        printf("Osoba s prezimenom '%s' ne postoji u listi.\n", prez);
        return 0;
    }

    Pozicija nova = (Pozicija)malloc(sizeof(Osoba));
    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return 0;
    }

    printf("Unesite ime (max 49 znakova): ");
    scanf("%s", nova->ime);
    printf("Unesite prezime (max 49 znakova): ");
    scanf("%s", nova->prezime);
    printf("Unesite godinu rodjenja: ");
    scanf("%d", &nova->godRod);

    nova->Next = pret->Next;
    pret->Next = nova;

    return 0;
}

void Sort(Pozicija P) {
    if (P->Next == NULL) {
        printf("Lista je prazna, nema se sto sortirati.\n");
        return;
    }

    if (P->Next->Next == NULL) {
        printf("Lista ima samo jedan element, nije potrebno sortiranje.\n");
        return;
    }

    Pozicija tren, pret, temp, kraj;
    kraj = NULL;
    while (P->Next != kraj) {
        pret = P;
        tren = P->Next;
        while (tren->Next != kraj) {
            if (strcmp(tren->prezime, tren->Next->prezime) > 0) {
                temp = tren->Next;
                tren->Next = temp->Next;
                temp->Next = tren;
                pret->Next = temp;

                pret = temp;
            }
            else {
                pret = tren;
                tren = tren->Next;
            }
        }
        kraj = tren;
    }
    printf("Lista je sortirana po prezimenima.\n");
}

int UpisUDat(Pozicija P) {
    FILE* fp = fopen("Osobe.txt", "w");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje!\n");
        return 0;
    }

    Pozicija tren = P->Next;
    while (tren != NULL) {
        fprintf(fp, "%s %s %d\n", tren->ime, tren->prezime, tren->godRod);
        tren = tren->Next;
    }

    fclose(fp);
    printf("Lista je uspjesno upisana u datoteku 'Osobe.txt'.\n");
    return 0;
}

int CitajIzDat(Pozicija P) {
    FILE* fp = fopen("Osobe.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke za citanje!\n");
        return 0;
    }

    char ime[50], prez[50];
    int god;

    while (fscanf(fp, "%s %s %d", ime, prez, &god) == 3) {
        Pozicija nova = (Pozicija)malloc(sizeof(Osoba));
        if (nova == NULL) {
            printf("Greska pri alokaciji memorije!\n");
            break;
        }

        strcpy(nova->ime, ime);
        strcpy(nova->prezime, prez);
        nova->godRod = god;
        nova->Next = NULL;

        Pozicija tren = P;
        while (tren->Next != NULL) {
            tren = tren->Next;
        }
        tren->Next = nova;
    }

    fclose(fp);
    printf("Lista je uspjesno ucitana iz datoteke 'Osobe.txt'.\n");
    return 0;
}

int main() {
    Osoba head;
    head.Next = NULL;

    int izbor;
    char prez[50];

    do {
        printf("\n--- MENI ---\n");
        printf("1 --> Dodaj na pocetak\n");
        printf("2 --> Ispis liste\n");
        printf("3 --> Dodaj na kraj\n");
        printf("4 --> Pronadi po prezimenu\n");
        printf("5 --> Obrisi po prezimenu\n");
        printf("6 --> Dodaj iza odredenog elementa\n");
        printf("7 --> Dodaj ispredodredenog elementa\n");
        printf("8 --> Sortiraj listu po prezimenima\n");
        printf("9 --> Upisi listu u datoteku\n");
        printf("10 --> Citaj listu iz datoteke\n");
        printf("0 --> Izlaz\n");
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
            printf("Unesite prezime za pretragu: ");
            scanf("%s", prez);
            Trazi(&head, prez);
            break;
        case 5:
            printf("Unesite prezime za brisanje: ");
            scanf("%s", prez);
            Brisi(&head, prez);
            break;
        case 6:
            printf("Unesite prezime osobe IZA koje dodajete: ");
            scanf("%s", prez);
            UnosIza(&head, prez);
            break;
        case 7:
            printf("Unesite prezime osobe ISPRED koje dodajete: ");
            scanf("%s", prez);
            UnosIspred(&head, prez);
            break;
        case 8: 
            Sort(&head);
            break;
        case 9: 
            UpisUDat(&head); 
            break;
        case 10:
            CitajIzDat(&head);
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default: 
            printf("Nepoznata opcija.\n");
            break;
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