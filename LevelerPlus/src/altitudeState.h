//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeState.h
 *  @date  Octubre, 2016
 *  @brief Altitude state class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ALTITUDE_STATE_H__
 #define __ALTITUDE_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CAltitudeState : public IState{
protected:
	CStateMachine* _pStateMachine;
public:
	CAltitudeState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CAltitudeState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ALTITUDE_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
