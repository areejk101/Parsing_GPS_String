

typedef struct {
	char sentenceType[3];
	char currentTime[11];
	char latitude[10];
	char latitudeDirection;
	char longitude[11];
	char longitudeDirection;
	int fixType;
	int satellitesUsed;
	float horizontalDilution;
	float altitude;
	char altitudeUnits;
	float meanSeaLevelHeight;
	char geoidSeparationUnits;
	float timeSinceLastDifferentialCorrection;
	int differentialStationID;
	unsigned int checksum;
} GPSData;


int parse_gps_data(const char *packet, GPSData *gpsData);


