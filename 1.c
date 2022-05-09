#include <stdio.h>
#include<math.h>
#define esp 0.00001
#define pi 3.14159

/*
函数功能: 计算正弦函数值
函数入口参数: 浮点型x, 存储要计算正弦的值
函数返回值: 正弦函数值
*/

float MySin(float x)
{
    float term = x;
    float sum = x;
    float n = 1;
    while(fabs(term) > esp)
    {
        term = -term * x * x / ((n + 1) * (n + 2));
        n += 2;
        sum += term;
    } 
    return sum;
}


int main()
{
    float x1 = pi / 4;
    float x2 = pi / 2;
    float x3 = pi / 4 * 3;
    
    float num1 = MySin(x1);
    float num2 = MySin(x2);
    float num3 = MySin(x3);

    printf("sin(Π/4) = %f\n",num1);
    printf("sin(Π/2) = %f\n",num2);
    printf("sin(3Π/4) = %f\n",num3);

    return 0;
}
