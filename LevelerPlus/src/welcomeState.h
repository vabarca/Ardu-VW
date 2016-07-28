//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef __WELCOME_STATE_H__
 #define __WELCOME_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CWelcomeState : public IState{
private:
  CStateMachine* _pStateMachine;
public:
  CWelcomeState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CWelcomeState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __WELCOME_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
