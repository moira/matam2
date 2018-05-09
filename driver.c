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
  sets status to the error code if an error occured.
  Error codes:
  DRIVER_MEMORY_ERROR – memory allocation failure,
  driverId is not a positive integer, or driver_name is a null pointer,
  according to the requirements.*/
Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
	if (driver_name == NULL || driverId <= 0) {
		if (status != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
		return NULL;
	}
	Driver driver = malloc(sizeof(*driver));
	if (driver == NULL) {
		if (status != NULL) {
			*status = DRIVER_MEMORY_ERROR;
		}
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

/*Given a pointer to the driver, destroys the driver instance.*/
void DriverDestroy(Driver driver) {
	if(driver == NULL){
		return;
	}
	free((void*)(driver->name));
	driver->name = NULL;
	free(driver);
	driver = NULL;
}

/*Given a pointer to a driver, returns the driver's name.
  Returns NULL when given a null pointer.*/
const char* DriverGetName(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->name;
	}
}

/*Given a pointer to a driver, returns the driver's ID.
  Returns NULL when given a null pointer.*/
int DriverGetId(Driver driver) {
	if (driver == NULL) {
		return 0;
	} else {
		return driver->driverId;
	}
}

/*Given a pointer to a driver, returns a pointer to the driver's team.
  Returns NULL when given a null pointer.*/
Team DriverGetTeam(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->team;
	}
}

/*Given a driver and a team, sets the driver's team to be this team.*/
void  DriverSetTeam(Driver driver, Team team) {
	if (driver != NULL && team != NULL) {
		driver->team = team;
	}
}

/*Given a driver and a season, adds this season to this driver instance. 
  If the team was empty, they become the first driver, otherwise 
  they become its second driver.*/
void  DriverSetSeason(Driver driver, Season season) {
	if (driver != NULL && season != NULL) {
		driver->season = season;
		driver->points = 0;
	}
}

/*Given the driver's position in a race, updates their points.*/
DriverStatus DriverAddRaceResult(Driver driver, int position) {
	if (position <= 0) {
		return INVALID_POSITION;
	} else if (driver == NULL) {
		return INVALID_DRIVER;
	} else if (driver->season == NULL) {
		return SEASON_NOT_ASSIGNED;
	} else {
		driver->points += (SeasonGetNumberOfDrivers(driver->season) - position);
		return DRIVER_STATUS_OK;
	}
}

/*Given a driver, returns their points.
  Returns 0 when given a null pointer.*/
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

/*Creates an immutable copy of a given string. 
  Returns NULL if the string is NULL.*/
static const char* DriverStringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}
