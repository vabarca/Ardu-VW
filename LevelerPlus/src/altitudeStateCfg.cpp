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
  _pStateMachine->_saveSeaLevelPressureCalib(_pStateMachine->_fSeaLevelPressureCalib);
  _fAltitude + _fAltitudeCalib= (((pow((_fSeaLevelPressureCalib / _fPress), 1.0f / 5.257f) - 1.0f) *
                 (_fTemperature + 273.15f)) /
                0.0065f);

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
  _pStateMachine->_u8g.drawStr(110,
    (u8g_int_t)_pStateMachine->_getDrawRowPos(1),
    "*");
  CAltitudeState::drawCurrentState();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
