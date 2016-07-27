//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  altitudeStateCfg.h
 *  @date  July, 2016
 *  @brief Altitude State configuration class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ALTITUDE_STATE_CFG_H__
 #define __ALTITUDE_STATE_CFG_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "IMenuState.h"

class CAltitudeStateCfg : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CAltitudeStateCfg(CMenu* oMenu):_pMenu(oMenu){}
	~CAltitudeStateCfg(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ALTITUDE_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
