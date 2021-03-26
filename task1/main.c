#include <limits.h>
#include <math.h>
//#---include <iostream> //for c++
#include <stdio.h>
#include <stdlib.h>



void question_1()
{
    int ans = 1, n;
    int* arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    ///////  Enter solution here ///////

    ////////////////////////////////////
    printf("%d\n", ans);
    free(arr);
}


void question_2()
{

    unsigned long long ans = 2;
    int n;
    scanf("%d", &n);
    ///////  Enter solution here ///////

    ////////////////////////////////////
    printf("%llu\n", ans);
}

void question_3()
{
    int ans = 3;
    int string_length;
    char string[100] = { 0 };
    scanf("%d", &string_length);
    scanf("%s", string);
    ///////  Enter solution here ///////

    ////////////////////////////////////
    printf("%d\n", ans);
}


int main(int argc, char** argv)
{
    int question;
    scanf("%d", &question);
    if (question == 1)
        question_1();
    else if (question == 2)
        question_2();
    else
        question_3();
    return 0;
}
