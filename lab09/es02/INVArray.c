//
// Created by Master on 16/12/2019.
//

#include "INVArray.h"


struct invArray_s {
    inv_t *vetInv;
    int nInv,maxInv;
};

invArray_t invArray_init(){
    struct invArray_s *ret=(struct invArray_s *)malloc(sizeof(struct invArray_s));
    ret->vetInv=(inv_t *)malloc(1 * sizeof(inv_t));
    ret->nInv=0;
    ret->maxInv=1;
    return ret;
}

void invArray_free(invArray_t invArray){
    free(invArray->vetInv);
    free(invArray);
}


void addInv(struct invArray_s *invArray,inv_t obj){
    if(invArray->nInv==invArray->maxInv){
        invArray->maxInv=invArray->maxInv*2;
        invArray->vetInv=realloc(invArray->vetInv,invArray->maxInv);
    }

    invArray->vetInv[invArray->nInv++]=obj;
}

void invArray_read(FILE *fp, invArray_t invArray){
    int nr,i,flag;
    inv_t tmp;
    if(fp!=stdin){
        fscanf(fp,"%d",&nr);
    }else{
        //legge solo la prima riga
        fprintf(fp,"nome tipo hp mp atk def mag spr\n");
        nr=1;
    }
    for(i=0;i<nr;i++) {
        if(inv_read(fp,&tmp)!=EOF)
            addInv(invArray, tmp);
        else printf("errore lettura file\n");
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    printf("lista oggetti nell'inventario: \n");
    for(i=0;i<invArray->nInv;i++){
        printf("[%d] ",i);
        inv_print(fp,&invArray->vetInv[i]);
    }
    for(i=0;i<50;i++) printf("_");
    printf("\n");
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp,&invArray->vetInv[index]);
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vetInv[index];
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0;i<invArray->nInv;i++){
        if(strcmp(invArray->vetInv[i].nome,name)==0){
            return i;
        }
    }
    return -1;
}
