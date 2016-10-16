//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  buttonhandler.h
 *  @date  November, 2015
 *  @brief
 *
 *
 *  @author Original from (C) 2011 By P. Bauermeister
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef CBUTTONHANDLER_H_
#define CBUTTONHANDLER_H_

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

//---[ Global defines: ]-------------------------------------------------------

#define DEFAULT_LONGPRESS_LEN    30  // Min nr of loops for a long press

enum eEvent
{
  EV_NONE=0
  ,EV_SHORTPRESS
  ,EV_LONGPRESS
};

//-----------------------------------------------------------------------------

class CButtonHandler
{
  protected:

    boolean         _was_pressed;     // previous state
    boolean         _generated_event; // generated event before relese button
    int             _pressed_counter; // press running duration
    const uint8_t   _pin;             // pin to which button is connected
    const int       _longpress_len;   // longpress duration
    long            _lastLoopTime;

  public:

    CButtonHandler(int pin, int longpress_len=DEFAULT_LONGPRESS_LEN);
    ~CButtonHandler(){}

   // Initialization done after construction, to permit static instances
    void init();

    // Handler, to be called in the loop()
    eEvent handle();
};

//-----------------------------------------------------------------------------
// http://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/

class CTheUltimateDebouncer
{
  protected:

    uint8_t         _button_history;
    const uint8_t   _pin;             // pin to which button is connected

  public:

    CTheUltimateDebouncer(uint8_t pin);
    ~CTheUltimateDebouncer(){}

    uint8_t is_pressed(void);
    uint8_t is_released(void);
    uint8_t is_down(void);
    uint8_t is_up(void);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif /* CBUTTONHANDLER_H_ */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
