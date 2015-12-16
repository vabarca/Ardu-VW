
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>

#include "I2Cdev.h"
#include "MPU60X0.h"

#include "ButtonHandler.h"
#include "EEPROMAnything.h"
#include "data.h"
#include "kalman.h"
#include "SSD1306.h"
  
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define RESTRICT_PITCH            // Comment out to restrict roll to 
                                  //±90deg instead - please 
                                  //read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf

#define BUTTON_PIN                8  // Button

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

const uint8_t EEPROM_CAL_PITCH    = 0; 
const uint8_t EEPROM_CAL_ROLL     = sizeof(double); 

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

CData oG;
CData oGDif;
CData oGCal;

Kalman oPitch;
Kalman oRoll;

SSD1306 oSSD1306;

int state = 0;

CButtonHandler oButton(BUTTON_PIN, DEFAULT_LONGPRESS_LEN);
MPU60X0 accelgyro(false,0x68);

uint32_t      timer;
double        dt;
double        gyroXrate, gyroYrate;
int16_t       ax, ay, az, gx, gy, gz;
float         temp;
const float   fM = 0.98;

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

void saveCalib(const CData& data)
{
  EEPROM_writeAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_writeAnything(EEPROM_CAL_ROLL,data.roll);
}

///////////////////////////
///////////////////////////

void loadCalib(CData& data)
{
  EEPROM_readAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_readAnything(EEPROM_CAL_ROLL,data.roll);
}

///////////////////////////
///////////////////////////

double getRoll()
{
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  return atan2((double)ay, (double)az) * RAD_TO_DEG;
#else // Eq. 28 and 29
  return atan(day / sqrt((double)ax * (double)ax + (double)az * (double)az)) * RAD_TO_DEG;
#endif 
}

///////////////////////////
///////////////////////////

