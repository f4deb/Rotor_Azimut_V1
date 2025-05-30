#ifndef OLED_H
#define OLED_H

#include "../../managed_components/lvgl__lvgl/lvgl.h"

#define I2C_HW_ADDR           0x3C
#define LCD_PIXEL_CLOCK_HZ    (400 * 1000)
#define PIN_NUM_RST           -1

// The pixel number in horizontal and vertical
#if CONFIG_LCD_CONTROLLER_SSD1306
#define LCD_H_RES              128
#define LCD_V_RES              CONFIG_SSD1306_HEIGHT
#elif CONFIG_LCD_CONTROLLER_SH1107
#define LCD_H_RES              64
#define LCD_V_RES              128
#endif
// Bit number used to represent command and parameter
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

void createLabel (int index);
void setTextOled(int index, char *text);
void setTextRotation(int value);
void setLongMode (int index, int value);
void setRecolor(int index, bool status);
void setXPos(int index, int value);
void setYPos(int index, int value);
void setPos(int index, int xvalue, int yvalue);
void drawRectangle(int x, int y, int dimx, int dimy, int size);
void drawLine(int index, int x, int y, int X, int Y, int Size);

void boussole (unsigned int azimut);


void clearScreen (void);

void saveLabel (lv_obj_t *label);

lv_obj_t*  getLabel(int index);

void oled (void);

#endif