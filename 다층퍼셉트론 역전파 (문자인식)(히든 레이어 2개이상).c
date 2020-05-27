#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PATTERN 14 //�н��� ������ ��

#define INPUT_LAYER_NODES 25 //�Է��� ���̾�
#define HIDDEN_LAYER_NODES 12 //������ ���̾�
#define HIDDEN_LAYER_FLOOR 2 //������ ��
#define OUTPUT_LAYER_NODES PATTERN //����� ���̾�

#define NO_EPOCH 100000//�н�Ƚ��
#define ETA 0.9 //�н���

//����ġ ����
double Input_To_Hidden_Weight[INPUT_LAYER_NODES][HIDDEN_LAYER_NODES];
double Hidden_to_Hidden_Weight[HIDDEN_LAYER_FLOOR - 1][HIDDEN_LAYER_NODES][HIDDEN_LAYER_NODES];
double Hidden_To_output_Weight[HIDDEN_LAYER_NODES][OUTPUT_LAYER_NODES];

//�ٷ°� ����� ����
double To_Hidden_Out[HIDDEN_LAYER_FLOOR][HIDDEN_LAYER_NODES];
double Hidden_To_output_Out[OUTPUT_LAYER_NODES];

//���� ���ϱ�
double Error_Score[OUTPUT_LAYER_NODES];
double Error_Total = 0;

//��Ÿ�� ����
double Output_Delta[OUTPUT_LAYER_NODES];
double Hidden_delta[HIDDEN_LAYER_FLOOR][HIDDEN_LAYER_NODES];

