#include "team.h"
#include "season.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* TeamStringDuplicate(char* str);

struct team {
	const char* name;
	Driver first_driver;
	Driver second_driver;
};

/*Given a name string, returns a new team with this name.
  Returns NULL in case of a failure.
  Error codes (appear in status):
  TEAM_MEMORY_ERROR – failure to allocate memory,
  TEAM_NULL_PTR – name string was a null pointer.*/
Team TeamCreate(TeamStatus* status, char* name) {
	if (name == NULL) {
		if (status != NULL) {
			*status = TEAM_NULL_PTR;
		}
		return NULL;
	}
	Team team = malloc(sizeof(*team));
	if (team == NULL) {
		if (status != NULL) {
			*status = TEAM_MEMORY_ERROR;
		}
		return NULL;
	}
	team->name = TeamStringDuplicate(name);
	team->first_driver = NULL;
	team->second_driver = NULL;
	if (status != NULL) {
		*status = TEAM_STATUS_OK;
	}
	return team;
}

/*Given a team and a driver, adds the driver to the team.
  Returns the status. Error codes (appear in status): 
  TEAM_NULL_PTR – one of the arguments is a null pointer,
  TEAM_FULL – the team already has two drivers.*/
TeamStatus TeamAddDriver(Team team, Driver driver) {
	if (team == NULL || driver == NULL) {
		return TEAM_NULL_PTR;
	}
	if (team->first_driver == NULL) {
		team->first_driver = driver;
		return TEAM_STATUS_OK;
	} else if (team->second_driver == NULL && driver != team->first_driver) {
		team->second_driver = driver;
		return TEAM_STATUS_OK;
	} else {
		return TEAM_FULL;
	}
}

/*Given a pointer to team, returns its name.
  Returns NULL if the pointer to the team is NULL.*/
const char* TeamGetName(Team team) {
	if (team == NULL) {
		return NULL;
	} else {
		return team->name;
	}
}

/*Given a team and a number – FIRST_DRIVER or SECOND_DRIVER – returns
  the index to the respective driver of this team.
  Returns NULL in case of an error.*/
Driver TeamGetDriver(Team team, DriverNumber driver_number) {
	if (team == NULL) {
		return NULL;
	}
	if (driver_number == FIRST_DRIVER) {
		return team->first_driver;
	} else if (driver_number == SECOND_DRIVER) {
		return team->second_driver;
	} else {
		return NULL;
	}
}

/*Given a team and a pointer to TeamStatus, returns the current number
  of the team's points.
  Error codes (appear in status):
  TEAM_NULL_PTR – team is a null pointer.*/
int TeamGetPoints(Team team, TeamStatus *status) {
	if (team == NULL) {
		if (status != NULL) {
			*status = TEAM_NULL_PTR;
		}
		return 0;
	}
	DriverStatus driver_status;
	int points = 0;
	if (team->first_driver != NULL) {
		points += DriverGetPoints(team->first_driver, &driver_status);
		if (team->second_driver != NULL) {
			points += DriverGetPoints(team->second_driver, &driver_status);
		}
	}
	if (status != NULL) {
		*status = TEAM_STATUS_OK;
	}
	return points;
}

/*Given a team name, destroys the team and its drivers.*/
void TeamDestroy(Team team) {
	if(team == NULL){
		return;
	}
	if(team->first_driver != NULL){
		DriverDestroy(team->first_driver);
		team->first_driver = NULL;
	}
	if(team->second_driver != NULL){
		DriverDestroy(team->second_driver);
		team->second_driver = NULL;
	}
	free((void*)(team->name));
	team->name = NULL;
	free(team);
	team = NULL;
}

/*Given a string, creates its immutable copy.
  Returns NULL in case of a memory allocation failure.*/
static const char* TeamStringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}
