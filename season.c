#include "season.h"

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
	Driver* drivers = malloc(sizeof(*Driver)*length*DRIVER_PER_TEAM);
	if (drivers == NULL) {
		free(teams) //destroy? what?
		return ////
	}
	return season;
}

void SeasonDestroy(Season season) {
	int counter = season->NumberOfTeams;
	for (int i = 0; i < counter; i++) {
		TeamDestroy(season->Team[i])
	}
	free(season->drivers);
	free(season);
}

Driver* SeasonGetDriversStandings(Season season) {
	quick_sort(season->drivers, season->NumberOfDrivers);
	return season->drivers;
}

Driver SeasonGetDriverByPosition(Season season, int position, SeasonStatus* status) {
	if (position <= 0 || position >= season->NumberOfDrivers) {
		status = INVALID_POSITION;
	} else {
		Driver* drivers = SeasonGetDriversStandings(season);
		return drivers[position-1];
	}
}

Team* SeasonGetTeamsStandings(Season season) {
	int count = season->NumberOfTeams;
	TeamStatus status;
	for (int i = 0; i < NumberOfTeams; i++) {
		season->teams->points = TeamGetPoints(season->team, status);
	}
	quick_sort(season->teams, season->NumberOfTeams);
	return season->teams;
}

Team SeasonGetTeamByPosition(Season season, int position, SeasonStatus* status) {
	if (position <= 0 || position >= season->NumberOfTeams) {
		status = INVALID_POSITION;
	} else {
		Team* teams = SeasonGetTeamsStandings(season);
		return teams[position-1];
	}
}

int SeasonGetNumberOfDrivers(Season season) {
	return season->NumberOfDrivers; //do we imply that season != Null?
}

int SeasonGetNumberOfTeams(Season season) {
	return season->NumberOfTeams; //do we imply that season != Null?
}

SeasonStatus SeasonAddRaceResult(Season season, int* results) {
	for (int i = 0; i < NumberOfDrivers; i++) {
		for (int j = 0; j < NumberOfDrivers; j++) {
			if (results[j] == season->drivers[i]->DriverId) {
				season->drivers[i] += NumberOfDrivers-j-1;
			}
		}
	}
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

const quick_sort(int* items, int number_of_items)
{
   int p, b = 1; 
   int t = number_of_items - 1;
   if (number_of_items < 2)
      return;
   swap(&items[0], &items[number_of_items/2]);
   p = items[0]->points;
   while(b <= t) {
      while(t >= b && items[t]->points >= p )
         t--;
      while(b <= t && items[b]->points < p)
         b++; 
      if (b < t) 
         swap(&items[b++], &items[t--]);
   }
   swap(&items[0], &items[t]);
   quick_sort(items, t);
   quick_sort(items + t + 1, items – t - 1);
}