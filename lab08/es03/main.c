#include <stdio.h>
#include <stdlib.h>
#include "INV.h"
#include "PG.h"
#define FileNamePG "pg.txt"
#define FileNameINV "inv.txt"


typedef enum {c_loadListPg,c_loadObj,c_newPg,c_delPg,c_editEquipPg,c_stat,c_displayList,c_searchObj,c_searchPg,c_exit,c_err}c_com;

c_com leggicomando();


int main() {
    int esci=0;
    char key[20];
    TABPG tabPg=NULL;
    TABINV tabInv=NULL;
    FILE *fp;

    while(!esci){
        switch (leggicomando()){
            case c_loadListPg:
                tabPg=creaListaPg();
                fp=fopen(FileNamePG,"r");
                loadPg(tabPg,fp);
                fclose(fp);
                break;
            case c_loadObj:
                tabInv=creaTabInv();
                fp=fopen(FileNameINV,"r");
                addObj_wrapper(tabInv,fp);
                fclose(fp);
                break;
            case c_newPg:
                loadPg(tabPg,stdin);
                break;
            case c_delPg:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                deletePg(tabPg,key);
                break;
            case c_editEquipPg:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                editEquipPg(tabPg,key,tabInv);
                break;
            case c_stat:
                printf("inserire codice PG:\n");
                scanf("%s",key);
                displayStat(tabPg,key);
                break;
            case c_displayList:
                displayList(tabPg);
                break;
            case c_searchObj:
                printf("inserire nome oggetto: ");
                scanf("%s",key);
                displayObj(searchObj(tabInv,key));
                break;
            case c_searchPg:
                printf("inserire codice personaggio: ");
                scanf("%s",key);
                displayPg(searchPg(tabPg,key));
                break;
            case c_exit:
                esci=1;
                break;
            case c_err:
                printf("comando errato\n");
                break;
        }
    }

    freeTabInv(tabInv);
    freeTabList(tabPg);
    return 0;
}

c_com leggicomando(){
    int cmd;
    printf("\ninserire numero comando:\n");
    printf("[1]carica elenco PG;\n[2]carica elenco oggetto;\n");
    printf("[3]aggiungi PG;\n[4]elimina PG;\n[5]modifica equipaggiamento Pg;\n");
    printf("[6]calcola statistiche;\n[7]DisplayList;\n[8]searchObj;\n[9]searchPg;\n[10]EXIT.\n");
    if(scanf("%d",&cmd)==1&&cmd>=0&&cmd<=c_err)
        return (c_com)cmd-1;
    return c_err;
}
