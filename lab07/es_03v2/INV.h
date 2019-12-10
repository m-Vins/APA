//
// Created by vins on 10/12/19.
//



#ifndef ES_03_LAB07MOD_INV_H
#define ES_03_LAB07MOD_INV_H
#define MAX 50+1

#include <stdio.h>

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct {
    char nome[MAX];
    char tipo[MAX];
    stat_t stat;
}inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

tabInv_t *creaTabInv(void);
void freeTabInv(tabInv_t *tabInv);
void addObj(tabInv_t *tabInv,inv_t obj);
void addObj_wrapper(tabInv_t *tabInv,FILE *fp);

#endif //ES_03_LAB07MOD_INV_H
