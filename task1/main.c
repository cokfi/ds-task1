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
    int* greater_right; // each cell contain the index of the greater element on right, =n if non exist
    int* greater_left; // each cell contain the index of the greater element on left, =-1 if non exist
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    greater_right = (int*)malloc(sizeof(int) * (n + 1));
    greater_left = (int*)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    clock_t start, end;
    double time_taken;
    start = clock();
// step 1:
    for (i = n - 1; i >= 0; i--) {
        greater_left[i] = -1; // init values- no greater on right
        greater_right[i] = n; // init values- no greater on left
    }
    int* index_array; // former greater element indexes array
    index_array = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; i++)
        index_array[i] = 0; // cell 0 is unused
    int counter = 0; // index_array counter of current element 
    for (i = 0; i < n; i++)// left elements
    {
        while (counter != 0 && arr[index_array[counter]] <= arr[i]) {
            counter = counter - 1;
        }

        if (counter != 0)
            greater_left[i] = index_array[counter];

        counter += 1;
        index_array[counter] = i;
    }
    counter = 0; // reset counter for right elements
    for (i = n - 1; i >= 0; i--) {
        while (counter != 0 && arr[index_array[counter]] <= arr[i]) {
            counter = counter - 1;
        }

        if (counter != 0)
            greater_right[i] = index_array[counter];

        counter += 1;
        index_array[counter] = i;
    }
// step 2:
    int* min_of_MaxPooling;
    int filter_size;
    min_of_MaxPooling = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; i++)
        min_of_MaxPooling[i] = 1001;// a cell for each filter size , cell 0 is unused
    for (int i = 0; i < n; i++) {
        filter_size = greater_right[i] - greater_left[i] - 1; // biggest filter size that will return arr[i] 
        if (min_of_MaxPooling[filter_size] > arr[i])
            min_of_MaxPooling[filter_size] = arr[i]; // save the min of all max pooling of the same filter size
    }
// step 3:
    for (int i = n - 1; i >= 1; i--) {
        if (min_of_MaxPooling[i] > min_of_MaxPooling[i + 1])
            min_of_MaxPooling[i] = min_of_MaxPooling[i + 1];//fill empty cells,smaller filter size will have smaller/equal value
    }
    for (int i = 1; i <= n; i++) {
        ans = ans + min_of_MaxPooling[i];
    }
    printf("%d\n", ans);
    free(arr);
    free(index_array);
    free(greater_left);
    free(greater_right);
    //measure time
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n", time_taken);
}


void question_2()
/* worst case cenerio = first n/2 upgrowing elements(modulo 100K) then n/2 zeros
[a*n/2 (first for loop) ]*[b (assignments) +c (find minimum operations)] = O(n)*[b+c] = O(n) 
considering the best case when the minimum value is on the last element of the array,
the function find_minimum will take n operations but will be needed only once so in every case we will get O(n).
######question_2 O notations = O(n)###### 
*/
{

    unsigned long long ans = 0;
    int n, q_index = 0, min_index=0;// q_index is the index for the next spot available in queue 
    int removal_q_index = 0,current_job;// removal_q_index is the starting index of the current queue 
    scanf("%d", &n);
    int* queue;
    queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &current_job);
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
