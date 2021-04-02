#include <limits.h>
#include <math.h>
//#---include <iostream> //for c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// this code implements three tasks:
// Task 1:
// input: array legnth - n ,array of n integers.
// the program finds it's Max Pooling with stride=1 and size = 1:n (result of n arrays)
// output: sum of minimun numbers, (each max pooling result return array, each array return a minimum number)
//Task 2:
//The sum of all jobs performed reduced by the minimum job existed when removed
// Task 3:

int find_maximum(int a[], int n, int s)// s = the SubArray starting index , n = SubArray ending index+1, O(n-s)
{
    int c, index = s;

    for (c = s+1; c < n; c++)
        if (a[c] > a[index])
            index = c;

    return index;
}
int find_minimum(int a[], int n, int s)//  n = array length, O(n)
{
    int c, index = 0;

    for (c = s+1; c < n; c++)
        if (a[c] < a[index])
            index = c;

    return index;
}
void question_1()
{
    int ans = 0, n;
    int* arr;
    scanf_s("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf_s("%d", &arr[i]);
    //program time
    clock_t start, end;
    double time_taken;
    start = clock();
    //
    ///////  Enter solution here ///////
    // i+1= filter size, j= filtered_arr index, s= starting SubArray index
    int* filtered_arr;
    ans = arr[find_minimum(arr, n,0)];// filter size = 1
    for (int i = 1; i < n; i++) {
        filtered_arr = (int*)malloc(sizeof(int) * (n - i));
        for (int s = 0; s < (n - i); s++) {
            filtered_arr[s] = arr[find_maximum(arr, s + i + 1, s)];
        }
        ans = ans + filtered_arr[find_minimum(filtered_arr, n - i,0)];
        free(filtered_arr);
    }
    ////////////////////////////////////
    printf("%d\n", ans);
    free(arr);
    //measure time
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n", time_taken);
    //
}


void question_2()
{

    unsigned long long ans = 2;
    int n;
    scanf_s("%d", &n);
    ///////  Enter solution here ///////

    ////////////////////////////////////
    printf("%llu\n", ans);
}

void question_3()
{
    int ans = 3;
    int string_length;
    char string[100] = { 0 };
    scanf_s("%d", &string_length);
    scanf_s("%s", string);
    ///////  Enter solution here ///////

    ////////////////////////////////////
    printf("%d\n", ans);
}



int main(int argc, char** argv)
{
    int question;
    printf("enter question number\n");
    scanf_s("%d", &question);
    if (question == 1)
        question_1();
    else if (question == 2)
        question_2();
    else
        question_3();
    return 0;
}
