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

// FlightCommandProcessor is responsible for decoding transmitter stick combinations
// for setting up AeroQuad modes such as motor arming and disarming

#ifndef _AQ_FLIGHT_COMMAND_READER_
#define _AQ_FLIGHT_COMMAND_READER_




#if defined (AltitudeHoldBaro) || defined (AltitudeHoldRangeFinder)

boolean isPositionHoldEnabledByUser()
{
#if defined (UseGPSNavigator)

  if ((receiverCommand[AUX1] < 1750) || (receiverCommand[AUX2] < 1750))
    {
      return true;
    }
  
  return false;

#else
  if (receiverCommand[AUX1] < 1750)
    {
      return true;
    }

  return false;
#endif

}

#endif


    
#if defined AltitudeHoldBaro || defined AltitudeHoldRangeFinder // OK
    
void	processAltitudeHoldStateFromReceiverCommand()
{
  if (isPositionHoldEnabledByUser()) // WILL DEPREDICATED
    {
      if (altitudeHoldState != ALTPANIC) // check for special condition with manditory override of Altitude hold
	{
	  if (!isAltitudeHoldInitialized)
	    {

#if defined AltitudeHoldBaro // OK

	      baroAltitudeToHoldTarget = getBaroAltitude();
	      PID[BARO_ALTITUDE_HOLD_PID_IDX].integratedError = 0;
	      PID[BARO_ALTITUDE_HOLD_PID_IDX].lastError = baroAltitudeToHoldTarget;

#endif
#if defined AltitudeHoldRangeFinder // OFF NOW

	      sonarAltitudeToHoldTarget = rangeFinderRange[ALTITUDE_RANGE_FINDER_INDEX];
	      PID[SONAR_ALTITUDE_HOLD_PID_IDX].integratedError = 0;
	      PID[SONAR_ALTITUDE_HOLD_PID_IDX].lastError = sonarAltitudeToHoldTarget;

#endif
	      altitudeHoldThrottle = receiverCommand[THROTTLE];
	      isAltitudeHoldInitialized = true;
	    }

	  altitudeHoldState = ON;
	}
    } 
  else
    {
      isAltitudeHoldInitialized = false;
      altitudeHoldState = OFF;
    }
}

#endif


#if defined (AutoLanding)

void	processAutoLandingStateFromReceiverCommand()
{
  if (receiverCommand[AUX3] < 1750)
    {
      if (altitudeHoldState != ALTPANIC) // check for special condition with manditory override of Altitude hold
	{
	  if (isAutoLandingInitialized)
	    {
	      autoLandingState = BARO_AUTO_DESCENT_STATE;

#if defined AltitudeHoldBaro

	      baroAltitudeToHoldTarget = getBaroAltitude();
	      PID[BARO_ALTITUDE_HOLD_PID_IDX].integratedError = 0;
	      PID[BARO_ALTITUDE_HOLD_PID_IDX].lastError = baroAltitudeToHoldTarget;

#endif
#if defined AltitudeHoldRangeFinder

	      sonarAltitudeToHoldTarget = rangeFinderRange[ALTITUDE_RANGE_FINDER_INDEX];
	      PID[SONAR_ALTITUDE_HOLD_PID_IDX].integratedError = 0;
	      PID[SONAR_ALTITUDE_HOLD_PID_IDX].lastError = sonarAltitudeToHoldTarget;

#endif

	      altitudeHoldThrottle = receiverCommand[THROTTLE];
	      isAutoLandingInitialized = true;
	    }
	  altitudeHoldState = ON;
	}
    }
  else
    {
      autoLandingState = OFF;
      autoLandingThrottleCorrection = 0;
      isAutoLandingInitialized = false;

#if defined (UseGPSNavigator)

      if ((receiverCommand[AUX1] > 1750) && (receiverCommand[AUX2] > 1750))
	{
	  altitudeHoldState = OFF;
	  isAltitudeHoldInitialized = false;
	}

#else

      if (receiverCommand[AUX1] > 1750)
	{
	  altitudeHoldState = OFF;
          isAltitudeHoldInitialized = false;
        }

#endif
    }
}
#endif



