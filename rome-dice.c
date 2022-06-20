#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct player {
	char *name;
	unsigned int stack;
	unsigned int turn;
} player_t;

unsigned short all_broke(player_t *players, unsigned short num_players);
int compare(const void *first, const void *second);
player_t *load_players(char *filename, unsigned short *num_players);
void print_players(player_t *players, unsigned short num_players);
unsigned short roll_dice();

int main(int argc, char **argv) {
	player_t *players = NULL;
	char *buffer = NULL;
	unsigned short i, num_players = 0, roll;
	unsigned int house = 16777216, turns = 0;
	
	if (argc == 2) {
		players = load_players(argv[1], &num_players);
	} else {
		printf("Number of players: ");
		scanf("%hu", &num_players);
		
		if ((buffer = (char *)calloc(256, sizeof(char))) == NULL) {
			fprintf(stderr, "unable to allocate memory\n");
			return EXIT_FAILURE;
		}
		
		if ((players = (player_t *)calloc(num_players, sizeof(player_t))) == NULL) {
			fprintf(stderr, "unable to allocate memory\n");
			return EXIT_FAILURE;
		}
		
		for (i = 0; i < num_players; i++) {
			printf("Player %hu's name: ", (unsigned short)(i + 1));
			scanf("%s", buffer);
			if ((players[i].name = (char *)calloc(strlen(buffer) + 1, sizeof(char))) == NULL) {
				fprintf(stderr, "unable to allocate memory\n");
				return EXIT_FAILURE;
			}
			strncpy(players[i].name, buffer, strlen(buffer));
			players[i].stack = 65536;
		}
	}
	print_players(players, num_players);
	
	srand(time(NULL));
	while (!all_broke(players, num_players)) {
		for (i = 0; i < num_players; i++) {
			if (players[i].stack < 4) {
				continue;
			}
			if (house < 10) {
				puts("House is bankrupt! All players exit now!");
				break;
			}
			roll = roll_dice();
			players[i].turn++;
			if (roll == 6) {
				house = house - 10;
				players[i].stack = players[i].stack + 10;
			} else if (roll <= 3) {
				house = house + 4;
				players[i].stack = players[i].stack - 4;
			}
			turns++;
		}
		if (house < 10) {
			break;
		}
	}
	qsort(players, num_players, sizeof(player_t), compare);
	printf("* * * * GAME OVER * * * *\nGame ended in %u turns.\nHouse ended with %u.\n\n", turns, house);
	print_players(players, num_players);
	
	for (i = 0; i < num_players; i++) {
		free(players[i].name);
	}
	free(buffer);
	free(players);
	return EXIT_SUCCESS;
}

unsigned short all_broke(player_t *players, unsigned short num_players) {
	unsigned short broke = TRUE, i;
	for (i = 0; i < num_players; i++) {
		broke = broke && players[i].stack < 4;
	}
	return broke;
}

int compare(const void *first, const void *second) {
	player_t *first_player = (player_t *)first;
	player_t *second_player = (player_t *)second;
	
	if (first_player->turn == second_player->turn) {
		return strcmp(first_player->name, second_player->name);
	}
	return second_player->turn - first_player->turn;
}

player_t *load_players(char *filename, unsigned short *num_players) {
	char *buffer = NULL, **names = NULL;
	unsigned short i = 0;
	FILE *fd = NULL;
	player_t *players = NULL;	
	
	if ((fd = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "unable to read input file");
		exit(EXIT_FAILURE);
	}
	if ((buffer = (char *)calloc(256, sizeof(char))) == NULL) {
		fprintf(stderr, "unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	if ((names = (char **)calloc(256, sizeof(char *))) == NULL) {
		fprintf(stderr, "unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	while (fgets(buffer, 256, fd) != NULL) {
		buffer[strlen(buffer) - 1] = '\0';
		if ((names[i] = (char *)calloc(strlen(buffer) + 1, sizeof(char))) == NULL) {
			fprintf(stderr, "unable to allocate memory\n");
			exit(EXIT_FAILURE);
		}
		strncpy(names[i], buffer, strlen(buffer));
		i++;
		(*num_players)++;
	}
	
	if ((players = (player_t *)calloc(*num_players, sizeof(player_t))) == NULL) {
		fprintf(stderr, "unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < *num_players; i++) {
		players[i].name = names[i];
		players[i].stack = 65536;
		players[i].turn = 0;
	}
	
	free(names);
	free(buffer);
	fclose(fd);
	return players;
}

void print_players(player_t *players, unsigned short num_players) {
	unsigned short i;
	puts("Player\tStack\tTurns");
	for (i = 0; i < num_players; i++) {
		printf("%s\t%u\t%u\n", players[i].name, players[i].stack, players[i].turn);
	}
	puts("");
}

unsigned short roll_dice() {
	return rand() % 6 + 1; 
}
