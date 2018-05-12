#include "graphics.h"
#include "data.h"

/*绘制极坐标直线，长度r，角度theta*/
static void DrawPolarLine(double r, double theta)
{
	double radians;

	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/*为TraverseLinkedList调用函数参数定制的绘制直线函数
*obj是角度指针，length是直线长度（全局变量）
*/
static void DrawKochSnowLine(double theta)
{
	DrawPolarLine(length, theta);
}
