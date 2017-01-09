
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
CButtonHandler goButton0(BUTTON_PIN0, DEFAULT_LONGPRESS_LEN);
CButtonHandler goButton1(BUTTON_PIN1, DEFAULT_LONGPRESS_LEN);
#endif

CStateMachine goMenu;

//-----------------------------------------------------------------------------
//---[ SETUP ]-----------------------------------------------------------------
//-----------------------------------------------------------------------------

void setup() {
  // Initialize serial port
  SERIAL_BEGIN;

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // Initialize System
  goMenu.setup();

// Initialize button
#ifndef ULTIMATE_DEBOUNCER
  goButton0.init();
  goButton1.init();
  delay(200);
#endif

  // Configure Led pin
  pinMode(LED_PIN, OUTPUT);
}

//-----------------------------------------------------------------------------
//---[ LOOP ]------------------------------------------------------------------
//-----------------------------------------------------------------------------

void loop() {
// Check buttons
#ifdef ULTIMATE_DEBOUNCER
  if (goButton0.is_pressed())
    goMenu.button0ShortPress();
  if (goButton1.is_pressed())
    goMenu.button1LongPress();
#else
  eEvent event(goButton0.handle());
  if (event == EV_SHORTPRESS)
    goMenu.button0ShortPress();
  if (event == EV_LONGPRESS)
    goMenu.button0LongPress();
  event = goButton1.handle();
  if (event == EV_SHORTPRESS)
    goMenu.button1ShortPress();
  if (event == EV_LONGPRESS)
    goMenu.button1LongPress();
#endif

  // main functions
  goMenu.runCalculus();
  goMenu.drawCurrentState();

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
