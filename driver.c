#include "driver.h"

typedef struct driver_t {
	int driverId;
	const char* driver_name;
	Team team;
	int points;//???
	Season season;
} *Driver;

Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
	Driver driver = malloc(sizeof(*driver));
	if (driver == NULL) {
		status = DRIVER_MEMORY_ERROR;
		return NULL;
	}
	driver->driver_name = StringDuplicate(driver_name);
	driver->driverId = driverId;
	driver->team = NULL;
	driver->points = 0;
	driver->season = NULL;
	status = DRIVER_STATUS_OK;
	return driver;
}

void DriverDestroy(Driver driver) {
	free(driver->driver_name);
	//free(driver->driver_points);//should this be an integer or a pointer?
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

Team  DriverGetTeam(Driver driver) {
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
		return INVALID POSITION;
	} else if (driver->season == NULL) {
		return SEASON_NOT_ASSIGNED;
	} else if (driver == NULL) {
		return NULL;
	} else {
		driver->points += position; //check
		return STATUS_OK;
	}
}

int DriverGetPoints(Driver driver, DriverStatus* status) { //there's a mistake in the hw description
	if (driver == NULL) {
		status = INVALID_DRIVER;
		return 0;
	} else {
		status = DRIVER_STATUS_OK;
		return driver -> points;
	}
}

