/*
  AeroQuad v3.0.1 - February 2012
  www.AeroQuad.com
  Copyright (c) 2012 Ted Carancho.  All rights reserved.
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

// FlightControl.pde is responsible for combining sensor measurements and
// transmitter commands into motor commands for the defined flight configuration (X, +, etc.)
//////////////////////////////////////////////////////////////////////////////
/////////////////////////// calculateFlightError /////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef _AQ_ALTITUDE_CONTROL_PROCESSOR_H_
#define _AQ_ALTITUDE_CONTROL_PROCESSOR_H_


#if defined AltitudeHoldBaro || defined AltitudeHoldRangeFinder // OK

#define INVALID_THROTTLE_CORRECTION -1000
#define ALTITUDE_BUMP_SPEED 0.01



/**
 * processAltitudeHold
 * 
 * This function is responsible to process the throttle correction 
 * to keep the current altitude if selected by the user 
 */
void	processAltitudeHold() // DEFINITION DE LA VARIABLE Throttle AVEC CORRECTION ASSISTEE
{
  if (altitudeHoldState == ON) // FlightCommandProcessor.h // MAINTIENT D'ALTITUDE
    {
      int altitudeHoldThrottleCorrection = INVALID_THROTTLE_CORRECTION;


#if defined AltitudeHoldRangeFinder // UserConfiguration.h // STABILISATION PAR TELEMETRE LASER // NOW OFF // A IMPLEMETER PLUS TARD
 
      /* if (isOnRangerRange(rangeFinderRange[ALTITUDE_RANGE_FINDER_INDEX])) // AQ_RangerFinder/RangeFinder.h // fonction qui retourne 1 si au dessus du plancher et en dessou du plafond */
      /* 	{ */
      /* 	  if (sonarAltitudeToHoldTarget == INVALID_RANGE) // AeroQuad.h (defined) // Si l'objectif d'altitude est invalide on reinitialise l'objectif */
      /* 	    { */
      /* 	      sonarAltitudeToHoldTarget = rangeFinderRange[ALTITUDE_RANGE_FINDER_INDEX]; */
      /* 	    } */

      /* 	  altitudeHoldThrottleCorrection = updatePID(sonarAltitudeToHoldTarget, rangeFinderRange[ALTITUDE_RANGE_FINDER_INDEX], &PID[SONAR_ALTITUDE_HOLD_PID_IDX]); // PID.h // function(target, position actuelle, struct) */
      /* 	  altitudeHoldThrottleCorrection = constrain(altitudeHoldThrottleCorrection, minThrottleAdjust, maxThrottleAdjust); // fonction system arduino */
      /* 	} */

#endif


#if defined AltitudeHoldBaro // OK // UserConfiguration.h // STABILISATION PAR BAROMETRE

      if (altitudeHoldThrottleCorrection == INVALID_THROTTLE_CORRECTION) // Si la correction automatique de l'altitude n'est pas activee ou altitude hors plancher/plafond 
	{
	  altitudeHoldThrottleCorrection = updatePID(baroAltitudeToHoldTarget, getBaroAltitude(), &PID[BARO_ALTITUDE_HOLD_PID_IDX]); // target definie par baroAltitudeToHoldTarget
	  altitudeHoldThrottleCorrection = constrain(altitudeHoldThrottleCorrection, minThrottleAdjust, maxThrottleAdjust);
	}

#endif        


      if (altitudeHoldThrottleCorrection == INVALID_THROTTLE_CORRECTION) // SI PAS D'INSTRUMENTS PAS DE CORRECTION // WILL DEPRECIATE
	{
	  throttle = receiverCommand[THROTTLE];
	  return;
	}
      

      
#if defined AltitudeHoldBaro || defined AltitudeHoldRangeFinder // OK

      float zDampeningThrottleCorrection = -updatePID(0.0, estimatedZVelocity, &PID[ZDAMPENING_PID_IDX]); // estimatedZVelocity defined in AeroQuad.h // valeur 0.0 ... 

      zDampeningThrottleCorrection = constrain(zDampeningThrottleCorrection, minThrottleAdjust, maxThrottleAdjust); // ???

#endif
      
    
      /* if (abs(altitudeHoldThrottle - receiverCommand[THROTTLE]) > altitudeHoldPanicStickMovement) // WILL DEPRECIATE */
      /* 	{ */
      /* 	  altitudeHoldState = ALTPANIC; // too rapid of stick movement so PANIC out of ALTHOLD */
      /* 	}  */
      /* else // APRES MODIFICATION ON ENTRE TOUJOURS DANS CETTE CONDITION */
      /* 	{ */
	  


	 /*  if (receiverCommand[THROTTLE] > (altitudeHoldThrottle + altitudeHoldBump)) // AKA changed to use holdThrottle + ALTBUMP - (was MAXCHECK) above 1900 */
/* 	    { */
/* #if defined AltitudeHoldBaro */

/* 	      baroAltitudeToHoldTarget += ALTITUDE_BUMP_SPEED; */

/* #endif */
/* #if defined AltitudeHoldRangeFinder */

/* 	      float newalt = sonarAltitudeToHoldTarget + ALTITUDE_BUMP_SPEED; */

/* 	      if (isOnRangerRange(newalt)) */
/* 		{ */
/* 		  sonarAltitudeToHoldTarget = newalt; */
/* 		} */

/* #endif */
/* 	    } */
	  
/* 	  if (receiverCommand[THROTTLE] < (altitudeHoldThrottle - altitudeHoldBump)) // AKA change to use holdThorrle - ALTBUMP - (was MINCHECK) below 1100 */
/* 	    { */
/* #if defined AltitudeHoldBaro */

/* 	      baroAltitudeToHoldTarget -= ALTITUDE_BUMP_SPEED; */

/* #endif */
/* #if defined AltitudeHoldRangeFinder */

/* 	      float newalt = sonarAltitudeToHoldTarget - ALTITUDE_BUMP_SPEED; */

/* 	      if (isOnRangerRange(newalt)) */
/* 		{ */
/* 		  sonarAltitudeToHoldTarget = newalt; */
/* 		} */

/* #endif */
/* 	    } */


	/* } */

      throttle = altitudeHoldThrottle + altitudeHoldThrottleCorrection + zDampeningThrottleCorrection; // MAIN CODE
    }
  else
    {
      /* throttle = receiverCommand[THROTTLE]; */
    }
}

#endif

#endif // _AQ_ALTITUDE_CONTROL_PROCESSOR_H_
