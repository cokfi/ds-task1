#include <limits.h>
#include <math.h>
//#---include <iostream> //for c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
void question_1() {
    /* 3 steps algorithm:
    step1: Find indexes of next greater and previous greater for every element. 
    step2: Find the smallest element for each filter size and save them in array.  
    step 3: fill untouched filters and sum step2's array.
    */
/*
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
    //
}
*/