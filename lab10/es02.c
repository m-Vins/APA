#include <stdio.h>
#include <stdlib.h>
#define FileName "elementi.txt"
#define MAX 100
#define MAXDIAG 5
#define ND 3
#define DD 11
#define DP 33


typedef enum {T,I,A}tipologia_t;
typedef enum {S,F}direzione_t;
typedef enum {TRUE,FALSE}boolean_t;


struct element_s{
    char nome[MAX];
    tipologia_t tipo;
    direzione_t dirIngr,dirUsc;
    boolean_t reqPrec,reqFin;
    float val;
    int diff;
};

typedef struct {
    struct element_s *elementi;
    int n;
}element_t;

struct BS {
    element_t diag[ND];
    float val;
    boolean_t BONUS;
}BestSol;

void searchSol(element_t elem);
int readFile(struct element_s **pElementi, FILE *fp);
void displayElement(struct element_s x);

int main() {
    element_t elem;
    FILE *fp;

    fp=fopen(FileName,"r");
    elem.n=readFile(&elem.elementi,fp);
    fclose(fp);

    for(int i=0;i<ND;i++) BestSol.diag[i].elementi=(struct element_s *)malloc(MAXDIAG* sizeof(struct element_s));
    BestSol.val=0;  BestSol.BONUS=FALSE;

    searchSol(elem);

    for(int nd=0;nd<ND;nd++){
        printf("DIAG #%d: \n",nd+1);
        for(int i=0;i<BestSol.diag[nd].n;i++){
            displayElement(BestSol.diag[nd].elementi[i]);
        }
    }
    printf("valore totale= %f",BestSol.val);
    if(BestSol.BONUS==TRUE) printf(" BONUS compreso.");

    return 0;
}

int readFile(struct element_s **pElementi, FILE *fp){
    int n;
    fscanf(fp,"%d\n",&n);
    struct element_s *elementi=(struct element_s* )malloc(n*sizeof(struct element_s));
    for(int i=0;i<n;i++){
        fscanf(fp,"%s%d%d%d%d%d%f%d",elementi[i].nome,&elementi[i].tipo,&elementi[i].dirIngr,
               &elementi[i].dirUsc,&elementi[i].reqPrec,&elementi[i].reqFin,
               &elementi[i].val,&elementi[i].diff);
    }
    *pElementi=elementi;
    return n;
}

int compatibility(struct element_s a,struct element_s b){
    return a.dirUsc==b.dirIngr;
}

int checkDiag(element_t diag) {
    for (int i = 0; i < diag.n; i++) {
        if (diag.elementi[i].tipo != T)
            return  1;
    }
    return 0;
}


void checkSol(element_t *sol){
    boolean_t Acrob_front,Acrob_retro,Acrob_seq;
    Acrob_front=Acrob_retro=Acrob_seq=FALSE;
    float val=0;
    int diff=0;


    for(int nd=0; nd < ND; nd++){
        for(int j=0;j<sol[nd].n; j++){
            if(sol[nd].elementi[j].tipo == A)
                Acrob_front=TRUE;
            if(sol[nd].elementi[j].tipo == I)
                Acrob_retro=TRUE;
            if((j < sol[nd].n - 1) && (sol[nd].elementi[j].tipo == I || sol[nd].elementi[j].tipo == A) && (sol[nd].elementi[j + 1].tipo == I || sol[nd].elementi[j + 1].tipo == A))
                Acrob_seq=TRUE;
            val+=sol[nd].elementi[j].val;
            diff+=sol[nd].elementi[j].diff;
        }
    }

    if(Acrob_front==FALSE||Acrob_retro==FALSE||Acrob_seq==FALSE||diff>DP) return;
    if(sol[ND-1].elementi[sol[ND-1].n-1].val>=8){
        val*=(float)1.5;    BestSol.BONUS=TRUE;
    }
    if(val<=BestSol.val)    return;

    //sostituisco la soluzione.
    BestSol.val=val;
    for(int nd=0; nd < ND; nd++){
        BestSol.diag[nd].n=sol[nd].n;
        for(int i=0; i < sol[nd].n; i++){
            BestSol.diag[nd].elementi[i]=sol[nd].elementi[i];
        }
    }
}






void searchSolR(int pos, element_t element, element_t *sol, int dd, int dp, int nd){
    int i;

    for(i=0;i<element.n&&pos<MAXDIAG;i++){
        if(pos==0&&element.elementi[i].dirIngr==F&&element.elementi[i].reqPrec==TRUE&&element.elementi[i].diff<=DD&&dp+element.elementi[i].diff<=DP){
            sol[nd].elementi[pos]=element.elementi[i];  sol[nd].n=1;
            searchSolR(1, element, sol, element.elementi[i].diff, dp + element.elementi[i].diff, nd);
        }
        if(pos!=0&&compatibility(sol[nd].elementi[pos-1],element.elementi[i])&&dd+element.elementi[i].diff<=DD&&dp+element.elementi[i].diff<=DP&&sol[nd].elementi[pos-1].reqFin==TRUE){
            sol[nd].elementi[pos]=element.elementi[i];  sol[nd].n++;
            searchSolR(pos + 1, element, sol, dd + element.elementi[i].diff, dp + element.elementi[i].diff, nd);
            sol[nd].n--;
        }
    }

    if(checkDiag(sol[nd])){
        if(nd+1<ND){
            searchSolR(0, element, sol, 0, dp, nd + 1);
        } else{
            checkSol(sol);
        }
    }
}

void searchSol(element_t elem){
    element_t *sol;
    sol=(element_t*)malloc(ND* sizeof(element_t));
    for(int i=0;i<ND;i++) {
        sol[i].elementi = (struct element_s *) malloc(MAXDIAG * sizeof(struct element_s));
        sol[i].n=0;
    }
    searchSolR(0, elem, sol, 0, 0, 0);
    for(int i=0;i<ND;i++)
        free(sol[i].elementi);
    free(sol);
}

void displayElement(struct element_s x){
    printf("nome: %s,tipo: ",x.nome);
    switch(x.tipo){
        case A:
            printf("Acrobatico Avanti,");
            break;
        case I:
            printf("Acrobatico Indietro,");
            break;
        case T:
            printf("Transitorio,");
            break;
    }
    printf("direzione ingresso: ");
    if(x.dirIngr==F)
        printf("frontale, ");
    else
        printf("di spalle, ");
    printf("direzione d'uscita: ");
    if(x.dirUsc==F)
        printf("frontale, ");
    else
        printf("di spalle, ");
    printf("requisito di precedenza: ");
    if(x.reqPrec==TRUE)
        printf("ok, ");
    else
        printf("not ok, ");
    printf("requisito di fine: ");
    if(x.reqFin==FALSE)
        printf("ok, ");
    else
        printf("not ok, ");
    printf("val: %f,diff: %d\n",x.val,x.diff);
}
