#include "season.h"
#include <string.h>

//https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=182 statuses?


const QuickSort(int* items, int number_of_items);

typedef struct season{
	int year;
	int number_of_teams;
	Team* teams;
	int number_of_drivers;
	Driver* drivers;
}*Season;

char** stringSplit(char* string, int* number_of_strings){
	*number_of_strings = 1;
	char** string_array = NULL;
	int i = 1;
	char* token = strtok(string, "\n")
	*string_array = token;
	while(token != NULL){
		token = strtok(NULL, "\n");
		*(string_array+i) = token;
		*number_of_strings++;
		i++;
	}
	return string_array;
}

Season SeasonCreate(SeasonStatus* status,const char* season_info){
	Season season = malloc(sizeof(*season));
	int number_of_rows;
	char** row_array = stringSplit(season_info, &number_of_rows);
	season->year = atol(*row_array);
	season->number_of_drivers = (number_of_rows-1)/3;
	int none_counter = 0;
	for(int i = 0; i < number_of_rows; i++){
		if(strcmp(row_array[i], "None") == 0){
			none_counter++;
		}
	}
	int number_of_drivers = 2 * team_counter - none_counter;
	int driver_counter = 0;
	for(int i = 1; i < number_of_rows; i+=3){
		season->teams[team_counter] = teamCreate(row_array[i]);
		if(!strcmp(row_array[i+1], "None")){
			season->drivers[driver_counter] = driverCreate(row_array[i+1], driver_counter+1);
		}
		if(!strcmp(row_array[i+1], "None")){
			season->drivers[driver_counter] = driverCreate(row_array[i+1], driver_counter+1);
		}
	}
	return season;
}

// Season SeasonCreate(SeasonStatus* status,const char* season_info) {
// 	Season season = malloc(sizeof(*season));
// 	int length = (CountLines(season_info)-EXTRA_LINES)/LINES_PER_TEAM;
// 	Team* teams = malloc(sizeof(*Team)*length);
// 	if (teams == NULL) {
// 		return ////
// 	}
// 	Driver* drivers = malloc(sizeof(*Driver)*length*DRIVER_PER_TEAM);
// 	if (drivers == NULL) {
// 		free(teams) //destroy? what?
// 		return ////
// 	}
// 	return season;
// }

void SeasonDestroy(Season season) {
	int counter = season->number_of_teams;
	for (int i = 0; i < counter; i++) {
		TeamDestroy(season->teams[i])
	}
	free(season->drivers);
	free(season);
}

Driver* SeasonGetDriversStandings(Season season) {
	return season->drivers;
}

const void SeasonResolveTiesForDrivers(Season season, int* results) {
	for (int i = 0; i < season->number_of_drivers; i++) {
		////
	}
}

const void SeasonResolveTiesForTeams(Season season, int* results) {
	for (int i = 0; i < season->number_of_teams; i++) {
		////
	}
}

Driver SeasonGetDriverByPosition(Season season, int position, SeasonStatus* status) {
	if (season == NULL) {
		status = SEASON_NULL_PTR;
		return NULL;
	}
	if (position <= 0 || position > season->number_of_drivers) {
		status = INVALID_POSITION;
		return NULL;
	} else {
		Driver* drivers = SeasonGetDriversStandings(season);
		return drivers[position-1];
	}
}

Team* SeasonGetTeamsStandings(Season season) {
	return season->teams;
}
 
// Team* SeasonGetTeamsStandings(Season season) {
// 	int count = season->number_of_teams;
// 	TeamStatus status;
// 	for (int i = 0; i < number_of_teams; i++) {
// 		season->teams->points = TeamGetPoints(season->team, status);
// 	}
// 	QuickSort(season->teams, season->number_of_teams);
// 	return season->teams;
// }

Team SeasonGetTeamByPosition(Season season, int position, SeasonStatus* status) {
	if (position <= 0 || position > season->number_of_teams) {
		status = BAD_SEASON_INFO;
	} else {
		Team* teams = SeasonGetTeamsStandings(season);
		return teams[position-1];
	}
}

int SeasonGetNumberOfDrivers(Season season) {
	if (season == NULL) {
		return 0;
	}
	return season->number_of_drivers;
}

int SeasonGetNumberOfTeams(Season season) {
	if (season == NULL) {
		return 0;
	}
	return season->number_of_teams;
}

SeasonStatus SeasonAddRaceResult(Season season, int* results) {
	for (int i = 0; i < number_of_drivers; i++) {
		for (int j = 0; j < number_of_drivers; j++) {
			if (results[j] == season->drivers[i]->DriverId) {
				season->drivers[i] += number_of_drivers-j-1;
			}
		}
	}
	QuickSort(season->drivers, season->number_of_drivers);

	int count = season->number_of_teams;
	TeamStatus status;
	for (int i = 0; i < number_of_teams; i++) {
		season->teams->points = TeamGetPoints(season->team, status);
	}
	QuickSort(season->teams, season->number_of_teams);
	SeasonResolveTiesForDrivers(Season season, int* results);
	SeasonResolveTiesForTeams(Season season, int* results);
	///
}


const void QuickSort(void* items, int number_of_items) {
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
   QuickSort(items, t);
   QuickSort(items + t + 1, items – t - 1);
}

