//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  resetState.h
 *  @date  July, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __RESET_STATE_H__
 #define __RESET_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "IMenuState.h"

class CResetState : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CResetState(CMenu* oMenu):_pMenu(oMenu){}
	~CResetState(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __RESET_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
