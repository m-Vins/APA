//
// Created by Master on 10/01/2020.
//

#ifndef ES01_DATA_H
#define ES01_DATA_H

#include <stdio.h>

typedef struct {
    int giorno, mese, anno;
}DATA;

DATA DATAread(FILE *fp);
void DATAprint(FILE *fp, DATA d);
int DATAcmp(DATA d1,DATA d2);
DATA DATAsetNull();

#endif //ES01_DATA_H
