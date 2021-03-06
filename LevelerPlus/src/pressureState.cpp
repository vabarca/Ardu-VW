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

void CPressureState::button0ShortPress() {
  _pStateMachine->setState(_pStateMachine->getResetState());
}

//-----------------------------------------------------------------------------

void CPressureState::button1ShortPress() {
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CPressureState::button0LongPress() {}

//-----------------------------------------------------------------------------

void CPressureState::button1LongPress() {}

//-----------------------------------------------------------------------------

void CPressureState::drawCurrentState() {
  // THIS LINE MUST BE UNCOMMENTED IF THIS IS THE DEFAULT STATE
  //_pStateMachine->_ulTimeStamp = millis();

  _pStateMachine->_setDrawNumberLines(2);
  _pStateMachine->_u8g.setPrintPos(
      (u8g_int_t)_pStateMachine->_getFloatDrawColPos(_pStateMachine->_fPress),
      (u8g_int_t)_pStateMachine->_getDrawRowPos(0));
  _pStateMachine->_u8g.print(_pStateMachine->_fPress, 1);

  _pStateMachine->_u8g.drawStr(5, (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
                               "Pres(mb)");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
