#include "MazeDataStruct.h"

int main()
{	
	time_t calendar_time = time(NULL);
	struct tm * tm_local = localtime(&calendar_time);
	int month = tm_local->tm_mon + 1;
	int day = tm_local->tm_mday;
	Start(month,day);
	_getch();
	return 0;
}