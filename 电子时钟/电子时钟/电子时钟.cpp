//编译环境：Visual Stdio 2019，EasyX 2020.07.21版本
//作	者：胡金涛
//
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <GUI.h>
#include <img.h>
#include <math.h>
#pragma warning(disable:4996)
POINT StartPoint = { 0,0 };																								//图片左上点
POINT CentralPoint = { 150 + StartPoint.x,151 + StartPoint.y };																//表盘圆心点

POINT TimePoint[180];
time_t tt = time(NULL);
tm* t = localtime(&tt);
int ts;
int main()
{
	initgraph(WIDTH, HEIGHT);																							//新建窗口
	ShowImgRGB888(StartPoint.x, StartPoint.y, 300, 300, gImage_1);														//画表盘
	TimePointInit(CentralPoint, TimePoint);																				//初始化指针终点位置
	while (!kbhit())																									//按任意键关闭
	{
		ts = t->tm_sec;
		time_t tt = time(NULL);
		tm* t = localtime(&tt);																							//获取系统时钟
		if (t->tm_sec != ts) {																								//每秒更新一次
			DrawNeedle(StartPoint, CentralPoint, TimePoint, t->tm_hour, t->tm_min, t->tm_sec, WHITE, BLUE, YELLOW, gImage_1);	//画出指针
		}
	}
	closegraph();																										//关闭窗口
}