//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeState.h
 *  @date  July, 2016
 *  @brief Attitude State class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ATTITUDE_STATE_H__
 #define __ATTITUDE_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CAttitudeState : public IState{
protected:
  CStateMachine* _pStateMachine;
public:
  CAttitudeState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CAttitudeState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ATTITUDE_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
