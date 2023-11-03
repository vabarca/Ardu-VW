//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeStateCfg.cpp
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

void CAltitudeStateCfg::button0ShortPress()
{
  _pStateMachine->_fAltitudeCalib +=10.0;
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1ShortPress()
{
  _pStateMachine->_fAltitudeCalib -=10.0;
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::getAndSaveCurrentSeaLevelPressure()
{
  const float press = _pStateMachine->_fPress;
  const float altitude = _pStateMachine->_fAltitude;
  const float altitudeCalib = _pStateMachine->_fAltitudeCalib;
  const float temp = _pStateMachine->_fTemperature;

  _pStateMachine->_fSeaLevelPressureCalib =  press * (pow((TERM_B * (altitude - altitudeCalib)/(temp + ABSOLUTE_ZERO)) + 1.0f,TERM_C));
  _pStateMachine->_saveSeaLevelPressureCalib(_pStateMachine->_fSeaLevelPressureCalib);

  _pStateMachine->_fAltitudeCalib = 0.0f;
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button0LongPress()
{
  getAndSaveCurrentSeaLevelPressure();
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1LongPress()
{
  getAndSaveCurrentSeaLevelPressure();
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::drawCurrentState()
{
  _pStateMachine->_setDrawNumberLines(2);  
  u8g_uint_t y = (u8g_int_t)_pStateMachine->_getDrawRowPos(1);
  _pStateMachine->_u8g.drawStr(110, y,"*");  
  CAltitudeState::drawCurrentState();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
