//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  vw.ino
 *  @date  November, 2015
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//---[ Global variables: ]-----------------------------------------------------

CData goG;
CData goGDif;
CData goGCal;

Kalman goPitch;
Kalman goRoll;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_FAST);

eStateMachine         geState(ESM_WELCOME);

#ifdef ULTIMATE_DEBOUNCER
  CTheUltimateDebouncer goButton0(BUTTON_PIN0);
  CTheUltimateDebouncer goButton1(BUTTON_PIN1);
#else
  CButtonHandler        goButton0(BUTTON_PIN0, DEFAULT_LONGPRESS_LEN);
  CButtonHandler        goButton1(BUTTON_PIN1, DEFAULT_LONGPRESS_LEN);
#endif

float                 gfTemperature(0.0f);
float                 gfAltitude(0.0f),gfAltitudeCalib(0.0f);
float                 gfPress(0.0f);
float                 gfHeading(0.0f);
float                 gfaMovavg_buff[MOVAVG_SIZE];
int16_t               ax(0), ay(0), az(0), gx(0), gy(0), gz(0);

MPU60X0               goAccelgyro(false,0x68);
MS561101BA            goBaro;
HMC58X3               goCompass;

//-----------------------------------------------------------------------------
//---[ Private Methods: ]------------------------------------------------------

void _saveAltitudeCalib(const float& data)
{
  EEPROM_writeAnything(EEPROM_CAL_ALTITUDE,data);
}

//-----------------------------------------------------------------------------

void _saveCalib(const CData& data)
{
  EEPROM_writeAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_writeAnything(EEPROM_CAL_ROLL,data.roll);
}

//-----------------------------------------------------------------------------

void _loadAltitudeCalib(float& data)
{
  EEPROM_readAnything(EEPROM_CAL_ALTITUDE,data);
}

//-----------------------------------------------------------------------------

void _loadCalib(CData& data)
{
  EEPROM_readAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_readAnything(EEPROM_CAL_ROLL,data.roll);
}

//-----------------------------------------------------------------------------

float _getRoll()
{
#ifdef RESTRICT_PITCH
  return atan2((float)ay, (float)az) * RAD_2_DEG;
#else
  return atan(day / sqrt((float)ax * (float)ax + (float)az * (float)az)) * RAD_2_DEG;
#endif 
}

//-----------------------------------------------------------------------------

