//
// Created by Master on 10/01/2020.
//

#ifndef ES01_TRANS_H
#define ES01_TRANS_H

#include "DATA.h"
#include "ORARIO.h"

struct dayVett_s {
    DATA day;
    float Quot;
    int nQuot;
};

typedef struct {
    int N,maxN;
    struct dayVett_s *DayVett;
}*TRVETT;
TRVETT TRVETTinit();
TRVETT TRVETTload(FILE *fp,int N,TRVETT TRv);
void TRVETTfree(TRVETT trv);
#endif //ES01_TRANS_H
