#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedList.h"
#include "semaphore.h"
#include <pthread.h>
#include <string.h>

Node* playlist1;
Node* playlist2;
Node* userplaylist;

sem_t del;



int randr(int min, int max){ //generate rand value in range
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void initLists(){

    char* genres[10] = {"pop", "rock", "jazz", "indie", "rap", "country", "metal", "electronic", "classical", "hip-hop"};

    srand(time(NULL)); //initalizer for randoms to work

    playlist1 = (Node*)malloc(sizeof(Node));
	playlist2 = (Node*)malloc(sizeof(Node));
    
    userplaylist = (Node*)malloc(sizeof(Node));


    Song* song = (Song*)malloc(sizeof(Song));
    sprintf(song->name, "Song Name 0");
    sprintf(song->genre, "%s", genres[randr(0,9)]);
    song->year = randr(1950, 2019);
    playlist1->data = *song;



    for(int i=1; i<10; i++){
        Song* song = (Song*)malloc(sizeof(Song));
        sprintf(song->name, "Song Name %d", i);
        sprintf(song->genre, "%s", genres[randr(0,9)]);
        song->year = randr(1950, 2019);

        append(&playlist1,*song);
    }
    for(int i=0; i<23; i++){
        Song* song = (Song*)malloc(sizeof(Song));
        sprintf(song->name, "Song Name %d", i);
        sprintf(song->genre, "%s", genres[randr(0,9)]);
        song->year = randr(1950, 2019);

        append(&playlist2,*song);
    }
}


void * cutPaste(void * arg){
    printf("hello from thread\n");

    int cutNum = randr(1,10);

    for(int i=0; i<cutNum; i++){
        Song cutSong = playlist1->data;
        deleteNode(&playlist1, 0);
        append(&userplaylist, cutSong);
    }

    
}

void * rmDisliked(void * arg){
    printf("hello from thread B\n");

    char * dislikedGenre = (char *) arg;

    sem_wait(&del);
        int i = 0;
        Node * current = playlist1;

        while (current != NULL){
            if(!strcmp(current->data.genre, dislikedGenre)){
                current = current->next;
                deleteNode(&playlist1, i);
                continue;
            }
            current = current->next;
            i++;
        }
    sem_post(&del);
    

    
}



void * rmOld(void * arg){
    printf("hello from thread C\n");
    int year = *((int *)arg);

    sem_wait(&del);
        int i = 0;
        Node * current = playlist1;

        while (current != NULL){
            if(current->data.year < year){
                current = current->next;
                deleteNode(&playlist1, i);
                continue;
            }
            current = current->next;
            i++;
        }
    sem_post(&del);

}


int main(){

    initLists();

    printList(playlist1);

    if(sem_init(&del, 0, 1) != 0)
	{
		printf("ERROR: cannot create semaphore\n");	
		return -1;
	}


    char dislikedGenre[15];
    printf("Please enter disliked genre: ");
    scanf(" %s", dislikedGenre);

    int year;
    printf("Please enter year: ");
    scanf(" %d", &year);

    void *memory = malloc(sizeof(int));
	int* yearP = (int *)memory;
	*yearP = year;
    

    pthread_t threadA;
    pthread_create(&threadA1, NULL, cutPaste, NULL);


    pthread_t threadB;
    pthread_create(&threadB, NULL, rmDisliked, dislikedGenre);

    pthread_t threadC;
    pthread_create(&threadC, NULL, rmOld, yearP);

    pthread_join(threadA, NULL);

    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printList(playlist1);
    printList(userplaylist);
    
}
