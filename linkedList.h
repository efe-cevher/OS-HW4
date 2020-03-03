#include"song.h"

struct node
{
    Song data;
    struct node * next;
};

typedef struct node Node;


void append(Node** head_ref, Song new_data);
void deleteNode(Node **head_ref, int position);
void printList(Node* n) ;
