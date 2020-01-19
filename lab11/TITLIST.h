//
// Created by Master on 11/01/2020.
//

#ifndef ES01_TITLIST_H
#define ES01_TITLIST_H

#include "TITOLO.h"

typedef struct list_s *TLIST;


TLIST TLISTinit();
void TLISTfree(TLIST x);
void TLISTinsert(TLIST List,TIT titolo);
void TLISTload(TLIST List,FILE *fp);
TIT TLISTsearch(TLIST List,char *cod);


#endif //ES01_TITLIST_H
