#include "team.h"
#include "season.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define ROWS_PER_TEAM 3
#define YEAR_ROWS 1
#define DRIVERS_PER_TEAM 2

typedef bool (*CmpFunction) (void*, void*, Season season);
static void sort (void** array, int n, CmpFunction compare, Season season);
static void AddDriversInTeams(Season season);
static int GetNumberOfDrivers(char** season_data, int arr_size);
static Driver* GetDrivers(char** season_data, int number_of_drivers, 
	Team* teams, Season season);
static int GetNumberOfDrivers(char** season_data, int arr_size);
static Team* GetTeams(char** season_data, int number_of_teams);
static int GetNumberOfTeams(int number_of_rows);
static int GetYear(char** season_data);
static char** StringSplit(char* string, int number_of_substrings, 
	const char* delimiter);
static int CharCount(const char* string, char character);
static bool TeamIsBigger (void* a, void *b, Season season);
static bool DriverIsBigger (void* a, void *b, Season season);

struct season{
	int year;
	int number_of_teams;
	Team* teams;
	int number_of_drivers;
	Driver* drivers;
	int* last_results;
};

/*Sorts an array of entities belonging to an instance of a season given
  a comparison function.*/
static void sort (void** array, int n, CmpFunction compare, Season season) {
	assert (array != NULL && compare != NULL);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (compare(array[i], array[j], season)) {
				void* tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

/*Sorts two teams according to their results in the season.*/ 
static bool TeamIsBigger (void* a, void *b, Season season) {
	TeamStatus team_status;
	int a_points = TeamGetPoints(a, &team_status);
	int b_points = TeamGetPoints(b, &team_status);
	if (a_points != b_points) {
		return a_points < b_points;
	} else {
		int first_a_id = DriverGetId(TeamGetDriver(a, FIRST_DRIVER));
		int second_a_id = DriverGetId(TeamGetDriver(a, SECOND_DRIVER));
		int first_b_id = DriverGetId(TeamGetDriver(b, FIRST_DRIVER));
		int second_b_id = DriverGetId(TeamGetDriver(b, SECOND_DRIVER));
		for (int i = 0; i < season->number_of_drivers; i++) {
			if (season->last_results[i] == first_a_id || 
				season->last_results[i] == second_a_id) {
				return false;
			}
			if (season->last_results[i] == first_b_id || 
				season->last_results[i] == second_b_id) {
				return true;
			}
		}
	}
	return false;
}

/*Sorts two drivers according to their results in the season.*/ 
bool DriverIsBigger (void* a, void *b, Season season) { //last results!
	DriverStatus driver_status;
	int a_points = DriverGetPoints(a, &driver_status);
	int b_points = DriverGetPoints(b, &driver_status);
	if (a_points != b_points) {
		return a_points < b_points;
	} else {
		for (int i = 0; i < season->number_of_drivers; i++) {
			if(season->last_results[i] == DriverGetId(a)) {
				return false;
			}
			if(season->last_results[i] == DriverGetId(b)) {
				return true;
			}
		}
	}
	return true;
}

/*Frees the memory allocated to season and all its elements*/
void SeasonDestroy(Season season) {
	if(season == NULL){
		return;
	}
	for (int i = 0; i < season->number_of_teams; i++) {
		TeamDestroy(season->teams[i]);
	}
	free(season->last_results);
	season->last_results=NULL;
	free(season->drivers);
	season->drivers = NULL;
	free(season->teams);
	season->teams = NULL;
	free(season);
	season = NULL;
}

/*Returns an array of drivers sorted by standing, from higher to lower*/
Driver* SeasonGetDriversStandings(Season season) {
	if (season == NULL) {
		return NULL;
	}
	Driver* drivers = malloc(sizeof(Driver)*(season->number_of_drivers));
	drivers = memcpy(drivers, season->drivers, 
		(season->number_of_drivers)*sizeof(Driver));
	return drivers;
}

/*Given a position in the season (positive integer), returns the driver 
  occupying this position. Sets status to error type if an error occurs.*/
Driver SeasonGetDriverByPosition(Season season, int position, 
	SeasonStatus* status) {
	if (season == NULL) {
		if (status != NULL) {
			*status = SEASON_NULL_PTR;
		}
		return NULL;
	}
	if (position <= 0 || position > season->number_of_drivers) {
		if (status != NULL) {
			*status = BAD_SEASON_INFO;
		}
		return NULL;
	}
	if (status != NULL) {
		*status = SEASON_OK;
	}
	return season->drivers[position-1]; 
}

/*Returns a pointer to an array of teams sorted by their standing in the season,
  from higher to lower.*/
Team* SeasonGetTeamsStandings(Season season) {
	if (season == NULL) {
		return NULL;
	}
	Team* teams = malloc(sizeof(Team)*(season->number_of_teams));
	teams = memcpy(teams, season->teams, 
		(season->number_of_teams)*sizeof(Team));
	return teams;
}

/*Given a position in the season (positive integer), returns the team occupying 
  this position. Sets status to the error type if an error occurs.*/
Team SeasonGetTeamByPosition(Season season, int position, 
	SeasonStatus* status) {
	if (season == NULL) {
		if (status != NULL) {
			*status = SEASON_NULL_PTR;
		}
		return NULL;
	}
	if (position <= 0 || position > season->number_of_teams) {
		if (status != NULL) {
			*status = BAD_SEASON_INFO;
		}
		return NULL;
	} else {
		if (status != NULL) {
			*status = SEASON_OK;
		}
		return season->teams[position-1];
	}
}

/*Returns the number of drivers in the season*/
int SeasonGetNumberOfDrivers(Season season) {
	if (season == NULL) {
		return 0;
	}
	return season->number_of_drivers;
}

/*Returns the number of teams in the season*/
int SeasonGetNumberOfTeams(Season season) {
	if (season == NULL) {
		return 0;
	}
	return season->number_of_teams;
}

/*Given the results of the last race, updates the season.*/
SeasonStatus SeasonAddRaceResult(Season season, int* results) {
	if (season == NULL || results == NULL) {
		return SEASON_NULL_PTR;
	}
	// test
	// for (int i = 0; i < season->number_of_drivers; i++) {
	// 	printf("%d\n", results[i]);
	// }
	memcpy(season->last_results, results, 
		(season->number_of_drivers)*sizeof(int));
	for (int i = 0; i < season->number_of_drivers; i++) {
		for (int j = 0; j < season->number_of_drivers; j++) {
			if (results[j] == DriverGetId(season->drivers[i])) {
				DriverAddRaceResult(season->drivers[i], j+1);
			}
		}
	}
	sort((void*)(season->drivers), season->number_of_drivers, DriverIsBigger, 
		season);
	sort((void*)(season->teams), season->number_of_teams, TeamIsBigger, season);
	// for (int i = 0; i < season->number_of_drivers; i++) {
	// 	printf("%d\n", DriverGetId(season->drivers[i]));
	// }
	// for (int j = 0; j < season->number_of_teams; j++) {
	// 	printf("%s\n", TeamGetName(season->teams[j]));
	// }
	return SEASON_OK;
}	

/*counts number of appearances of a char in string*/
static int CharCount(const char* string, char character){
	int number_of_characters = 0;
	for(int i = 0; i < strlen(string); i++){
		if(*(string+i) == character){
			number_of_characters++;
		}
	}
	return number_of_characters;
}

/*splits string into array of substrings that were seperated with
the delimiter in the original*/
static char** StringSplit(char* string, int number_of_substrings, 
	const char* delimiter){
	char** string_arr = malloc(sizeof(*string_arr)*number_of_substrings);
	char* substring = strtok(string, delimiter);
	for (int i = 0; i < number_of_substrings; ++i){
		*(string_arr+i) = malloc(strlen(substring)+1);
		strcpy(*(string_arr+i), substring);
		substring = strtok(NULL, delimiter);
	}
	return string_arr;
}

/*gets year of a season from an array of strings that
contains information about the season*/
static int GetYear(char** season_data){
	int year = atol(*season_data);
	return year;
}

/*gets number of teams given the number of rows in the season_info file*/
static int GetNumberOfTeams(int number_of_rows){
	int number_of_teams = (number_of_rows-YEAR_ROWS)/(ROWS_PER_TEAM);
	return number_of_teams;
}

/*adds teams to the teams array field of season*/
static Team* GetTeams(char** season_data, int number_of_teams){
	Team* teams = malloc(sizeof(*teams)*number_of_teams);
	int team_counter = 0;
	for(int i = YEAR_ROWS; team_counter < number_of_teams; i += ROWS_PER_TEAM){
		TeamStatus status;
		*(teams+team_counter) = TeamCreate(&status,*(season_data+i)); 
		team_counter++;
	}
	return teams;
}

/*gets number of drivers in season data array*/
static int GetNumberOfDrivers(char** season_data, int arr_size){
	int number_of_drivers = 0;
	for(int i = YEAR_ROWS; i < arr_size-DRIVERS_PER_TEAM; i+=ROWS_PER_TEAM){
		for(int j = 1; j <= DRIVERS_PER_TEAM; j++){
			if(strcmp(*(season_data+i+j), "None")){
				number_of_drivers++;
			}
		}
	}
	return number_of_drivers;
}

/*adds drivers to the drivers field of season
adjusts teams of drivers*/
static Driver* GetDrivers(char** season_data, int number_of_drivers, 
	Team* teams, Season season){
	Driver* drivers = malloc(sizeof(*drivers)*number_of_drivers);
	int driver_count = 0;
	int team_counter = 0;
	for(int i = YEAR_ROWS; driver_count < number_of_drivers; i+=ROWS_PER_TEAM){
		for(int j = 1; j <= DRIVERS_PER_TEAM; j++){
			if(strcmp(*(season_data+i+j), "None")){
				DriverStatus status;
				*(drivers+driver_count) = DriverCreate(&status, 
					*(season_data+i+j), driver_count+1);
				DriverSetTeam(*(drivers+driver_count), *(teams+team_counter));
				DriverSetSeason(*(drivers+driver_count), season);
				driver_count++;
			}
		}
		team_counter++;
	}
	return drivers;
}

/*Given an instance of season, adds drivers in teams.*/
static void AddDriversInTeams(Season season){
	for(int i = 0; i < season->number_of_drivers; i++){ 
		TeamAddDriver(DriverGetTeam(season->drivers[i]), season->drivers[i]);
	}
}

/*Given a file containing the information about the season, initializes an
  instance of a season.*/
Season SeasonCreate(SeasonStatus* status, const char* season_info){
	bool status_is_valid = status != NULL;
	if (status_is_valid) {
		*status = SEASON_OK;
	}
	Season season = malloc(sizeof(*season));
	if(season == NULL && status_is_valid){
		*status = SEASON_MEMORY_ERROR;
	}
	int number_of_rows = CharCount(season_info, '\n');
	char* temp_string = malloc(strlen(season_info)+1);
	if(temp_string == NULL && status_is_valid){
		*status = SEASON_MEMORY_ERROR;
	}
	strcpy(temp_string, season_info);
	char** season_data = StringSplit(temp_string, number_of_rows, "\n");
	if(season_data == NULL && status_is_valid){
		*status = SEASON_MEMORY_ERROR;
	}
	season->year = GetYear(season_data);
	season->number_of_teams = GetNumberOfTeams(number_of_rows);
	season->number_of_drivers = GetNumberOfDrivers(season_data, number_of_rows);
	season->teams = GetTeams(season_data, season->number_of_teams);
	season->drivers = GetDrivers(season_data, season->number_of_drivers, 
		season->teams, season);
	season->last_results = malloc(sizeof(int)*(season->number_of_drivers));
	AddDriversInTeams(season);
	for(int i = 0; i < number_of_rows; i++){
		free(*(season_data+i));
	}
	free(season_data);
	free(temp_string);
	return season;
}
