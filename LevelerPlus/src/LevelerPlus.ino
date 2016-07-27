//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  vw.ino
 *  @date  November, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

 //-----------------------------------------------------------------------------
 //---[ Macros: ]---------------------------------------------------------------

 //#define ULTIMATE_DEBOUNCER
 //#define SERIAL_OUTPUT
 #define USE_BARO
 //#define USE_MAG

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------

#include "includes.h"
#include "menu.h"

//-----------------------------------------------------------------------------
//---[ Global variables: ]-----------------------------------------------------

#ifdef ULTIMATE_DEBOUNCER
  CTheUltimateDebouncer goButton0(BUTTON_PIN0);
  CTheUltimateDebouncer goButton1(BUTTON_PIN1);
#else
  CButtonHandler        goButton0(BUTTON_PIN0, DEFAULT_LONGPRESS_LEN);
  CButtonHandler        goButton1(BUTTON_PIN1, DEFAULT_LONGPRESS_LEN);
#endif

CMenu                   goMenu;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _button0ShortPress()
{
  switch(geState)
  {
  case ESM_TEMP:            geState = ESM_ALTITUDE;  break;
  case ESM_ALTITUDE:        geState = ESM_HEADING;   break;
  case ESM_HEADING:         geState = ESM_ATTITUDE;  break;
  case ESM_ATTITUDE:        geState = ESM_RESET;     break;
  case ESM_RESET:           geState = ESM_TEMP;      break;
  case ESM_WELCOME:         geState = ESM_TEMP;      break;
  case ESM_CALIB_ATTITUDE:                           break;
  case ESM_CALIB_ALTITUDE:                           break;
  default:                                           break;
  }
}

//-----------------------------------------------------------------------------

void _button0LongPress()
{
  switch(geState)
  {
  case ESM_RESET:           break;
  case ESM_ATTITUDE:        break;
  case ESM_ALTITUDE:        break;
  case ESM_HEADING:         break;
  case ESM_TEMP:            break;
  case ESM_CALIB_ATTITUDE:  break;
  case ESM_CALIB_ALTITUDE:  break;
  case ESM_WELCOME:         break;
  default:                  break;
  }
}

//-----------------------------------------------------------------------------

void _button1ShortPress()
{
  switch(geState)
  {
  case ESM_ATTITUDE:        break;
  case ESM_ALTITUDE:        break;
  case ESM_RESET:           break;
  case ESM_TEMP:            break;
  case ESM_HEADING:         break;
  case ESM_WELCOME:         break;
  case ESM_CALIB_ATTITUDE:  break;
  case ESM_CALIB_ALTITUDE:  break;
  default:                  break;
  }
}

//-----------------------------------------------------------------------------

void _button1LongPress()
{
  switch(geState)
  {
  case ESM_RESET:
    _reset();
    break;
  case ESM_ATTITUDE:
    _saveCalib(goG);
    goGCal = goG;
    geState = ESM_CALIB_ATTITUDE;
    break;
  case ESM_ALTITUDE:
    #ifdef USE_BARO
      _saveAltitudeCalib(gfAltitude);
      gfAltitudeCalib = gfAltitude;
      geState = ESM_CALIB_ALTITUDE;
    #endif
    break;
  case ESM_HEADING:         break;
  case ESM_TEMP:            break;
  case ESM_CALIB_ATTITUDE:  break;
  case ESM_CALIB_ALTITUDE:  break;
  case ESM_WELCOME:         break;
  default:                  break;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _showAltitude()
{
  #ifdef USE_BARO
    u8g.setPrintPos(20,25);
    u8g.print(gfAltitude - gfAltitudeCalib);
    u8g.setPrintPos(95,25);
    u8g.print("m");
    u8g.setPrintPos(20,45);
    u8g.print(gfPress);
    u8g.setPrintPos(95,45);
    u8g.print("mb");

    SERIAL_PRINT("Pres: ");
    SERIAL_PRINT(gfPress);
    SERIAL_PRINT(" mbar altitude: ");
    SERIAL_PRINT(gfAltitude);
    SERIAL_PRINTLN(" m");
  #else
    geState = ESM_HEADING;
  #endif
}

//-----------------------------------------------------------------------------

void _showTemp()
{
  u8g.setPrintPos(40,35);
  u8g.print(gfTemperature);
  u8g.setPrintPos(90,35);
  u8g.print("C");

  SERIAL_PRINT("Temp: ");
  SERIAL_PRINT(gfTemperature);
  SERIAL_PRINTLN(" degC");
}

//-----------------------------------------------------------------------------

void _showHeading()
{
  #ifdef USE_MAG
    u8g.drawCircle(64, 32, 24);

    uint8_t xN((uint8_t)(24*sin(M_PI_D - gfHeading)));
    uint8_t yN((uint8_t)(24*cos(M_PI_D - gfHeading)));
    u8g.setFontPosCenter();
    u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"N");
    u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"S");
    u8g.drawStr(-xN + SSD1306_LCDWIDTH_MED,-yN+ SSD1306_LCDHEIGHT_MED,"E");
    u8g.drawStr(xN + SSD1306_LCDWIDTH_MED,yN+ SSD1306_LCDHEIGHT_MED,"O");
    u8g.setFontPosBaseline();

    u8g.setPrintPos(0,10);
    u8g.print(gfHeading);

    SERIAL_PRINT("Orientation: ");
    SERIAL_PRINT(gfHeading * RAD_2_DEG);
    SERIAL_PRINTLN(" deg");
  #else
    geState = ESM_ATTITUDE;
  #endif
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

inline void _showResetMsg()
{
  u8g.drawStr(10,40,"Reset System?");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void _draw()
{
  static unsigned long timeStamp(millis());
  switch(geState)
  {
    case ESM_ALTITUDE: _showAltitude(); timeStamp = millis(); break;
    case ESM_ATTITUDE: _showAttitude(); timeStamp = millis(); break;
    case ESM_TEMP:     _showTemp();     timeStamp = millis(); break;
    case ESM_HEADING:  _showHeading();  timeStamp = millis(); break;
    case ESM_RESET:    _showResetMsg(); timeStamp = millis(); break;
    case ESM_CALIB_ATTITUDE:
      _showSystCalib();
      if(millis() - timeStamp > 1500)
        geState = ESM_ATTITUDE;
      break;
    case ESM_CALIB_ALTITUDE:
      _showSystCalib();
      if(millis() - timeStamp > 1500)
        geState = ESM_ALTITUDE;
      break;
    case ESM_WELCOME:
      _showWelcome();
      if(millis() - timeStamp > 3000)
        geState = ESM_TEMP;
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

  //Initialize button
#ifndef ULTIMATE_DEBOUNCER
  goButton0.init();
  goButton1.init();
  delay(200);
#endif

  //Initialize System
  goMenu.setup();

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
  if(goButton0.is_pressed())goMenu.button0ShortPress();
  if(goButton1.is_pressed())goMenu.button1LongPress();
#else
  eEvent event (goButton0.handle());
  if(event==EV_SHORTPRESS) goMenu.button0ShortPress();
  if(event==EV_LONGPRESS)  goMenu.button0LongPress();
  event = goButton1.handle();
  if(event==EV_SHORTPRESS) goMenu.button1ShortPress();
  if(event==EV_LONGPRESS)  goMenu.button1LongPress();
#endif

  //main functions
  goMenu.runCalculus();

  //Draw information (only drawing operations)
  u8g.firstPage();
  do {
    goMenu.drawCurrentState();
  } while(u8g.nextPage());

  digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
