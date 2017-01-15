//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeState.cpp
 *  @date  Octubre, 2016
 *  @brief Altitude state class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void CAltitudeState::button0ShortPress() {
  _pStateMachine->setState(_pStateMachine->getHeadingState());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button1ShortPress() {
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button0LongPress() {
  _pStateMachine->setState(_pStateMachine->getAltitudeStateCfg());
}

//-----------------------------------------------------------------------------

void CAltitudeState::button1LongPress() {
  _pStateMachine->setState(_pStateMachine->getAltitudeStateCfg());
}

//-----------------------------------------------------------------------------

void CAltitudeState::drawCurrentState() {
  // THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  _pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.setPrintPos(
      (u8g_int_t)_pStateMachine->_getFloatDrawColPos(
          _pStateMachine->_fAltitude),
      (u8g_int_t)_pStateMachine->_getDrawRowPos(0));
  _pStateMachine->_u8g.print(_pStateMachine->_fAltitude, 1);

  _pStateMachine->_u8g.drawStr(20, (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
                               "Alt(m)");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
