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

#define MIN_NB_SATS_IN_USE 5 // MAINTENANT TRAITE SUR LA RASPBERRY

#define GPS2RAD (1.0/572957795.0)
#define RAD2DEG 57.2957795

GeodeticPosition currentPosition;

float cosLatitude = 0.7; // @ ~ 45 N/S, this will be adjusted to home loc

void initializeGpsData() // "OK" IF AVAILABLE VALUE FROM GPS RECEIVER
{
  gpsData.lat = GPS_INVALID_ANGLE; // OK
  gpsData.lon = GPS_INVALID_ANGLE; // OK
  gpsData.course = GPS_INVALID_ANGLE;
  gpsData.speed = GPS_INVALID_SPEED;
  gpsData.height = GPS_INVALID_ALTITUDE; // OK
  gpsData.accuracy = GPS_INVALID_ACCURACY;
  gpsData.fixage = GPS_INVALID_AGE;
  gpsData.state = GPS_DETECTING;
  gpsData.sentences = 0;
  gpsData.sats = 0; // OK
  gpsData.fixtime = 0xFFFFFFFF; // OK
}

void gpsSendConfig()
{

}

void initializeGps()
{
  initializeGpsData();
}

void updateGps()
{
  currentPosition.latitude = gpsData.lat;
  currentPosition.longitude = gpsData.lon;
  currentPosition.altitude = gpsData.height;
}

boolean haveAGpsLock() // SI LE GPS EST ACTIF
{
  return (/* gpsData.state > GPS_NOFIX && */ gpsData.sats >= MIN_NB_SATS_IN_USE); // gpsData.state > 1 et nbr de sattelite(s) actif(s) : definit a la valeur 0 dans le fichier GpsAdapter.h
}

long getCourse()  // NOT AVAILABLE NOW
{
  return gpsData.course / 1000; // to whole degrees
}

unsigned long getGpsSpeed() // NOT AVAILABLE NOW
{
  return gpsData.speed;
}

unsigned long getGpsFixTime() // OK
{
  return gpsData.fixtime;
}

unsigned long getGpsAltitude() // OK
{
  return gpsData.height;
}

void setProjectionLocation(struct GeodeticPosition pos)
{
  cosLatitude = cos((float)pos.latitude * GPS2RAD);
}

float gpsRawDistance = 0.0;
float gpsBearing = 0;

void computeDistanceAndBearing(struct GeodeticPosition p1, struct GeodeticPosition p2) // A MODIFIER
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
