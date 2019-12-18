#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "PGlist.h"
#include "INVArray.h"
#include "PG.h"

#define N_SCELTE 7
#define DBG 1

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione){
    int i=0;
    printf("\nMENU'\n");
    for(i=0;i<N_SCELTE;i++)
        printf("%2d > %s\n",i,scelte[i]);
    scanf(" %d",selezione);
}

int main(int argc, char **argv) {
    char *scelte[] = {
            "Uscita",
            "Stampa personaggi",
            "Stampa inventario",
            "Cerca personaggio",
            "Aggiungi personaggio",
            "Elimina personaggio",
            "Modifica equip"
    };

    char codiceRicerca[LEN];
    int selezione;
    FILE *fp1,*fp2;
    bool fineProgramma;

    pgList_t pgList = pgList_init();
    invArray_t invArray = invArray_init();
    pg_t *pgp, pg;



    fp1 = fopen("pg.txt","r");
    pgList_read(fp1, pgList);
    fclose(fp1);
#if DBG
    pgList_print(stdout, pgList,invArray);
#endif /* DBG */

    fp2 = fopen("inv.txt","r");
    invArray_read(fp2, invArray);
    fclose(fp2);
#if DBG
    invArray_print(stdout, invArray);
#endif /* DBG */

    fineProgramma = falso;

    do {
        stampaMenu(scelte, &selezione);
        switch(selezione){

            case 0: {
                fineProgramma = vero;
            } break;

            case 1: {
                pgList_print(stdout, pgList, invArray);
            } break;

            case 2: {
                invArray_print(stdout, invArray);
            } break;

            case 3: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp!=NULL) {
                    pg_print(stdout, pgp, invArray);
                }
            } break;

            case 4: {
                printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
                if (pg_read(stdin, &pg) != EOF) {
                    pgList_insert(pgList, pg);
                }
            } break;

            case 5: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgList_remove(pgList, codiceRicerca);
            } break;

            case 6: {
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp!=NULL) {
                    pg_updateEquip(pgp, invArray);
                }
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!fineProgramma);

    pgList_free(pgList);
    invArray_free(invArray);

    return 0;
}
