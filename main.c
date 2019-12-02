#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"
#include "semaphore.h"
#include <pthread.h>
#include <string.h>

List * playlist1;
List * playlist2;
List * userplaylist;

sem_t del;



int randr(int min, int max){ //generate rand value in range
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void initLists(){

    char* genres[10] = {"pop", "rock", "jazz", "indie", "rap", "country", "metal", "electronic", "classical", "hip-hop"};

    srand(time(NULL)); //initalizer for randoms to work

    playlist1 = makelist();
    playlist2 = makelist();
    userplaylist = makelist();

    for(int i=0; i<10; i++){
        Song* song = (Song*)malloc(sizeof(Song*));
        sprintf(song->name, "Song Name %d", i);
        sprintf(song->genre, "%s", genres[randr(0,9)]);
        song->year = randr(1950, 2019);

        add(*song, playlist1);
    }
    for(int i=0; i<23; i++){
        Song* song = (Song*)malloc(sizeof(Song*));
        sprintf(song->name, "Song Name %d", i);
        sprintf(song->genre, "%s", genres[randr(0,9)]);
        song->year = randr(1950, 2019);

        add(*song, playlist2);
    }
}


void * cutPaste(void * arg){
    printf("hello from thread\n");

    

    
}

void * rmDisliked(void * arg){
    printf("hello from thread\n");

    char * dislikedGenre = (char *) arg;

    sem_wait(&del);
        for(int i=0; i<getSize(playlist2); i++){
            Song current = get(i,playlist2);
            if(!strcmp(current.genre, dislikedGenre)){
                delete(current, playlist2);
            }
        }  
    sem_post(&del);
    

    
}

void removeOld(int year, List * list){

    Song current;

    for(int i=0; i<getSize(list); i++){
        current = get(i,list);
        //delete(current, list);
        if(current.year < year){
            
        }
    }
}

void * rmOld(void * arg){
    printf("hello from thread\n");
    int year = *((int *)arg);

    sem_wait(&del);
        removeOld(year, playlist2);
    sem_post(&del);

    display(playlist2);
    
}


int main(){

    initLists();

    display(playlist2);

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
    
    pthread_t threadA1;
    pthread_create(&threadA1, NULL, cutPaste, NULL);

    pthread_t threadA2;
    pthread_create(&threadA2, NULL, cutPaste, NULL);

    pthread_t threadA3;
    pthread_create(&threadA3, NULL, cutPaste, NULL);

    //pthread_t threadB;
    //pthread_create(&threadB, NULL, rmDisliked, dislikedGenre);

    pthread_t threadC;
    pthread_create(&threadC, NULL, rmOld, yearP);

    //pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
    
    destroy(playlist2);
    display(playlist2);
    
}
