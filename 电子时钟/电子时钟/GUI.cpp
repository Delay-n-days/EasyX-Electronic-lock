#include <GUI.h>

//RGB565���㺯��
void GUI_DrawPoint(int x, int y,uint color)
{
    int r,g,b;
    DWORD COLOR;
    r=(color&63488)>>8;
    g=(color&2016)>>3;
    b=(color&31)<<3;
    COLOR=RGB(b,g,r);//bgr ��ס�ˣ������EasyX����ɫ��bgr ��������ƨ��
	putpixel(x, y, COLOR);
}
//��ʾRGB565ͼƬ����ɫ��̫��
void ShowImgRGB565(int x0,int y0, int W,int H,const unsigned char *p) //��ʾ����ͼƬ
{
	int i,x,y;
	unsigned char picH, picL;
	uint fc;
	for (i = 0; i < W * H; i++)
	{
        y=i/W;
        x=i-y*W;
		picL = *(p + i * 2); //���ݵ�λ��ǰ
		picH = *(p + i * 2 + 1);
        fc=picH*256+picH;
		GUI_DrawPoint(x+x0,y+y0,fc);
	}
}
//��ʾ32λRGBͼƬ
void ShowImgRGB888(int x0, int y0, int W, int H, const unsigned char* p) //��ʾ����ͼƬ
{
	int i, x, y;
	unsigned char picR, picG,picB;
	DWORD fc;
	for (i = 0; i < W * H; i++)
	{
		y = i / W;
		x = i - y * W;
		picR = *(p + i * 3); //���ݵ�λ��ǰ
		picG = *(p + i * 3 + 1);
		picB = *(p + i * 3 + 2);
		fc = RGB(picB, picG, picR);
		putpixel(x+x0, y+y0, fc);
	}
}
//32λ��ɫ����
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
//��ʼ������ָ��λ��
//ʱ��TimePoint[0]~TimePoint[59]
//�֣�TimePoint[60]~TimePoint[119]
//�룺TimePoint[120]~TimePoint[179]
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
//��ʱ������װ
void delay_ms(DWORD t)
{
	Sleep(t);
}

//�����뺯��
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

//���㣬��ɫ����ͼƬ�����������ڸ�ʱ��ָ�룩
void Gui_DrawPoint(int x, int y, POINT StartPoint,const unsigned char* p)
{
	unsigned char picR, picG, picB;
	DWORD color;
	int i;
	i = (y-StartPoint.y) * 300 + (x - StartPoint.x);
	picR = *(p + i * 3); //���ݵ�λ��ǰ
	picG = *(p + i * 3 + 1);
	picB = *(p + i * 3 + 2);
	color = RGB(picB, picG, picR);
	putpixel(x, y, color);
}
//���ߣ���ɫ����ͼƬ
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
	dx = x1 - x0;//����x����
	dy = y1 - y0;//����y����
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
//�������ߺ���
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
	dx = x1 - x0;//����x����
	dy = y1 - y0;//����y����
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