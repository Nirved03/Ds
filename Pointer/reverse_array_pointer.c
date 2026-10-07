//prectical 2.1

#include <stdio.h>

int main()
{
    int arr[100], n, i;
    int *ptr;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    ptr = &arr[n - 1];

    printf("\nArray elements in reverse order are:\n");

    for(i = n - 1; i >= 0; i--)
    {
        printf("%d ", *ptr);
        ptr--;
    }

    return 0;
}
