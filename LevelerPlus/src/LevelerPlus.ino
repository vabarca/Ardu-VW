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
//---[ Includes: ]-------------------------------------------------------------

#include "includes.h"
#include "stateMachine.h"

//-----------------------------------------------------------------------------
//---[ Global variables: ]-----------------------------------------------------

#ifdef ULTIMATE_DEBOUNCER
  CTheUltimateDebouncer goButton0(BUTTON_PIN0);
  CTheUltimateDebouncer goButton1(BUTTON_PIN1);
#else
  CButtonHandler        goButton0(BUTTON_PIN0, DEFAULT_LONGPRESS_LEN);
  CButtonHandler        goButton1(BUTTON_PIN1, DEFAULT_LONGPRESS_LEN);
#endif

CStateMachine           goMenu;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*
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

*/
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
  goMenu.drawCurrentState();

  digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
