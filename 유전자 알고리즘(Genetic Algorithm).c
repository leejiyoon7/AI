#include <stdio.h>
#include <math.h>
#include <time.h>

#define PATTERN 100 //패턴의 수
#define PATTERN_LENGTH 15 //패턴의 길이
#define PATTERN_MAXINT pow(2.0, (double)PATTERN_LENGTH) //패턴길이에 따른 최댓값
#define Mutation_Rate 0.05 //Mutation Rate 값

int binary_genome[PATTERN][PATTERN_LENGTH]; //유전자 값
int eval[PATTERN]; //Evaluation 값
int genome_tmp[PATTERN][PATTERN_LENGTH]; //임시 유전자 값
int tmp_to_10[PATTERN]; //10진수 변환을 위한 임시배열
int count = 0;
double select_probability[PATTERN]; //Select Probability 값
double accumulated_probability[PATTERN]; //Accumulated Probability 값
double random_num[PATTERN]; //Random number 값

//fitness 함수 선언
int fitness(int x) {
    int return_value;

    return_value = 10 * x - 500;

    return return_value;
}


int main()
{
    //초기 유전자 생성
    srand(time(NULL));
    for (int i = 0; i < PATTERN; i++) {
        int tmp;
        int count = 0;
        tmp = rand() % (int)PATTERN_MAXINT - 1; //최댓값 안에서 랜덤값 생성

        //이진수로 변환하여 저장
        for (int j = PATTERN_LENGTH - 1; j > -1; j--) {
            int a;
            a = (tmp >> j) & 1;
            binary_genome[i][count] = a;
            count++;
        }
    }

    //초기 유전자 출력
    for (int i = 0; i < PATTERN; i++) {
        printf("v[%d] = ( ", i);
        for (int j = 0; j < PATTERN_LENGTH; j++) {
            printf("%d", binary_genome[i][j]);
        }
        printf(" )\n");
    }
    printf("\n");

    while(count <= 90) {

    //Evaluation 값 계산
    for (int i = 0; i < PATTERN; i++) {
        int tmp = 0;
        int weight = 1;
        for (int j = PATTERN_LENGTH - 1; j > -1; j--) {
            if (binary_genome[i][j] == 1)
                tmp += weight;
            weight = weight * 2;
        }

        if (fitness(tmp) < 0)
            eval[i] = fitness(tmp) * (-1);
        else
            eval[i] = fitness(tmp);
    }

    //Total Fitness 구하기
    int Total_Fitness = 0;
    for (int i = 0; i < PATTERN; i++) {
        Total_Fitness += eval[i];
    }

    //Select Probability 값 구하기
    for (int i = 0; i < PATTERN; i++) {
        select_probability[i] = (double)eval[i] / (double)Total_Fitness;
    }

    //Accumulated Probability 값 구하기
    double accumulated_tmp = 0;
    for (int i = 0; i < PATTERN; i++) {
        accumulated_tmp += select_probability[i];
        accumulated_probability[i] = accumulated_tmp;
    }

    //랜덤값 생성
    for (int i = 0; i < PATTERN; i++)
        random_num[i] = 0.0001 * (rand() % 10000);

    //랜덤넘버를 이용한 변경
    for (int i = 0; i < PATTERN; i++) {
        for (int j = 0; j < PATTERN; j++) {
            if (random_num[i] > accumulated_probability[j] && random_num[i] <= accumulated_probability[j + 1]) {
                for (int k = 0; k < PATTERN_LENGTH; k++)
                    genome_tmp[i][k] = binary_genome[j + 1][k];
            }
            else if (random_num[i] < accumulated_probability[0])
                for (int k = 0; k < PATTERN_LENGTH; k++)
                    genome_tmp[i][k] = binary_genome[0][k];
        }
    }

    //크로스오버시킬 유전자 선택
    int a = rand() % PATTERN;
    int b = rand() % PATTERN;

    //교차지점 랜덤 선택
    int c = 1 + (rand() % PATTERN_LENGTH - 1);
    printf("%d, %d, %d \n", a, b, c);

    //Crossover 변환 후 저장
    for (int i = c; i < PATTERN_LENGTH; i++) {
        int tmp;
        tmp = genome_tmp[a][i];
        genome_tmp[a][i] = genome_tmp[b][i];
        genome_tmp[b][i] = tmp;
    }

    //랜덤값 생성
    for (int i = 0; i < PATTERN; i++)
        random_num[i] = 0.0001 * (rand() % 10000);

    //Mutation Rate (0과 1 바뀜)
    for (int i = 0; i < PATTERN; i++) {
        if (random_num[i] < Mutation_Rate) {
            for (int j = 0; j < PATTERN_LENGTH; j++) {
                if (genome_tmp[i][j] == 1)
                    genome_tmp[i][j] = 0;
                else
                    genome_tmp[i][j] = 1;
            }
        }
    }

    //tmp파일에서 복제
    for (int i = 0; i < PATTERN; i++) {
        for (int j = 0; j < PATTERN_LENGTH; j++) {
            binary_genome[i][j] = genome_tmp[i][j];
        }
    }

    for (int i = 0; i < PATTERN; i++) {
        printf("v[%d] = ( ", i);
        for (int j = 0; j < PATTERN_LENGTH; j++) {
            printf("%d", binary_genome[i][j]);
        }
        printf(" )\n");
    }
    printf("\n");

    //10진수로 변환
    for (int i = 0; i < PATTERN; i++) {
        int tmp = 0;
        int weight = 1;
        for (int j = PATTERN_LENGTH - 1; j > -1; j--) {
            if (binary_genome[i][j] == 1)
                tmp += weight;
            weight = weight * 2;
        }
        tmp_to_10[i] = tmp;
    }

    //가장 큰 수 찾기
    int Maxium_num = tmp_to_10[0];
    for (int i = 0; i < PATTERN; i++) {
        if (Maxium_num < tmp_to_10[i])
            Maxium_num = tmp_to_10[i];
    }

    //가장 큰 수의 개수찾기
    count = 0;
    for (int i = 0; i < PATTERN; i++) {
        if (Maxium_num == tmp_to_10[i])
            count++;
    }
    printf("가장 큰 수의 개수는 %d입니다. \n", count);

}

    return 0;
}