//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeStateCfg.h
 *  @date  July, 2016
 *  @brief Altitude State configuration class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ALTITUDE_STATE_CFG_H__
 #define __ALTITUDE_STATE_CFG_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "stateMachine.h"

//-----------------------------------------------------------------------------

class CAltitudeStateCfg : public IState{
private:
  CStateMachine* _pStateMachine;
public:
  CAltitudeStateCfg(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CAltitudeStateCfg(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ALTITUDE_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
