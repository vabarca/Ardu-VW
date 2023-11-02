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

#include "altitudeState.h"

//-----------------------------------------------------------------------------

class CAltitudeStateCfg : public CAltitudeState{
private:
	void getAndSaveCurrentSeaLevelPressure();
public:
  CAltitudeStateCfg(CStateMachine* pStateMachine):CAltitudeState{pStateMachine}{}
	~CAltitudeStateCfg(){}
	virtual void button0ShortPress();
	virtual void button1ShortPress();
	virtual void button0LongPress();
	virtual void button1LongPress();
	virtual void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ALTITUDE_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