#if defined (UseGPSNavigator)

void	processGpsNavigationStateFromReceiverCommand() // COMMANDES D'EXECUTION DE NAVIGATION AUTOMATIQUE ET MAINTIENT D'UNE POSITION
{
  // COMMANDE D'INNITIALISATION DE LA BASE D'OPERATION : A MODIFIER
  
  if (motorArmed == OFF && receiverCommand[THROTTLE] < MINCHECK && receiverCommand[ZAXIS] < MINCHECK && receiverCommand[YAXIS] > MAXCHECK && receiverCommand[XAXIS] > MAXCHECK && haveAGpsLock())
    {
      homePosition.latitude = currentPosition.latitude;
      homePosition.longitude = currentPosition.longitude;
      homePosition.altitude = DEFAULT_HOME_ALTITUDE;
    }


  if (receiverCommand[AUX2] < 1750) // Enter in execute mission state, if none, go back home, override the position hold // COMMANDE D'EXECUTION DE LA NAVIGATION AUTOMATIQUE 
    {  
      if (!isGpsNavigationInitialized)
	{
	  gpsRollAxisCorrection = 0;
	  gpsPitchAxisCorrection = 0;
	  gpsYawAxisCorrection = 0;
	  isGpsNavigationInitialized = true;
	}
  
      positionHoldState = OFF;         // disable the position hold while navigating
      isPositionHoldInitialized = false;
  
      navigationState = ON; // NAVIGATION AUTOMATIQUE ACTIVEE
    }
  else if (receiverCommand[AUX1] < 1250) // COMMANDE DE MAINTIENT DE LA POSITION ACTUELLE (A MODIFIER ET UTILISER POUR LA MOBILISATION SUR UN OBJECTIF DU PARCOURT)
    {
      if (!isPositionHoldInitialized)
	{
	  gpsRollAxisCorrection = 0;
	  gpsPitchAxisCorrection = 0;
	  gpsYawAxisCorrection = 0;
  
	  positionHoldPointToReach.latitude = currentPosition.latitude;
	  positionHoldPointToReach.longitude = currentPosition.longitude;
	  positionHoldPointToReach.altitude = getBaroAltitude();
	  isPositionHoldInitialized = true;
	}
  
      isGpsNavigationInitialized = false;  // disable navigation
      navigationState = OFF;
  
      positionHoldState = ON;
    }
  else // Navigation and position hold are disabled
    {
      positionHoldState = OFF;
      isPositionHoldInitialized = false;
  
      navigationState = OFF;
      isGpsNavigationInitialized = false;
      
      gpsRollAxisCorrection = 0;
      gpsPitchAxisCorrection = 0;
      gpsYawAxisCorrection = 0;
    }
}
#endif




void	processZeroThrottleFunctionFromReceiverCommand() // ARMEMENT / DESARMEMENT MOTEUR
{
  
  if (receiverCommand[ZAXIS] < MINCHECK && motorArmed == ON) // DESARMEMENT DES MOTEURS
    {
      commandAllMotors(MINCOMMAND);
      motorArmed = OFF;
      inFlight = false;

#if defined BattMonitorAutoDescent

      batteryMonitorAlarmCounter = 0;
      batteryMonitorStartThrottle = 0;
      batteyMonitorThrottleCorrection = 0.0;

#endif
    }    

  
  if ((receiverCommand[ZAXIS] < MINCHECK) && (receiverCommand[XAXIS] > MAXCHECK) && (receiverCommand[YAXIS] < MINCHECK)) // Zero Gyro and Accel sensors (left stick lower left, right stick lower right corner)
    {
      calibrateGyro();
      computeAccelBias();
      storeSensorsZeroToEEPROM();
      calibrateKinematics();
      zeroIntegralError();
      pulseMotors(3);
    }   

  if (receiverCommand[ZAXIS] > MAXCHECK && motorArmed == OFF && safetyCheck == ON) // ARMEMENT DES MOTEURS (left stick lower right corner)
    {
      for (byte motor = 0; motor < LASTMOTOR; motor++) // ALLUMAGE DES MOTEURS
	{
	  motorCommand[motor] = MINTHROTTLE;
	}

      motorArmed = ON; // MOTEURS ARMES

      zeroIntegralError();
  }
  
  if (receiverCommand[ZAXIS] > MINCHECK) // Prevents accidental arming of motor output if no transmitter command received
    {
      safetyCheck = ON; 
    }
}




