#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER
#include "song.h"

typedef struct node Node;

typedef struct list List;

List * makelist();
void add(Song data, List * list);
void delete(Song data, List * list);
void display(List * list);
void reverse(List * list);
void destroy(List * list);

#endif