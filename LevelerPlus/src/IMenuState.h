//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  IMenuState.h
 *  @date  July, 2016
 *  @brief Interface
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#ifndef __IMENU_STATE_H__
 #define __IMENU_STATE_H__

 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

class CMenu;
class IMenuState{
public:
	virtual ~IMenuState(){};
	virtual void button0ShortPress() = 0;
	virtual void button1ShortPress() = 0;
	virtual void button0LongPress() = 0;
	virtual void button1LongPress() = 0;
	virtual void drawCurrentState() = 0;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif  // __IMENU_STATE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
