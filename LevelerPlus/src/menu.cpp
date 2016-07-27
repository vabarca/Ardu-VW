//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  menu.cpp
 *  @date  July, 2016
 *  @brief Attitude State configuration class
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------

#include "menu.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CMenu::CMenu():
	_pWelcomeState(new CWelcomeState {this})
	,_pTempState (new CTempState{this})
  ,_pTempStateCfg (new CTempStateCfg{this})
	,_pAltitudeState (new CAltitudeState{this})
  ,_pAltitudeStateCfg (new CAltitudeStateCfg{this})
	,_pAttitudeState (new CAttitudeState{this})
	,_pAttitudeStateCfg (new CAttitudeStateCfg{this})
  ,_u8g(U8G_I2C_OPT_FAST)
  ,_fTemperature(0.0f)
  ,_fAltitude(0.0f)
  ,_fAltitudeCalib(0.0f)
  ,_fPress(0.0f)
  ,_fHeading(0.0f)
  ,_i16ax(0)
  ,_i16ay(0)
  ,_i16az(0)
  ,_i16gx(0)
  ,_i16gy(0)
  ,_i16gz(0)
{
  _pState = _pWelcomeState;
}
CMenu::~CMenu()
{
  delete _pWelcomeState;
	delete _pTempState;
	delete _pAltitudeState;
	delete _pAttitudeState;
	delete _pTempStateCfg;
	delete _pAltitudeStateCfg;
	delete _pAttitudeStateCfg;

	_pState 			      = 0;
	_pWelcomeState 		  = 0;
	_pTempState 		    = 0;
	_pAltitudeState 	  = 0;
	_pAttitudeState 	  = 0;
	_pTempStateCfg 		  = 0;
	_pAltitudeStateCfg 	= 0;
	_pAttitudeStateCfg 	= 0;
}

void  CMenu::setup()
{
  // Display configuration
  switch(_u8g.getMode())
  {
    case U8G_MODE_R3G3B2:   _u8g.setColorIndex(255); break; // white
    case U8G_MODE_GRAY2BIT: _u8g.setColorIndex(3); break; // max intensity
    case U8G_MODE_HICOLOR:  _u8g.setHiColorByRGB(255,255,255); break;
    case U8G_MODE_BW:
    default:                _u8g.setColorIndex(1); break;// pixel on
  }

  _u8g.setFontPosBaseline();
  //_u8g.setFont(u8g_font_fub11);
  _u8g.setFont(u8g_font_unifont);
  //_u8g.setFont(u8g_font_9x18);
  //_u8g.setRot180();

  // initialize accelgyro device
  _oAccelgyro.initialize();
  _oAccelgyro.testConnection();


#ifdef USE_MAG
  // Initialize compas device
  _oCompass.init(false); // Dont set mode yet, we'll do that later on.
  // Calibrate HMC using self test, not recommended to change the gain after calibration.
  _oCompass.calibrate(1, 32); // Use gain 1=default, valid 0-7, 7 not recommended.
  // Single mode conversion was used in calibration, now set continuous mode
  _oCompass.setMode(0);
#endif

#ifdef USE_BARO
  //initialize baro
  _oBaro.init(MS561101BA_ADDR_CSB_LOW);
  delay(100);

  // populate gfaMovavg_buff before starting loop
  for(int i=0; i<MOVAVG_SIZE; i++)
    _faMovavg_buff[i] = _oBaro.getPressure(MS561101BA_OSR_4096);
#endif

  //Load calibration
  _loadCalib(_oGCal);
  _loadAltitudeCalib(_fAltitudeCalib);

  //Set kalman staring point
  _oAccelgyro.getMotion6(&_i16ax, &_i16ay, &_i16az, &_i16gx, &_i16gy, &_i16gz);
  _oRoll.setAngle(_getRoll());
  _oPitch.setAngle(_getPitch());
}

//State machine
void  CMenu::button0ShortPress(){_pState->button0ShortPress();}
void  CMenu::button1ShortPress(){_pState->button1ShortPress();}
void  CMenu::button0LongPress(){_pState->button0LongPress();}
void  CMenu::button1LongPress(){_pState->button1LongPress();}
void  CMenu::drawCurrentState(){_pState->drawCurrentState();}

