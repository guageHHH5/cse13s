#include <stdio.h>
#include <stdlib.h>
#include "names.h"
#include <stdbool.h>

typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;
const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER};

int main(){
	int players = 2;
	printf("Number of players (2 to 10)? ");
	int scanf_result = scanf("%d", &players);
	if (scanf_result < 1 || players < 2 || players > 10){
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
	}
	unsigned seed = 2023;
	printf("Random-number seed? ");
	unsigned num_assignments = scanf("%u", &seed);
	if (num_assignments < 1){
		fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
	}
	srandom(seed);
	int player_scores[players];
	for(int i = 0; i< players; i += 1){
		player_scores[i] = 0;
	}
	
	int win = 0;
	while(win == 0){
		for(int i = 0; i < players; i +=1){
			printf("%s\n", player_name[i]);
			int side_roll = 0;
			while(side_roll == 0){
				int rand = random();
				int roll = rand % 7;
				switch(pig[roll]){
					case SIDE:
						printf(" rolls 0, has %d\n", player_scores[i]);
						side_roll = 1;
						break;
					case RAZORBACK:
						player_scores[i] += 10;
						printf(" rolls 10, has %d\n", player_scores[i]);
						break;
					case TROTTER:
						player_scores[i] += 10;
						printf(" rolls 10, has %d\n", player_scores[i]);
						break;
					case SNOUTER:
						player_scores[i] += 15;
						printf(" rolls 15, has %d\n", player_scores[i]);
						break;
					default:
						player_scores[i] += 5;
						printf(" rolls 5, has %d\n", player_scores[i]);
						break;

				}
				if(player_scores[i] >= 100){
					printf("%s won!\n", player_name[i]);
					return 0;
				}
			}
		}
	}
}
