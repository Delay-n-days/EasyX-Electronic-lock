#include <GUI.h>

//RGB565画点函数
void GUI_DrawPoint(int x, int y,uint color)
{
    int r,g,b;
    DWORD COLOR;
    r=(color&63488)>>8;
    g=(color&2016)>>3;
    b=(color&31)<<3;
    COLOR=RGB(b,g,r);//bgr 记住了，他妈的EasyX的颜色是bgr 罗马车的马屁股
	putpixel(x, y, COLOR);
}
//显示RGB565图片，颜色不太正
void ShowImgRGB565(int x0,int y0, int W,int H,const unsigned char *p) //显示完整图片
{
	int i,x,y;
	unsigned char picH, picL;
	uint fc;
	for (i = 0; i < W * H; i++)
	{
        y=i/W;
        x=i-y*W;
		picL = *(p + i * 2); //数据低位在前
		picH = *(p + i * 2 + 1);
        fc=picH*256+picH;
		GUI_DrawPoint(x+x0,y+y0,fc);
	}
}
//显示32位RGB图片
void ShowImgRGB888(int x0, int y0, int W, int H, const unsigned char* p) //显示完整图片
{
	int i, x, y;
	unsigned char picR, picG,picB;
	DWORD fc;
	for (i = 0; i < W * H; i++)
	{
		y = i / W;
		x = i - y * W;
		picR = *(p + i * 3); //数据低位在前
		picG = *(p + i * 3 + 1);
		picB = *(p + i * 3 + 2);
		fc = RGB(picB, picG, picR);
		putpixel(x+x0, y+y0, fc);
	}
}
//32位颜色清屏
void Lcd_clear(uint color)
{
    int x,y;
for (int i = 0; i<WIDTH*HEIGHT;i++)
	{
        y=i/WIDTH;
        x=i-y*WIDTH;
		putpixel(x,y,color);
	}
}
//初始化表盘指针位置
//时：TimePoint[0]~TimePoint[59]
//分：TimePoint[60]~TimePoint[119]
//秒：TimePoint[120]~TimePoint[179]
void TimePointInit(POINT CentralPoint,POINT *TimePoint)
{
	double PIn, x, y;
	int j = 0;
	for (double i = 50;i <= 90;i = i + 20)
		for (PIn = 45;PIn < 105;PIn++)
		{
			x = CentralPoint.y + cos(PIn * 2 * PI / 60) * i;
			y = CentralPoint.x + sin(PIn * 2 * PI / 60) * i;
			TimePoint[j].x = (int)x;
			TimePoint[j].y = (int)y;
			j++;
		}
}
//延时函数包装
void delay_ms(DWORD t)
{
	Sleep(t);
}

//画表针函数
void DrawNeedle(POINT StartPoint, POINT CentralPoint,POINT* TimePoint, int hour, int min, int sec, COLORREF color1, COLORREF color2, COLORREF color3, const unsigned char* p)
{	
	int H0,H1,min1,sec1;
	H0 = hour * 5 + min * 5 / 60;
	min = min + 1;
	sec = sec + 1;
	H1 = H0 - 1;
	min1 = min - 1;
	sec1 = sec - 1;

	if (H0 == 60)H0 = 0;
	if (H1 == 60)H1 = 0;
	if (min == 60)min = 0;
	if (min1 == 60)min1 = 0;
	if (sec == 60)sec = 0;
	if (sec1 == 60)sec1 = 0;

	DrawImgLine(CentralPoint.x, CentralPoint.y, TimePoint[120 + sec1].x, TimePoint[120 + sec1].y, StartPoint, p);
	line2(CentralPoint.x, CentralPoint.y, TimePoint[120 + sec].x, TimePoint[120 + sec].y, color3);
	
	DrawImgLine(CentralPoint.x, CentralPoint.y, TimePoint[60 + min1 ].x, TimePoint[60 + min1 ].y, StartPoint, p);
	line2(CentralPoint.x, CentralPoint.y, TimePoint[60+min].x, TimePoint[60+min].y, color2);

	DrawImgLine(CentralPoint.x, CentralPoint.y, TimePoint[(int)H1].x, TimePoint[(int)H1].y, StartPoint, p);
	line2(CentralPoint.x, CentralPoint.y, TimePoint[(int)H0].x, TimePoint[(int)H0].y, color1);
}