double getPitch()
{
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  return atan(-(double)ax / sqrt((double)ay * (double)ay + (double)az * (double)az)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  return atan2(-(double)ax, (double)az) * RAD_TO_DEG;
#endif 
}

///////////////////////////
///////////////////////////

void buttonLongPress()
{
  oSSD1306.zoomOn();
  
  saveCalib(oG);
  oGCal = oG;
  
  oSSD1306.clearVideoBuffer();
  oSSD1306.send_string("System calibrated!!!",12,14);
  oSSD1306.displayVideoBuffer();
  delay(1500);
}

///////////////////////////
///////////////////////////

void buttonShortPress()
{
  //Scroll machine state
  state++;
  state&=0x01;

  switch(state)
  {
    case 0:  
      oSSD1306.zoomOff();   
      break;
    case 1:  
      oSSD1306.zoomOn(); 
      break;
  }
}

///////////////////////////
///////////////////////////

void measureProcess()
{
  // Balance calculus
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  gyroXrate = (double)gx / 131.0; // Convert to deg/s
  gyroYrate = (double)gy / 131.0; // Convert to deg/s

#ifdef RESTRICT_PITCH
  oG.roll = oRoll.getAngle(getRoll(), gyroXrate, dt); // Calculate the angle using a Kalman filter
  oG.pitch = oPitch.getAngle(getPitch(), gyroYrate, dt);
#else
  oG.pitch = oPitch.getAngle(getPitch(), gyroYrate, dt); // Calculate the angle using a Kalman filter
  oG.roll = oRoll.getAngle(getRoll(), gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif

  oGDif.roll   = oG.roll - oGCal.roll;
  oGDif.pitch  = oG.pitch - oGCal.pitch;
}

///////////////////////////
///////////////////////////

void tempProcess()
{
  temp = fM * temp + (1.0-fM)*(((float)accelgyro.getTemperature()/340.00f)+36.53f);
}

///////////////////////////
///////////////////////////

void showTemp()
{
  int offset = 41;
  
  oSSD1306.zoomOn();
  
  oSSD1306.send_string("T: ",12,offset);
  offset+=15;
  oSSD1306.send_float(temp,12,offset,3);
  offset+=20;
  oSSD1306.send_string(" C",12,offset);
}

///////////////////////////
///////////////////////////

void showMeasurement()
{
  oSSD1306.zoomOff();
    
  oSSD1306.send_float((float)oGDif.roll,2,1);
  oSSD1306.send_float((float)oGDif.pitch,10,1);

  for(uint8_t i = 0; i < 3 ; i++)
  {
    oSSD1306.drawVLine(0,(SSD1306_LCDWIDTH / 2)+i,SSD1306_LCDHEIGHT);
    oSSD1306.drawHLine((SSD1306_LCDHEIGHT / 2)+i,0,SSD1306_LCDWIDTH);
  }

  int y = (int)oGDif.roll;
  int x = -(int)oGDif.pitch;

  y+=(SSD1306_LCDWIDTH / 2)-1;
  x+=(SSD1306_LCDHEIGHT / 2)-1;

  int squareSize = 7;
  
  oSSD1306.drawFillSquare(x-squareSize-1,y-squareSize-1,squareSize);
  oSSD1306.drawFillSquare(x+squareSize-2,y-squareSize-1,squareSize);
  oSSD1306.drawFillSquare(x-squareSize-1,y+squareSize-2,squareSize);
  oSSD1306.drawFillSquare(x+squareSize-2,y+squareSize-2,squareSize);
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

void setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  //Initialize Display
  oSSD1306.init(true);
  oSSD1306.brightness(255);
  oSSD1306.clearDisplay();
  oSSD1306.zoomOn();  
  delay(1000);

  //Initialize button
  oButton.init();
  delay(200);

  // initialize device
  accelgyro.initialize();
  delay(200);

  // verify connection
  if(!accelgyro.testConnection())
  {
    oSSD1306.clearVideoBuffer();
    oSSD1306.send_string("MPU6050 failed!!",12,24);
    oSSD1306.displayVideoBuffer();
    while(1);
  }
  
  //Load calibration
  loadCalib(oGCal);

  //Set kalman staring point
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  oRoll.setAngle(getRoll());
  oPitch.setAngle(getPitch());

  //Get Temp
  temp = ((float)accelgyro.getTemperature()/340.00f)+36.53f;

  //Wellcome message
  oSSD1306.clearVideoBuffer();
  oSSD1306.send_string("SYSTEM READY!!",12,29);
  oSSD1306.displayVideoBuffer();
  delay(2000); 
}

///////////////////////////
///////////////////////////

void loop()
{
  //Clear display buffer
  oSSD1306.clearVideoBuffer();
  
  //---------------------

  measureProcess();
  tempProcess();

  //---------------------

  switch(state)
  {
    case 0:  showMeasurement();   break;
    case 1:  showTemp();          break;
  }
  
  //---------------------

  switch(oButton.handle())
  {
    case EV_SHORTPRESS: buttonShortPress(); break;
    case EV_LONGPRESS:  buttonLongPress();  break;
  }

  //---------------------
  
  //update display
  oSSD1306.displayVideoBuffer();
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/*

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 

#include <Wire.h>
#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf

Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;

// IMU Data 
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
int16_t tempRaw;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only
double compAngleX, compAngleY; // Calculated angle using a complementary filter
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

// TODO: Make calibration routine

void setup() {
  Serial.begin(115200);
  Wire.begin();
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz

  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode

  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    Serial.print(F("Error reading sensor"));
    while (1);
  }

  delay(100); // Wait for sensor to stabilize

  // Set kalman and gyro starting angle 
  while (i2cRead(0x3B, i2cData, 6));
  accX = (i2cData[0] << 8) | i2cData[1];
  accY = (i2cData[2] << 8) | i2cData[3];
  accZ = (i2cData[4] << 8) | i2cData[5];

  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = roll;
  compAngleY = pitch;

  timer = micros();
}

void loop() {
  // Update all the values 
  while (i2cRead(0x3B, i2cData, 14));
  accX = ((i2cData[0] << 8) | i2cData[1]);
  accY = ((i2cData[2] << 8) | i2cData[3]);
  accZ = ((i2cData[4] << 8) | i2cData[5]);
  tempRaw = (i2cData[6] << 8) | i2cData[7];
  gyroX = (i2cData[8] << 8) | i2cData[9];
  gyroY = (i2cData[10] << 8) | i2cData[11];
  gyroZ = (i2cData[12] << 8) | i2cData[13];

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  double gyroXrate = gyroX / 131.0; // Convert to deg/s
  double gyroYrate = gyroY / 131.0; // Convert to deg/s

#ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    compAngleX = roll;
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleX) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    compAngleY = pitch;
    kalAngleY = pitch;
    gyroYangle = pitch;
  } else
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleY) > 90)
    gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif

  gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  gyroYangle += gyroYrate * dt;
  //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate() * dt;

  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;

  // Reset the gyro angle when it has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;

  // Print Data 
#if 0 // Set to 1 to activate
  Serial.print(accX); Serial.print("\t");
  Serial.print(accY); Serial.print("\t");
  Serial.print(accZ); Serial.print("\t");
  Serial.print(gyroX); Serial.print("\t");
  Serial.print(gyroY); Serial.print("\t");
  Serial.print(gyroZ); Serial.print("\t");
  Serial.print("\t");
#endif

  Serial.print(roll); Serial.print("\t");
  Serial.print(gyroXangle); Serial.print("\t");
  Serial.print(compAngleX); Serial.print("\t");
  Serial.print(kalAngleX); Serial.print("\t");

  Serial.print("\t");

  Serial.print(pitch); Serial.print("\t");
  Serial.print(gyroYangle); Serial.print("\t");
  Serial.print(compAngleY); Serial.print("\t");
  Serial.print(kalAngleY); Serial.print("\t");

#if 0 // Set to 1 to print the temperature
  Serial.print("\t");
  double temperature = (double)tempRaw / 340.0 + 36.53;
  Serial.print(temperature); Serial.print("\t");
#endif

  Serial.print("\r\n");
  delay(2);
}
 
 */
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

/*
 * 
 * #include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az, gx, gy, gz;
double timeStep, time, timePrev;
double arx, ary, arz, grx, gry, grz, gsx, gsy, gsz, rx, ry, rz;

int i;
double gyroScale = 131;

void setup() {

  Wire.begin();
  Serial.begin(9600);
  accelgyro.initialize();

  time = millis();

  i = 1;

}

void loop() {

  // set up time for integration
  timePrev = time;
  time = millis();
  timeStep = (time - timePrev) / 1000; // time-step in s

  // collect readings
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // apply gyro scale from datasheet
  gsx = gx/gyroScale;   gsy = gy/gyroScale;   gsz = gz/gyroScale;

  // calculate accelerometer angles
  arx = (180/3.141592) * atan(ax / sqrt(square(ay, 2) + square(az, 2))); 
  ary = (180/3.141592) * atan(ay / sqrt(square(ax, 2) + square(az, 2)));
  arz = (180/3.141592) * atan(sqrt(square(ay) + square(ax)) / az);


  // set initial values equal to accel values
  if (i == 1) {
    grx = arx;
    gry = ary;
    grz = arz;
  }
  // integrate to find the gyro angle
  else{
    grx = grx + (timeStep * gsx);
    gry = gry + (timeStep * gsy);
    grz = grz + (timeStep * gsz);
  }  

  // apply filter
  rx = (0.96 * arx) + (0.04 * grx);
  ry = (0.96 * ary) + (0.04 * gry);
  rz = (0.96 * arz) + (0.04 * grz);

  // print result
  Serial.print(i);   Serial.print("\t");
  Serial.print(timePrev);   Serial.print("\t");
  Serial.print(time);   Serial.print("\t");
  Serial.print(timeStep, 5);   Serial.print("\t\t");
  Serial.print(ax);   Serial.print("\t");
  Serial.print(ay);   Serial.print("\t");
  Serial.print(az);   Serial.print("\t\t");
  Serial.print(gx);   Serial.print("\t");
  Serial.print(gy);   Serial.print("\t");
  Serial.print(gz);   Serial.print("\t\t");
  Serial.print(arx);   Serial.print("\t");
  Serial.print(ary);   Serial.print("\t");
  Serial.print(arz);   Serial.print("\t\t");
  Serial.print(grx);   Serial.print("\t");
  Serial.print(gry);   Serial.print("\t");
  Serial.print(grz);   Serial.print("\t\t");
  Serial.print(rx);   Serial.print("\t");
  Serial.print(ry);   Serial.print("\t");
  Serial.println(rz);

  i = i + 1;
  delay(50);

}

*/

