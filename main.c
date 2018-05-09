#include <stdio.h>
#include <stdlib.h>
#include "driver.h"
#include "team.h"
#include "season.h"

int main() {
    printf("\nMemorry Tests , (valgring it)");
    printf("\nPress enter to start");
    getchar();
    DriverStatus ds;
    TeamStatus ts;
    SeasonStatus ss;
    Driver driver =  DriverCreate(&ds, "driver_1", 1);
    Team team = TeamCreate(&ts, "Team_1");
    Season season = SeasonCreate(&ss, "2018\nTeam_1\nDriver_1\nDriver_2\nTeam_1\nDriver_1\nDriver_2\n");
    DriverDestroy(driver);
    TeamDestroy(team);
    SeasonDestroy(season);
}