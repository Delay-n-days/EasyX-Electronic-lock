#include <graphics.h>
#include <math.h>

#define WIDTH 300	// 宽
#define HEIGHT 300	// 高
#define PI 3.1415926

#define uRED 0x0015
#define uGREEN 0x07e8
#define uBLUE 0xA800
#define uWHITE 0xffff
#define uBLACK 0x0000
#define uYELLOW 0x57ff
#define uGRAY0 0xEF7D //灰色0 3165 00110 001011 00101
#define uGRAY1 0x8410 //灰色1      00000 000000 00000
#define uGRAY2 0x4208 //灰色2  1111111111011111
typedef unsigned int        uint;
void GUI_DrawPoint(int x, int y,uint color);
void ShowImgRGB565(int x0, int y0, int W, int H, const unsigned char* p);
void ShowImgRGB888(int x0, int y0, int W, int H, const unsigned char* p);
void TimePointInit(POINT CentralPoint, POINT* TimePoint);
void Lcd_clear(uint color);
void DrawNeedle(POINT StartPoint, POINT CentralPoint, POINT* TimePoint, int hour, int min, int sec, COLORREF color, COLORREF color2, COLORREF color3, const unsigned char* p);
void DrawImgLine(int x, int y, int x0, int y0, POINT StartPoint, const unsigned char* p);
void Gui_DrawPoint(int x, int y, POINT StartPoint, const unsigned char* p);
void line2(int x0, int y0, int x1, int y1, DWORD color);
void delay_ms(DWORD t);