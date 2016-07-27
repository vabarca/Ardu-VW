//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  attitudeStateCfg.h
 *  @date  July, 2016
 *  @brief Attitude State configuration class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __ATTITUDE_STATE_CFG_H__
 #define __ATTITUDE_STATE_CFG_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "IMenuState.h"

class CAttitudeStateCfg : public IMenuState{
private:
	CMenu* _pMenu;
public:
	CAttitudeStateCfg(CMenu* oMenu):_pMenu(oMenu){}
	~CAttitudeStateCfg(){}
	void button0ShortPress();
	void button1ShortPress();
	void button0LongPress();
	void button1LongPress();
	void drawCurrentState();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __ATTITUDE_STATE_CFG_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