//画点，颜色基于图片，（适用于遮盖时间指针）
void Gui_DrawPoint(int x, int y, POINT StartPoint,const unsigned char* p)
{
	unsigned char picR, picG, picB;
	DWORD color;
	int i;
	i = (y-StartPoint.y) * 300 + (x - StartPoint.x);
	picR = *(p + i * 3); //数据低位在前
	picG = *(p + i * 3 + 1);
	picB = *(p + i * 3 + 2);
	color = RGB(picB, picG, picR);
	putpixel(x, y, color);
}
//画线，颜色基于图片
void DrawImgLine(int x0, int y0, int x1, int y1, POINT StartPoint, const unsigned char* p)
{
	int dx,             // difference in x's
		dy,             // difference in y's
		dx2,            // dx,dy * 2
		dy2,
		x_inc,          // amount in pixel space to move during drawing
		y_inc,          // amount in pixel space to move during drawing
		error,          // the discriminant i.e. error i.e. decision variable
		index;          // used for looping	
	dx = x1 - x0;//计算x距离
	dy = y1 - y0;//计算y距离
	if (dx >= 0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx = -dx;
	}
	if (dy >= 0)
	{
		y_inc = 1;
	}
	else
	{
		y_inc = -1;
		dy = -dy;
	}
	dx2 = dx << 1;
	dy2 = dy << 1;
	if (dx > dy)
	{
		error = dy2 - dx;
		// draw the line
		for (index = 0; index <= dx; index++)
		{
			Gui_DrawPoint(x0, y0, StartPoint, p);
			if (error >= 0) 
			{
				error -= dx2;
				y0 += y_inc;
			} 
			error += dy2;
			x0 += x_inc;
		} 
	}
	else
	{
		error = dx2 - dy;
		for (index = 0; index <= dy; index++)
		{
			Gui_DrawPoint(x0, y0, StartPoint, p);
			if (error >= 0)
			{
				error -= dy2;
				x0 += x_inc;
			}
			error += dx2;
			y0 += y_inc;
		}
	} 
}
//正常画线函数
void line2(int x0, int y0, int x1, int y1,DWORD color )
{
	int dx,             // difference in x's
		dy,             // difference in y's
		dx2,            // dx,dy * 2
		dy2,
		x_inc,          // amount in pixel space to move during drawing
		y_inc,          // amount in pixel space to move during drawing
		error,          // the discriminant i.e. error i.e. decision variable
		index;          // used for looping	
	dx = x1 - x0;//计算x距离
	dy = y1 - y0;//计算y距离
	if (dx >= 0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx = -dx;
	}
	if (dy >= 0)
	{
		y_inc = 1;
	}
	else
	{
		y_inc = -1;
		dy = -dy;
	}
	dx2 = dx << 1;
	dy2 = dy << 1;
	if (dx > dy)
	{
		error = dy2 - dx;
		// draw the line
		for (index = 0; index <= dx; index++)
		{
			putpixel(x0, y0, color);
			if (error >= 0)
			{
				error -= dx2;
				y0 += y_inc;
			}
			error += dy2;
			x0 += x_inc;
		}
	}
	else
	{
		error = dx2 - dy;
		for (index = 0; index <= dy; index++)
		{
			putpixel(x0, y0,color);
			if (error >= 0)
			{
				error -= dy2;
				x0 += x_inc;
			}
			error += dx2;
			y0 += y_inc;
		}
	}
}