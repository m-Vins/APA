//
// Created by vins on 10/12/19.
//


#ifndef ES_03_LAB07MOD_PG_H
#define ES_03_LAB07MOD_PG_H
#define MAX 50+1

#include <stdio.h>
#include "INV.h"

typedef struct {
    int inUso;
    inv_t **vettEq;
}tabEquip_t;

typedef struct {
    char codice[7];
    char nome[MAX];
    char classe[MAX];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;


typedef struct node *link,nodoPg_t;

struct node{
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

tabPg_t *creaListaPg(void);
link newNode(pg_t pg,link next);
void loadPg(tabPg_t *tabPg, FILE *fp);
link searchPg(link head,char *key);
link deletePg(link head, char *key);
void editEquipPg(link head,char *key,tabInv_t *tabInv);
void displayStat(tabPg_t *tabPg,char *key);
typedef enum {c_add,c_remove}c_equip;

#endif //ES_03_LAB07MOD_PG_H
