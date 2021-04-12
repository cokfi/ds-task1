#include <limits.h>
#include <math.h>
//#---include <iostream> //for c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void question_1() {
    int ans = 0, n, minimum_of_maxP, temp_index, global_max_index;
    int* arr;
    int* bigger_right;
    int* bigger_left;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    bigger_right = (int*)malloc(sizeof(int) * (n + 1));
    bigger_left = (int*)malloc(sizeof(int) * (n + 1));

    //for (int i = 0; i < n; i++)
    //    scanf("%d", &arr[i]);
    for (int i = 0; i < n; i++)
        arr[i] = 1000;
    //program time settings
    clock_t start, end;
    double time_taken;
    start = clock();
    //

    int next, i, j;
    for (i = 0; i < n; i++) { // O(n^2)
        bigger_right[i] = n; // init values- no bigger on left
        for (j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                bigger_right[i] = j;
                break;
            }
        }
    }
    for (i = n - 1; i >= 0; i--) { // O(n^2)
        bigger_left[i] = -1; // init values- no bigger on right
        for (j = i - 1; j >= 0; j--) {
            if (arr[i] < arr[j]) {
                bigger_right[i] = j;
                break;
            }
        }
    }
    // Create and initialize answer array
    int* min_of_MaxPooling;
    int filter_size;
    min_of_MaxPooling = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; i++)
        min_of_MaxPooling[i] = n;// a cell for each filter size , cell 0 is unused
    for (int i = 0; i < n; i++) {
        filter_size = bigger_right[i] - bigger_left[i] - 1; // biggest filter size that will return arr[i] 
        if (min_of_MaxPooling[filter_size] > arr[i])
            min_of_MaxPooling[filter_size] = arr[i]; // save the min of all max pooling of the same filter size
    }
    for (int i = n - 1; i >= 1; i--) {
        if (min_of_MaxPooling[i] > min_of_MaxPooling[i + 1])
            min_of_MaxPooling[i] = min_of_MaxPooling[i + 1];//fill empty cells,smaller filter size will have smaller/equal value
    }
    for (int i = 1; i <= n; i++) {
        ans = ans + min_of_MaxPooling[i];
    }
    printf("%d\n", ans);
}
/*
int main(int argc, char** argv)
{
    int question;
    printf("enter question number\n");
    scanf("%d", &question);
    if (question == 1)
        question_1();
    /*        else if (question == 2)
                question_2();
            else
                question_3();*/
/*    return 0;
}*/