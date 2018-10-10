#include <stdio.h>
#define SIZE 16

int main(void)
{
	int key, low, high, middle, k = 0;
	int data[SIZE] = { 2,6,11,13,18,20,22,27,29,34,34,38,41,42,45,47 };

	printf("탐색할 값을 입력하시오 : ");
	scanf("%d", &key);

	low = 0;
	high = SIZE - 1;

	while (low <= high)
	{
		printf("[%d , %d]\n", low, high);
		middle = (low + high) / 2;
		if (key == data[middle])
		{
			printf("\n탐색성공 : 저장위치 = data[%d] \n\n", middle);
			break;
		}
		else if (key > data[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}
	return 0;
}

