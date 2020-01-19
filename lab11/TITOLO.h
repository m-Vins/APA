//
// Created by Master on 10/01/2020.
//

#ifndef ES01_TITOLO_H
#define ES01_TITOLO_H

#include "QUOTBST.h"

typedef struct titolo_s *TIT;


TIT TITnew(char* cod);
void TITfree(TIT x);
TIT TITread(FILE *fp);
void TITprint(TIT titolo,FILE *fp);
BST TITgetBst(TIT titolo);
char* TITgetName(TIT titolo);
int TITcmp(TIT t1,TIT t2);
int TITcmpCod(TIT t1,char *cod);

#endif //ES01_TITOLO_H
