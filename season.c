#include "team.h"
#include "season.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void SwapDrivers(Driver driver1, Driver driver2);
static void SwapTeams(Team team1, Team team2);
static void QuickSortDrivers(Driver* drivers, int number_of_drivers);
static void TiebreakQuickSortDrivers(Driver* drivers, int number_of_drivers); 
static void QuickSortTeams(Team* teams, int number_of_teams);
static void TiebreakQuickSortTeams(Team* teams, int number_of_teams);
static void AddDriversInTeams(Season season);
static int GetNumberOfDrivers(char** season_data, int arr_size);
static void DriverTiebreakSort(Season season);
static void AddDriversInTeams(Season season);
static Driver* GetDrivers(char** season_data, int number_of_drivers, Team* teams);
static int GetNumberOfDrivers(char** season_data, int arr_size);
static Team* GetTeams(char** season_data, int number_of_teams);
static int GetNumberOfTeams(int number_of_rows);
static int GetYear(char** season_data);
static char** StringSplit(char* string, int number_of_substrings, const char* delimiter);
static int CharCount(const char* string, char ch);
static void GetBestResultForTeams(Season season, int number_of_teams);
static void DriverTiebreakSort(Season season);
static void TeamTiebreakSort(Season season);

#ifndef DRIVER_STRUCT_DEC_1
#define DRIVER_STRUCT_DEC_2
struct driver {
	int driverId;
	const char* driver_name;
	Team team;
	int points;
	Season season;
	int last_result;
};
#endif 

#ifndef TEAM_STRUCT_DEC_1
#define TEAM_STRUCT_DEC_2
struct team {
	const char* name;
	Driver first_driver;
	Driver second_driver;
	int points;
	int best_result;
};
#endif


struct season{
	int year;
	int number_of_teams;
	Team* teams;
	int number_of_drivers;
	Driver* drivers;
};


void SeasonDestroy(Season season) {
	for (int i = 0; i < season->number_of_teams; i++) {
		TeamDestroy(season->teams[i]);
	}
	free(season->drivers);
	free(season);
}

Driver* SeasonGetDriversStandings(Season season) {
	if (season == NULL) {
		return NULL;
	}
	return season->drivers;
}

Driver SeasonGetDriverByPosition(Season season, int position, SeasonStatus* status) {
	if (season == NULL) {
		if (status != NULL) {
			*status = SEASON_NULL_PTR;
		}
		return NULL;
	}
	if (position <= 0 || position > season->number_of_drivers) {
		if (status != NULL) {
			*status = BAD_SEASON_INFO;
			return NULL;
		}
	}
	if (status != NULL) {
		*status = SEASON_OK;
	}
	return season->drivers[position-1];
}

Team* SeasonGetTeamsStandings(Season season) {
	if (season == NULL) {
		return NULL;
	}
	return season->teams;
}

