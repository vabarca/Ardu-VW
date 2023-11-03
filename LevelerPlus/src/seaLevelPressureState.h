//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  pressureState.h
 *  @date  Octubre, 2023
 *  @brief Pressure State class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef SEA_LEVEL_PRESSURE_STATE_H
 #define SEA_LEVEL_PRESSURE_STATE_H

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #include "stateMachine.h"

 //-----------------------------------------------------------------------------

class CSeaLevelPressureState : public IState{
protected:
	CStateMachine* _pStateMachine;
public:
	CSeaLevelPressureState(CStateMachine* pStateMachine):_pStateMachine(pStateMachine){}
	~CSeaLevelPressureState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // SEA_LEVEL_PRESSURE_STATE_H

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