float _getPitch()
{
#ifdef RESTRICT_PITCH
  return atan(-(float)ax / sqrt((float)ay * (float)ay + (float)az * (float)az)) * RAD_2_DEG;
#else
  return atan2(-(float)ax, (float)az) * RAD_2_DEG;
#endif 
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _buttonLongPress()
{
  switch(geState)
  {
  case ESM_ATTITUDE:
    _saveCalib(goG);
    goGCal = goG;
    geState = ESM_CALIB;
    break;
  case ESM_HEADING:
  case ESM_TEMP:
  case ESM_ALTITUDE:
    _saveAltitudeCalib(gfAltitude);
    gfAltitudeCalib = gfAltitude;
    geState = ESM_CALIB_ALTITUDE;
    break;
  case ESM_CALIB:
  case ESM_CALIB_ALTITUDE:
  case ESM_WELCOME:
  default:
    break;
  }
}

//-----------------------------------------------------------------------------

void _buttonShortPress()
{
  switch(geState)
  {
  case ESM_ATTITUDE: geState = ESM_TEMP;      break;
  case ESM_TEMP:     geState = ESM_ALTITUDE;  break;
  case ESM_ALTITUDE: geState = ESM_HEADING;   break;
  case ESM_HEADING:  geState = ESM_ATTITUDE;  break;
  case ESM_WELCOME:  geState = ESM_ATTITUDE;  break;
  case ESM_CALIB:
  case ESM_CALIB_ALTITUDE:
  default:                                    break;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _pushAvg(float val)
{
  static int movavg_i(0);
  gfaMovavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}

//-----------------------------------------------------------------------------

float _getAvg(float * buff, int size)
{
  float sum = 0.0;
  for(int i=0; i<size; i++)
    sum += buff[i];

  return sum / size;
}

//-----------------------------------------------------------------------------

void _attitudeTask()
{
  static uint32_t timerCnt(0);
  static float   dt(0.0f), gyroXrate(0.0f), gyroYrate(0.0f);

  // Balance calculus
  goAccelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  dt = (float)(micros() - timerCnt) / 1000000; // Calculate delta time
  timerCnt = micros();

  gyroXrate = gx / 131.0; // Convert to deg/s
  gyroYrate = gy / 131.0; // Convert to deg/s

  goG.roll = goRoll.getAngle(_getRoll(), gyroXrate, dt); // Calculate the angle using a Kalman filter
  goG.pitch = goPitch.getAngle(_getPitch(), gyroYrate, dt); // Calculate the angle using a Kalman filter

  goGDif.roll   = goG.roll - goGCal.roll;
  goGDif.pitch  = goG.pitch - goGCal.pitch;

  SERIAL_PRINT("data:\t");
  SERIAL_PRINT(gyroXrate); SERIAL_PRINT("\t");
  SERIAL_PRINT(gyroYrate); SERIAL_PRINT("\t");
  SERIAL_PRINT(_getRoll()); SERIAL_PRINT("\t");
  SERIAL_PRINT(_getPitch()); SERIAL_PRINT("\t");
  SERIAL_PRINT(goG.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(goG.pitch); SERIAL_PRINT("\t");
  SERIAL_PRINT(goGCal.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(goGCal.pitch); SERIAL_PRINT("\t");
  SERIAL_PRINT(goGDif.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(goGDif.pitch); SERIAL_PRINTLN("\t **");
}

//-----------------------------------------------------------------------------

void _pressTask()
{
  _pushAvg(goBaro.getPressure(MS561101BA_OSR_4096));
  gfPress = _getAvg(gfaMovavg_buff, MOVAVG_SIZE);
}

//-----------------------------------------------------------------------------

void _tempTask()
{
  gfTemperature = goBaro.getTemperature(MS561101BA_OSR_4096);
}

//-----------------------------------------------------------------------------

void _altitudeTask()
{
  //return (1.0f - pow(press/101325.0f, 0.190295f)) * 4433000.0f;
  gfAltitude = ((pow((SEA_LEVEL_PRESSURE / gfPress),
      1.0f/5.257f) - 1.0f) * (gfTemperature + 273.15f)) / 0.0065f;
}

//-----------------------------------------------------------------------------

void _headingTask()
{
  float fx,fy,fz;
  goCompass.getValues(&fx,&fy,&fz);
  gfHeading = atan2(fy, fx);
  if(gfHeading < 0)
    gfHeading += M_PI_D;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _showAltitude()
{
  u8g.setPrintPos(20,40);
  u8g.print(gfAltitude - gfAltitudeCalib);
  u8g.setPrintPos(100,40);
  u8g.print("m");
  
  SERIAL_PRINT("Pres: ");
  SERIAL_PRINT(gfPress);
  SERIAL_PRINT(" mbar altitude: ");
  SERIAL_PRINT(gfAltitude);
  SERIAL_PRINTLN(" m");
}

//-----------------------------------------------------------------------------

void _showTemp()
{
  u8g.setPrintPos(20,40);
  u8g.print(gfTemperature);
  u8g.setPrintPos(100,40);
  u8g.print("C");
  
  SERIAL_PRINT("Temp: ");
  SERIAL_PRINT(gfTemperature);
  SERIAL_PRINTLN(" degC");
}

//-----------------------------------------------------------------------------

void _showHeading()
{
  u8g.drawCircle(64, 32, 24);

  uint8_t xN((uint8_t)(24*sin(M_PI_D - gfHeading)));
  uint8_t yN((uint8_t)(24*cos(M_PI_D - gfHeading)));
  u8g.setFontPosCenter();
  u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"N");
  u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"S");
  u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"E");
  u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"O");
  u8g.setFontPosBaseline();

  //u8g.setPrintPos(0,10);
  //u8g.print(gfHeading);

  SERIAL_PRINT("Orientation: ");
  SERIAL_PRINT(gfHeading * RAD_2_DEG);
  SERIAL_PRINTLN(" deg");
}

//-----------------------------------------------------------------------------

void _showAttitude()
{
  static int y(SSD1306_LCDHEIGHT_MED);
  static int x(SSD1306_LCDWIDTH_MED);
  static const int SQUARE_SIZE(8);
  static const int SQUARE_SIZE_MED(SQUARE_SIZE/2);

  //u8g.setPrintPos(0,11);
  //u8g.print(goGDif.roll);
  //u8g.setPrintPos(0,22);
  //u8g.print(goGDif.pitch);

  u8g.drawBox(0,SSD1306_LCDHEIGHT_MED-2,SSD1306_LCDWIDTH,SQUARE_SIZE_MED);
  u8g.drawBox(SSD1306_LCDWIDTH_MED-2,0,SQUARE_SIZE_MED,SSD1306_LCDHEIGHT);

  y=(int)goGDif.roll + (SSD1306_LCDHEIGHT_MED)-SQUARE_SIZE_MED;
  x=-(int)goGDif.pitch + (SSD1306_LCDWIDTH_MED)-SQUARE_SIZE_MED;

  u8g.drawBox(x-SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  u8g.drawBox(x+SQUARE_SIZE,y-SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  u8g.drawBox(x-SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
  u8g.drawBox(x+SQUARE_SIZE,y+SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);

  SERIAL_PRINT("a/g:\t");
  SERIAL_PRINT(ax); SERIAL_PRINT("\t");
  SERIAL_PRINT(ay); SERIAL_PRINT("\t");
  SERIAL_PRINT(az); SERIAL_PRINT("\t");
  SERIAL_PRINT(gx); SERIAL_PRINT("\t");
  SERIAL_PRINT(gy); SERIAL_PRINT("\t");
  SERIAL_PRINT(gz); SERIAL_PRINT("\t ->");
  SERIAL_PRINT(x); SERIAL_PRINT("\t");
  SERIAL_PRINTLN(y);
}

//-----------------------------------------------------------------------------

void _showSystCalib()
{
  u8g.setPrintPos(40,25);
  u8g.print("System");
  u8g.setPrintPos(20,36);
  u8g.print("Calibrated!");
}

//-----------------------------------------------------------------------------

inline void _showWelcome()
{
  u8g.drawStr(10,40,"GO for launch!");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _tasks()
{
  _attitudeTask();
  _pressTask();
  _tempTask();
  switch(geState)
  {
    case ESM_ALTITUDE: _altitudeTask();    break;
    case ESM_HEADING:  _headingTask();     break;
    case ESM_ATTITUDE:
    case ESM_TEMP:
    case ESM_CALIB:
    case ESM_WELCOME:
    case ESM_CALIB_ALTITUDE:
    default:                               break;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _draw()
{
  static unsigned long timeStamp(millis());
  switch(geState)
  {
    case ESM_ALTITUDE:
      _showAltitude();
      timeStamp = millis();
      break;
    case ESM_ATTITUDE:
      _showAttitude();
      timeStamp = millis();
      break;
    case ESM_TEMP:
      _showTemp();
      timeStamp = millis();
      break;
    case ESM_CALIB:
      _showSystCalib();
      if(millis() - timeStamp > 1500)
        geState = ESM_ATTITUDE;
      break;
    case ESM_CALIB_ALTITUDE:
      _showSystCalib();
      if(millis() - timeStamp > 1500)
        geState = ESM_ALTITUDE;
      break;
    case ESM_HEADING:
      _showHeading();
      timeStamp = millis();
      break;
    case ESM_WELCOME:
      _showWelcome();
      if(millis() - timeStamp > 5000)
        geState = ESM_ATTITUDE;
      break;
    default:
      break;
  }
}

//-----------------------------------------------------------------------------
//---[ SETUP ]-----------------------------------------------------------------
//-----------------------------------------------------------------------------

void setup()
{
  //Initialize serial port
  SERIAL_BEGIN;
  
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // Display configuration
  switch(u8g.getMode())
  {
    case U8G_MODE_R3G3B2:   u8g.setColorIndex(255); break; // white
    case U8G_MODE_GRAY2BIT: u8g.setColorIndex(3); break; // max intensity
    case U8G_MODE_HICOLOR:  u8g.setHiColorByRGB(255,255,255); break;
    case U8G_MODE_BW:       
    default:                u8g.setColorIndex(1); break;// pixel on
  }
 
  u8g.setFontPosBaseline();
  //u8g.setFont(u8g_font_fub11);
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_9x18);
  //u8g.setRot180();

  //Initialize button
#ifndef ULTIMATE_DEBOUNCER
  goButton0.init();
  goButton1.init();
  delay(200);
#endif

  // initialize accelgyro device
  goAccelgyro.initialize();
  goAccelgyro.testConnection();

  // Initialize compas device
  goCompass.init(false); // Dont set mode yet, we'll do that later on.
  // Calibrate HMC using self test, not recommended to change the gain after calibration.
  goCompass.calibrate(1, 32); // Use gain 1=default, valid 0-7, 7 not recommended.
  // Single mode conversion was used in calibration, now set continuous mode
  goCompass.setMode(0);

  //initialize baro
  goBaro.init(MS561101BA_ADDR_CSB_LOW);
  delay(100);
  
  // populate gfaMovavg_buff before starting loop
  for(int i=0; i<MOVAVG_SIZE; i++)
    gfaMovavg_buff[i] = goBaro.getPressure(MS561101BA_OSR_4096);

  //Load calibration
  _loadCalib(goGCal);
  _loadAltitudeCalib(gfAltitudeCalib);

  //Set kalman staring point
  goAccelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  goRoll.setAngle(_getRoll());
  goPitch.setAngle(_getPitch());
  
  //Configure Led pin
  pinMode(LED_PIN,OUTPUT);
}

//-----------------------------------------------------------------------------
//---[ LOOP ]------------------------------------------------------------------
//-----------------------------------------------------------------------------

void loop()
{
  //Check buttons
#ifdef ULTIMATE_DEBOUNCER
  if(goButton0.is_pressed())_buttonShortPress();
  if(goButton1.is_pressed())_buttonLongPress();
#else
  if(goButton0.handle()==EV_SHORTPRESS) _buttonShortPress();
  if(goButton1.handle()==EV_LONGPRESS)  _buttonLongPress();
#endif

  //main functions
  _tasks();

  //Draw information (only drawing operations)
  u8g.firstPage();
  do {
    _draw();
  } while(u8g.nextPage());

  digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

