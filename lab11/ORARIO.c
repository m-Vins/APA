//
// Created by Master on 10/01/2020.
//

#include "ORARIO.h"
#include <stdio.h>
#include <string.h>


ORA ORAread(FILE *fp){
    ORA t;
    fscanf(fp,"%d:%d",&t.ora,&t.minuti);
    return t;
}

void ORAprint(FILE *fp,ORA t){
    printf("orario: %02d:%02d",t.ora,t.minuti);
}

int ORAcmp(ORA t1,ORA t2){
    char str1[5],str2[5];
    sprintf(str1,"%02d%02d",t1.ora,t1.minuti);
    sprintf(str2,"%02d%02d",t2.ora,t2.minuti);
    return strcmp(str1,str2);
}