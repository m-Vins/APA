//
// Created by Master on 16/12/2019.
//

#include "PG.h"


int pg_read(FILE *fp, pg_t *pgp) {
    int ret1=fscanf(fp, "%s%s%s", pgp->cod, pgp->nome, pgp->classe);
    int ret2=stat_read(fp,&pgp->eq_stat);
    pgp->b_stat=pgp->eq_stat;
    pgp->equip=equipArray_init();
    return (ret1==EOF||ret2==EOF ? EOF:1);
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"\nCODICE: %s; NOME: %s; CLASSE: %s;\n",pgp->cod,pgp->nome,pgp->classe);
    equipArray_print(fp,pgp->equip,invArray);
    printf("statistiche PG:");
    stat_print(fp,&pgp->eq_stat,MIN_STAT);
    for(int i=0;i<50;i++) printf("_");
    printf("\n");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int i;
    stat_t stat_tmp;
    equipArray_update(pgp->equip,invArray);
    //per aggiornare le statistiche le ricalcolo da capo;
    pgp->eq_stat.hp=pgp->b_stat.hp;
    pgp->eq_stat.mp=pgp->b_stat.mp;
    pgp->eq_stat.atk=pgp->b_stat.atk;
    pgp->eq_stat.def=pgp->b_stat.def;
    pgp->eq_stat.mag=pgp->b_stat.mag;
    pgp->eq_stat.spr=pgp->b_stat.spr;

    for(i=0;i<equipArray_inUse(pgp->equip);i++){
        stat_tmp=inv_getStat(invArray_getByIndex(invArray,equipArray_getEquipByIndex(pgp->equip,i)));
        pgp->eq_stat.hp+=stat_tmp.hp;
        pgp->eq_stat.mp+=stat_tmp.mp;
        pgp->eq_stat.atk+=stat_tmp.atk;
        pgp->eq_stat.mag+=stat_tmp.mag;
        pgp->eq_stat.def+=stat_tmp.def;
        pgp->eq_stat.spr+=stat_tmp.spr;
    }
}