//Globals
void  CMenu::_saveAltitudeCalib(const float& data){EEPROM_writeAnything(EEPROM_CAL_ALTITUDE,data);}
void  CMenu::_saveCalib(const CData& data){
  EEPROM_writeAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_writeAnything(EEPROM_CAL_ROLL,data.roll);
}
void  CMenu::_loadAltitudeCalib(float& data){EEPROM_readAnything(EEPROM_CAL_ALTITUDE,data);}
void  CMenu::_loadCalib(CData& data){
  EEPROM_readAnything(EEPROM_CAL_PITCH,data.pitch);
  EEPROM_readAnything(EEPROM_CAL_ROLL,data.roll);
}
float CMenu::_getRoll(){
#ifdef RESTRICT_PITCH
  return atan2((float)_i16ay, (float)_i16az) * RAD_2_DEG;
#else
  return atan(_i16ay / sqrt((float)_i16ax * (float)_i16ax + (float)_i16az * (float)_i16az)) * RAD_2_DEG;
#endif
}
float CMenu::_getPitch(){
#ifdef RESTRICT_PITCH
  return atan(-(float)_i16ax / sqrt((float)_i16ay * (float)_i16ay + (float)_i16az * (float)_i16az)) * RAD_2_DEG;
#else
  return atan2(-(float)_i16ax, (float)az) * RAD_2_DEG;
#endif
}
void  CMenu::_reset(){asm volatile ("  jmp 0");}
void  CMenu::_pushAvg(float val){
  static int movavg_i(0);
  _faMovavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}
float   CMenu::_getAvg(float * buff, int size){
  float sum = 0.0;
  for(int i=0; i<size; i++)
    sum += buff[i];

  return sum / size;
}
void CMenu::_attitudeTask(){
  static uint32_t timerCnt(0);
  static float   dt(0.0f), gyroXrate(0.0f), gyroYrate(0.0f);

  // Balance calculus
  _oAccelgyro.getMotion6(&_i16ax, &_i16ay, &_i16az, &_i16gx, &_i16gy, &_i16gz);

  dt = (float)(micros() - timerCnt) / 1000000; // Calculate delta time
  timerCnt = micros();

  gyroXrate = _i16gx / 131.0; // Convert to deg/s
  gyroYrate = _i16gy / 131.0; // Convert to deg/s

  _oG.roll = _oRoll.getAngle(_getRoll(), gyroXrate, dt); // Calculate the angle using a Kalman filter
  _oG.pitch = _oPitch.getAngle(_getPitch(), gyroYrate, dt); // Calculate the angle using a Kalman filter

  _oGDif.roll   = _oG.roll - _oGCal.roll;
  _oGDif.pitch  = _oG.pitch - _oGCal.pitch;

  SERIAL_PRINT("data:\t");
  SERIAL_PRINT(gyroXrate); SERIAL_PRINT("\t");
  SERIAL_PRINT(gyroYrate); SERIAL_PRINT("\t");
  SERIAL_PRINT(_getRoll()); SERIAL_PRINT("\t");
  SERIAL_PRINT(_getPitch()); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oG.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oG.pitch); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGCal.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGCal.pitch); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGDif.roll); SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGDif.pitch); SERIAL_PRINTLN("\t **");
}
void CMenu::_pressTask(){
  #ifdef USE_BARO
    _pushAvg(_oBaro.getPressure(MS561101BA_OSR_4096));
    _fPress = _getAvg(_faMovavg_buff, MOVAVG_SIZE);
  #endif
}
void CMenu::_tempTask(){
  static float fTempOffset(-6.53);
  #ifdef USE_BARO
    _fTemperature = _oBaro.getTemperature(MS561101BA_OSR_4096) + fTempOffset;
  #else
    static float fM = 0.98;
    static float fTAdj = 36.53f;
    _fTemperature = fM * _fTemperature +
      (1.0 - fM) *
      (((float)_oAccelgyro.getTemperature() / 340.00f) + fTAdj + fTempOffset);
  #endif
}
void CMenu::_altitudeTask(){
  #ifdef USE_BARO
    _fAltitude = ((pow((SEA_LEVEL_PRESSURE / _fPress),
        1.0f/5.257f) - 1.0f) * (_fTemperature + 273.15f)) / 0.0065f;
  #endif
}
void CMenu::_headingTask(){
  #ifdef USE_MAG
    static float fx,fy,fz;
    goCompass.getValues(&fx,&fy,&fz);
    gfHeading = atan2(fy, fx);
    if(gfHeading < 0)
      gfHeading += M_PI_D;
  #endif
}
void CMenu::runCalculus(){
  _tempTask();
  _pressTask();
  _altitudeTask();
  _attitudeTask();
}
