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

void delete(Song data, List * list){
    Node * current = list->head;            
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