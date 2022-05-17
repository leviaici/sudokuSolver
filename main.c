#include <stdio.h>
#include <stdlib.h>

// inspirat de pe geeksforgeeks
int tabla[9][9];

char verificareTablaInitiala() {
    for(int linie = 0; linie < 9; linie++)
        for(int coloana = 0; coloana < 9; coloana++) {
            for(int i = linie + 1; i < 9; i++) // verificam daca se gaseste termenul deja pe coloana
                if(tabla[i][coloana] == tabla[linie][coloana] && tabla[linie][coloana])
                    return 'N';

            for(int j = coloana + 1; j < 9; j++) // verificam daca se gaseste termenul deja pe linie
                if(tabla[linie][j] == tabla[linie][coloana] && tabla[linie][coloana])
                    return 'N';

            for(int i = linie; i < 3; i++) // verificam daca se gaseste termenul deja in chenar
                for(int j = coloana + 1; j < 3; j++)
                    if(tabla[i + linie - linie % 3][j + coloana - coloana % 3] == tabla[linie][coloana] && tabla[linie][coloana])
                        return 'N';
        }

    return 'Y';
}
char verificareTabla(int linie, int coloana, int numar) {
    for(int i = 0; i < 9; i++) // verificam daca se gaseste termenul deja pe coloana
        if(tabla[i][coloana] == numar)
            return 'N';

    for(int j = 0; j < 9; j++) // verificam daca se gaseste termenul deja pe linie
        if(tabla[linie][j] == numar)
            return 'N';

    for(int i = 0; i < 3; i++) // verificam daca se gaseste termenul deja in chenar
        for(int j = 0; j < 3; j++)
            if(tabla[i + linie - linie % 3][j + coloana - coloana % 3] == numar)
                return 'N';

    return 'Y';
}

char rezolvare(int linie, int coloana) {
    if(coloana == 9) {
        if(linie == 8) // verificam daca am terminat toata matricea de completat
            return 'Y';
        else { // e cazul sa trecem la linia urmatoare si sa resetam coloana
            linie++;
            coloana = 0;
        }
    }

    if(tabla[linie][coloana]) // daca e deja completata casuta, trecem mai departe
        return rezolvare(linie, coloana + 1);

    for(int i = 1; i <= 9; i++) {
        if(verificareTabla(linie, coloana, i) == 'Y') {
            tabla[linie][coloana] = i;
            if (rezolvare(linie, coloana + 1) == 'Y')
                return 'Y';
        }
        tabla[linie][coloana] = 0;
    }
    return 'N';
}

void citireTabla() {
    FILE *fin = fopen("tabla.txt","r");

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            fscanf(fin, "%d", &tabla[i][j]);

}
void afisareTabla() {
    for(int i = 0; i < 9; i++, puts("")) {
        if(i % 3 == 0)
            printf("-------------------------\n");
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0)
                printf("| ");
            printf("%d ", tabla[i][j]);
        }
        printf("|");
    }
    printf("-------------------------\n");
}

int main() {
    citireTabla();
    if(verificareTablaInitiala() == 'Y') {
        afisareTabla();
        rezolvare(0, 0);
    }else {
        afisareTabla();
        printf("Nu exista solutie la tabla introdusa. Verifica daca ai introdus-o corect si incearca din nou.");
        exit(1);
    }
    afisareTabla();
    return 0;
}