//�Է°� ����
int input[INPUT_LAYER_NODES];

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
	  0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
   { //��
	  1, 1, 1, 1, 1, 0 ,0 ,0 ,0 ,1 ,1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
   { //��
	  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   { //��
	  1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
   { //��
	  0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}
};



int outPutDataSet[PATTERN][OUTPUT_LAYER_NODES] = { //��µǾ���ϴ� ��
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //��
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}  //��
};

//�ñ׸��̵� �Լ�
//����� 0��1������ ������ ��ȯ
double sigmoid(double x) {
	double exp_value;
	double return_value;

	exp_value = exp((double)-x);

	return_value = 1.0 / (1.0 + exp_value);

	return return_value;
}


int main() {
	srand(time(NULL));

	//���ᰡ��ġ 0.01~0.99������ ���������� �ʱ�ȭ
	for (int i = 0; i < INPUT_LAYER_NODES; i++) {
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			Input_To_Hidden_Weight[i][j] = 0.01 * (1.0 + (rand() % 99));
		}
	}
	for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) {
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
				Hidden_to_Hidden_Weight[i][j][k] = 0.01 * (1.0 + (rand() % 99));
			}
		}
	}
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) {
		for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
			Hidden_To_output_Weight[i][j] = 0.01 * (1.0 + (rand() % 99));
		}
	}

	int a = 0;

	while (NO_EPOCH > a ) { //epoch��ŭ �ݺ�
		for (int z = 0; z < PATTERN; z++) { //���� �� ��ŭ �ݺ�
			double tmp = 0;
			Error_Total = 0;

			//--------------��� �� ��� �� ����-----------------
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //�Է��� --> ������ ��°�
				for (int j = 0; j < INPUT_LAYER_NODES; j++) {
					tmp += inPutDataSet[z][j] * Input_To_Hidden_Weight[j][i];
				}
				To_Hidden_Out[0][i] = sigmoid(tmp);
				tmp = 0;
			}

			for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) { //������ --> ������ ��°�
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
						tmp += To_Hidden_Out[i][k] * Hidden_to_Hidden_Weight[i][k][j];
					}
					To_Hidden_Out[i + 1][j] = sigmoid(tmp);
					tmp = 0;
				}
			}

			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //������ --> ����� ��°�
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					tmp += To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][j] * Hidden_To_output_Weight[j][i];
				}
				Hidden_To_output_Out[i] = sigmoid(tmp);
				tmp = 0;
			}

			//--------------���� ���-------------------
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
				Error_Score[i] = 0.5 * (outPutDataSet[z][i] - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
				Error_Total += Error_Score[i];
			}

			//---------------��Ÿ�� ���------------------
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //����� �������
				Output_Delta[i] = Hidden_To_output_Out[i] * (1 - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
			}

			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //����� �ٷ� �Ʒ� ������ �������
				tmp = 0;
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					tmp += Output_Delta[j] * Hidden_To_output_Weight[i][j];
				}
				Hidden_delta[0][i] = To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][i] * (1 - To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][i]) * tmp;
				tmp = 0;
			}
			for (int k = 1; k < HIDDEN_LAYER_FLOOR; k++) {
				for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //������ ������ �������
					tmp = 0;
					for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
						tmp += Hidden_delta[k-1][j]* Hidden_to_Hidden_Weight[HIDDEN_LAYER_FLOOR-1-k][i][j];
					}
					Hidden_delta[k][i] = To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1 - k][i] * (1 - To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1 - k][i]) * tmp;
					tmp = 0;
				}
			}

			//--------------����ġ ����-----------------
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) {
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					Hidden_To_output_Weight[i][j] += (ETA * Output_Delta[j] * To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][i]);
				}
			}

			for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) {
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
						Hidden_to_Hidden_Weight[HIDDEN_LAYER_FLOOR - 2 - i][j][k] += (ETA * Hidden_delta[i][k] * To_Hidden_Out[HIDDEN_LAYER_FLOOR - 2 - i][j]);
					}
				}
			}

			for (int i = 0; i < INPUT_LAYER_NODES; i++) {
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					Input_To_Hidden_Weight[i][j] += (ETA * Hidden_delta[HIDDEN_LAYER_FLOOR-1][j] * inPutDataSet[z][i]);
				}
			}
		}
		//������ ���
		printf("%f\n", Error_Total);
		//�������� 0.0007�̸��̸� �н�����
		if (Error_Total < 0.0007)
			break;

		printf("EPOCH:%d\n", a + 1);
		a++;
	}

	while (1) {
	//�Է¹޾Ƽ� �����ϱ�
	printf("\n�н��Ϸ�! �Է°��� �־����.\n");

	printf("%d���� �Է��ϼ��� (%d * %d) \n", (int)sqrt(INPUT_LAYER_NODES), (int)sqrt(INPUT_LAYER_NODES), (int)sqrt(INPUT_LAYER_NODES));
	for (int i = 0; i < sqrt(INPUT_LAYER_NODES); i++) {
		int tmp = i * (int)sqrt(INPUT_LAYER_NODES);
		scanf_s("%d %d %d %d %d", &input[tmp + 0], &input[tmp + 1], &input[tmp + 2], &input[tmp + 3], &input[tmp + 4]);
		}

	double tmp = 0;

	//��� �� ��� �� ����
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //�Է��� --> ������ ��°�
		for (int j = 0; j < INPUT_LAYER_NODES; j++) {
			tmp += input[j] * Input_To_Hidden_Weight[j][i];
		}
		To_Hidden_Out[0][i] = sigmoid(tmp);
		tmp = 0;
	}

	for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) { //������ --> ������ ��°�
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
				tmp += To_Hidden_Out[i][k] * Hidden_to_Hidden_Weight[i][k][j];
			}
			To_Hidden_Out[i + 1][j] = sigmoid(tmp);
			tmp = 0;
		}
	}

	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //������ --> ����� ��°�
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			tmp += To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][j] * Hidden_To_output_Weight[j][i];
		}
		Hidden_To_output_Out[i] = sigmoid(tmp);
		printf("%f  ", Hidden_To_output_Out[i]);
		tmp = 0;
	}
	printf("\n");

	//����� �ִ� ���ϱ�
	double tmp_1 = Hidden_To_output_Out[0];
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 < Hidden_To_output_Out[i])
			tmp_1 = Hidden_To_output_Out[i];
	}

	int Pattern_no; 

	//�ִ��� 1,�������� 0���� ��ȯ�Ͽ� ���
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 / Hidden_To_output_Out[i] == 1) {
			Hidden_To_output_Out[i] = 1;
			Pattern_no = i;
		}
		else
			Hidden_To_output_Out[i] = 0;
		printf("%d ", (int)Hidden_To_output_Out[i]);
	}

	printf("\n�Է��� ���ϰ� ��µ� ����\n");
	
		for (int i = 0; i < sqrt(INPUT_LAYER_NODES); i++) {
			for (int j = 0; j < sqrt(INPUT_LAYER_NODES); j++) {
				int k = ((int)sqrt(INPUT_LAYER_NODES) * i) + j;
				if (input[k] == 1)
					printf("�� ");
				else
					printf("�� ");
			}

			if (i == (int)sqrt(INPUT_LAYER_NODES)/2)
				printf("     ---->>     ");
			else
				printf("                ");

			for (int j = 0; j < sqrt(INPUT_LAYER_NODES); j++) {
				int k = ((int)sqrt(INPUT_LAYER_NODES) * i) + j;
				if (inPutDataSet[Pattern_no][k] == 1)
					printf("�� ");
				else
					printf("�� ");
			}
			printf("\n");
		}
	}
	return 0;
}