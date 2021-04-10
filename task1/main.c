#include <limits.h>
#include <math.h>
//#---include <iostream> //for c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* this code implements three tasks:
 Task 1:
 input: array legnth - n ,array of n integers.
 the program finds it's Max Pooling with stride=1 and size = 1 to n (result of n arrays)
 output: sum of minimun numbers, (each max pooling result return an array, each array return a minimum number)
 Task 2:
 The sum of all jobs performed reduced by the minimum job existed when removed from queue
 Task 3:
 */

int find_maximum(int a[], int n, int s)// s = the SubArray starting index , n = SubArray ending index+1, O(n-s)
{
    int c, index = s;

    for (c = s+1; c < n; c++)
        if (a[c] > a[index])
            index = c;

    return index;
}
int find_minimum(int a[], int n, int s)// s = the SubArray starting index , n = SubArray ending index+1, O(n-s)
{
    int c, index = 0;

    for (c = s+1; c < n; c++)
        if (a[c] < a[index])
            index = c;

    return index;
}
void question_1()
{
    int ans = 0, n,temp_index=0,starting_SubArray,ending_index,max_index,min_index;
    int* arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        //scanf("%d", &arr[i]);
        arr[i] = 1;
    }
    //program time settings
    clock_t start, end;
    double time_taken;
    start = clock();
    //
    // i+1= filter size, j= filtered_arr index, s= starting SubArray index
    int* filtered_arr;
    temp_index = 0;
    for (int c = 1; c < n; c++) {  //find maximum
        if (arr[c] > arr[temp_index])
            temp_index = c;
    }
    ans = arr[temp_index];// filter size = 1
    //measure time
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n", time_taken);
    for (int i = 1; i < n; i++) {
        filtered_arr = (int*)malloc(sizeof(int) * (n - i));
        for (int s = 0; s < (n - i); s++) {// s = staring index of subarray
            temp_index = s;
            ending_index = s + i;
            for (int c = s + 1; c < ending_index + 1; c++) {  //find maximum
                if (arr[c] > arr[temp_index])
                    temp_index = c;
            }
            filtered_arr[s] = arr[temp_index];// Max Pooling
        }
        temp_index = 0;
        for (int c = 1; c < n - i; c++) {// find minimum
            if (filtered_arr[c] < filtered_arr[temp_index])
                temp_index = c;
        }
        ans = ans + filtered_arr[temp_index];
        free(filtered_arr);
    }
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

    unsigned long long ans = 0;
    int n, q_index = 0, min_index=0;// q_index is the index for the next spot available in queue 
    int removal_q_index = 0,current_job;// removal_q_index is the starting index of the current queue 
    scanf("%d", &n);
    int* queue;
    //program time settings
    clock_t start, end;
    double time_taken;
    start = clock();
    queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < 4000000; i++) {
        current_job = i % 100;
        if (current_job > 0) { // add to queue
            queue[q_index] = current_job;
            if ( queue[q_index]<=queue[min_index]){
                min_index = q_index;
            }
            q_index += 1;
        }
        else if ((current_job == 0) && (q_index>removal_q_index)){ // remove from queue
            ans += queue[removal_q_index] - queue[min_index];
            removal_q_index += 1;
            if (min_index <= (removal_q_index-1)) {
                min_index = find_minimum(queue, q_index, removal_q_index);
            }
   
        }
    }
    for (int i = 0; i < 1000000; i++) {
        current_job = 0;
        if (current_job > 0) { // add to queue
            queue[q_index] = current_job;
            if (queue[q_index] <= queue[min_index]) {
                min_index = q_index;
            }
            q_index += 1;
        }
        else if ((current_job == 0) && (q_index > removal_q_index)) { // remove from queue
            ans += queue[removal_q_index] - queue[min_index];
            removal_q_index += 1;
            if (min_index <= (removal_q_index - 1)) {
                min_index = find_minimum(queue, q_index, removal_q_index);
            }

        }
    }
    printf("%llu\n", ans);
    //measure time
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n", time_taken);
    //
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
    printf("enter question number\n");
    scanf("%d", &question);
    if (question == 1)
        question_1();
    else if (question == 2)
        question_2();
    else
        question_3();
    return 0;
}
