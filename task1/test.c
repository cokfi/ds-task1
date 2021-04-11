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
bigger_right = (int*)malloc(sizeof(int) * (n+1));
bigger_left = (int*)malloc(sizeof(int) * (n + 1));

for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);
//for (int i = 0; i < n; i++)
//    arr[i] = 1000;
//program time settings
clock_t start, end;
double time_taken;
start = clock();
//

int next, i, j;
for (i = 0; i < n; i++){ // O(n^2)
    bigger_right[i] = n; // init values- no bigger on left
    for (j = i + 1; j < n; j++){
        if (arr[i] < arr[j]){
            bigger_right[i] = j;
            break;
        }
    }
}
for (i = n-1; i >= 0; i--) { // O(n^2)
    bigger_left[i] = -1; // init values- no bigger on right
    for (j = i -1; j >= 0; j--) {
        if (arr[i] < arr[j]) {
            bigger_right[i] = j;
            break;
        }
    }
}


// i+1= filter size, j= filtered_arr index, s= starting SubArray index
int* filtered_arr;
global_max_index = find_minimum(arr, n, 0);
ans = arr[global_max_index];// filter size = 1
for (int i = n-1; i >= 0; i--) {
    //filtered_arr = (int*)malloc(sizeof(int) * (n - i));
    if (global_max_index<i &&global_max_index>=)
    minimum_of_maxP = arr[find_maximum(arr, i + 1, 0)];// Max Pooling
    for (int s = 1; s < (n - i); s++) {
        temp_index = find_maximum(arr, s + i + 1, s);// Max Pooling
        if (arr[temp_index] < minimum_of_maxP)
            minimum_of_maxP = arr[temp_index];
    }
    ans = ans + minimum_of_maxP;
}
printf("%d\n", ans);
free(arr);
//measure time
end = clock();
time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
printf("fun() took %f seconds to execute \n", time_taken);
//
}


{
    // Used to find previous and next smaller
    stack<int> s;

    // Arrays to store previous and next smaller
    int left[n + 1];
    int right[n + 1];

    // Initialize elements of left[] and right[]
    for (int i = 0; i < n; i++)
    {
        left[i] = -1;
        right[i] = n;
    }

    // Fill elements of left[] using logic discussed on
    // https://www.geeksforgeeks.org/next-greater-element/
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && arr[s.top()] >= arr[i])
            s.pop();

        if (!s.empty())
            left[i] = s.top();

        s.push(i);
    }

    // Empty the stack as stack is
// going to be used for right[]
    while (!s.empty())
        s.pop();

    // Fill elements of right[] using same logic
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && arr[s.top()] >= arr[i])
            s.pop();

        if (!s.empty())
            right[i] = s.top();

        s.push(i);
    }

    // Create and initialize answer array
    int ans[n + 1];
    for (int i = 0; i <= n; i++)
        ans[i] = 0;

    // Fill answer array by comparing minimums of all
    // lengths computed using left[] and right[]
    for (int i = 0; i < n; i++)
    {
        // length of the interval
        int len = right[i] - left[i] - 1;

        // arr[i] is a possible answer for this length
        // 'len' interval, check if arr[i] is more than
        // max for 'len'
        ans[len] = max(ans[len], arr[i]);
    }

    // Some entries in ans[] may not be filled yet. Fill
    // them by taking values from right side of ans[]
    for (int i = n - 1; i >= 1; i--)
        ans[i] = max(ans[i], ans[i + 1]);

    // Print the result
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

// Driver program
int main()
{
    int arr[] = { 10, 20, 30, 50, 10, 70, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printMaxOfMin(arr, n);
    return 0;
}