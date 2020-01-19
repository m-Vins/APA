//
// Created by Master on 11/01/2020.
//

#ifndef ES01_QUOTBST_H
#define ES01_QUOTBST_H

#include "DATA.h"

struct quot_s{
    DATA day;
    float Quot;
};
typedef struct quot_s QUOT;
typedef struct BST_s *BST;


BST BSTinit();
void BSTfree(BST bst);
void BSTinsertLeafR(BST bst, QUOT quot);
float BSTsearch(BST bst, DATA day);
void BSTsearchMinMaxInterval(BST bst,DATA dayMin,DATA dayMax,float *min,float *max);
void BSTsearchMinMax(BST bst, float *min, float *max);
QUOT NEWQuot(DATA day,float Quot);
void BSTbalance(BST bst, int Soglia);
void BSTDisplay(BST bst,FILE *fp,int cmd);

#endif //ES01_QUOTBST_H
