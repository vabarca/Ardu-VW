//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  pressureState.cpp
 *  @date  Octubre, 2016
 *  @brief Altitude State class
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

void CSeaLevelPressureState::button0ShortPress() {
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CSeaLevelPressureState::button1ShortPress() {
  _pStateMachine->setState(_pStateMachine->getPressureState());
}

//-----------------------------------------------------------------------------

void CSeaLevelPressureState::button0LongPress() {}

//-----------------------------------------------------------------------------

void CSeaLevelPressureState::button1LongPress() {}

//-----------------------------------------------------------------------------

void CSeaLevelPressureState::drawCurrentState() {
  // THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  _pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_setDrawNumberLines(2);
  u8g_int_t x = (u8g_int_t)_pStateMachine->_getFloatDrawColPos(_pStateMachine->_fSeaLevelPressure);
  u8g_int_t y = (u8g_int_t)_pStateMachine->_getDrawRowPos(0);
  _pStateMachine->_u8g.setPrintPos(x, y);
  _pStateMachine->_u8g.print(_pStateMachine->_fSeaLevelPressure, 1);
  x = 0;
  y = (u8g_int_t)_pStateMachine->_getDrawRowPos(1);
  _pStateMachine->_u8g.drawStr(x, y, "SPres(mb)");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
