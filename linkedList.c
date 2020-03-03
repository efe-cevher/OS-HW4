#include<stdio.h>
#include<stdlib.h>


#include"linkedList.h"





void append(Node** head_ref, Song new_data) 
{ 
    /* 1. allocate node */
    Node* new_node = (Node*) malloc(sizeof(Node)); 
  
    Node *last = *head_ref;  /* used in step 5*/
   
    /* 2. put in the data  */
    new_node->data  = new_data; 
  
    /* 3. This new node is going to be the last node, so make next  
          of it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }   
       
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
   
    /* 6. Change the next of last node */
    last->next = new_node; 
    return;     
}

void deleteNode(Node **head_ref, int position) 
{ 
   // If linked list is empty 
   if (*head_ref == NULL) 
      return; 
  
   // Store head node 
   Node* temp = *head_ref; 
  
    // If head needs to be removed 
    if (position == 0) 
    { 
        *head_ref = temp->next;   // Change head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Find previous node of the node to be deleted 
    for (int i=0; temp!=NULL && i<position-1; i++) 
         temp = temp->next; 
  
    // If position is more than number of ndoes 
    if (temp == NULL || temp->next == NULL) 
         return; 
  
    // Node temp->next is the node to be deleted 
    // Store pointer to the next of node to be deleted 
    Node *next = temp->next->next; 
  
    // Unlink the node from linked list 
    free(temp->next);  // Free memory 
  
    temp->next = next;  // Unlink the deleted node from list 
}

void printList(Node* n) 
{ 
    while (n != NULL) { 
        printf(" %s, %s, %d \n", n->data.name, n->data.genre, n->data.year); 
        n = n->next; 
    } 
}