Team SeasonGetTeamByPosition(Season season, int position, SeasonStatus* status) {
	if (position <= 0 || season == NULL || position > season->number_of_teams) {
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
	SeasonStatus season_status;
	season_status = SEASON_OK;
	for (int i = 0; i < season->number_of_drivers; i++) {
		for (int j = 0; j < season->number_of_drivers; j++) {
			if (results[j] == DriverGetId(season->drivers[i])) {
				DriverAddRaceResult(season->drivers[i], season->number_of_drivers-j-1);
				season->drivers[i]->last_result = season->number_of_drivers-j-1; //we must do something here
			}
		}
	}
	QuickSortDrivers(season->drivers, season->number_of_drivers);
	DriverTiebreakSort(season);
	TeamStatus status;
	GetBestResultForTeams(season, season->number_of_teams);
	for (int i = 0; i < season->number_of_teams; i++) {
	season->teams[i]->points = TeamGetPoints(season->teams[i], &status);//and here
	}
	QuickSortTeams(season->teams, season->number_of_teams);
	TeamTiebreakSort(season);
	return status;
}	

/*sorts drivers in case of an equal number of
points of different drivers in season*/
static void DriverTiebreakSort(Season season){
	int sequence_length = 1; 
	for(int i = 1; i < season->number_of_drivers; i++){
		DriverStatus status;
		int current_driver_points = DriverGetPoints(season->drivers[i], &status);
		int previous_driver_points = DriverGetPoints(season->drivers[i-1], &status);
		if(current_driver_points == previous_driver_points){
			sequence_length++;
		}
		else{
			TiebreakQuickSortDrivers(&(season->drivers[i]), sequence_length);
			sequence_length = 1;
			i++;
		}
	}
}

/*sorts teams in case of an equal number of
points of different teams in season*/
static void TeamTiebreakSort(Season season){
		int sequence_length = 1; 
	for(int i = 1; i < season->number_of_teams; i++){
		TeamStatus status;
		int current_team_points = TeamGetPoints(season->teams[i], &status);
		int previous_team_points = TeamGetPoints(season->teams[i-1], &status);
		if(current_team_points == previous_team_points){
			sequence_length++;
		}
		else{
			TiebreakQuickSortTeams(&(season->teams[i]), sequence_length);
			sequence_length = 1;
			i++;
		}
	}
}

static void SwapDrivers(Driver driver1, Driver driver2){
	Driver temp_driver = driver1;
	driver1 = driver2;
	driver2 = temp_driver;
}

static void QuickSortDrivers(Driver* drivers, int number_of_drivers) {
   int p, b = 1;
   int t = number_of_drivers - 1;
   if (number_of_drivers < 2)
      return;
   SwapDrivers(drivers[0], drivers[number_of_drivers/2]);
   p = drivers[0]->points;
   while(b <= t) {
      while(t >= b && drivers[t]->points >= p )
         t--;
      while(b <= t && drivers[b]->points < p)
         b++; 
      if (b < t) 
         SwapDrivers(drivers[b++], drivers[t--]);
   }
   SwapDrivers(drivers[0], drivers[t]);
   QuickSortDrivers(drivers, t);
   QuickSortDrivers(&drivers[t+1], number_of_drivers-t-1);
}

static void TiebreakQuickSortDrivers(Driver* drivers, int number_of_drivers) {
   int p, b = 1;
   int t = number_of_drivers - 1;
   if (number_of_drivers < 2)
      return;
   SwapDrivers(drivers[0], drivers[number_of_drivers/2]);
   p = drivers[0]->last_result;
   while(b <= t) {
      while(t >= b && drivers[t]->last_result >= p )
         t--;
      while(b <= t && drivers[b]->last_result < p)
         b++; 
      if (b < t) 
         SwapDrivers(drivers[b++], drivers[t--]);
   }
   SwapDrivers(drivers[0], drivers[t]);
   QuickSortDrivers(drivers, t);
   QuickSortDrivers(&drivers[t+1], number_of_drivers-t-1);
}

static void SwapTeams(Team team1, Team team2){
	Team temp_team = team1;
	team1 = team2;
	team2 = temp_team;
}

static void TiebreakQuickSortTeams(Team* teams, int number_of_teams) {
   int p, b = 1;
   int t = number_of_teams - 1;
   if (number_of_teams < 2)
      return;
   SwapTeams(teams[0], teams[number_of_teams/2]);
   p = teams[0]->best_result;
   while(b <= t) {
      while(t >= b && teams[t]->best_result >= p )
         t--;
      while(b <= t && teams[b]->best_result < p)
         b++; 
      if (b < t) 
         SwapTeams(teams[b++], teams[t--]);
   }
   SwapTeams(teams[0], teams[t]);
   QuickSortTeams(teams, t);
   QuickSortTeams(&teams[t+1], number_of_teams-t-1);
}

static void QuickSortTeams(Team* teams, int number_of_teams) {
   int p, b = 1;
   int t = number_of_teams - 1;
   if (number_of_teams < 2)
      return;
   SwapTeams(teams[0], teams[number_of_teams/2]);
   p = teams[0]->points;
   while(b <= t) {
      while(t >= b && teams[t]->points >= p )
         t--;
      while(b <= t && teams[b]->points < p)
         b++; 
      if (b < t) 
         SwapTeams(teams[b++], teams[t--]);
   }
   SwapTeams(teams[0], teams[t]);
   QuickSortTeams(teams, t);
   QuickSortTeams(&teams[t+1], number_of_teams-t-1);
}

/*adjusts best_result field for teams in season*/
static void GetBestResultForTeams(Season season, int number_of_teams){
	for(int i = 0; i < number_of_teams; i++){
		int first_driver_last_result = season->teams[i]->first_driver->last_result;
		int second_driver_last_result = season->teams[i]->first_driver->last_result;
		if (first_driver_last_result > second_driver_last_result){
			season->teams[i]->best_result = first_driver_last_result;
		}
		else{
			season->teams[i]->best_result = second_driver_last_result;
		}
	}
}

/***********************SEASON_CREATE****************************************/

/*counts number of appearances of a char in string*/
static int CharCount(const char* string, char ch){
	int number_of_ch = 0;
	for(int i = 0; i < strlen(string); i++){
		if(*(string+i) == ch){
			number_of_ch++;
		}
	}
	return number_of_ch;
}

/*splits string into array of substrings that were seperated with
the delimiter in the original*/
static char** StringSplit(char* string, int number_of_substrings, const char* delimiter){
	char** string_arr = malloc(sizeof(*string_arr)*number_of_substrings);
	char* substring = strtok(string, delimiter);
	for (int i = 0; i < number_of_substrings; ++i){
		*(string_arr+i) = malloc(sizeof(**(string_arr+i))*strlen(substring));
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

static int GetNumberOfTeams(int number_of_rows){
	int number_of_teams = (number_of_rows-1)/(3);
	return number_of_teams;
}

/*adds teams to the teams array field of season*/
static Team* GetTeams(char** season_data, int number_of_teams){
	Team* teams = malloc(sizeof(*teams)*number_of_teams);
	int team_counter = 0;
	for(int i = 1; team_counter < number_of_teams; i += 3){
		TeamStatus status;
		*(teams+team_counter) = TeamCreate(&status,*(season_data+i)); 
		team_counter++;
	}
	return teams;
}

/*gets number of drivers in season data array*/
static int GetNumberOfDrivers(char** season_data, int arr_size){
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
static Driver* GetDrivers(char** season_data, int number_of_drivers, Team* teams){
	Driver* drivers = malloc(sizeof(*drivers)*number_of_drivers);
	int driver_count = 1;
	int team_counter = 0;
	for(int i = 1; driver_count <= number_of_drivers; i+=3){
		for(int j = 1; j <= 2; j++){
			if(strcmp(*(season_data+i+j), "None")){
				DriverStatus status;
				*(drivers+driver_count) = DriverCreate(&status, *(season_data+i+j), driver_count);
				DriverSetTeam(*(drivers+driver_count), *(teams+team_counter));
				driver_count++;
			}
		}
		team_counter++;
	}
	return drivers;
}

static void AddDriversInTeams(Season season){
	for(int i = 0; i < season->number_of_drivers; i++){ 
		TeamAddDriver(DriverGetTeam(season->drivers[i]), season->drivers[i]);
	}
}

Season SeasonCreate(SeasonStatus* status, const char* season_info){
	Season season = malloc(sizeof(*season));
	int number_of_newline_chars = CharCount(season_info, '\n');
	int number_of_rows = number_of_newline_chars;
	char* temp_string = malloc(sizeof(*temp_string)*(strlen(season_info)+1));
	strcpy(temp_string, season_info);
	char** season_data = StringSplit(temp_string, number_of_rows, "\n");
	season->year = GetYear(season_data);
	season->number_of_teams = GetNumberOfTeams(number_of_rows);
	season->number_of_drivers = GetNumberOfDrivers(season_data, number_of_rows);
	season->teams = GetTeams(season_data, season->number_of_teams);
	season->drivers = GetDrivers(season_data, season->number_of_drivers, season->teams);
	AddDriversInTeams(season);
	return season;
}
