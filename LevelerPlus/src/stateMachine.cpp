//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  stateMachine.cpp
 *  @date  Octubre, 2016
 *  @brief
 *
 *
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include "includes.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CStateMachine::CStateMachine()
    : _pWelcomeState(new CWelcomeState(this)),
      _pAltitudeState(new CAltitudeState{this}),
      _pAltitudeStateCfg(new CAltitudeStateCfg{this}),
      _pAltitudeRelState(new CAltitudeRelState{this}),
      _pAttitudeState(new CAttitudeState{this}),
      _pAttitudeStateCfg(new CAttitudeStateCfg{this}),
      _pResetState(new CResetState{this}),
      _pPressureState(new CPressureState{this})
#ifdef USE_TEMP_STATE
      ,
      _pTempState(new CTempState{this}), _pTempStateCfg(new CTempStateCfg{this})
#endif
#ifdef USE_MAG
      ,
      _pHeadingState(new CHeadingState{this})
#endif
      ,
      _ulTimeStamp(millis()), _u8g(U8G_I2C_OPT_FAST), _fTemperature(0.0f),
      _fTemperatureCalib(0.0f), _fAltitude(0.0f), _fAltitudeCalib(0.0f),
      _fAltitudeRef(0.0f), _fPress(0.0f), _fHeading(0.0f),
      _ui8DrawNumberLines(1)

{
  _pState = _pWelcomeState;
}

//-----------------------------------------------------------------------------

CStateMachine::~CStateMachine() {
  delete _pWelcomeState;
  delete _pAltitudeState;
  delete _pAltitudeStateCfg;
  delete _pAltitudeRelState;
  delete _pAttitudeState;
  delete _pAttitudeStateCfg;
  delete _pResetState;
  delete _pPressureState;
#ifdef USE_TEMP_STATE
  delete _pTempState;
  delete _pTempStateCfg;
#endif
#ifdef USE_MAG
  delete _pHeadingState;
#endif

  _pState = 0;
  _pWelcomeState = 0;
  _pAltitudeState = 0;
  _pAltitudeStateCfg = 0;
  _pAltitudeRelState = 0;
  _pAttitudeState = 0;
  _pAttitudeStateCfg = 0;
  _pResetState = 0;
  _pPressureState = 0;
  _pTempState = 0;
  _pTempStateCfg = 0;
  _pHeadingState = 0;
}

//-----------------------------------------------------------------------------

void CStateMachine::setup() {
  // Display configuration
  switch (_u8g.getMode()) {
  case U8G_MODE_R3G3B2:
    _u8g.setColorIndex(255);
    break; // white
  case U8G_MODE_GRAY2BIT:
    _u8g.setColorIndex(3);
    break; // max intensity
  case U8G_MODE_HICOLOR:
    _u8g.setHiColorByRGB(255, 255, 255);
    break;
  case U8G_MODE_BW:
  default:
    _u8g.setColorIndex(1);
    break; // pixel on
  }

  _u8g.setFontPosBaseline();
  //_u8g.setFont(u8g_font_fub11);
  //_u8g.setFont(u8g_font_unifont);
  //_u8g.setFont(u8g_font_gdb17);
  //_u8g.setFont(u8g_font_gdr20);
  _u8g.setFont(u8g_font_courB18r);
  //_u8g.setRot180();

  // initialize accelgyro device
  _oAccelgyro.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  //_oAccelgyro.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  _oAccelgyro.setThreshold(3);

#ifdef USE_MAG
  while (!_oCompass.begin())
    delay(500);

  // Set measurement range
  _oCompass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  _oCompass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  _oCompass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  _oCompass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  _oCompass.setOffset(0, 0);
#endif

  // Set initial number of lines to be displayed
  _setDrawNumberLines(1);

#ifdef USE_BARO
  // initialize baro
  _oBaro.init(MS561101BA_ADDR_CSB_LOW);
  delay(100);

  // populate gfaMovavg_buff before starting loop
  float fPress{0};
  for (int i = 0; i < MOVAVG_SIZE;) {
    fPress = _oBaro.getPressure(MS561101BA_OSR_4096);
    if (fPress) {
      _faMovavg_buff[i] = fPress;
      i++;
    }
  }

#endif

  // Load calibration
  _loadCalib(_oGCal);
  _loadAltitudeCalib(_fAltitudeCalib);
  _loadAltitudeRef(_fAltitudeRef);
  _loadTempCalib(_fTemperatureCalib);
}

