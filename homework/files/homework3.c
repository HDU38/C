#include <stdio.h>

#define MAX 100

int g_people[MAX] = { 0 };

void JosephCircle(int m, int n)
{
	int next = 0, i, index, peopleAlive = m, currentIndex = 1;
	int count = 0;
	if (m > MAX) return;
	for (i = 1; i <= m; i++) g_people[i] = 1;
	for (i = 0; i < m; i++)
	{
		for (index = currentIndex; count<n; index++)
		{
			if (index > m) index = index % m;
			if (g_people[index])
			{
				count++;
			}
		}
		printf("%d ", index -1);
		g_people[index - 1] = 0;
		currentIndex = index;
		if (currentIndex > m)
			currentIndex = currentIndex % m;
		while (!g_people[currentIndex])
		{
			currentIndex++;
			if (currentIndex > m)
				currentIndex = currentIndex % m;
		}
		count = 0;
	}
}
int mainhomework3()
{
	JosephCircle(10, 5);
	getchar();
	return 0;
}