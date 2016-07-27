//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef __ATTITUDE_STATE_H__
 #define __ATTITUDE_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "IMenuState.h"

class CAttitudeState : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CAttitudeState(CMenu* oMenu):_pMenu(oMenu){}
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
