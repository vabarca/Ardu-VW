//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  menu.h
 *  @date  July, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

 #ifndef __MENU_H__
  #define __MENU_H__

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//---[ Main class: ]-----------------------------------------------------------

class CMenu{

private:
  //State machine
  IMenuState* _pWelcomeState;
  IMenuState* _pTempState;
  IMenuState* _pTempStateCfg;
  IMenuState* _pAltitudeState;
  IMenuState* _pAltitudeStateCfg;
  IMenuState* _pAttitudeState;
  IMenuState* _pAttitudeStateCfg;
  IMenuState* _pState;

	//Globals
  CData                 _oG;
  CData                 _oGDif;
  CData                 _oGCal;

  Kalman                _oPitch;
  Kalman                _oRoll;

  U8GLIB_SSD1306_128X64 _u8g;

  float                 _fTemperature;
  float                 _fAltitude;
  float                 _fAltitudeCalib;
  float                 _fPress;
  float                 _fHeading;
  float                 _faMovavg_buff[MOVAVG_SIZE];
  int16_t               _i16ax, _i16ay, _i16az, _i16gx, _i16gy, _i16gz;

  MPU60X0               _oAccelgyro;
  #ifdef USE_BARO
    MS561101BA          _oBaro;
  #endif
  #ifdef USE_MAG
    HMC58X3             _oCompass;
  #endif

private:
  void  _saveAltitudeCalib(const float& data);
  void  _saveCalib(const CData& data);
  void  _loadAltitudeCalib(float& data);
  void  _loadCalib(CData& data);
  float _getRoll();
  float _getPitch();
  void  _reset();
  void  _pushAvg(float val);
  float _getAvg(float * buff, int size);
  void  _attitudeTask();
  void  _pressTask();
  void  _tempTask();
  void  _altitudeTask();
  void  _headingTask();

public:
	CMenu();
	~CMenu();

  void  setup();
  void  runCalculus();

	//State machine
	void  button0ShortPress();
	void  button1ShortPress();
	void  button0LongPress();
	void  button1LongPress();
	void  drawCurrentState();

	inline IMenuState* getTempState() const {return _pTempState;}
	inline IMenuState* getTempStateCfg()const {return _pTempStateCfg;}
	inline IMenuState* getAltitudeState()const {return _pAltitudeState;}
	inline IMenuState* getAltitudeStateCfg()const {return _pAltitudeStateCfg;}
	inline IMenuState* getAttitudeState()const {return _pAttitudeState;}
	inline IMenuState* getAttitudeStateCfg()const {return _pAttitudeStateCfg;}

	inline void setState(IMenuState* pState){this->_pState = pState;}
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // __MENU_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
