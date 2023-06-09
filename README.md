ESP-IDF
====================

# Parsing_GPS_String
Create a library for ESP-32 in C/C++ using esp-idf v5.0 stable for Parsing GPS data from individual data in a struct. GPS data is usually in NMEA format

- The code deals with GGA format of GPS data
- Header file is in: components/GPS_parse/include/GPS_parse.h
- Parseing function is in: components/GPS_parse/GPS_parse.c
- unit test code is main.cpp

## How to use
1. include the library 
> #include "GPS_parse.h"
2. load the structure with the name GPSData

> GPSData GPSdoc
3. Call the function 
>parse_gps_data(< a string packet>, &gpsData)


By following these steps, you can include the library, load the `GPSData` structure, and parse GPS data using the provided function.

Simply copy the above text and paste it into your `README.md` file.



## Attributes to access from the structure
| Attribute Name in code | Description |
|------------------------|-------------|
| sentenceType           | Sentence type of the GPS data |
| currentTime            | Current time in UTC format (if available) |
| latitude               | Latitude value in DDMM.MMM format |
| latitudeDirection      | Compass direction of latitude |
| longitude              | Longitude value in DDDMM.MMM format |
| longitudeDirection     | Compass direction of longitude |
| fixType                | Type of fix (0 for no fix, 1 for GPS, 2 for DGPS) |
| satellitesUsed         | Number of satellites used for the fix |
| horizontalDilution     | Horizontal dilution of precision value |
| altitude               | Altitude above mean sea level |
| altitudeUnits          | Units of altitude (M for meters) |
| meanSeaLevelHeight     | Height of mean sea level above WGS-84 earth ellipsoid |
| geoidSeparationUnits   | Units of the geoid separation (M for meters) |
| timeSinceLastDifferentialCorrection | Time since the last differential correction (ignored if inactive) |
| differentialStationID  | ID of the differential station (ignored if inactive) |
| checksum               | Checksum validation value (in hexadecimal) |


## Algorithm 
1. input string and the structure
2. Check for the validity of the string size and initiator
3. Create your own bytewise checksum 
4. Check if checksum is present in the string 
5. Compare the two checksums
6. use token method to splice the string using strtok_r() function
7. assign the values to the attributes of the structure 

