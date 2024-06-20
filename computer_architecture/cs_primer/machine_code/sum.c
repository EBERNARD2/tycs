#include <stdio.h>
#include <stdlib.h>

int sum(int *arr, int n) {
    int total = 0;
    
    for (int i = 0; i < n; i++)
        total += arr[i];
    
    return total;
}

int main() {
    int arr[] = {5, 20, 3};

    int total = sum(arr, sizeof(arr) / sizeof(int));
    printf("Total: %d\n", total);
    exit(0);
}