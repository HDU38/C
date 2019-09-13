#include<stdio.h>

#define M 3

#define N 5



int main69()

{

	int i, j, k;

	int A[M][N] = { {5,3,2,4,0}, {2,3,5,0,4}, {0,4,4,4,3} };
	int B[N][M] = { {5,3,2}, {2,3,5}, {4,4,4}, {3,2,7}, {6,5,2} };

	int result[M][M] = { 0 };

	for (i = 0; i < M; i++)

	{

		for (j = 0; j < M; j++)

		{

			for (k = 0; k < N; k++)

			{

				result[i][j] += A[i][k] * B[k][j];

			}

			printf("%d ", result[i][j]);

		}

		printf("\n");

	}

	getch();

	return 0;

}