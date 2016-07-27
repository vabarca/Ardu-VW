//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  tempStateCfg.h
 *  @date  July, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __TEMP_STATE_CFG_H__
 #define __TEMP_STATE_CFG_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "IMenuState.h"

class CTempStateCfg : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CTempStateCfg(CMenu* oMenu):_pMenu(oMenu){}
	~CTempStateCfg(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __TEMP_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------