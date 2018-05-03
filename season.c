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
// 		season->teams->points = TeamGetPoints(season->team, status);// 	}
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
				season->drivers[i]->points += number_of_drivers-j-1;
				season->drivers[i]->last_result = number_of_drivers-j-1;
			}
		}
	}
	QuickSort(season->drivers, season->number_of_drivers, points);
	DriverTiebreakSort(season, results);
	
	int count = season->number_of_teams;
	TeamStatus status;
	for (int i = 0; i < number_of_teams; i++) {
		season->*(teams+i)->points = TeamGetPoints(season->*(teams+i), status);
	}
	QuickSort(season->teams, season->number_of_teams, points);
	TeamTiebreakSort(season, results);
}	


void DriverTiebreakSort(Season season){
	int sequence_length = 1; 
	for(int i = 1; i < season->number_of_drivers; i++){
		int current_driver_points = DriverGetPoints(season->*(drivers+i));
		int previous_driver_points = DriverGetPoints(season->*(drivers+i-1));
		if(current_driver_points == previous_driver_points){
			sequence_length++;
		}
		else{
			QuickSort(season->(drivers+i), sequence_length, last_result);
			sequence_length = 1;
			i++;
		}
	}
}

void TeamTiebreakSort(Season season){
		int sequence_length = 1; 
	for(int i = 1; i < season->number_of_teams; i++){
		int current_team_points = TeamGetPoints(season->*(teams+i));
		int previous_team_points = TeamGetPoints(season->*(teams+i-1));
		if(current_team_points == previous_team_points){
			sequence_length++;
		}
		else{
			QuickSort(season->(teams+i), sequence_length, best_result);
			sequence_length = 1;
			i++;
		}
	}
}

const void QuickSort(void* items, int number_of_items, size_t field_type) {
   int p, b = 1;
   int t = number_of_items - 1;
   if (number_of_items < 2)
      return;
   swap(&items[0], &items[number_of_items/2]);
   p = items[0]->field_type;
   while(b <= t) {
      while(t >= b && items[t]->field_type >= p )
         t--;
      while(b <= t && items[b]->field_type < p)
         b++; 
      if (b < t) 
         swap(&items[b++], &items[t--]);
   }
   swap(&items[0], &items[t]);
   QuickSort(items, t);
   QuickSort(items + t + 1, items – t - 1);
}

void getBestResultsForTeams(Season season, int number_of_teams){
	for(int i = 0; i < number_of_teams; i++){
		int first_driver_last_result = season->*(teams+i)->first_driver->last_result;
		int second_driver_last_result = season->*(teams+i)->first_driver->last_result;
		if (first_driver_last_result > second_driver_last_result){
			season->*(teams+i)->best_result = first_driver_last_result;
		}
		else{
			season->*(teams+i)->best_driver = second_driver_last_result;
		}
	}
}

/*counts number of appearances of a char in string*/
int charCount(char* string, char ch){
	int number_of_ch = 0
	for(int i = 0; i < strlen(string); i++){
		if(*(string+i) == ch){
			number_of_ch++;
		}
	}
	return number_of_ch;
}

/*splits string into array of substrings that were seperated with
the delimiter in the original*/
char** stringSplit(char* string, int number_of_substrings, char delimiter){
	char** string_arr = malloc(sizeof(*string_arr)*number_of_substrings);
	char* substring = strtok(string, delimiter);
	for (int i = 0; i < number_of_substrings; ++i){
		strcpy(*(string_arr+i), substring);
		substring = strtok(NULL, delimiter);
	}
	return string_arr;
}

/*gets year of a season from an array of strings that
contains information about the season*/
int getYear(char** season_data){
	int year = atol(*season_data);
	return year;
}

int getNumberOfTeams(int number_of_rows){
	int number_of_teams = (number_of_rows-1)/(3);
	return number_of_teams;
}

/*adds teams to the teams array field of season*/
Team* getTeams(char** season_data, int number_of_teams){
	Team* teams = malloc(sizeof(*teams)*number_of_teams);
	int team_counter = 0;
	for(int i = 1; team_counter < number_of_teams; i += 3){
		TeamStatus team_status;
		*(teams+team_counter) = TeamCreate(&status,*(season_data+i)); 
		team_counter++;
	}
	return teams;
}

/*gets number of drivers in season data array*/
int getNumberOfDrivers(char** season_data, int arr_size){
	int number_of_drivers = 0;
	for(int i = 1; i < arr_size-2; i+=3){
		for(int j = 1; j <= 2; j++){
			if(strcmp(*(season_data+i+j), "None")){
				number_of_drivers++;
			}
		}
	}
	return number_of_drivers;
}

/*adds drivers to the drivers field of season
adjusts teams of drivers*/
Driver* setDrivers(char** season_data, int number_of_drivers, Team* teams){
	Driver* drivers = malloc(sizeof(*drivers)*number_of_drivers);
	int driver_count = 1;
	int team_counter
	for(int i = 1; driver_count <= number_of_drivers; i+=3){
		for(int j = 1; j <= 2; j++){
			if(strcmp(*(season_data+i+j), "None")){
				DriverStatus status;
				*(drivers+driver_count) = DriverCreate(&status, *(season_data+i+j), driver_count);
				DriverSetTeam(*(drivers+driver_count), teams);
				driver_count++;
			}
		}
	}
	return drivers;
}

Season SeasonCreate(SeasonStatus* status,const char* season_info){
	Season season = malloc(sizeof(*season));
	int number_of_newline_chars = charCount(season_info, "\n");
	number_of_rows = number_of_newline_chars;
	char** season_data = stringSplit(season_info, number_of_rows, "\n");
	season->year = getYear(season_data);
	season->number_of_teams = getNumberOfTeams(number_of_rows);
	season->number_of_drivers = getNumberOfDrivers(season_data, number_of_rows);
	season->teams = getTeams(season_data, season->number_of_teams);
	season->drivers = getDrivers(season_data, season->number_of_drivers, season->teams);
	for(int i = 0; i < season->number_of_drivers; i++){
		driver = season->*(drivers+i); 
		TeamAddDriver(DriverGetTeam(driver), driver);
	}
	return season;
}