//-----------------------------------------------------------------------------

// State machine
void CStateMachine::button0ShortPress() { _pState->button0ShortPress(); }

//-----------------------------------------------------------------------------

void CStateMachine::button1ShortPress() { _pState->button1ShortPress(); }

//-----------------------------------------------------------------------------

void CStateMachine::button0LongPress() { _pState->button0LongPress(); }

//-----------------------------------------------------------------------------

void CStateMachine::button1LongPress() { _pState->button1LongPress(); }

//-----------------------------------------------------------------------------

void CStateMachine::drawCurrentState() {
  _u8g.firstPage();
  do {
    _pState->drawCurrentState();
  } while (_u8g.nextPage());

  if (millis() - _ulTimeStamp > 60000)
    setState(getAltitudeState());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void CStateMachine::_restoreSettings() {
  // Show pre-reset message
  _u8g.firstPage();
  do {
    _u8g.drawStr(5, 35, "wait...");
  } while (_u8g.nextPage());

  // Clear eeprom
  for (unsigned int i = 0; i < EEPROM.length(); i++)
    EEPROM.write(i, 0);

  // Reset System
  asm volatile("jmp 0");
}

//-----------------------------------------------------------------------------

// Globals
void CStateMachine::_saveAltitudeCalib(const float &data) {
  EEPROM_writeAnything(EEPROM_CAL_ALTITUDE, data);
}

//-----------------------------------------------------------------------------

void CStateMachine::_loadAltitudeCalib(float &data) {
  EEPROM_readAnything(EEPROM_CAL_ALTITUDE, data);
}

//-----------------------------------------------------------------------------

// Globals
void CStateMachine::_saveAltitudeRef(const float &data) {
  EEPROM_writeAnything(EEPROM_REF_ALTITUDE, data);
}

//-----------------------------------------------------------------------------

void CStateMachine::_loadAltitudeRef(float &data) {
  EEPROM_readAnything(EEPROM_REF_ALTITUDE, data);
}

//-----------------------------------------------------------------------------

void CStateMachine::_saveCalib(const CData &data) {
  EEPROM_writeAnything(EEPROM_CAL_PITCH, data.pitch);
  EEPROM_writeAnything(EEPROM_CAL_ROLL, data.roll);
  EEPROM_writeAnything(EEPROM_CAL_YAW, data.yaw);
}

//-----------------------------------------------------------------------------

void CStateMachine::_saveTempCalib(const float &data) {
  EEPROM_writeAnything(EEPROM_CAL_TEMP, data);
}

//-----------------------------------------------------------------------------

void CStateMachine::_loadTempCalib(float &data) {
  EEPROM_readAnything(EEPROM_CAL_TEMP, data);
}

//-----------------------------------------------------------------------------

void CStateMachine::_loadCalib(CData &data) {
  EEPROM_readAnything(EEPROM_CAL_PITCH, data.pitch);
  EEPROM_readAnything(EEPROM_CAL_ROLL, data.roll);
  EEPROM_readAnything(EEPROM_CAL_YAW, data.yaw);
}

//-----------------------------------------------------------------------------

void CStateMachine::_pushAvg(float val) {
  static int movavg_i(0);
  _faMovavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}

//-----------------------------------------------------------------------------

float CStateMachine::_getAvg(float *buff, int size) {
  float sum = 0.0;
  for (int i = 0; i < size; i++)
    sum += buff[i];

  return sum / size;
}

//-----------------------------------------------------------------------------

void CStateMachine::_attitudeTask() {
  static uint32_t timerCnt(0);
  static float dt(0.0f);
  static Vector norm;

  // Read normalized values
  norm = _oAccelgyro.readNormalizeGyro();

  dt = (float)(micros() - timerCnt) / 1000000; // Calculate delta time
  timerCnt = micros();

  // Calculate Pitch, Roll and Yaw
  _oG.pitch = _oG.pitch + norm.YAxis * dt;
  _oG.roll = _oG.roll + norm.XAxis * dt;
  _oG.yaw = _oG.yaw + norm.ZAxis * dt;

  _oGDif.roll = _oG.roll - _oGCal.roll;
  _oGDif.pitch = _oG.pitch - _oGCal.pitch;
  _oGDif.yaw = _oG.yaw - _oGCal.yaw;

  SERIAL_PRINT("data:\t");
  SERIAL_PRINT(gyroXrate);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(gyroYrate);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_getRoll());
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_getPitch());
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oG.roll);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oG.pitch);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oG.yaw);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGCal.roll);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGCal.pitch);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGCal.yaw);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGDif.roll);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGDif.pitch);
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_oGDif.yaw);
  SERIAL_PRINTLN("\t **");
}

