//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeStateCfg.h
 *  @date  July, 2016
 *  @brief Altitude State configuration class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ATTITUDE_STATE_CFG_H__
 #define __ATTITUDE_STATE_CFG_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "attitudeState.h"

//-----------------------------------------------------------------------------

class CAttitudeStateCfg : public CAttitudeState{
public:
  CAttitudeStateCfg(CStateMachine* pStateMachine):CAttitudeState{pStateMachine}{}
	~CAttitudeStateCfg(){}
	virtual void button0ShortPress();
	virtual void button1ShortPress();
	virtual void button0LongPress();
	virtual void button1LongPress();
	virtual void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ATTITUDE_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
