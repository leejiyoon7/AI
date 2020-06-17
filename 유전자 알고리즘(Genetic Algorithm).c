#include <stdio.h>
#include <math.h>
#include <time.h>

#define PATTERN 100 //������ ��
#define PATTERN_LENGTH 15 //������ ����
#define PATTERN_MAXINT pow(2.0, (double)PATTERN_LENGTH) //���ϱ��̿� ���� �ִ�
#define Mutation_Rate 0.05 //Mutation Rate ��

int binary_genome[PATTERN][PATTERN_LENGTH]; //������ ��
int eval[PATTERN]; //Evaluation ��
int genome_tmp[PATTERN][PATTERN_LENGTH]; //�ӽ� ������ ��
int tmp_to_10[PATTERN]; //10���� ��ȯ�� ���� �ӽù迭
int count = 0;
double select_probability[PATTERN]; //Select Probability ��
double accumulated_probability[PATTERN]; //Accumulated Probability ��
double random_num[PATTERN]; //Random number ��

//fitness �Լ� ����
int fitness(int x) {
    int return_value;

    return_value = 10 * x - 500;

    return return_value;
}


int main()
{
    //�ʱ� ������ ����
    srand(time(NULL));
    for (int i = 0; i < PATTERN; i++) {
        int tmp;
        int count = 0;
        tmp = rand() % (int)PATTERN_MAXINT - 1; //�ִ� �ȿ��� ������ ����

        //�������� ��ȯ�Ͽ� ����
        for (int j = PATTERN_LENGTH - 1; j > -1; j--) {
            int a;
            a = (tmp >> j) & 1;
            binary_genome[i][count] = a;
            count++;
        }
    }

    //�ʱ� ������ ���
    for (int i = 0; i < PATTERN; i++) {
        printf("v[%d] = ( ", i);
        for (int j = 0; j < PATTERN_LENGTH; j++) {
            printf("%d", binary_genome[i][j]);
        }
        printf(" )\n");
    }
    printf("\n");

    while(count <= 90) {

    //Evaluation �� ���
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

    //Total Fitness ���ϱ�
    int Total_Fitness = 0;
    for (int i = 0; i < PATTERN; i++) {
        Total_Fitness += eval[i];
    }

    //Select Probability �� ���ϱ�
    for (int i = 0; i < PATTERN; i++) {
        select_probability[i] = (double)eval[i] / (double)Total_Fitness;
    }

    //Accumulated Probability �� ���ϱ�
    double accumulated_tmp = 0;
    for (int i = 0; i < PATTERN; i++) {
        accumulated_tmp += select_probability[i];
        accumulated_probability[i] = accumulated_tmp;
    }

    //������ ����
    for (int i = 0; i < PATTERN; i++)
        random_num[i] = 0.0001 * (rand() % 10000);

    //�����ѹ��� �̿��� ����
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

    //ũ�ν�������ų ������ ����
    int a = rand() % PATTERN;
    int b = rand() % PATTERN;

    //�������� ���� ����
    int c = 1 + (rand() % PATTERN_LENGTH - 1);
    printf("%d, %d, %d \n", a, b, c);

    //Crossover ��ȯ �� ����
    for (int i = c; i < PATTERN_LENGTH; i++) {
        int tmp;
        tmp = genome_tmp[a][i];
        genome_tmp[a][i] = genome_tmp[b][i];
        genome_tmp[b][i] = tmp;
    }

    //������ ����
    for (int i = 0; i < PATTERN; i++)
        random_num[i] = 0.0001 * (rand() % 10000);

    //Mutation Rate (0�� 1 �ٲ�)
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

    //tmp���Ͽ��� ����
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

    //10������ ��ȯ
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

    //���� ū �� ã��
    int Maxium_num = tmp_to_10[0];
    for (int i = 0; i < PATTERN; i++) {
        if (Maxium_num < tmp_to_10[i])
            Maxium_num = tmp_to_10[i];
    }

    //���� ū ���� ����ã��
    count = 0;
    for (int i = 0; i < PATTERN; i++) {
        if (Maxium_num == tmp_to_10[i])
            count++;
    }
    printf("���� ū ���� ������ %d�Դϴ�. \n", count);

}

    return 0;
}