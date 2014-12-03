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

/****************************************************************************
	Code modifie dans le cadre du developpement du projet epicopter.
*****************************************************************************/

#include "UserConfiguration.h" // Edit this file first before uploading to the AeroQuad

#if defined(UseGPSNMEA) || defined(UseGPSUBLOX) || defined(UseGPSMTK) || defined(UseGPS406)
 #define UseGPS
#endif 

#if defined(UseGPSNavigator) && !defined(AltitudeHoldBaro)
  #error "GpsNavigation NEED AltitudeHoldBaro defined"
#endif

#if defined(AutoLanding) && (!defined(AltitudeHoldBaro) || !defined(AltitudeHoldRangeFinder))
  #error "AutoLanding NEED AltitudeHoldBaro and AltitudeHoldRangeFinder defined"
#endif 

#include <EEPROM.h>
#include <Wire.h> // comunication with I2C devices (library)
#include <GlobalDefined.h> // Libraries/AQ_Defines defines XAXIS YAXIS ZAXIS THROTTLE MODE AUX1 AUX2 AUX3 AUX4 AUX5 ON OFF ALTPANIC
#include "AeroQuad.h"
#include "PID.h"
#include <AQMath.h>
#include <FourtOrderFilter.h>

#ifdef BattMonitor // ACTIF

  #include <BatteryMonitorTypes.h>

#endif

#define LED_Green 13
#define LED_Red 4
#define LED_Yellow 31

#include <Device_I2C.h>
  
#define ITG3200_ADDRESS_ALTERNATE // Gyroscope declaration
#include <Gyroscope_ITG3200_9DOF.h>

// Accelerometer declaration
#include <Accelerometer_ADXL345_9DOF.h>

#define RECEIVER_MEGA // Receiver Declaration
#include <Receiver_MEGA.h>

#define MOTOR_PWM_Timer // Type de moteurs utilises
#include <Motors_PWM_Timer.h>

#ifdef HeadingMagHold // heading mag hold declaration : ACTIF
    
  #include <Compass.h>
  #define SPARKFUN_9DOF_5883L

  #include <HeadingFusionProcessorMARG.h>
  #include <Magnetometer_HMC5883L.h>

#endif

#ifdef AltitudeHoldBaro // Altitude declaration : ACTIF

  #define BMP085
  #include <BarometricSensor_BMP085.h>
  
#endif

/* #ifdef AltitudeHoldRangeFinder // NON ACTIF */
    
/*   #define XLMAXSONAR  */

/* #endif */

#ifdef BattMonitor // Battery Monitor declaration : ACTIF

  #ifdef POWERED_BY_VIN
    #define BattDefaultConfig DEFINE_BATTERY(0, 0, 15.0, 0, BM_NOPIN, 0, 0) // v2 shield powered via VIN (no diode)
  #else // powered by power jack : ACTIF
    #define BattDefaultConfig DEFINE_BATTERY(0, 0, 15.0, 0.82, BM_NOPIN, 0, 0) // v2 shield powered via power jack
  #endif

#else

  #undef BattMonitorAutoDescent
  #undef POWERED_BY_VIN        

#endif
  
#ifndef UseGPS

  #undef UseGPSNavigator

#endif


void initPlatform() // Put AeroQuadMega_v21 specific initialization need here
{
  pinMode(LED_Red, OUTPUT);
  digitalWrite(LED_Red, LOW);
  pinMode(LED_Yellow, OUTPUT);
  digitalWrite(LED_Yellow, LOW);

  // pins set to INPUT for camera stabilization so won't interfere with new camera class

  /* pinMode(33, INPUT); // disable SERVO 1, jumper D12 for roll */
  /* pinMode(34, INPUT); // disable SERVO 2, jumper D11 for pitch */
  /* pinMode(35, INPUT); // disable SERVO 3, jumper D13 for yaw */

  pinMode(43, OUTPUT); // LED 1
  pinMode(44, OUTPUT); // LED 2
  pinMode(45, OUTPUT); // LED 3
  pinMode(46, OUTPUT); // LED 4
  
  digitalWrite(43, HIGH); // LED 1 on
  digitalWrite(44, HIGH); // LED 2 on
  digitalWrite(45, HIGH); // LED 3 on
  digitalWrite(46, HIGH); // LED 4 on
  
  Wire.begin();
  TWBR = 12;
}

