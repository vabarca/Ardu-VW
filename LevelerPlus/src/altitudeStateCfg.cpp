//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeStateCfg.cpp
 *  @date  July, 2016
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

}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1ShortPress()
{

}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button0LongPress()
{
  _pStateMachine->_saveAltitudeCalib(_pStateMachine->_fAltitude);
  _pStateMachine->_fAltitudeCalib = _pStateMachine->_fAltitude;
  _pStateMachine->setState(_pStateMachine->getAltitudeState());
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CAltitudeStateCfg::drawCurrentState()
{
  _pStateMachine->_u8g.setPrintPos(120,10);
  _pStateMachine->_u8g.print('*');
  CAltitudeState::drawCurrentState();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
