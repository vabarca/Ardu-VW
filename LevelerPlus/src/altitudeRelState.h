//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeRelState.h
 *  @date  Octubre, 2016
 *  @brief Relative altitude State class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ALTITUDE_REL_STATE_H__
 #define __ALTITUDE_REL_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CAltitudeRelState : public IState{
protected:
	CStateMachine* _pStateMachine;
public:
	CAltitudeRelState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CAltitudeRelState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ALTITUDE_REL_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
