//
// Created by Master on 16/12/2019.
//

#include "equipArray.h"


struct equipArray_s {
    int inUso;
    int vettEq[EQUIP_SLOT];
};

equipArray_t equipArray_init(){
    struct equipArray_s *ret=(equipArray_t)malloc(sizeof(struct equipArray_s));
    return ret;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}


int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i=0;i<equipArray->inUso;i++) {
        printf("[%d] ",i);
        inv_print(fp,invArray_getByIndex(invArray,equipArray->vettEq[i]));
    }
}


void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int cmd,index;
    int i,esci=0;

    while(!esci) {
        printf("[0] aggiunta oggetto; [1] rimozione oggetto; [2] torna al menù;\n");
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                if (equipArray->inUso < EQUIP_SLOT) {
                    printf("lista oggetti inventario:\n");
                    invArray_print(stdout, invArray);
                    printf("selezionare indice oggetto\n");
                    scanf("%d", &index);
                    equipArray->vettEq[++equipArray->inUso] = index;
                } else {
                    printf("equipaggiamenot completo. impossibile aggiungere oggetti.\n");
                }
                break;
            case 1:
                if(equipArray->inUso>0){
                    printf("l'equipaggiamento del pg contiene i seguenti oggetti: \n");
                    equipArray_print(stdout,equipArray,invArray);

                    printf("inserire indice oggetto da rimuovere: ");
                    scanf("%d",&index);
                    for(i=index;i<equipArray->inUso-1;i++)
                        equipArray->vettEq[i]=equipArray->vettEq[i+1];
                    equipArray->inUso--;
                    //sposta di una casella tutti gli elementi sulla destra;
                }else{
                    printf("l'equipaggiamento del PG non contiene oggetti, scegliere altra opzone.");
                }
                break;
            case 2:
                esci=1;
                break;
            default:
                printf("comando errato.\n");
        }
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    if(index<0||index>equipArray->inUso-1){
        printf("errore indice.\n");
        return -1;
    }
    return equipArray->vettEq[index];
}