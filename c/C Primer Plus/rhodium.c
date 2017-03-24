#include <stdio.h>
int main (void)
{
	float weight, value;
	printf ("Are you worth your weight in rhodium?\n");
	printf ("Let's check it out.\n");
	printf ("Please enter your weight in pounds: ");
	//从用户处获取
	scanf ("%f", &weight);
	//假设铑为每蛊司770美元
	//14.5833把常衡制的英镑转换为金衡制的蛊司
	value = 770 * weight * 14.5833;
	printf ("Your weight in rhodium is worth $%0.2f.\n", value);
	printf ("eat more to maintain your value.\n");
	return 0;
}

