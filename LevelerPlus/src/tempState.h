//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  tempState.h
 *  @date  July, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __TEMP_STATE_H__
 #define __TEMP_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CTempState : public IState{
protected:
  CStateMachine* _pStateMachine;
public:
  CTempState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CTempState(){}
	virtual void button0ShortPress();
	virtual void button1ShortPress();
	virtual void button0LongPress();
	virtual void button1LongPress();
	virtual void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __TEMP_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
