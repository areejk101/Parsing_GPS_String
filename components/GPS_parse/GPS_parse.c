#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_parse.h"

int parse_gps_data(const char *packet, GPSData *gpsData) {

	char packetCopy[256]; // Assuming a maximum length for the packet
	strncpy(packetCopy, packet, sizeof(packetCopy) - 1);
	packetCopy[sizeof(packetCopy) - 1] = '\0'; // Ensure null termination

	//printf("\ndebug 1\n");

	if (strlen(packet) < 7 || packet[0] != '$') {
		printf("error no $ found\n");
		return -1; // Invalid packet
	}
	int i = 1;
	int checksum = 0;
	while (packet[i] != '*' && packet[i] != '\0') {
		checksum ^= packet[i];
		i++;
	}

	if (packet[i] != '*') {
		printf("invalid checksum\n");
		return -1; // Invalid packet
	}

	// Convert checksum from ASCII to integer
	char checksumStr[3];
	strncpy(checksumStr, packet + i + 1, 2);
	checksumStr[2] = '\0';
	int packetChecksum = (int) strtol(checksumStr, NULL, 16);

	if (checksum != packetChecksum) {
		printf("error no $ found\n");
		return -1; // Invalid packet
	}

	//printf("debug 2\n");

	char *token;
	char *rest = packetCopy;
	int inc = 0;

	while ((token = strtok_r(rest, ",", &rest))) {
		inc++;
		if (inc == 1) {
			strncpy(gpsData->sentenceType, token,
					sizeof(gpsData->sentenceType) - 1);
			gpsData->sentenceType[sizeof(gpsData->sentenceType) - 1] = '\0';
			//printf("debug: sentenceType = %s\n", gpsData->sentenceType);
		} else if (inc == 2) {
			strncpy(gpsData->currentTime, token,
					sizeof(gpsData->currentTime) - 1);
			gpsData->currentTime[sizeof(gpsData->currentTime) - 1] = '\0';
			//printf("debug: currentTime = %s\n", gpsData->currentTime);
		} else if (inc == 3) {
			strncpy(gpsData->latitude, token, sizeof(gpsData->latitude) - 1);
			gpsData->latitude[sizeof(gpsData->latitude) - 1] = '\0';
			//printf("debug: latitude = %s\n", gpsData->latitude);
		} else if (inc == 4) {
			gpsData->latitudeDirection = token[0];
			//printf("debug: latitudeDirection = %c\n", gpsData->latitudeDirection);
		} else if (inc == 5) {
			strncpy(gpsData->longitude, token, sizeof(gpsData->longitude) - 1);
			gpsData->longitude[sizeof(gpsData->longitude) - 1] = '\0';
			//printf("debug: longitude = %s\n", gpsData->longitude);
		} else if (inc == 6) {
			gpsData->longitudeDirection = token[0];
			//printf("debug: longitudeDirection = %c\n", gpsData->longitudeDirection);
		} else if (inc == 7) {
			gpsData->fixType = atoi(token);
			//printf("debug: fixType = %d\n", gpsData->fixType);
		} else if (inc == 8) {
			gpsData->satellitesUsed = atoi(token);
			//printf("debug: satellitesUsed = %d\n", gpsData->satellitesUsed);
		} else if (inc == 9) {
			gpsData->horizontalDilution = atof(token);
			//printf("debug: horizontalDilution = %f\n", gpsData->horizontalDilution);
		} else if (inc == 10) {
			gpsData->altitude = atof(token);
			//printf("debug: altitude = %f\n", gpsData->altitude);
		} else if (inc == 11) {
			gpsData->altitudeUnits = token[0];
			//printf("debug: altitudeUnits = %c\n", gpsData->altitudeUnits);
		} else if (inc == 12) {
			gpsData->meanSeaLevelHeight = atof(token);
			//printf("debug: meanSeaLevelHeight = %f\n", gpsData->meanSeaLevelHeight);
		} else if (inc == 13) {
			gpsData->geoidSeparationUnits = token[0];
			//printf("debug: geoidSeparationUnits = %c\n", gpsData->geoidSeparationUnits);
		} else if (inc == 14) {
			gpsData->timeSinceLastDifferentialCorrection = atof(token);
			//printf("debug: timeSinceLastDifferentialCorrection = %f\n", gpsData->timeSinceLastDifferentialCorrection);
		} else if (inc == 15) {
			gpsData->differentialStationID = atoi(token);
			//printf("debug: differentialStationID = %d\n", gpsData->differentialStationID);
		} else if (inc == 16) {
			gpsData->checksum = (unsigned int) strtol(token, NULL, 16);
			// printf("debug: checksum = %u\n", gpsData->checksum);
		}

	}

	return 0; // Success
}
