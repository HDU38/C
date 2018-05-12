#include "graphics.h"
#include "data.h"

/*���Ƽ�����ֱ�ߣ�����r���Ƕ�theta*/
static void DrawPolarLine(double r, double theta)
{
	double radians;

	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/*ΪTraverseLinkedList���ú����������ƵĻ���ֱ�ߺ���
*obj�ǽǶ�ָ�룬length��ֱ�߳��ȣ�ȫ�ֱ�����
*/
static void DrawKochSnowLine(double theta)
{
	DrawPolarLine(length, theta);
}
