#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* this code implements three tasks:
 Task 1:
 input: array legnth - n ,array of n integers.
 the program finds it's Max Pooling with stride=1 and size = 1 to n (result of n arrays)
 output: sum of minimun numbers, (each max pooling result return an array, each array return a minimum number)
 Task 2:
 The sum of all jobs performed reduced by the minimum job existed when removed from queue
 Task 3:
 input: string legnth - n ,array of n chars.
 output: the length of the longest subarray Palindrome.
 */

void question_1() {
    /* 3 steps algorithm:
    step1: Find indexes of next greater and previous greater for every element.
    step2: Find the smallest element for each filter size and save them in array(that won't fill the entire array).
    step 3: fill untouched filters and print the sum of step2's array.

    step 1 operations = a*n (the "while loop" inside "for loop" wont surpass O(n) because counter can add only 1(maximum) each "for" iteration) 
    step 2 operations = b*n , step 3 operations = c*n , total operations = [a+b+c]*n
    #####O notation = O(n)######
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
}


void question_2()
/* worst case cenerio = [1, 100K, 100K, 0, 0, 0, 1, 100K, 100K, 0, 0, 0, 1 ...] 
(3 jobs in loop because if there were less members in queue  there won't occur any calculation insde the while loop)
a*n+[n/6 (first for loop) ]*[b (assignments) +*k('while loop operations)] = (a+((b+k)/6)*n = O(k*n) 
(k is bounded to 100K and statistically will be much less) 
######O notations = O(k*n), (in our task **WE CAN WRITE** O(n), because k Smaller than n in magnitude)###### 
*/
{

    unsigned long long ans = 0;
    int n, q_index = 0, min_index=0;// q_index is the index for the next spot available in queue 
    int removal_q_index = 0,current_job,min_value;// removal_q_index is the starting index of the current queue 
    scanf("%d", &n);
    int* queue;
    int* value_to_index;
    value_to_index = (int*)malloc(sizeof(int) * (101000));
    queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i <= 100000; i++)//initialize value_to_index
        value_to_index[i] = 0;

    for (int i = 0; i < n; i++) { // queue flow
        scanf("%d", &current_job);
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
/* O notation calculations:
for loop inside for loop operations =n^2 , single for loop operations = max 4*n, last for loop inside for loop =max c*n^2
total operations <= n^2 +4*n +c*n^2  
###### O notations = O(n^2)######
*/
{
    int ans = 1;
    int string_length,rows,cols,offset;
    char string[100] = { 0 };
    scanf("%d", &string_length);
    scanf("%s", string);
    ///////  Enter solution here ///////
    rows = string_length;
    cols = string_length;
    int* pali_matrix = (int*)malloc(rows * cols * sizeof(int)); // offset = i * cols + j,  corresponds to pali_matrix[i, j]
    for (int i = 0; i < rows; i++) { //initialize matrix, each cell indication wheter substing i:j is a Palindrom
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                pali_matrix[i * cols + j] = 1; // size 1 palindroms
            }
            else {
                pali_matrix[i * cols + j] = 0;
            }
        }
    }
    int starting_index = 0;
    for (int i = 0; i < string_length - 1; ++i) {//size =2 palindroms
        if (string[i] == string[i + 1]) {
            offset = i * cols + (i + 1);// i+1 = column, i = row
            pali_matrix[offset] = 1;
            ans = 2;
        }
    }
    
    int j; // column's index
    for (int sub_length = 3; sub_length <= string_length; sub_length++) { // size = 3 and longer palindroms
        for (int i = 0; i < string_length - sub_length + 1; ++i) {
            j = i + sub_length - 1;

            offset = (i + 1) * cols + (j - 1); // i+1 - row, j-1 column
            if (pali_matrix[offset]==1 && string[i] == string[j]) {
                pali_matrix[i*cols+j] = 1;
                if (sub_length > ans) {
                    ans = sub_length;
                }
            }
        }
    }

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
