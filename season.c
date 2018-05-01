#include "season.h"
#define EXTRA_LINES 1
#define LINES_PER_TEAM 3
#define DRIVERS_PER_TEAM 2

typedef struct season {
	int year;
	int NumberOfTeams;
	Team* teams;
	int NumberOfDrivers;
	Driver* drivers;
} *Season

Season SeasonCreate(SeasonStatus* status,const char* season_info) {
	Season season = malloc(sizeof(*season));
	int length = (CountLines(season_info)-EXTRA_LINES)/LINES_PER_TEAM;
	Team* teams = malloc(sizeof(*Team)*length);
	if (teams == NULL) {
		return ////
	}
	Driver* drivers = malloc(sizeof(*Driver)*length*DRIVER_PER_TEAM)
	char buffer[BUFF_SIZE] = "";
	fclose(fd);
	return season;
}

const int CountLines(char* str) {
	int length = strlen(str);
	int count = 0;
	for(int i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') {
			count++;
		}
	}
	return count;
}