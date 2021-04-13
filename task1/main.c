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
void question_1() {
    /* 3 steps algorithm:
    step1: Find indexes of next greater and previous greater for every element.
    step2: Find the smallest element for each filter size and save them in array(that won't fill the entire array).
    step 3: fill untouched filters and print the sum of step2's array.

    step 1 operations = a*n (the "while loop" inside "for loop" wont surpass O(n) because counter can add only 1(max) each "for" iteration) 
    step 2 operations = b*n ; step 3 operations = c*n
    #####hence, question_1() O notation = O(n)######
    */
    int ans = 0, n, minimum_of_maxP, i;
    int* arr;
    scanf_s("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    greater_right = (int*)malloc(sizeof(int) * (n + 1));
    greater_left = (int*)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n; i++)
        scanf_s("%d", &arr[i]);
    //program time settings
    clock_t start, end;
    double time_taken;
    start = clock();
    //
    // i+1= filter size, j= filtered_arr index, s= starting SubArray index
    int* filtered_arr;
    ans = arr[find_minimum(arr, n,0)];// filter size = 1
    for (int i = 1; i < n; i++) {
        filtered_arr = (int*)malloc(sizeof(int) * (n - i));
        for (int s = 0; s < (n - i); s++) {
            filtered_arr[s] = arr[find_maximum(arr, s + i + 1, s)];// Max Pooling
        }
        ans = ans + filtered_arr[find_minimum(filtered_arr, n - i,0)];
        free(filtered_arr);
    }
    printf("%d\n", ans);
    free(arr);
    free(index_array);
    free(greater_left);
    free(greater_right);
}


void question_2()
/* worst case cenerio = [1, 100K, 100K, 0, 0, 0, 1, 100K, 100K, 0, 0, 0, 1 ...]
[n (first for loop) ]*[b (assignments) +*k('while loop operations)] = O(n)*[b+k] = O(k*n) 
(k is bounded to 100K and statistically will be much less) 
######question_2 O notations = O(k*n), (in our task we can write O(n), because k Smaller than n in magnitude)###### 
*/
{

    unsigned long long ans = 0;
    int n, q_index = 0, min_index=0;// q_index is the index for the next spot available in queue 
    int removal_q_index = 0,current_job;// removal_q_index is the starting index of the current queue 
    scanf_s("%d", &n);
    int* queue;
    int* value_to_index;
    value_to_index = (int*)malloc(sizeof(int) * (101000));
    queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &current_job);
        if (current_job > 0) { // add to queue
            queue[q_index] = current_job;
            if ( queue[q_index]<=queue[min_index]){ // save min index
                min_index = q_index;
            }
            q_index += 1;
            value_to_index[current_job] = q_index; 
        }
        else if ((current_job == 0) && (q_index>removal_q_index)){ // remove from queue
            ans += queue[removal_q_index] - queue[min_index];
            if (value_to_index[queue[removal_q_index]] == removal_q_index) // remove from val2idx
                value_to_index[queue[removal_q_index]] = 0;
            removal_q_index += 1;
            if (min_index <= (removal_q_index-1)) { // set a new min_index
                min_value = queue[min_index];
                while (value_to_index[min_value] == 0 &&q_index>removal_q_index) {
                    min_value += 1;
                }
                if (q_index == removal_q_index) {
                    min_index = q_index;
                }
                else{
                    min_index = value_to_index[min_value];
                }
            }
   
        }
    }
    printf("%llu\n", ans);
    free(queue);
    free(value_to_index);
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
