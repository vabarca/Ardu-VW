//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#ifndef _SSD1306_H_
#define _SSD1306_H_

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#include "I2Cdev.h"

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define SSD1306_128_64
//#define SSD1306_128_32

#ifdef SSD1306_128_64
  #define SSD1306_LCDHEIGHT             64
  #define SSD1306_LCDWIDTH              128
#endif

#if defined(SSD1306_128_32)
  #define SSD1306_LCDHEIGHT             32
  #define SSD1306_LCDWIDTH              128
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

class SSD1306
{
  public:

    SSD1306(){}
    ~SSD1306(){}

    void init(bool fastmode);
    void clearDisplay(void);
    void startScrollLeft(uint8_t start, uint8_t stop);
    void startScrollRight(uint8_t start, uint8_t stop);
    void startScrollDiagLeft(uint8_t start, uint8_t stop);
    void startScrollDiagRight(uint8_t start, uint8_t stop);	
    void deactive_scroll();
    void inverDisplay();
    void normalDisplay();
    void brightness(unsigned char Brightness);
    void dim(bool dim);
    void zoomOn();
    void zoomOff();

    //-------------------

    void send_string(const char *s,uint8_t row, uint8_t col, bool bInvert = false);
    void send_long(long lData,uint8_t row, uint8_t col, bool bInvert = false);
    void send_float(float fData, uint8_t row, uint8_t col, unsigned char decimal = 2, bool bInvert = false);

    //-------------------

    void displayVideoBuffer();
    void clearVideoBuffer();
  
    //-------------------
  
    bool getPixel(uint8_t row, uint8_t col);
    void setPixel(uint8_t row, uint8_t col);
    void clearPixel(uint8_t row, uint8_t col);
    void drawVLine(uint8_t row, uint8_t col, int8_t lenght);
    void drawHLine(uint8_t row, uint8_t col, int8_t lenght);
    inline void drawSquare(uint8_t row, uint8_t col, int8_t width,uint8_t thickness = 1){drawRectangle(row,col,width,width,thickness);}
    inline void drawFillSquare(uint8_t row, uint8_t col, int8_t width){drawFillRectangle(row,col,width,width);};
    void drawRectangle(uint8_t row, uint8_t col, int8_t width, int8_t height,uint8_t thickness = 1);
    void drawFillRectangle(uint8_t row, uint8_t col, int8_t width, int8_t height);

  private:
  
    void _send_long(long lData,uint8_t& row, uint8_t& col, bool bInvert = false);
    void _send_float(float fData, uint8_t& row, uint8_t& col, unsigned char decimal = 2, bool bInvert = false);

    void _send_Data_buff(uint8_t *buff, uint16_t size);
    void _send_Data(uint8_t val);
    void _send_Cmd(uint8_t command);
    
    void _startScroll(uint8_t dir, uint8_t start, uint8_t stop);
    void _startScrollDiag(uint8_t dir, uint8_t start, uint8_t stop);
    
    void _drawChar(unsigned char ascii, uint8_t& row, uint8_t& col, bool bInvert);
  
    inline uint16_t _getPixelBytePos(uint8_t row, uint8_t col);
    inline uint8_t  _getPixelByte(uint8_t row, uint8_t col);
    uint8_t*        _getPixelByteP(uint8_t row, uint8_t col);
    inline void     _setPixelByte(uint8_t row, uint8_t col,uint8_t data);
};

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#endif // _SSD1306_H_ 

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
