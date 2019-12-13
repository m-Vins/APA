//
// Created by Master on 12/12/2019.
//

#ifndef ES_03_LAB08_PG_H
#define ES_03_LAB08_PG_H
#define MAX 50+1

#include <stdio.h>
#include "INV.h"

typedef struct node *LINK;
typedef struct tabPg_t *TABPG;


TABPG creaListaPg(void);
void loadPg(TABPG tabPg, FILE *fp);
LINK searchPg(TABPG tabPg,char *key);
void deletePg(TABPG tabPg, char *key);
void editEquipPg(TABPG tabPg,char *key,TABINV tabInv);
void displayStat(TABPG tabPg,char *key);
void displayPg(LINK node);
void freeTabList(TABPG tabPg);
void displayList(TABPG tabPg);



#endif //ES_03_LAB08_PG_H
