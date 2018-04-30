#include "team.h"

typedef struct team {
	const char* TeamName;
	Driver FirstDriver;
	Driver SecondDriver;
} *Team;

Team TeamCreate(TeamStatus* status, char* name) {
	Team team = malloc(sizeof(*team));
	if (!team) {
		TeamStatus = MEMORY_ERROR;
		return NULL;
	}
	team->name = StringDuplicate(name);
	team->FirstDriver = NULL;
	team->SecondDriver = NULL;
	status = STATUS_OK;
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

int TeamGetPoints(Team  team, TeamStatus *status) {
	if (team == NULL) {
		return NULL;
	} else {
		TeamStatus = STATUS_OK;
		/////////////////////////////
	}
}

void TeamDestroy(Team team) {
	free(team->FirstDriver);
	free(team->SecondDriver);
	free(team->name);
	free(team);
}

const char* StringDuplicate(const char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}


