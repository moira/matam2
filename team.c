#include "team.h"
#include <string.h>

static const char* TeamStringDuplicate(char* str);

typedef struct team {
	const char* name;
	Driver first_driver;
	Driver second_driver;
	Driver best_driver;
	int points;
} *Team;

Team TeamCreate(TeamStatus* status, char* name) {
	Team team = malloc(sizeof(*team));
	if (team == NULL) {
		if (status != NULL) {
			*status = MEMORY_ERROR;
		}
		return NULL;
	}
	if (name == NULL) { //https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=189
		free(team);
		if (status != NULL) {
			*status = MEMORY_ERROR;
		}
		return NULL;
	}
	team->name = TeamStringDuplicate(name);
	team->first_driver = NULL;
	team->second_driver = NULL;
	team->best_driver = NULL;
	team->points = 0;
	if (status != NULL) {
		*status = STATUS_OK;
	}
	return team;
}

TeamStatus TeamAddDriver(Team team, Driver driver) {
	if (team == NULL || driver = NULL) {
		return TEAM_NULL_PTR;
	}
	if (team->first_driver == NULL) {
		team->first_driver = driver;
		return STATUS_OK;
	} else if (team->second_driver == NULL) {
		team->second_driver = driver;
		return STATUS_OK;
	} else {
		return TEAM_FULL;
	}
}

const char* TeamGetName(Team team) {
	if (team == NULL) {
		return NULL;
	} else {
		return team->name;
	}
}

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

int TeamGetPoints(Team team, TeamStatus *status) {
	if (team == NULL) {
		if (status != NULL) {
			*status = TEAM_NULL_PTR;
		}
		return 0;
	} else {
		int points = 0;
		if (team->first_driver != NULL) {
			points += first_driver->points;
			if (team->second_driver != NULL) {
				points += second_driver->points;
			}
		}
		if (status != NULL) {
			*status = STATUS_OK;
		}
		return points;
	}
}

void TeamDestroy(Team team) {
	free(team->first_driver);
	free(team->second_driver);
	free(team->best_driver);
	free(team->name);
	free(team);
}

static const char* TeamStringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

