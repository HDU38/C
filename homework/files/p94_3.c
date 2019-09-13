#include<stdio.h>

void if_struct(int score) {
	if (score >= 90 && score <= 100) {
		printf(" A\n");
	}
	else if (score >= 80) {
		printf(" B\n");
	}
	else if (score >= 70) {
		printf(" C\n");
	}
	else if (score >= 60) {
		printf(" D\n");
	}
	else if (score >= 0) {
		printf(" E\n");
	}
	else {
		return;
	}
}
void switch_struct(int score) {
	int i;
	for (i = 90; i <= 100; i++) {
		switch (score - i) {
		case 0:
			printf(" A\n");
			return;
		}
	}
	for (i = 80; i <= 89; i++) {
		switch (score - i) {
		case 0:
			printf(" B\n");
			return;
		}
	}
	for (i = 70; i <= 79; i++) {
		switch (score - i) {
		case 0:
			printf(" C\n");
			return;
		}
	}
	for (i = 60; i <= 69; i++) {
		switch (score - i) {
		case 0:
			printf(" D\n");
			return;
		}
	}
	for (i = 0; i <= 59; i++) {
		switch (score - i) {
		case 0:
			printf(" E\n");
			return;
		}
	}
}

int main3() {
	while (1) {
		int score;
		printf("ÇëÊäÈë³É¼¨:");
		scanf("%d", &score);
		if_struct(score);
		switch_struct(score);
	}
	return 0;
}
