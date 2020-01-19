//
// Created by Master on 10/01/2020.
//

#include "DATA.h"
#include <stdio.h>
#include <string.h>

DATA DATAread(FILE *fp){
    DATA d;
    fscanf(fp,"%d/%d/%d",&d.anno,&d.mese,&d.giorno);
    return d;
}

void DATAprint(FILE *fp, DATA d){
    fprintf(fp,"%04d/%02d/%02d",d.anno,d.mese,d.giorno);
}

int DATAcmp(DATA d1,DATA d2){
    char str1[11],str2[11];
    sprintf(str1,"%04d/%02d/%02d",d1.anno,d1.mese,d1.giorno);
    sprintf(str2,"%04d/%02d/%02d",d2.anno,d2.mese,d2.giorno);
    return strcmp(str1,str2);
}

DATA DATAsetNull(){
    DATA d;
    d.giorno=d.mese=d.anno=-1;
    return d;
}