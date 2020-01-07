//
// Created by Master on 04/01/2020.
//

#ifndef ES04_ST_H
#define ES04_ST_H

typedef struct st_s *ST;

ST STinit();
int STinsert(char* name,char *rete, struct st_s *st);
int STsearchByName(char *name, struct st_s *st);
int STsearchByRete(char *rete, struct st_s *st);
char *STsearchNameByIndex(int index, struct st_s *st);
char *STsearchReteByIndex(int index, struct st_s *st);
void STdelete(int index, struct st_s *st);
void STfree(ST st);
int STcount(ST st);

#endif //ES04_ST_H
