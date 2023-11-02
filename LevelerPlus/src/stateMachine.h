//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  stateMachine.h
 *  @date  Octubre, 2016
 *  @brief Main application
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

//-----------------------------------------------------------------------------
//---[ Includes: ]-------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//---[ Main class: ]-----------------------------------------------------------

class CStateMachine;
class IState {
public:
  virtual ~IState(){};
  virtual void button0ShortPress() = 0;
  virtual void button1ShortPress() = 0;
  virtual void button0LongPress() = 0;
  virtual void button1LongPress() = 0;
  virtual void drawCurrentState() = 0;
};

//-----------------------------------------------------------------------------

class CStateMachine {
  friend class CHeadingState;
  friend class CWelcomeState;
  friend class CTempState;
  friend class CTempStateCfg;
  friend class CAltitudeState;
  friend class CAltitudeStateCfg;
  friend class CAltitudeRelState;
  friend class CAttitudeState;
  friend class CAttitudeStateCfg;
  friend class CResetState;
  friend class CPressureState;

private:
  // State machine
  IState *_pState;
  IState *_pWelcomeState;
  IState *_pAltitudeState;
  IState *_pAltitudeStateCfg;
  IState *_pAltitudeRelState;
  IState *_pAttitudeState;
  IState *_pAttitudeStateCfg;
  IState *_pResetState;
  IState *_pPressureState;
  IState *_pTempState;
  IState *_pTempStateCfg;
  IState *_pHeadingState;

  unsigned long _ulTimeStamp;

  CData _oG;
  CData _oGDif;
  CData _oGCal;

  Kalman _oPitch;
  Kalman _oRoll;
  Kalman _oYaw;

  U8GLIB_SSD1306_128X64 _u8g;

  float _fTemperature;
  float _fTemperatureCalib;
  float _fAltitude;
  float _fAltitudeCalib;
  float _fSeaLevelPressureCalib;
  float _fAltitudeRef;
  float _fPress;
  float _fHeading;
  float _faMovavg_buff[MOVAVG_SIZE];
  uint8_t _ui8DrawNumberLines;
  int16_t _i16ax, _i16ay, _i16az, _i16gx, _i16gy, _i16gz;

  MPU60X0 _oAccelgyro;
#ifdef USE_BARO
  MS561101BA _oBaro;
#endif
#ifdef USE_MAG
  HMC5883L _oCompass;
#endif

private:
  void _saveTempCalib(const float &data);
  void _loadTempCalib(float &data);
  void _saveSeaLevelPressureCalib(const float &data);
  void _loadSeaLevelPressureCalib(float &data);
  void _saveAltitudeRef(const float &data);
  void _loadAltitudeRef(float &data);
  void _saveCalib(const CData &data);
  void _loadCalib(CData &data);
  float _getRoll();
  float _getPitch();
  void _pushAvg(float val);
  float _getAvg(float *buff, int size);
  void _attitudeTask();
  void _pressTask();
  void _tempTask();
  void _altitudeTask();
  void _headingTask();
  void _restoreSettings();
  uint8_t _getFloatDrawColPos(const float &data);
  uint8_t _getDrawRowPos(const uint8_t line);
  inline void _setDrawNumberLines(uint8_t value) {
    _ui8DrawNumberLines = value - 1;
  }

public:
  CStateMachine();
  ~CStateMachine();

  void setup();
  void runCalculus();

  // State machine
  void button0ShortPress();
  void button1ShortPress();
  void button0LongPress();
  void button1LongPress();
  void drawCurrentState();

  inline IState *getAltitudeState() const { return _pAltitudeState; }
  inline IState *getAltitudeStateCfg() const { return _pAltitudeStateCfg; }
  inline IState *getAltitudeRelState() const { return _pAltitudeRelState; }
  inline IState *getAttitudeState() const { return _pAttitudeState; }
  inline IState *getAttitudeStateCfg() const { return _pAttitudeStateCfg; }
  inline IState *getResetState() const { return _pResetState; }
  inline IState *getPressureState() const { return _pPressureState; }
  inline IState *getTempState() const { return _pTempState; }
  inline IState *getTempStateCfg() const { return _pTempStateCfg; }
  inline IState *getHeadingState() const { return _pHeadingState; }

  inline void setState(IState *pState) { this->_pState = pState; }
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // __STATE_MACHINE_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
