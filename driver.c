#include "team.h"
#include "season.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* DriverStringDuplicate(char* str);

#define DRIVER_STRUCT_DEC_1

struct driver {
	int driverId;
	const char* driver_name;
	Team team;
	int points;
	Season season;
	int last_result;
};

Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
	Driver driver = malloc(sizeof(*driver));
	if (driver == NULL) {
		if (status != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
		return NULL;
	}
	if (driver_name == NULL || driverId < 0) {
		if (driver != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
		free(driver);
		return NULL;
	}
	driver->driver_name = DriverStringDuplicate(driver_name);
	driver->driverId = driverId;
	driver->team = NULL;
	driver->points = 0;
	driver->last_result = 0;
	driver->season = NULL;
	if (status != NULL) {
		*status = DRIVER_STATUS_OK;
	}
	return driver;
}

void DriverDestroy(Driver driver) {
	//free(driver->driver_name); // does not compile
	free(driver);
}

const char* DriverGetName(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->driver_name;
	}
}

int DriverGetId(Driver driver) {
	if (driver == NULL) {
		return 0;
	} else {
		return driver->driverId;
	}
}

Team DriverGetTeam(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->team;
	}
}

void  DriverSetTeam(Driver driver, Team team) {
	driver->team = team;
}

void  DriverSetSeason(Driver driver, Season season) {
	driver->season = season;
	driver->points = 0;
}

DriverStatus DriverAddRaceResult(Driver driver, int position) {
	if (position <= 0) {
		return INVALID_POSITION;
	} else if (driver->season == NULL) {
		return SEASON_NOT_ASSIGNED;
	} else if (driver == NULL) {
		return INVALID_DRIVER;
	} else {
		driver->points += position;
		return DRIVER_STATUS_OK;
	}
}

int DriverGetPoints(Driver driver, DriverStatus* status) {
	if (driver == NULL) {
		if (status != NULL) {
			*status = INVALID_DRIVER;
		}
		return 0;
	} else {
		if (status != NULL) {
			*status = DRIVER_STATUS_OK;
		}
		return driver -> points;
	}
}

static const char* DriverStringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}
