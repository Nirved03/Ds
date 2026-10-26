#include <stdio.h>

#define MAX 50

// Binary search (iterative): returns index if found, -1 otherwise
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;   // middle index

        if (arr[mid] == key)
            return mid;                     // found
        else if (key < arr[mid])
            high = mid - 1;                 // search left half
        else
            low = mid + 1;                  // search right half
    }

    return -1;                              // not found
}

int main() {
    int arr[MAX], n, key;

    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter %d elements in SORTED (ascending) order:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the element to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, n, key);

    if (result != -1)
        printf("Element %d found at index %d (position %d).\n", key, result, result + 1);
    else
        printf("Element %d not found in the array.\n", key);

    return 0;
}