#include "song.h"

typedef struct node Node;

typedef struct list List;

List * makelist();
void add(Song data, List * list);
int delete(Song data, List * list);
Song get(int index, List * list);
void destroy(List * list);
int getSize(List * list);
int isEmpty(List * list);
void display(List * list);
