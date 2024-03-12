#include <stdio.h>
int two2ten(int bin)    //10진수 형태로 입력받은 8비트 2진수를 10진수로 변환하는 함수
{
    int copy = bin;
    int n = 128;
    int temp = 10000000;
    int realBin = 0;
    int flag = 0;
    if (copy / 10000000)
    {
        flag = 1;
        copy -= 1;
        for (int i = 10; i <= 10000000; i *= 10)
            if ((copy % i) / (i / 10) == 9)
            {
                copy -= (i / 10) * 8;
            }
        copy = copy % 100000000;

        while (temp != 0)
        {
            if (copy / temp == 0)
                realBin += temp;
            copy %= temp;
            temp /= 10;
        }
        temp = 10000000;
        copy = realBin;
        realBin = 0;
    }
    while (copy > 0)
    {
        if (copy / temp)
        {
            realBin += n;
        }
        copy %= temp;
        temp /= 10;
        n /= 2;
    }
    if (flag)
        return -realBin;
    else    return realBin;
}
int twoPlus(int n1, int n2) //8비트 2진수 비트연산(더하기)
{
    int result = 0;
    int rest;
    for (int i = 10; i <= 100000000; i *= 10)
    {
        rest = result % (i / 10);
        if (((n1 % i) / (i / 10) + (n2 % i) / (i / 10) + (result % i) / (i / 10)) == 3)
            result = (i + i / 10);
        else if (((n1 % i) / (i / 10) + (n2 % i) / (i / 10) + (result % i) / (i / 10)) == 2)
            result = i;
        else
            result = ((n1 % i) / (i / 10) + (n2 % i) / (i / 10) + (result % i) / (i / 10)) * (i / 10);
        result += rest;
    }
    return result;
}
int ten2two(int ten)   //10진수를 입력받아 8비트 2진수를 1비트씩 출력하는 함수
{
    int result = 0;
    int cnt = 10000000;
    if (ten > 0)
    {
        for (int i = 128; i > 0; i /= 2)
        {
            result += (ten / i)* cnt;
            ten %= i;
            cnt /= 10;
        }
    }
    else if (ten < 0)
    {
        ten = -ten;
        ten -= 1;
        for (int i = 128; i > 0; i /= 2)
        {
            if (ten / i == 0)
                result += cnt;
            ten %= i;
            cnt /= 10;
        }
    }
    return result;
}
int main(void)
{
    int select;
    int num1, num2;
    printf("1. 이진수 변환기    2. 이진수 덧셈기    3. 이진수 뺄셈기\n\n\n");
    printf("번호를 선택하세요 : ");
    scanf("%d", &select);
    switch (select)
    {
    case 1:
    {
        printf("8비트 이진수를 입력하세요 : ");
        scanf("%d", &num1);
        printf("십진수로 %d입니다.\n", two2ten(num1));
        break;
    }
    case 2:
    {
        int cnt = 0;
        printf("첫 번째 8비트 이진수를 입력하세요 : ");
        scanf("%d", &num1);
        printf("두 번째 8비트 이진수를 입력하세요 : ");
        scanf("%d", &num2);
        printf("두 이진수의 합은 ");
        for (int i = 10000000; i >= 1; i /= 10)
        {
            if ((twoPlus(num1, num2) % 100000000) / i)
                break;
            else cnt++;
        }
        if (twoPlus(num1, num2) % 100000000 == 0)
            cnt--;
        for (int i = 0; i < cnt; i++)
            printf("0");
        printf("%d이고, 십진수로 %d입니다.\n", twoPlus(num1, num2) % 100000000, two2ten(twoPlus(num1, num2) % 100000000));
        break;
    }
    case 3:
    {
        int cnt = 0;
        printf("첫 번째 8비트 이진수를 입력하세요 : ");
        scanf("%d", &num1);
        printf("두 번째 8비트 이진수를 입력하세요 : ");
        scanf("%d", &num2);
        printf("두 이진수의 차는 ");
        for (int i = 10000000; i >= 1; i /= 10)
        {
            if (ten2two(two2ten(num1) - two2ten(num2)) / i)
                break;
            else cnt++;
        }
        if (ten2two(two2ten(num1) - two2ten(num2)) == 0)
            cnt--;
        for (int i = 0; i < cnt; i++)
            printf("0");
        printf("%d이고 십진수로 %d입니다.\n", ten2two(two2ten(num1) - two2ten(num2)), two2ten(ten2two(two2ten(num1) - two2ten(num2))));
        break;
    }
    }
}