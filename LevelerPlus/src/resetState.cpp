//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  resetState.cpp
 *  @date  Octubre, 2016
 *  @brief
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

void CResetState::button0ShortPress() {
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CResetState::button1ShortPress() {
  _pStateMachine->setState(_pStateMachine->getPressureState());
}

//-----------------------------------------------------------------------------

void CResetState::button0LongPress() { _pStateMachine->_restoreSettings(); }

//-----------------------------------------------------------------------------

void CResetState::button1LongPress() { this->button0LongPress(); }

//-----------------------------------------------------------------------------

void CResetState::drawCurrentState() {
  // THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_setDrawNumberLines(2);
  u8g_int_t x = 25;
  u8g_int_t y = (u8g_int_t)_pStateMachine->_getDrawRowPos(0);
  _pStateMachine->_u8g.drawStr(x, y,"Reset");
  x = 15;
  y = (u8g_int_t)_pStateMachine->_getDrawRowPos(1);
  _pStateMachine->_u8g.drawStr(x, y,"system?");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
