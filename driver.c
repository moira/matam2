#include "team.h"
#include "season.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* DriverStringDuplicate(char* str);

struct driver {
	int driverId;
	const char* name;
	Team team;
	int points;
	Season season;
};

/*Given a name string and an integer ID, creates a driver instance.
  Sets status to DRIVER_STATUS_OK if the instance was created,
  sets status to the error type if an error occured.*/
Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
	Driver driver = malloc(sizeof(*driver));
	if (driver == NULL) {
		if (status != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
		return NULL;
	}
	if (driver_name == NULL || driverId <= 0) {
		if (status != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
		free(driver);
		return NULL;
	}
	driver->name = DriverStringDuplicate(driver_name);
	driver->driverId = driverId;
	driver->team = NULL;
	driver->points = 0;
	driver->season = NULL;
	if (status != NULL) {
		*status = DRIVER_STATUS_OK;
	}
	return driver;
}

void DriverDestroy(Driver driver) {
	if(driver == NULL){
		return;
	}
	free((void*)(driver->name));
	driver->name = NULL;
	free(driver);
	driver = NULL;
}

const char* DriverGetName(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->name;
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
	if (driver != NULL && team != NULL) { //add smth?
		driver->team = team;
	}
}

void  DriverSetSeason(Driver driver, Season season) {
	if (driver != NULL && season != NULL) {
		driver->season = season;
		driver->points = 0;
	}
}

DriverStatus DriverAddRaceResult(Driver driver, int position) {
	if (position <= 0) { //CHECK
		return INVALID_POSITION;
	} else if (driver == NULL) {
		return INVALID_DRIVER;
	} else if (driver->season == NULL) {
		return SEASON_NOT_ASSIGNED;
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
