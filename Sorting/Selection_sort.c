#include <stdio.h>

#define MAX 50

int main() {
    int arr[MAX], n, temp, minIndex;

    printf("Enter number of elements (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Selection Sort
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;             // remember the smallest so far
        }

        if (minIndex != i) {
            temp = arr[i];                // swap smallest into position i
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    printf("\nSorted array (Selection Sort): ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}