//-----------------------------------------------------------------------------

void CStateMachine::_pressTask() {
#ifdef USE_BARO
  _pushAvg(_oBaro.getPressure(MS561101BA_OSR_4096));
  _fPress = _getAvg(_faMovavg_buff, MOVAVG_SIZE);
#endif
}

//-----------------------------------------------------------------------------

void CStateMachine::_tempTask() {
#ifdef USE_BARO
  _fTemperature =
      _oBaro.getTemperature(MS561101BA_OSR_4096) + _fTemperatureCalib;
#else
  static float fM = 0.98;
  _fTemperature =
      fM * _fTemperature +
      (1.0 - fM) * ((float)_oAccelgyro.readTemperature() + _fTemperatureCalib);
#endif

  SERIAL_PRINT("Temp:");
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_fTemperature);
  SERIAL_PRINT("\t");
  SERIAL_PRINTLN("degC");
}

//-----------------------------------------------------------------------------

void CStateMachine::_altitudeTask() {
#ifdef USE_BARO
  _fAltitude = (((pow((SEA_LEVEL_PRESSURE / _fPress), 1.0f / 5.257f) - 1.0f) *
                 (_fTemperature + 273.15f)) /
                0.0065f) +
               _fAltitudeCalib;

  SERIAL_PRINT("Pres:");
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_fPress);
  SERIAL_PRINT("\t");
  SERIAL_PRINT("mbar altitude:");
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_fAltitude);
  SERIAL_PRINT("\t");
  SERIAL_PRINT("m altitude calib:");
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_fAltitudeCalib);
  SERIAL_PRINT("\t");
  SERIAL_PRINTLN("m");
#endif
}

//-----------------------------------------------------------------------------

void CStateMachine::_headingTask() {
#ifdef USE_MAG
  static float fx, fy, fz;
  _oCompass.getValues(&fx, &fy, &fz);
  _fHeading = atan2(fy, fx);
  if (_fHeading < 0)
    _fHeading += M_PI_D;

  SERIAL_PRINT("Orientation:");
  SERIAL_PRINT("\t");
  SERIAL_PRINT(_fHeading * RAD_2_DEG);
  SERIAL_PRINT("\t");
  SERIAL_PRINTLN("deg");
#endif
}

//-----------------------------------------------------------------------------

uint8_t CStateMachine::_getFloatDrawColPos(const float &data) {
  int iCol = 14;
  float fTemp = abs(data);
  if (fTemp < 1000)
    iCol += 8;
  if (fTemp < 100)
    iCol += 8;
  if (fTemp < 10)
    iCol += 8;
  if (data < 0)
    iCol -= 10;
  return iCol;
}

//-----------------------------------------------------------------------------

uint8_t CStateMachine::_getDrawRowPos(const uint8_t line) {
  static const uint8_t ibaseRow[3] = {35, 27, 20};
  static const uint8_t igapRow[3] = {0, 30, 22};
  return (ibaseRow[_ui8DrawNumberLines] +
          (line * igapRow[_ui8DrawNumberLines]));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void CStateMachine::runCalculus() {
  this->_tempTask();
  this->_pressTask();
  this->_headingTask();
  this->_altitudeTask();
  this->_attitudeTask();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
