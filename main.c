#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "linkedlist.h"

int randr(int min, int max){ //generate rand vaiue in range
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}



char* genres[10] = {"pop", "rock", "jazz", "indie", "rap", "country", "metal", "electronic", "classical", "hip-hop"};

int main(){

    srand(time(NULL)); //initalizer for randoms to work

    List * playlist1 = makelist();
    List * playlist2 = makelist();
    List * userplaylist = makelist();

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
    Song song = get(2,playlist2);
    printf("%s, %s, %d", song.name, song.genre, song.year);

}
