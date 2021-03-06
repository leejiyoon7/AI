#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PATTERN 14 //학습할 패턴의 수

#define INPUT_LAYER_NODES 25 //입력층 레이어
#define HIDDEN_LAYER_NODES 12 //은닉층 레이어
#define HIDDEN_LAYER_FLOOR 2 //은닉층 수
#define OUTPUT_LAYER_NODES PATTERN //출력층 레이어

#define NO_EPOCH 100000//학습횟수
#define ETA 0.9 //학습률

//가중치 선언
double Input_To_Hidden_Weight[INPUT_LAYER_NODES][HIDDEN_LAYER_NODES];
double Hidden_to_Hidden_Weight[HIDDEN_LAYER_FLOOR - 1][HIDDEN_LAYER_NODES][HIDDEN_LAYER_NODES];
double Hidden_To_output_Weight[HIDDEN_LAYER_NODES][OUTPUT_LAYER_NODES];

//줄력값 저장부 선언
double To_Hidden_Out[HIDDEN_LAYER_FLOOR][HIDDEN_LAYER_NODES];
double Hidden_To_output_Out[OUTPUT_LAYER_NODES];

//오차 구하기
double Error_Score[OUTPUT_LAYER_NODES];
double Error_Total = 0;

//델타값 선언
double Output_Delta[OUTPUT_LAYER_NODES];
double Hidden_delta[HIDDEN_LAYER_FLOOR][HIDDEN_LAYER_NODES];

//입력값 선언
int input[INPUT_LAYER_NODES];

