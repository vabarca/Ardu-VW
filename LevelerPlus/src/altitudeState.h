//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeState.h
 *  @date  July, 2016
 *  @brief Altitude State class
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

#include "IMenuState.h"

class CAltitudeState : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CAltitudeState(CMenu* oMenu):_pMenu(oMenu){}
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