//
// Created by Master on 10/01/2020.
//

#include "TRANS.h"
#include <stdlib.h>

TRVETT TRVETTinit(){
    TRVETT x=malloc(sizeof *x);
    x->DayVett=malloc(sizeof *x->DayVett);
    x->N=0;
    x->maxN=1;
    return x;
}

void TRVETTfree(TRVETT trv){
    free(trv->DayVett);
    free(trv);
}


TRVETT TRVETTload(FILE *fp,int N,TRVETT TRv){
    ORA ora;//inutile
    DATA dataTmp;
    int pos;
    float val;
    int n;


    for(int i=0;i<N;i++){
        if(TRv->maxN==TRv->N){
            TRv->maxN*=2;
            TRv->DayVett=realloc(TRv->DayVett, TRv->maxN*sizeof *TRv->DayVett);
        }

        dataTmp=DATAread(fp);
        ora=ORAread(fp);//inutile.
        fscanf(fp,"%f%d\n",&val,&n);

        //controllo se son già state inserite transazioni in quella data.
        pos=-1;
        for(int j=0;j<TRv->N;j++){
            if(DATAcmp(dataTmp,TRv->DayVett[j].day)==0){
                pos=j;
                break;
            }
        }
        if(pos==-1){
            TRv->DayVett[TRv->N].day=dataTmp;
            TRv->DayVett[TRv->N].Quot=(val*(float)n);
            TRv->DayVett[TRv->N++].nQuot=n;
        }else{
            TRv->DayVett[pos].nQuot+=n;
            TRv->DayVett[pos].Quot+=(val*(float)n);
        }
    }

    //calcola le quotazioni in ogni giornata.
    for(int i=0;i<TRv->N;i++)
        TRv->DayVett[i].Quot/=(float)TRv->DayVett[i].nQuot;

}