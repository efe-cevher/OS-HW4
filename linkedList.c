#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

struct node {
    Song data;
    struct node * next;
};

struct list {
    Node * head; 
};

Node * createnode(Song data);

Node * createnode(Song data){
    Node * newNode = malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List * makelist(){
    List * list = malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    return list;
}

Song get(int index, List * list) {
    Node * current = list->head;
    
    for(int i=0; i<index; i++){
        current = current->next;
    }
    return current->data;
}

void add(Song data, List * list){
  Node * current = NULL;
    if(list->head == NULL){
        list->head = createnode(data);
    }
    else {
        current = list->head; 
        while (current->next!=NULL){
            current = current->next;
        }
        current->next = createnode(data);
    }
}


int delete(Song data, List * list){
/*   Node * current = list->head;            
    Node * previous = current;           
    while(current != NULL){           
        if(current->data.year == data.year && !strcmp(current->data.genre, data.genre) && !strcmp(current->data.name, data.name)){
            previous->next = current->next;

            if(current == list->head){
                list->head = current->next;
            }
                
            free(current);
            return;
        }                               
        previous = current;             
        current = current->next;        
    } 
*/

    //start from the first link
    Node* current = list->head;
    Node* previous = NULL;
        
    //if list is empty
    if(list->head == NULL) {
        return -1;
    }

    //navigate through list
    while(!(current->data.year == data.year && !strcmp(current->data.genre, data.genre) && !strcmp(current->data.name, data.name))) {

        //if it is last node
        if(current->next == NULL) {
            return -1;
        } else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }

    //found a match, update the link
    if(current == list->head) {
        //change first to point to next link
        list->head = list->head->next;
    } else {
        //bypass the current link
        previous->next = current->next;
    }    
	
   return 1;
}


int getSize(List * list){
    Node * current = list->head;
    int c = 0;

    while(current != NULL){           
        c++;
        current = current->next;        
    }
    return c;
}

int isEmpty(List * list){
    if(getSize(list) == 0){
        return 1;
    }else{
        return 0;
    }
}

void display(List * list) {
    Node * current = list->head;
    if(list->head == NULL) 
        return;
    
    for(; current != NULL; current = current->next) {
        printf("%s, %s, %d\n", current->data.name, current->data.genre, current->data.year);
    }
}

void destroy(List * list){
    Node * current = list->head;
    Node * next = current;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}