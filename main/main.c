#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_parse.h"

int main() {
	const char *packet =
			"$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
	GPSData gpsData;
	printf("%s\n", packet);

	if (parse_gps_data(packet, &gpsData) == 0) {
		printf(
				"===============================================================\n");
		printf("Time: %s\n", gpsData.currentTime);
		printf("Latitude: %s\n", gpsData.latitude);
		printf("Latitude Direction: %c\n", gpsData.latitudeDirection);
		printf("Longitude: %s\n", gpsData.longitude);
		printf("Longitude Direction: %c\n", gpsData.longitudeDirection);
		printf("Fix Type: %d\n", gpsData.fixType);
		printf("Satellites Used: %d\n", gpsData.satellitesUsed);
		printf("Horizontal Dilution: %.2f\n", gpsData.horizontalDilution);
		printf("Altitude: %.2f\n", gpsData.altitude);
		printf("Altitude Units: %c\n", gpsData.altitudeUnits);
		printf("Mean Sea Level Height: %.2f\n", gpsData.meanSeaLevelHeight);
		printf("Geoid Separation Units: %c\n", gpsData.geoidSeparationUnits);
		printf("Time Since Last Differential Correction: %.2f\n",
				gpsData.timeSinceLastDifferentialCorrection);
		printf("Differential Station ID: %d\n", gpsData.differentialStationID);
		printf("Checksum: %u\n", gpsData.checksum);
	} else {
		printf("Failed to parse GPS data\n");
	}

	return 0;
}
;

void app_main(void) {
	printf("Hello, ESP-IDF!\n");
	main();

	printf("Exiting app_main\n");
}
