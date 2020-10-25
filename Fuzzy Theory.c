#include <stdlib.h>
#include <stdio.h>

int number_of_cars, little, normal, many;
int average_speed, little2, normal2, many2;
int score[9], Medium_value[9];
int numerator, denominator, second;

int main(void) {
	printf("ÀÌ¸§: 201636042 ÀÌÁöÀ±\n");
	printf("Á¦¸ñ: Traffic Light\n");
	printf("Â÷·®ÀÇ ¼ö¿Í Æò±Õ¼Óµµ¸¦ ÀÔ·ÂÇÏ¼¼¿ä.\n");
	printf("1. Â÷·®ÀÇ ¼ö (0-30) : ");
	scanf_s("%d", &number_of_cars);
	printf("2. Æò±Õ ¼Óµµ (0-60) : ");
	scanf_s("%d", &average_speed);

	printf("number_of_cars : %d unit\n", number_of_cars);
	printf("average_speed : %d km/h\n", average_speed);

	//ÆÛÁöÈ­ Â÷·®ÀÇ ¾ç
	if (number_of_cars <= 7) {
		little = 100;
		normal = 0;
		many = 0;
		printf("\nÀûÀº Â÷·® : %d%%", little);
	}
	else if (number_of_cars > 7 && number_of_cars <= 13) {
		little = 100 - ((number_of_cars - 7) * 10);
		normal = ((number_of_cars - 7) * 10);
		many = 0;
		printf("\nÀûÀº Â÷·® : %d%%", little);
		printf("\nÁß°£ Â÷·® : %d%%", normal);
	}
	else if (number_of_cars > 13 && number_of_cars <= 17) {
		little = 0;
		normal = 100;
		many = 0;
		printf("\nÁß°£ Â÷·® : %d%%", normal);
	}
	else if (number_of_cars > 17 && number_of_cars <= 23) {
		little = 0;
		normal = 100 - ((number_of_cars - 17) * 10);
		many = ((number_of_cars - 17) * 10);
		printf("\nÁß°£ Â÷·® : %d%%", normal);
		printf("\n¸¹Àº Â÷·® : %d%%", many);
	}
	else {
		little = 0;
		normal = 0;
		many = 100;
		printf("\n¸¹Àº Â÷·® : %d%%", many);
	}

	//ÆÛÁöÈ­  Æò±Õ¼Óµµ
	if (average_speed <= 15) {
		little2 = 100;
		normal2 = 0;
		many2 = 0;
		printf("\nÀûÀº ¼Óµµ : %d%%", little2);
	}
	else if (average_speed > 15 && average_speed <= 25) {
		little2 = 100 - ((average_speed - 15) * 10);
		normal2 = ((average_speed - 15) * 10);
		many2 = 0;
		printf("\nÀûÀº ¼Óµµ : %d%%", little2);
		printf("\nº¸Åë ¼Óµµ : %d%%", normal2);
	}
	else if (average_speed > 25 && average_speed <= 35) {
		little2 = 0;
		normal2 = 100;
		many2 = 0;
		printf("\nº¸Åë ¼Óµµ : %d%%", normal2);
	} 
	else if (average_speed > 35 && average_speed <= 45) {
		little2 = 0;
		normal2 = 100 - ((average_speed - 35) * 10);
		many2 = ((average_speed - 35) * 10);
		printf("\nº¸Åë ¼Óµµ : %d%%", normal2);
		printf("\nºü¸¥ ¼Óµµ : %d%%", many2);
	}
	else {
		little2 = 0;
		normal2 = 0;
		many2 = 100;
		printf("\nºü¸¥ ¼Óµµ : %d%%", many2);
	}

	//rule based
	if (little < little2) {
		score[0] = little;
		Medium_value[0] = 30;
	}
	else
		score[0] = little2;
	Medium_value[0] = 30;

	if (little < normal2){
		score[1] = little;
		Medium_value[1] = 30;
	}
	else{
		score[1] = normal2;
		Medium_value[1] = 30;
	}

	if (little < many2){
		score[2] = little;
		Medium_value[2] = 30;
	}
	else{
		score[2] = many2;
		Medium_value[2] = 30;
	}

	if (normal < little2){
		score[3] = normal;
		Medium_value[3] = 60;
	}
	else{
		score[3] = little2;
		Medium_value[3] = 60;
	}

	if (normal < normal2){
		score[4] = normal;
		Medium_value[4] = 60;
	}
	else{
		score[4] = normal2;
		Medium_value[4] = 60;
	}

	if (normal < many2){
		score[5] = normal;
		Medium_value[5] = 60;
	}
	else{
		score[5] = many2;
		Medium_value[5] = 60;
	}

	if (many < little2){
		score[6] = many;
		Medium_value[6] = 90;
	}
	else{
		score[6] = little2;
		Medium_value[6] = 90;
	}
	if (many < normal2)
	{
		score[7] = many; 
		Medium_value[7] = 90;
	}
	else{
		score[7] = normal2; 
		Medium_value[7] = 90;
	}

	if (many < many2){
		score[8] = many; 
		Medium_value[8] = 90;
	}
	else{
		score[8] = many2; 
		Medium_value[8] = 90;
	}

	
	numerator = score[0] + score[1] + score[2] + score[3] + score[4] + score[5] + score[6] + score[7] + score[8];
	denominator = 
		(score[0] * Medium_value[0]) + (score[1] * Medium_value[1]) + (score[2] * Medium_value[2]) + 
		(score[3] * Medium_value[3]) + (score[4] * Medium_value[4]) + (score[5] * Medium_value[5]) + 
		(score[6] * Medium_value[6]) + (score[7] * Medium_value[7]) + (score[8] * Medium_value[8]);


	if (numerator == 0)
	{
		second = 0;
		printf("\n³ì»öºÒÀÌ %dÃÊµ¿¾È ÄÑÁý´Ï´Ù.\n", second);
	}
	else
	{
		second = denominator / numerator;
		printf("\n³ì»öºÒÀÌ %dÃÊµ¿¾È ÄÑÁý´Ï´Ù.\n\n", second);
	}

	return 0;
}
