#include "team.h"

static const char* StringDuplicate(char* str);

typedef struct team {
	const char* team_name;
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
	team->name = StringDuplicate(name);
	team->FirstDriver = NULL;
	team->SecondDriver = NULL;
	team->BestDriver = NULL;
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
	if (team->FirstDriver == NULL) {
		team->FirstDriver = driver;
		return STATUS_OK;
	} else if (team->SecondDriver == NULL) {
		team->SecondDriver = driver;
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
		return team->FirstDriver;
	} else if (driver_number == SECOND_DRIVER) {
		return team->SecondDriver;
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
		if (team->FirstDriver != NULL) {
			points += FirstDriver->points;
			if (team->SecondDriver != NULL) {
				points += SecondDriver->points;
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

static const char* StringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

