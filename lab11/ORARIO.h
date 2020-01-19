//
// Created by Master on 10/01/2020.
//

#ifndef ES01_ORARIO_H
#define ES01_ORARIO_H

#include <stdio.h>

typedef struct {
    int ora;
    int minuti;
}ORA;

ORA ORAread(FILE *fp);
void ORAprint(FILE *fp,ORA t);
int ORAcmp(ORA t1,ORA t2);

#endif //ES01_ORARIO_H