void initializePlatformSpecificAccelCalibration() // called when eeprom is initialized
{
  // Kenny default value, a real accel calibration is strongly recommended
  accelScaleFactor[XAXIS] = 0.0365570020;
  accelScaleFactor[YAXIS] = 0.0363000011;
  accelScaleFactor[ZAXIS] = -0.0384629964;

  #ifdef HeadingMagHold

    magBias[XAXIS]  = 1.500000;
    magBias[YAXIS]  = 205.500000;
    magBias[ZAXIS]  = -33.000000;

  #endif
}

void measureCriticalSensors() // Measure critical sensors
{
  measureGyroSum();
  measureAccelSum();
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/



//********* HARDWARE GENERALIZATION SECTION **************

#ifndef ADC_NUMBER_OF_BITS // default to 10bit ADC (AVR)
  #define ADC_NUMBER_OF_BITS 10
#endif

#include "Kinematics.h" //****************** KINEMATICS DECLARATION **************
#include "Kinematics_ARG.h" // Specifique a la carte ARDUINO MEGA 2560

#ifdef BattMonitor //*************** BATTERY MONITOR DECLARATION ************ // NON ACTIF

  #include <BatteryMonitor.h>
  #ifndef BattCustomConfig
    #define BattCustomConfig BattDefaultConfig
  #endif
  struct BatteryData batteryData[] = {BattCustomConfig};

#endif

#if defined(quadPlusConfig) //******** FLIGHT CONFIGURATION DECLARATION ************** // quadPlusConfig DEFINED

  #include "FlightControlQuadPlus.h"

#endif

#if defined(UseGPS)
 
  #if !defined(HeadingMagHold)
    #error We need the magnetometer to use the GPS
  #endif 
  #include <GpsAdapter.h>
  #include "GpsNavigator.h"

#endif

#define SERIAL_PORT Serial // SERIAL_PORT Serial USED

// Include this last as it contains objects from above declarations ==>

#include "AltitudeControlProcessor.h"
#include "FlightControlProcessor.h" // Control de vol
#include "FlightCommandProcessor.h" // Control de commandes
#include "HeadingHoldProcessor.h"
#include "DataStorage.h"

#if defined(UseGPS) || defined(BattMonitor) // ACTIF

  #include "LedStatusProcessor.h"

#endif  

#include "SerialCom.h" // DEFINED

void setup() /* Main setup function, called one time at bootup initialize all system and sub system of the Aeroquad */
{
  SERIAL_BEGIN(BAUD); // DEFINED NOW AT 115200 in AeroQuad.h

  pinMode(LED_Green, OUTPUT);
  digitalWrite(LED_Green, LOW);

  initCommunication(); // Fonction vide
  readEEPROM(); // defined in DataStorage.h // recuperation de la configuration enregistre apres calibrage
  
  boolean firstTimeBoot = false;
  
  if (readFloat(SOFTWARE_VERSION_ADR) != SOFTWARE_VERSION) // If we detect the wrong soft version, we init all parameters
    { 
      initializeEEPROM(); // defined in DataStorage.h
      writeEEPROM();
      firstTimeBoot = true;
    }
  
  initPlatform(); // defined in platform_aeroquad32.h
  
#if defined(quadXConfig) || defined(quadPlusConfig) || defined(quadY4Config) || defined(triConfig) // quadPlusConfig DEFINED
  initializeMotors(FOUR_Motors);
/* #elif defined(hexPlusConfig) || defined(hexXConfig) || defined(hexY6Config) */
/*   initializeMotors(SIX_Motors); */
/* #elif defined(octoX8Config) || defined(octoXConfig) || defined(octoPlusConfig) */
/*   initializeMotors(EIGHT_Motors); */
#endif

  initializeReceiver(LASTCHANNEL); // defined in Receiver_MEGA.h
  initReceiverFromEEPROM();
  
  // Initialize sensors
  // If sensors have a common initialization routine
  // insert it into the gyro class because it executes first
  initializeGyro(); // defined in Gyro.h
  while (!calibrateGyro()); // this make sure the craft is still befor to continue init process
  initializeAccel(); // defined in Accel.h
  if (firstTimeBoot)
    {
      computeAccelBias();
      writeEEPROM();
    }
  setupFourthOrder();
  initSensorsZeroFromEEPROM();
  
  // Integral Limit for attitude mode
  // This overrides default set in readEEPROM()
  // Set for 1/2 max attitude command (+/-0.75 radians)
  // Rate integral not used for now
  PID[ATTITUDE_XAXIS_PID_IDX].windupGuard = 0.375;
  PID[ATTITUDE_YAXIS_PID_IDX].windupGuard = 0.375;
  
  // Flight angle estimation
  initializeKinematics();

#ifdef HeadingMagHold // ACTIF
    vehicleState |= HEADINGHOLD_ENABLED;
    initializeMagnetometer();
    initializeHeadingFusion();
#endif
  
  // Optional Sensors
#ifdef AltitudeHoldBaro // ACTIF
    initializeBaro();
    vehicleState |= ALTITUDEHOLD_ENABLED;
#endif
#ifdef AltitudeHoldRangeFinder // NON ACTIF
    inititalizeRangeFinders();
    vehicleState |= RANGE_ENABLED;
    PID[SONAR_ALTITUDE_HOLD_PID_IDX].P = PID[BARO_ALTITUDE_HOLD_PID_IDX].P*2;
    PID[SONAR_ALTITUDE_HOLD_PID_IDX].I = PID[BARO_ALTITUDE_HOLD_PID_IDX].I;
    PID[SONAR_ALTITUDE_HOLD_PID_IDX].D = PID[BARO_ALTITUDE_HOLD_PID_IDX].D;
    PID[SONAR_ALTITUDE_HOLD_PID_IDX].windupGuard = PID[BARO_ALTITUDE_HOLD_PID_IDX].windupGuard;
#endif
  
#ifdef BattMonitor // ACTIF

    initializeBatteryMonitor(sizeof(batteryData) / sizeof(struct BatteryData), batteryMonitorAlarmVoltage); // batteryMonitorAlarmVoltage defined into DataStorage at value 3.33
    vehicleState |= BATTMONITOR_ENABLED;

#endif

#if defined(BinaryWrite) || defined(BinaryWritePID)
  
  #ifdef OpenlogBinaryWrite
    binaryPort = &Serial1;
    binaryPort->begin(115200);
    delay(1000);
  #else
    binaryPort = &Serial;
  #endif

#endif
  
#if defined(UseGPS) // ACTIF

    initializeGps();

#endif 

  previousTime = micros();
  digitalWrite(LED_Green, HIGH);
  safetyCheck = 0;

  // Fin de phase d'initialisation apres demarage : execution de la fonction loop
}

void process100HzTask() // * 100Hz task
{
  
  G_Dt = (currentTime - hundredHZpreviousTime) / 1000000.0;
  hundredHZpreviousTime = currentTime;
  
  evaluateGyroRate();
  evaluateMetersPerSec();

  for (int axis = XAXIS; axis <= ZAXIS; axis++)
    {
      filteredAccel[axis] = computeFourthOrder(meterPerSecSec[axis], &fourthOrder[axis]);
    }
    
  calculateKinematics(gyroRate[XAXIS], gyroRate[YAXIS], gyroRate[ZAXIS], filteredAccel[XAXIS], filteredAccel[YAXIS], filteredAccel[ZAXIS], G_Dt);
  
  #if defined AltitudeHoldBaro || defined AltitudeHoldRangeFinder

    zVelocity = (filteredAccel[ZAXIS] * (1 - accelOneG * invSqrt(isq(filteredAccel[XAXIS]) + isq(filteredAccel[YAXIS]) + isq(filteredAccel[ZAXIS])))) - runTimeAccelBias[ZAXIS] - runtimeZBias;
    if (!runtimaZBiasInitialized)
      {
	runtimeZBias = (filteredAccel[ZAXIS] * (1 - accelOneG * invSqrt(isq(filteredAccel[XAXIS]) + isq(filteredAccel[YAXIS]) + isq(filteredAccel[ZAXIS])))) - runTimeAccelBias[ZAXIS];
	runtimaZBiasInitialized = true;
      }
    estimatedZVelocity += zVelocity;
    estimatedZVelocity = (velocityCompFilter1 * zVelocity) + (velocityCompFilter2 * estimatedZVelocity);

  #endif    

  #if defined(AltitudeHoldBaro)

    measureBaroSum(); 
    if (frameCounter % THROTTLE_ADJUST_TASK_SPEED == 0)
      {  //  50 Hz tasks
	evaluateBaroAltitude();
      }

  #endif
        
  processFlightControl();
  
  
  #if defined(BinaryWrite)
  
    if (fastTransfer == ON)
      {  // write out fastTelemetry to Configurator or openLog
	fastTelemetry();
      }
  
  #endif      
  
  #if defined(UseGPS) // ACTIF
  
    updateGps();

  #endif
  
}

void process50HzTask() // 50Hz task
{

  G_Dt = (currentTime - fiftyHZpreviousTime) / 1000000.0;
  fiftyHZpreviousTime = currentTime;

  readPilotCommands(); // Reads external pilot commands and performs functions based on stick configuration 
  
  #ifdef AltitudeHoldRangeFinder // NON ACTIF

    updateRangeFinders();

  #endif

  #if defined(UseGPS) // ACTIF

    if (haveAGpsLock() && !isHomeBaseInitialized())
      {
        initHomeBase();
      }

  #endif

}

void process10HzTask1() // 10Hz task
{

#if defined(HeadingMagHold) // ACTIF
  
    G_Dt = (currentTime - tenHZpreviousTime) / 1000000.0;
    tenHZpreviousTime = currentTime;
     
    measureMagnetometer(kinematicsAngle[XAXIS], kinematicsAngle[YAXIS]);
    
    calculateHeading();
    
#endif

}

void process10HzTask2() //  * low priority 10Hz task 2
{

  G_Dt = (currentTime - lowPriorityTenHZpreviousTime) / 1000000.0;
  lowPriorityTenHZpreviousTime = currentTime;
  
  #if defined(BattMonitor) // ACTIF
  
    measureBatteryVoltage(G_Dt*1000.0);

  #endif

  readSerialCommand(); // LECTURE DE COMMANDE SUR LA VOIE SERIE USB
  sendSerialTelemetry();
}

void process10HzTask3() // * low priority 10Hz task 3
{

  G_Dt = (currentTime - lowPriorityTenHZpreviousTime2) / 1000000.0;
  lowPriorityTenHZpreviousTime2 = currentTime;
    
  #if defined(UseGPS) || defined(BattMonitor) // NON ACTIF
  
    processLedStatus();

  #endif
    
}

void process1HzTask() // * 1Hz task
{}

void loop () /* MAIN LOOP FUNCTION */
{
  
  currentTime = micros();
  deltaTime = currentTime - previousTime;

  measureCriticalSensors();
  

  if (deltaTime >= 10000) // 100Hz task loop
    {
    
      frameCounter++;
    
      process100HzTask();

  
      if (frameCounter % TASK_50HZ == 0) // 50Hz task loop
	{
	  process50HzTask();
	}
          
      if (frameCounter % TASK_10HZ == 0) // 10Hz task loop
	{
	  process10HzTask1();
	}
      else if ((currentTime - lowPriorityTenHZpreviousTime) > 100000)
	{
	  process10HzTask2();
	}
      else if ((currentTime - lowPriorityTenHZpreviousTime2) > 100000)
	{
	  process10HzTask3();
	}
      
      if (frameCounter % TASK_1HZ == 0) // 1Hz task loop
	{
	  process1HzTask();
	}
      
      previousTime = currentTime;
    }
  
  if (frameCounter >= 100)
    {
      frameCounter = 0;
    }
}