int inPutDataSet[PATTERN][INPUT_LAYER_NODES] = { //입력 데이터
   { //ㄱ
	  1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
   { //ㄴ
	  1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   { //ㄷ
	  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   { //ㄹ
	  1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   { //ㅁ
	  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
   { //ㅂ
	  1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
   { //ㅅ
	  0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
   { //ㅇ
	  0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0},
   { //ㅈ
	  1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
   { //ㅊ
	  0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
   { //ㅋ
	  1, 1, 1, 1, 1, 0 ,0 ,0 ,0 ,1 ,1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
   { //ㅌ
	  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   { //ㅍ
	  1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
   { //ㅎ
	  0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}
};



int outPutDataSet[PATTERN][OUTPUT_LAYER_NODES] = { //출력되어야하는 값
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄱ
   {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄴ
   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄷ
   {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄹ
   {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㅁ
   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //ㅂ
   {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //ㅅ
   {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //ㅇ
   {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //ㅈ
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //ㅊ
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //ㅋ
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //ㅌ
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //ㅍ
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}  //ㅎ
};

//시그모이드 함수
//상수를 0과1사이의 값으로 변환
double sigmoid(double x) {
	double exp_value;
	double return_value;

	exp_value = exp((double)-x);

	return_value = 1.0 / (1.0 + exp_value);

	return return_value;
}


int main() {
	srand(time(NULL));

	//연결가중치 0.01~0.99사이의 랜덤값으로 초기화
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

	while (NO_EPOCH > a ) { //epoch만큼 반복
		for (int z = 0; z < PATTERN; z++) { //패턴 수 만큼 반복
			double tmp = 0;
			Error_Total = 0;

			//--------------출력 값 계산 후 저장-----------------
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //입력층 --> 은닉층 출력값
				for (int j = 0; j < INPUT_LAYER_NODES; j++) {
					tmp += inPutDataSet[z][j] * Input_To_Hidden_Weight[j][i];
				}
				To_Hidden_Out[0][i] = sigmoid(tmp);
				tmp = 0;
			}

			for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) { //은닉층 --> 은닉층 출력값
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
						tmp += To_Hidden_Out[i][k] * Hidden_to_Hidden_Weight[i][k][j];
					}
					To_Hidden_Out[i + 1][j] = sigmoid(tmp);
					tmp = 0;
				}
			}

			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //은닉층 --> 출력층 출력값
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					tmp += To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][j] * Hidden_To_output_Weight[j][i];
				}
				Hidden_To_output_Out[i] = sigmoid(tmp);
				tmp = 0;
			}

			//--------------오차 계산-------------------
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
				Error_Score[i] = 0.5 * (outPutDataSet[z][i] - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
				Error_Total += Error_Score[i];
			}

			//---------------델타값 계산------------------
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //출력층 오차계산
				Output_Delta[i] = Hidden_To_output_Out[i] * (1 - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
			}

			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //출력층 바로 아래 은닉층 오차계산
				tmp = 0;
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					tmp += Output_Delta[j] * Hidden_To_output_Weight[i][j];
				}
				Hidden_delta[0][i] = To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][i] * (1 - To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][i]) * tmp;
				tmp = 0;
			}
			for (int k = 1; k < HIDDEN_LAYER_FLOOR; k++) {
				for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //나머지 은닉층 오차계산
					tmp = 0;
					for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
						tmp += Hidden_delta[k-1][j]* Hidden_to_Hidden_Weight[HIDDEN_LAYER_FLOOR-1-k][i][j];
					}
					Hidden_delta[k][i] = To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1 - k][i] * (1 - To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1 - k][i]) * tmp;
					tmp = 0;
				}
			}

			//--------------가중치 수정-----------------
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
		//오차값 출력
		printf("%f\n", Error_Total);
		//오차값이 0.0007미만이면 학습종료
		if (Error_Total < 0.0007)
			break;

		printf("EPOCH:%d\n", a + 1);
		a++;
	}

	while (1) {
	//입력받아서 저장하기
	printf("\n학습완료! 입력값을 넣어보세요.\n");

	printf("%d개씩 입력하세요 (%d * %d) \n", (int)sqrt(INPUT_LAYER_NODES), (int)sqrt(INPUT_LAYER_NODES), (int)sqrt(INPUT_LAYER_NODES));
	for (int i = 0; i < sqrt(INPUT_LAYER_NODES); i++) {
		int tmp = i * (int)sqrt(INPUT_LAYER_NODES);
		scanf_s("%d %d %d %d %d", &input[tmp + 0], &input[tmp + 1], &input[tmp + 2], &input[tmp + 3], &input[tmp + 4]);
		}

	double tmp = 0;

	//출력 값 계산 후 저장
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //입력층 --> 은닉층 출력값
		for (int j = 0; j < INPUT_LAYER_NODES; j++) {
			tmp += input[j] * Input_To_Hidden_Weight[j][i];
		}
		To_Hidden_Out[0][i] = sigmoid(tmp);
		tmp = 0;
	}

	for (int i = 0; i < HIDDEN_LAYER_FLOOR - 1; i++) { //은닉층 --> 은닉층 출력값
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			for (int k = 0; k < HIDDEN_LAYER_NODES; k++) {
				tmp += To_Hidden_Out[i][k] * Hidden_to_Hidden_Weight[i][k][j];
			}
			To_Hidden_Out[i + 1][j] = sigmoid(tmp);
			tmp = 0;
		}
	}

	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //은닉층 --> 출력층 출력값
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			tmp += To_Hidden_Out[HIDDEN_LAYER_FLOOR - 1][j] * Hidden_To_output_Weight[j][i];
		}
		Hidden_To_output_Out[i] = sigmoid(tmp);
		printf("%f  ", Hidden_To_output_Out[i]);
		tmp = 0;
	}
	printf("\n");

	//결과값 최댓값 구하기
	double tmp_1 = Hidden_To_output_Out[0];
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 < Hidden_To_output_Out[i])
			tmp_1 = Hidden_To_output_Out[i];
	}

	int Pattern_no; 

	//최댓값은 1,나머지는 0으로 변환하여 출력
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 / Hidden_To_output_Out[i] == 1) {
			Hidden_To_output_Out[i] = 1;
			Pattern_no = i;
		}
		else
			Hidden_To_output_Out[i] = 0;
		printf("%d ", (int)Hidden_To_output_Out[i]);
	}

	printf("\n입력한 패턴과 출력된 패턴\n");
	
		for (int i = 0; i < sqrt(INPUT_LAYER_NODES); i++) {
			for (int j = 0; j < sqrt(INPUT_LAYER_NODES); j++) {
				int k = ((int)sqrt(INPUT_LAYER_NODES) * i) + j;
				if (input[k] == 1)
					printf("■ ");
				else
					printf("□ ");
			}

			if (i == (int)sqrt(INPUT_LAYER_NODES)/2)
				printf("     ---->>     ");
			else
				printf("                ");

			for (int j = 0; j < sqrt(INPUT_LAYER_NODES); j++) {
				int k = ((int)sqrt(INPUT_LAYER_NODES) * i) + j;
				if (inPutDataSet[Pattern_no][k] == 1)
					printf("■ ");
				else
					printf("□ ");
			}
			printf("\n");
		}
	}
	return 0;
}