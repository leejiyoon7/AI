#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PATTERN 10 //학습할 패턴의 수

#define INPUT_LAYER_NODES 25 //입력층 레이어
#define HIDDEN_LAYER_NODES 12 //은닉층 레이어
#define OUTPUT_LAYER_NODES PATTERN //출력층 레이어

#define NO_EPOCH 3000//학습횟수
#define ETA 0.2 //학습률

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
		0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1}
};

int outPutDataSet[PATTERN][OUTPUT_LAYER_NODES] = { //출력되어야하는 값
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄱ
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //ㄴ
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //ㄷ
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //ㄹ
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //ㅁ
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //ㅂ
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //ㅅ
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //ㅇ
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //ㅈ
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}  //ㅊ
};

//시그모이드 함수
//상수를 0과1사이의 확률값으로 변환
double sigmoid(double x) {
	double exp_value;
	double return_value;

	exp_value = exp((double)-x);

	return_value = 1.0 / (1.0 + exp_value);

	return return_value;
}

int main() {
	srand(time(NULL));
	//가중치 선언
	double Input_To_Hidden_Weight[INPUT_LAYER_NODES][HIDDEN_LAYER_NODES];
	double Hidden_To_output_Weight[HIDDEN_LAYER_NODES][OUTPUT_LAYER_NODES];

	//줄력값 저장부 선언
	double Input_To_Hidden_Out[HIDDEN_LAYER_NODES];
	double Hidden_To_output_Out[OUTPUT_LAYER_NODES];

	//오차 구하기
	double Error_Score[OUTPUT_LAYER_NODES];
	double Error_Total = 0;

	//델타값 선언
	double Output_Delta[OUTPUT_LAYER_NODES];
	double Hidden_delta[HIDDEN_LAYER_NODES];

	//입력값 선언
	int input[INPUT_LAYER_NODES];

	//연결가중치 0.01~0.99사이의 랜덤값으로 초기화
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

	for (int a = 0; a < NO_EPOCH; a++) { //epoch만큼 반복
		for (int z = 0; z < PATTERN; z++) { //패턴 수 만큼 반복
			double tmp = 0;

			//출력 값 계산 후 저장
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //입력층 --> 은닉층 출력값
				for (int j = 0; j < INPUT_LAYER_NODES; j++) {
					tmp += inPutDataSet[z][j] * Input_To_Hidden_Weight[j][i];
				}
				Input_To_Hidden_Out[i] = sigmoid(tmp);
				tmp = 0;
			}
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //은닉층 --> 출력층 출력값
				for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
					tmp += Input_To_Hidden_Out[j] * Hidden_To_output_Weight[j][i];
				}
				Hidden_To_output_Out[i] = sigmoid(tmp);
				printf("%f  ", Hidden_To_output_Out[i]);
				tmp = 0;
			}
			printf("\n");

			//오차 계산
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
				Error_Score[i] = 0.5 * (outPutDataSet[z][i] - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
				Error_Total += Error_Score[i];
			}

			//오차값 출력
			printf("%f\n", Error_Total);
			Error_Total = 0;

			//델타값 계산
			for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //출력층 오차계산
				Output_Delta[i] = Hidden_To_output_Out[i] * (1 - Hidden_To_output_Out[i]) * (outPutDataSet[z][i] - Hidden_To_output_Out[i]);
			}
			for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //은닉층 오차계산
				tmp = 0;
				for (int j = 0; j < OUTPUT_LAYER_NODES; j++) {
					tmp += Output_Delta[j] * Hidden_To_output_Weight[i][j];
				}
				Hidden_delta[i] = Input_To_Hidden_Out[i] * (1 - Input_To_Hidden_Out[i]) * tmp;
				tmp = 0;
			}

			//가중치 수정
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

	//가중치 출력
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

	//입력받아서 저장하기
	printf("\n학습완료! 입력값을 넣어보세요.\n");
	for (int i = 0; i < INPUT_LAYER_NODES; i++) {
		printf("%d번째에 들어갈 수: ", i);
		scanf_s("%d", &input[i]);
	}

	double tmp = 0;

	//출력 값 계산 후 저장
	for (int i = 0; i < HIDDEN_LAYER_NODES; i++) { //입력층 --> 은닉층 출력값
		for (int j = 0; j < INPUT_LAYER_NODES; j++) {
			tmp += input[j] * Input_To_Hidden_Weight[j][i];
		}
		Input_To_Hidden_Out[i] = sigmoid(tmp);
		tmp = 0;
	}
	printf("\n");
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) { //은닉층 --> 출력층 출력값
		for (int j = 0; j < HIDDEN_LAYER_NODES; j++) {
			tmp += Input_To_Hidden_Out[j] * Hidden_To_output_Weight[j][i];
		}
		Hidden_To_output_Out[i] = sigmoid(tmp);
		printf("%f ", Hidden_To_output_Out[i]);
		tmp = 0;
	}
	printf("\n");

	//결과값 최댓값 구하기
	double tmp_1 = Hidden_To_output_Out[0];
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 < Hidden_To_output_Out[i])
			tmp_1 = Hidden_To_output_Out[i];
	}

	//최댓값은 1,나머지는 0으로 변환하여 출력
	for (int i = 0; i < OUTPUT_LAYER_NODES; i++) {
		if (tmp_1 / Hidden_To_output_Out[i] == 1)
			Hidden_To_output_Out[i] = 1;
		else
			Hidden_To_output_Out[i] = 0;
		printf("%d ", (int)Hidden_To_output_Out[i]);
	}
	return 0;
}