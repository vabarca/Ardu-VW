//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeStateCfg.cpp
 *  @date  July, 2016
 *  @brief Attitude State configuration class
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

void CAttitudeStateCfg::button0ShortPress(){}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button1ShortPress(){}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button0LongPress()
{
  _pStateMachine->_saveCalib(_pStateMachine->_oG);
  _pStateMachine->_oGCal = _pStateMachine->_oG;
  _pStateMachine->setState(_pStateMachine->getAttitudeState());
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::button1LongPress()
{
  this->button0LongPress();
}

//-----------------------------------------------------------------------------

void CAttitudeStateCfg::drawCurrentState(){}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
