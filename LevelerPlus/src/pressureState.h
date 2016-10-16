//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  pressureState.h
 *  @date  Octubre, 2016
 *  @brief Pressure State class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __PRESSURE_STATE_H__
 #define __PRESSURE_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CPressureState : public IState{
protected:
	CStateMachine* _pStateMachine;
public:
	CPressureState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CPressureState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __PRESSURE_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
