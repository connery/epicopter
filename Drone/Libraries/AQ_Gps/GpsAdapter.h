/*
  AeroQuad v3.0 - May 2011
  www.AeroQuad.com
  Copyright (c) 2011 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _AQ_GPS_ADAPTER_H_
#define _AQ_GPS_ADAPTER_H_

#include <GpsDataType.h>

struct gpsData gpsData; // This is accessed by the parser functions directly !

#ifndef GPS_SERIAL
  #define GPS_SERIAL Serial1
#endif

#define MIN_NB_SATS_IN_USE 6

#define GPS2RAD (1.0/572957795.0)
#define RAD2DEG 57.2957795

GeodeticPosition currentPosition;

float cosLatitude = 0.7; // @ ~ 45 N/S, this will be adjusted to home loc

struct gpsType
{
  const char *name;
  void (*init)();
  int  (*processData)(unsigned char);
};

byte  gpsConfigsSent;  // number of cfg msgs sent
byte  gpsConfigTimer;  // 0 = no more work, 1 = send now, >1 wait

// const unsigned long gpsBaudRates[] = { 9600L, 19200L, 38400L, 57600L, 115200L};

/* const struct gpsType gpsTypes[] = { */
/* #ifdef UseGPSUBLOX */
/*   { "UBlox", ubloxInit, ubloxProcessData }, */
/* #endif */
/* #ifdef UseGPSNMEA */
/*   { "NMEA", nmeaInit, nmeaProcessData }, */
/* #endif */
/* #ifdef UseGPSMTK16 */
/*   { "MTK16", mtk16Init, mtk16ProcessData }, */
/* #endif */
/* }; */

/* #define GPS_NUMBAUDRATES (sizeof(gpsBaudRates)/sizeof(gpsBaudRates[0])) */
/* #define GPS_NUMTYPES     (sizeof(gpsTypes)/sizeof(gpsTypes[0])) */

/* // Timeout for GPS */
/* #define GPS_MAXIDLE_DETECTING 200 // 2 seconds at 100Hz */
/* #define GPS_MAXIDLE 500           // 5 seconds at 100Hz */

void initializeGpsData()
{
  gpsData.lat = GPS_INVALID_ANGLE;
  gpsData.lon = GPS_INVALID_ANGLE;
  gpsData.course = GPS_INVALID_ANGLE;
  gpsData.speed = GPS_INVALID_SPEED;
  gpsData.height = GPS_INVALID_ALTITUDE;
  gpsData.accuracy = GPS_INVALID_ACCURACY;
  gpsData.fixage = GPS_INVALID_AGE;
  gpsData.state = GPS_DETECTING;
  gpsData.sentences = 0;
  gpsData.sats = 0;
  gpsData.fixtime = 0xFFFFFFFF;
}

/* struct gpsConfigEntry gpsConfigEntries[] = { */
/* #ifdef UseGPSMTK16 */
/*   MTK_CONFIGS, */
/* #endif */
/* #ifdef UseGPSUBLOX */
/*   UBLOX_CONFIGS, */
/* #endif */
/*   { NULL, 0 } */
/* }; */

/* void gpsSendConfig() // Send initialization strings to GPS one by one, it supports both string and binary packets */
/* { */
/*   if (gpsConfigEntries[gpsConfigsSent].data) { */
/*     if (gpsConfigEntries[gpsConfigsSent].len) { */
/*       for (int i=0; i<gpsConfigEntries[gpsConfigsSent].len; i++) { */
/*         GPS_SERIAL.write(gpsConfigEntries[gpsConfigsSent].data[i]); */
/*       } */
/*       gpsConfigTimer=gpsConfigEntries[gpsConfigsSent].len; */
/*     } */
/*     else { */
/*       GPS_SERIAL.print((char*)gpsConfigEntries[gpsConfigsSent].data); */
/*       gpsConfigTimer=strlen((char*)gpsConfigEntries[gpsConfigsSent].data); */
/*     } */
/*     if (gpsConfigTimer<10) { */
/*       gpsConfigTimer=10; */
/*     } */
/*     gpsConfigsSent++; */
/*   } */
/* } */

/* void initializeGps() // Initialize GPS subsystem (called once after powerup) */
/* { */
/*     gpsData.baudrate = 0; */
/*     GPS_SERIAL.begin(gpsBaudRates[gpsData.baudrate]); */
/*     for (gpsData.type=0; (gpsData.type < GPS_NUMTYPES); gpsData.type++) { */
/*       gpsTypes[gpsData.type].init(); */
/*     } */
/*     initializeGpsData(); */
/*  } */