/**
 * readPilotCommands
 * 
 * This function is responsible to read receiver
 * and process command from the users
 */
void readPilotCommands()
{

  readReceiver(); // recuperation des commandes du pilote 

  // CODE DEVELOPPEMENT (croux_g)

  // DEBUT D'AFFICHAGE

  SERIAL_PRINT("ReceiverCommand[XAXIS] : ");
  SERIAL_PRINT(receiverCommand[XAXIS]);
  SERIAL_PRINT(" [YAXIS] : ");
  SERIAL_PRINT(receiverCommand[YAXIS]);
  SERIAL_PRINT(" [ZAXIS] : ");
  SERIAL_PRINT(receiverCommand[ZAXIS]);

  SERIAL_PRINT(" [THROTTLE] : ");
  SERIAL_PRINT(receiverCommand[THROTTLE]);
  SERIAL_PRINT(" [MODE] : ");
  SERIAL_PRINT(receiverCommand[MODE]);
  SERIAL_PRINT(" [AUX1] : ");
  SERIAL_PRINT(receiverCommand[AUX1]);
  SERIAL_PRINT(" [AUX2] : ");
  SERIAL_PRINT(receiverCommand[AUX2]);
  SERIAL_PRINT(" [AUX3] : ");
  SERIAL_PRINT(receiverCommand[AUX3]);
  SERIAL_PRINT(" [AUX4] : ");
  SERIAL_PRINT(receiverCommand[AUX4]);
  SERIAL_PRINT(" [AUX5] : ");
  SERIAL_PRINTLN(receiverCommand[AUX5]);

  // FIN D'AFFICHAGE

  // FIN CODE DEVELOPPEMENT
  
  if (receiverCommand[THROTTLE] < MINCHECK) // MINCHECK 1100 // SI LE JOYSTICK DE GAUCHE EST EN BAS
    {
      processZeroThrottleFunctionFromReceiverCommand(); // ARMEMENT / DESARMENT DES MOTEURS
    
      // COMMENT : apres armement ( -> motorArmed = ON, BOUCLE x4 / -> motorCommand[motor] = MINTHROTTLE;)
    }

  if (!inFlight && motorArmed == ON && receiverCommand[THROTTLE] > minArmedThrottle) // minArmedThrottle = 1150 // SI LE JOYSTICK DE GAUCHE EST UN PETIT PEU AU DESSUS DE LA POSITION BASSE
    {
      inFlight = true; // COMMENT : En phase de vol
    }

  flightMode = ATTITUDE_FLIGHT_MODE; // TOUJOURS DANS CE MODE
  

  // !!! NOUVEAU CODE !!! //

  // DEVELOPPEMENT : EXECUTION FROM RADIO CONTROL

  // receiverCommand[AUX2] < 1750 // ACTIVATION DE LA NAVIGATION AUTOMATIQUE
  
  // receiverCommand[AUX1] < 1250 // ACTIVATION MAINTIENT DE POSITION

#if defined AltitudeHoldBaro || defined AltitudeHoldRangeFinder // OK

  /* processAltitudeHoldStateFromReceiverCommand(); */

#endif
  
#if defined (AutoLanding) // OFF

  /* processAutoLandingStateFromReceiverCommand(); */

#endif

#if defined (UseGPSNavigator) // OK

  processGpsNavigationStateFromReceiverCommand(); // COMMANDES D'EXECUTION DE NAVIGATION AUTOMATIQUE ET MAINTIENT D'UNE POSITION (A UTILISER / MODIFIER)

#endif
}

#endif // _AQ_FLIGHT_COMMAND_READER_

