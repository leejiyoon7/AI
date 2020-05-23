#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PATTERN 10 //�н��� ������ ��

#define INPUT_LAYER_NODES 25 //�Է��� ���̾�
#define HIDDEN_LAYER_NODES 12 //������ ���̾�
#define OUTPUT_LAYER_NODES PATTERN //����� ���̾�

#define NO_EPOCH 3000//�н�Ƚ��
#define ETA 0.2 //�н���

int inPutDataSet[PATTERN][INPUT_LAYER_NODES] = { //�Է� ������
	{ //��
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{ //��
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{ //��
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{ //��
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{ //��
		1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	{ //��
		1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	{ //��
		0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{ //��
		0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0},
	{ //��
		1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	{ //��
		0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1}
};

int outPutDataSet[PATTERN][OUTPUT_LAYER_NODES] = { //��µǾ���ϴ� ��
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //��
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //��
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //��
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //��
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //��
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //��
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //��
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //��
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}  //��
};

//�ñ׸��̵� �Լ�
//����� 0��1������ Ȯ�������� ��ȯ
double sigmoid(double x) {
	double exp_value;
	double return_value;

	exp_value = exp((double)-x);

	return_value = 1.0 / (1.0 + exp_value);

	return return_value;
}

int main() {
	srand(time(NULL));
	//����ġ ����
	double Input_To_Hidden_Weight[INPUT_LAYER_NODES][HIDDEN_LAYER_NODES];
	double Hidden_To_output_Weight[HIDDEN_LAYER_NODES][OUTPUT_LAYER_NODES];

	//�ٷ°� ����� ����
	double Input_To_Hidden_Out[HIDDEN_LAYER_NODES];
	double Hidden_To_output_Out[OUTPUT_LAYER_NODES];

	//���� ���ϱ�
	double Error_Score[OUTPUT_LAYER_NODES];
	double Error_Total = 0;

	//��Ÿ�� ����
	double Output_Delta[OUTPUT_LAYER_NODES];
	double Hidden_delta[HIDDEN_LAYER_NODES];

	//�Է°� ����
	int input[INPUT_LAYER_NODES];

	//���ᰡ��ġ 0.01~0.99������ ���������� �ʱ�ȭ
	for (int i = 0; i < INPUT_LAYER_NODES; i++) {
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			Input_To_Hidden_Weight[i][j] = 0.01 * (1.0 + (rand() % 99));
		}
	}
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) {
		for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
			Hidden_To_output_Weight[i][j] = 0.01 * (1.0 + (rand() % 99));
		}
	}

	for (int a = 0; a < NO_EPOCH; a++) { //epoch��ŭ �ݺ�
		for (int z = 0; z < PATTERN; z++) { //���� �� ��ŭ �ݺ�
			double tmp = 0;

			//��� �� ��� �� ����
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //�Է��� --> ������ ��°�
				for (int j = 0; j < INPUT_LAYER_NODES; j++) {
					tmp += inPutDataSet[z][j] * Input_To_Hidden_Weight[j][i];
				}
				Input_To_Hidden_Out[i] = sigmoid(tmp);
				tmp = 0;
			}
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //������ --> ����� ��°�
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					tmp += Input_To_Hidden_Out[j] * Hidden_To_output_Weight[j][i];
				}
				Hidden_To_output_Out[i] = sigmoid(tmp);
				printf("%f  ", Hidden_To_output_Out[i]);
				tmp = 0;
			}
			printf("\n");

			//���� ���
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
				Error_Score[i] = 0.5 * (outPutDataSet[z][i] - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
				Error_Total += Error_Score[i];
			}

			//������ ���
			printf("%f\n", Error_Total);
			Error_Total = 0;

			//��Ÿ�� ���
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //����� �������
				Output_Delta[i] = Hidden_To_output_Out[i] * (1 - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
			}
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //������ �������
				tmp = 0;
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					tmp += Output_Delta[j] * Hidden_To_output_Weight[i][j];
				}
				Hidden_delta[i] = Input_To_Hidden_Out[i] * (1 - Input_To_Hidden_Out[i]) * tmp;
				tmp = 0;
			}

			//����ġ ����
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) {
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					Hidden_To_output_Weight[i][j] += (ETA * Output_Delta[j] * Input_To_Hidden_Out[i]);
				}
			}
			for (int i = 0; i < INPUT_LAYER_NODES; i++) {
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					Input_To_Hidden_Weight[i][j] += (ETA * Hidden_delta[j] * inPutDataSet[z][i]);
				}
			}
		}
		printf("EPOCH:%d\n", a + 1);
	}

	//����ġ ���
	printf("Input_To_Hidden_Weight\n");
	for (int i = 0; i < INPUT_LAYER_NODES; i++) {
		printf("[");
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			printf("%f   ", Input_To_Hidden_Weight[i][j]);
		}
		printf("]\n");
	}
	printf("\nHidden_To_output_Weight\n");
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) {
		printf("[");
		for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
			printf("%f   ", Hidden_To_output_Weight[i][j]);
		}
		printf("]\n");
	}

	//�Է¹޾Ƽ� �����ϱ�
	printf("\n�н��Ϸ�! �Է°��� �־����.\n");
	for (int i = 0; i < INPUT_LAYER_NODES; i++) {
		printf("%d��°�� �� ��: ", i);
		scanf_s("%d", &input[i]);
	}

	double tmp = 0;

	//��� �� ��� �� ����
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //�Է��� --> ������ ��°�
		for (int j = 0; j < INPUT_LAYER_NODES; j++) {
			tmp += input[j] * Input_To_Hidden_Weight[j][i];
		}
		Input_To_Hidden_Out[i] = sigmoid(tmp);
		tmp = 0;
	}
	printf("\n");
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //������ --> ����� ��°�
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			tmp += Input_To_Hidden_Out[j] * Hidden_To_output_Weight[j][i];
		}
		Hidden_To_output_Out[i] = sigmoid(tmp);
		printf("%f ", Hidden_To_output_Out[i]);
		tmp = 0;
	}
	printf("\n");

	//����� �ִ� ���ϱ�
	double tmp_1 = Hidden_To_output_Out[0];
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 < Hidden_To_output_Out[i])
			tmp_1 = Hidden_To_output_Out[i];
	}

	//�ִ��� 1,�������� 0���� ��ȯ�Ͽ� ���
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 / Hidden_To_output_Out[i] == 1)
			Hidden_To_output_Out[i] = 1;
		else
			Hidden_To_output_Out[i] = 0;
		printf("%d ", (int)Hidden_To_output_Out[i]);
	}
	return 0;
}