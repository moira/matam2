#include "season.h"

typedef struct season{
	int year;
	int number_of_teams;
	Team* teams;
	int number_of_drivers;
	Driver* drivers;
}*Season;

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

/*adds teams to the teams array of season*/
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
	number_of_rows = number_of_newline_chars+1;
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
