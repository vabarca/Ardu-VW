//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  buttonhandler.cpp
 *  @date  July, 2016
 *  @brief
 *
 *
 *  @author Original from (C) 2011 By P. Bauermeister
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ButtonHandler.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CButtonHandler::CButtonHandler(int p, int lp)
: _pin(p),_longpress_len(lp),_was_pressed(false),
  _lastLoopTime(0),_pressed_counter(0)
{
}

//-----------------------------------------------------------------------------

void CButtonHandler::init()
{
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH); // pull-up
  _was_pressed = false;
  _pressed_counter = 0;
  _lastLoopTime = millis();
}

//-----------------------------------------------------------------------------

eEvent CButtonHandler::handle()
{
  eEvent event (EV_NONE);

  if(millis() - _lastLoopTime < 30)
    return event;

  _lastLoopTime = millis();

  int now_pressed (!digitalRead(_pin));

  if (!now_pressed && _was_pressed)
  {
    // handle release event
    if (_pressed_counter < _longpress_len)
      event = EV_SHORTPRESS;
    else
      event = EV_LONGPRESS;
  }
  else
  {
    event = EV_NONE;
  }

  // update press running duration
  if (now_pressed)
    ++_pressed_counter;
  else
    _pressed_counter = 0;

  // remember state, and we're done
  _was_pressed = now_pressed;
  return event;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CTheUltimateDebouncer::CTheUltimateDebouncer(uint8_t p)
: _pin(p), _button_history(0x00)
{
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH); // pull-up
}

//-----------------------------------------------------------------------------

uint8_t CTheUltimateDebouncer::is_pressed(void)
{
  _button_history = _button_history << 1;
  _button_history |= digitalRead(_pin);
  if((_button_history & B11000111) == B00000111)
  {
    _button_history = B11111111;
    return 1;
  }
  return 0;
}

//-----------------------------------------------------------------------------

uint8_t CTheUltimateDebouncer::is_released(void)
{
  _button_history = _button_history << 1;
  _button_history |= digitalRead(_pin);
  if((_button_history & B11000111) == B11000000)
  {
    _button_history = B00000000;
    return 1;
  }
  return 0;
}

//-----------------------------------------------------------------------------
uint8_t CTheUltimateDebouncer::is_down(void)
{
  return (_button_history == B11111111);
}

//-----------------------------------------------------------------------------
uint8_t CTheUltimateDebouncer::is_up(void)
{
  return (_button_history == B00000000);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
