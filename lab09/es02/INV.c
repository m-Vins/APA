//
// Created by Master on 16/12/2019.
//

#include "INV.h"


int stat_read(FILE *fp, stat_t *statp){
    int ret=fscanf(fp,"%d%d%d%d%d%d",&(statp->hp),&(statp->mp),&(statp->atk),&(statp->def),&(statp->mag),&(statp->spr));
    return ret;
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp,"hp: %d; mp: %d; atk: %d; def: %d; mag: %d; spr: %d;\n",
            (statp->hp<soglia ? soglia : statp->hp),(statp->mp<soglia ? soglia : statp->mp),(statp->atk<soglia ? soglia : statp->atk),
            (statp->def<soglia ? soglia : statp->def),(statp->mag<soglia ? soglia : statp->mag),(statp->spr<soglia ? soglia : statp->spr));
}

int inv_read(FILE *fp, inv_t *invp){
    int ret1=fscanf(fp,"%s %s",invp->nome,invp->tipo);
    int ret2=stat_read(fp,&invp->stat);
    return (ret1==EOF||ret2==EOF ? EOF:1);
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"nome: %s; tipo: %s;\n",invp->nome,invp->tipo);
    stat_print(fp,&invp->stat,INT_MIN);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}