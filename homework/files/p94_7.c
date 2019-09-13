#include<stdio.h>

int main5() {
	int year, month, day;
	int result;
	while (1) {
		printf("请输入年月日:");
		scanf("%d %d %d", &year, &month, &day);
		switch (month) {
		case 1:
			result = day;
			break;
		case 2:
			result = 31 + day;
			break;
		case 3:
			result = 59 + day;
			break;
		case 4:
			result = 90 + day;
			break;
		case 5:
			result = 120 + day;
			break;
		case 6:
			result = 151 + day;
			break;
		case 7:
			result = 181 + day;
			break;
		case 8:
			result = 212 + day;
			break;
		case 9:
			result = 243 + day;
			break;
		case 10:
			result = 273 + day;
			break;
		case 11:
			result = 304 + day;
			break;
		case 12:
			result = 334 + day;
			break;
		default:
			break;
		}
		/* 是闰年且月份大于二，加一天 */
		if (month > 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
			result++;
		}
		printf("%d年%d月%d日是该年的第%d天\n", year, month, day, result);
	}
	return 0;
}