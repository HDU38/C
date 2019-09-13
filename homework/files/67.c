#include <stdio.h>

int main67()

{



	int salary[100] = { 130, 220, 340, 407, 508, 691, 755, 860, 945, 1002 };
	int i, sum = 0;
	int money_100 = 0, money_50 = 0, money_20 = 0, money_10 = 0, money_5 = 0, money_1 = 0;
	for (i = 0; i < 50; i++)
	{
		//scanf("%d", &salary[i]);
		sum += salary[i];
	}
	printf("总额为%d\n", sum);
	i = -1;
	while (salary[++i])
	{
		money_100 += salary[i] / 100;
		money_50 += salary[i] % 100 / 50;
		money_20 += salary[i] % 100 % 50 / 20;
		money_10 += salary[i] % 100 % 50 % 20 / 10;
		money_5 += salary[i] % 100 % 50 % 20 % 10 / 5;
		money_1 += salary[i] % 100 % 50 % 20 % 10 % 5;
	}
   printf("100元%d张，50元%d张，20元%d张，10元%d张，5元%d张，1元%d张", money_100, money_50, money_20, money_10, money_5, money_1);
   getchar();
   return 0;

}

