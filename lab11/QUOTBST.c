//
// Created by Master on 11/01/2020.
//

#include "QUOTBST.h"
#include <stdlib.h>
#include <limits.h>
#define DBG 1



typedef struct node_s *link;
struct node_s {
    struct quot_s QUOT;
    int N;
    link l,r,p;
};

struct BST_s {
    link root;
    link z;
};
static link NewNode(link p, link l, link r,int N, struct quot_s quot);
static struct quot_s QUOTsetNull(){
    struct quot_s x;
    x.Quot=-1;
    x.day=DATAsetNull();
    return x;
}

BST BSTinit(){
    BST bst=malloc(sizeof *bst);
    bst->root=(bst->z=NewNode(NULL,NULL,NULL,0,QUOTsetNull()));
}

QUOT NEWQuot(DATA day,float quot){
    QUOT x;
    x.day=day;      x.Quot=quot;
    return x;
}

static void bstFreeR(link x,link z){
    if(x==z)
        return;
    bstFreeR(x->l,z);
    bstFreeR(x->r,z);

    free(x);
}

void BSTfree(BST bst){
    bstFreeR(bst->root,bst->z);
    free(bst);
}

static link NewNode(link p, link l, link r,int N, struct quot_s quot){
    link x=malloc(sizeof *x);
    x->QUOT=quot; x->l=l; x->r=r;
    x->p=p;     x->N=N;
    return x;
}


link insertR(link x,link z, struct quot_s quot) {
    if (x == z) {
        return NewNode(z,z, z, 1, quot);
    }
    if (DATAcmp(x->QUOT.day, quot.day) > 0) {
        x->l = insertR(x->l, z, quot);
        x->l->p=x;
    }
    else {
        x->r = insertR(x->r, z, quot);
        x->r->p=x;
    }
    (x->N)++;
    return x;
}

void BSTinsertLeafR(BST bst, struct quot_s quot){
    bst->root=insertR(bst->root,bst->z,quot);
}

float searchR(link x,link z,DATA day){
    if(x==z)
        return -1;
    if(DATAcmp(x->QUOT.day,day)==0)
        return x->QUOT.Quot;
    if(DATAcmp(x->QUOT.day,day)>0)
        return searchR(x->l,z,day);
    return searchR(x->r,z,day);
}

float BSTsearch(BST bst, DATA day){
    return searchR(bst->root,bst->z,day);
}

static DATA dayMinR(link x,link z){
    return x->l!=z ? dayMinR(x->l,z):x->QUOT.day;
}

static DATA dayMaxR(link x,link z){
    return x->r!=z ? dayMaxR(x->r,z):x->QUOT.day;
}


static void searchMinMax(link x, link z, float *min, float *max, DATA dayMin, DATA dayMax){
    if(x->l!=NULL&&DATAcmp(x->l->QUOT.day,dayMin)>=0)
        searchMinMax(x->l,z,min,max,dayMin,dayMax);
    if(x->QUOT.Quot<(*min))
        *min=x->QUOT.Quot;
    if(x->QUOT.Quot>(*max))
        *max=x->QUOT.Quot;
    if(x->r!=NULL&&DATAcmp(x->r->QUOT.day,dayMax)<=0)
        searchMinMax(x->r,z,min,max,dayMin,dayMax);
}

void BSTsearchMinMaxInterval(BST bst,DATA dayMin,DATA dayMax,float *min,float *max){
    *max=INT_MIN;
    *min=INT_MAX;
    searchMinMax(bst->root,bst->z,min,max,dayMin,dayMax);
}

void BSTsearchMinMax(BST bst, float *min, float *max){
    *max=INT_MIN;
    *min=INT_MAX;
    DATA daymin=dayMinR(bst->root,bst->z);
    DATA daymax=dayMaxR(bst->root,bst->z);
    searchMinMax(bst->root,bst->z,min,max,daymin,daymax);
}

static int max(int a, int b){
    return a>b ? a:b;
}

static int maxPathR(link x,link z){
    if(x==z)
        return 0;
    return max(maxPathR(x->l,z),maxPathR(x->r,z))+1;
}

static int min(int a, int b){
    return a<b ? a:b;
}

static int minPathR(link x,link z){
    if(x==z)
        return 0;
    return min(minPathR(x->l,z),minPathR(x->r,z))+1;
}

static link RotL(link h){
    link x=h->r;
    h->r=x->l;
    if(x->l!=NULL) x->l->p=h;
    x->l=h;
    x->p=h->p;
    h->p=x;
    x->N=h->N;
    h->N=(h->l ? h->l->N:0)+(h->r ? h->r->N:0)+1;
    return x;
}

static link RotR(link h){
    link x=h->l;
    h->l=x->r;
    if(x->r!=NULL) x->r->p=h;
    x->r=h;
    x->p=h->p;
    h->p=x;
    x->N=h->N;
    h->N=(h->l ? h->l->N:0)+(h->r ? h->r->N:0)+1;
    return x;
}

static link partR(link x,link z,int r){
    if(x==z)    return z;
    int t=(x->l!=z ? x->l->N:0);
    if(t>r){
        x->l=partR(x->l,z,r);
        x=RotR(x);
    }
    if(t<r){
        x->r=partR(x->r,z,r-t-1);
        x=RotL(x);
    }
    return x;
}

static link balanceR(link x, link z){
    int r;
    if(x==z)
        return z;
    r=(x->N+1)/2-1;
    x=partR(x,z,r);
    x->l=balanceR(x->l,z);
    x->r=balanceR(x->r,z);
    return x;
}

void BSTbalance(BST bst, int Soglia){
    if(maxPathR(bst->root,bst->z)/minPathR(bst->root,bst->z)<=Soglia)
        return;
    /*bst->root=*/balanceR(bst->root,bst->z);
}


static void display(link x,link z,FILE *fp,int cmd){
    if(x==z)
        return;
    if(cmd==1){
        DATAprint(fp,x->QUOT.day);
        fprintf(fp,"-->Quot: %f  (N:  %d)\n\n",x->QUOT.Quot,x->N);
    }
    display(x->l,z,fp,cmd);
    if(cmd==2){
        DATAprint(fp,x->QUOT.day);
        fprintf(fp,"-->Quot: %f  (N:  %d)\n\n",x->QUOT.Quot,x->N);
    }
    display(x->r,z,fp,cmd);
    if(cmd==3){
        DATAprint(fp,x->QUOT.day);
        fprintf(fp,"-->Quot: %f  (N:  %d)\n\n",x->QUOT.Quot,x->N);
    }
};

void BSTDisplay(BST bst,FILE *fp,int cmd){
    display(bst->root,bst->z,fp,cmd);
}