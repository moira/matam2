#include "driver.h"

typedef struct driver_t {
	int driverId;
	const char* driver_name;
	Team team;
	Points points;//???
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
	driver->points = NULL;
	driver->season = NULL;
	status = DRIVER_STATUS_OK;
	return driver;
}

void   DriverDestroy(Driver driver) {
	free(driver->driver_name);
	free(driver->driver_points);//????
	free(driver);
}

const char* DriverGetName(Driver driver) {
	if (driver == NULL) {
		return NULL;
	} else {
		return driver->driver_name;
	}
}

int DriverGetId(Driver driver);
Team  DriverGetTeam(Driver driver);
void  DriverSetTeam(Driver driver, Team team);
void  DriverSetSeason(Driver driver, Season season);
DriverStatus DriverAddRaceResult(Driver driver, int position);
int DriverGetPoints(Driver driver, DriverStatus* status);

