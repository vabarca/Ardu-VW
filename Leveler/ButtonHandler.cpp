
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ButtonHandler.h"

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

CButtonHandler::CButtonHandler(int p, int lp)
: _pin(p), _longpress_len(lp)
{
}

//////////////////////////
//////////////////////////
//////////////////////////

void CButtonHandler::init()
{
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH); // pull-up
  _was_pressed = false;
  _pressed_counter = 0;
  _lastLoopTime = millis();
}

//////////////////////////
//////////////////////////
//////////////////////////

eEvent CButtonHandler::handle()
{
  eEvent event (EV_NONE);

	if(millis() - _lastLoopTime < 20)
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

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