void updateGps() // Read data from GPS, this should be called at 100Hz to make sure no data is lost due to overflowing serial input buffer
{
  /* gpsData.idlecount++; */

  /* while (GPS_SERIAL.available()) */
  /*   { */
  /*     unsigned char c = GPS_SERIAL.read(); */
  /*     int ret=0; */

  /*     if (gpsData.state == GPS_DETECTING) // If we are detecting run all parsers, stopping if any reports success */
  /* 	{ */
  /* 	  for (gpsData.type=0; (gpsData.type < GPS_NUMTYPES); gpsData.type++) */
  /* 	    { */
  /* 	      ret = gpsTypes[gpsData.type].processData(c); */
  /* 	      if (ret) // found GPS device start sending configuration */
  /* 		{ */
  /* 		  gpsConfigsSent = 0; */
  /* 		  gpsConfigTimer = 1; */
  /* 		  break; */
  /* 		} */
  /* 	    } */
  /* 	} */
  /*     else // Normal operation just execute the detected parser */
  /* 	{ */
  /* 	  ret = gpsTypes[gpsData.type].processData(c); */
  /* 	} */

  /*   if (ret) // Upon a successfully parsed sentence, zero the idlecounter and update position data */
  /*     { */
  /* 	if (gpsData.state == GPS_DETECTING) */
  /* 	  { */
  /* 	    gpsData.state = GPS_NOFIX; // make sure to lose detecting state (state may not have been updated by parser) */
  /* 	  } */

  /* 	gpsData.idlecount=0; */


  // LECTURE DES DONNEES DE POSITIONNEMENT

	currentPosition.latitude = gpsData.lat;
	currentPosition.longitude = gpsData.lon;
	currentPosition.altitude = gpsData.height;
      }
    }

  /* if (gpsConfigTimer) // Schedule confg sending if needed */
  /*   { */
  /*     if (gpsConfigTimer==1) */
  /* 	{ */
  /* 	  gpsSendConfig(); */
  /* 	} */
  /*     gpsConfigTimer--; */
  /*   } */

  /* if (gpsData.idlecount > ((gpsData.state == GPS_DETECTING) ? GPS_MAXIDLE_DETECTING : GPS_MAXIDLE)) // Check for inactivity, we have two timeouts depending on scan status */
  /*   { */
  /*     gpsData.idlecount=0; */
  /*     if (gpsData.state == GPS_DETECTING) // advance baudrate */
  /* 	{ */
  /* 	  gpsData.baudrate++; */
  /* 	  if (gpsData.baudrate >= GPS_NUMBAUDRATES) */
  /* 	    { */
  /* 	      gpsData.baudrate = 0; */
  /* 	    } */
  /*     GPS_SERIAL.begin(gpsBaudRates[gpsData.baudrate]); */
  /*   } */

    /* gpsData.state = GPS_DETECTING; // ensure detection state (if we lost connection to GPS) */

    /* for (gpsData.type=0; (gpsData.type < GPS_NUMTYPES); gpsData.type++) //  reinitialize all parsers */
    /*   { */
    /* 	gpsTypes[gpsData.type].init(); */
    /*   } */

    initializeGpsData(); // zero GPS state
    }
}

boolean haveAGpsLock() // SI LE GPS EST ACTIF
{
  return (gpsData.state > GPS_NOFIX) && (gpsData.sats >= MIN_NB_SATS_IN_USE); // gpsData.state > 1 et nbr de sattelite(s) actif(s) : definit a la valeur 0 dans le fichier GpsAdapter.h
}

long getCourse()
{
  return gpsData.course / 1000; // to whole degrees
}
unsigned long getGpsSpeed()
{
  return gpsData.speed;
}

unsigned long getGpsFixTime()
{
  return gpsData.fixtime;
}

unsigned long getGpsAltitude()
{
  return gpsData.height;
}

void setProjectionLocation(struct GeodeticPosition pos)
{
  cosLatitude = cos((float)pos.latitude * GPS2RAD);
}

float gpsRawDistance = 0.0;
float gpsBearing = 0;

void computeDistanceAndBearing(struct GeodeticPosition p1, struct GeodeticPosition p2)
{
  const float x = (float)(p2.longitude - p1.longitude) * GPS2RAD * cosLatitude;
  const float y = (float)(p2.latitude - p1.latitude) * GPS2RAD;
 
  gpsRawDistance = sqrt(x*x+y*y);
  gpsBearing = (RAD2DEG * atan2(x,y));
}

float getDistanceMeter()
{
  return (gpsRawDistance * 6371009);
}

float getDistanceFoot()
{
  return (gpsRawDistance * 20903280);
}

#endif
