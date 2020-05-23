#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define NEURON 25
#define PATTERN 4

int W[25][25];
int count = 0;

void hardLimiter(int* out);
void weights(int(*p)[NEURON]);
void transfer(int* in, int* out, int(*W)[NEURON]);
void arraycopy(int* from, int* to);
int cheak(int(*p)[NEURON], int* out);

int main() {
	int p[PATTERN][NEURON] = {
		{ //��
			 1,  1,  1,  1, 1,
			-1, -1, -1, -1, 1,
			-1, -1, -1, -1, 1,
			-1, -1, -1, -1, 1,
			-1, -1, -1, -1, 1
			},
		{ //��
			1, -1, -1, -1, -1,
			1, -1, -1, -1, -1,
			1, -1, -1, -1, -1,
			1, -1, -1, -1, -1,
			1,  1,  1,  1,  1
			},
		{ //��
			 1,  1,  1,  1,  1,
			 1, -1, -1, -1, -1,
			 1, -1, -1, -1, -1,
			 1, -1, -1, -1, -1,
			 1,  1,  1,  1,  1
			 },
		{ //��
			  1,  1,  1,  1,  1,
			 -1, -1, -1, -1,  1,
			  1,  1,  1,  1,  1,
			  1, -1, -1, -1, -1,
			  1,  1,  1,  1,  1
			  }
		};

	int in[NEURON] = { //��
		 1, -1, -1, -1, -1,
		 1, -1, -1, -1, -1,
		 1,  1,  1,  1,  1,
		-1,  1,  1, -1, -1,
		-1, -1,  1,  1,  1
	};

	int out[NEURON];
	int tmpin[NEURON];

	printf(" �ΰ����� 5���� ���� \n 201636042 ������");

	arraycopy(in, tmpin);
	weights(p);

	while (!cheak(p, out))
	{
		transfer(tmpin, out, W);
		hardLimiter(out);
		arraycopy(out, tmpin);
	}
	return 0;
}

int cheak(int(*p)[NEURON], int* out) { //��������� �н������� �����ϴ��� üũ
	int i, s;
	int chk = FALSE;

	for (s = 0; s < PATTERN; s++) {
		for (i = 0; i < NEURON; i++) {
			if (p[s][i] == out[i])
				chk = TRUE;
			else
			{
				chk = FALSE;
				break;
			}
		}
		if (chk == TRUE)
			return TRUE;
	}
	return FALSE;
}

void arraycopy(int* from, int* to) {
	int i;
	for (i = 0; i < NEURON; i++) {
		to[i] = from[i];
	}
}

void weights(int(*p)[NEURON]) { //���ᰡ��ġ ���
	int s, i, j;

	printf("\n1. ���� ����ġ ��� \n");

	for (s = 0; s < PATTERN; s++) {
		for (i = 0; i < NEURON; i++) {
			for (j = 0; j < NEURON; j++) {
				if (i == j)
					W[i][j] = 0;
				else
					W[i][j] = W[i][j] + (p[s][i] * p[s][j]);
			}
		}
	}
	for (i = 0; i < NEURON; i++) {
		for (j = 0; j < NEURON; j++) {
			printf("%2d", W[i][j]);
		}
		printf("\n");
	}
}

void transfer(int* in, int* out, int(*W)[NEURON]) { //�Է��� ���ϰ� ����ġ�� ���ؼ� ��������� ����
	int i, j;
	int tmp;
	count++;
	printf("\n");
	printf("[Step %d]\n", count);
	printf("2. �Է����ϰ� ����ġ�� ������ ��������� ����\n");

	for (i = 0; i < NEURON; i++) {
		tmp = 0;
		for (j = 0; j < NEURON; j++) {
			tmp = tmp + (in[j] * W[i][j]);
		}
		out[i] = tmp;
	}
	for (i = 0; i < NEURON; i++) {
		printf("%4d ", out[i]);
		if ((i % 5) == 4)
			printf("\n");
	}
}

void hardLimiter(int* out) { //������Ͽ� ���ؼ� 0���� ũ�Ű������� 1 0���� ������ -1
	int i;

	printf("\n 3. ������Ͽ� ���ؼ� 0���� ũ�Ű������� 1 0���� ������ -1 ��ȯ\n");
	for (i = 0; i < NEURON; i++) {
		if (out[i] >= 0)
			out[i] = 1;
		else
			out[i] = -1;
	}

	for (i = 0; i < NEURON; i++) {
		printf("%2d ", out[i]);
		if ((i % 5) == 4)
			printf("\n");
	}
}