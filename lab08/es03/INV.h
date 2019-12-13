//
// Created by Master on 12/12/2019.
//

#ifndef ES_03_LAB08_INV_H
#define ES_03_LAB08_INV_H

#define MAX 50+1

#include <stdio.h>

typedef struct tabInv_t *TABINV;
typedef struct inv_t *INV;


TABINV creaTabInv(void);
void freeTabInv(TABINV tabInv);
void addObj_wrapper(TABINV tabInv, FILE *fp);
void displayObj(INV obj);
int getHP(INV inv);
int getMP(INV inv);
int getATK(INV inv);
int getDEF(INV inv);
int getMAG(INV inv);
int getSPR(INV inv);
int getNOBJ(TABINV tabInv);
void displayINV(TABINV tabInv);
INV getOBJ(TABINV tabInv,int index);
INV searchObj(TABINV tabinv, char *key);


#endif //ES_03_LAB08_INV_H
