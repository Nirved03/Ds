//1.Write a program to create an array and demonstrate insertion, deletion, traversal, and search operations.

#include <stdio.h>
int main()
{
    int arr[100], n, i;
    int choice, pos, value, key, found;
    char ch;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Search\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter position to insert: ");
                scanf("%d", &pos);

                printf("Enter value: ");
                scanf("%d", &value);

                if(pos < 1 || pos > n + 1)
                {
                    printf("Invalid Position\n");
                }
                else
                {
                    for(i = n; i >= pos; i--)
                    {
                        arr[i] = arr[i - 1];
                    }

                    arr[pos - 1] = value;
                    n++;

                    printf("Array after insertion:\n");
                    for(i = 0; i < n; i++)
                    {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &pos);

                if(pos < 1 || pos > n)
                {
                    printf("Invalid Position\n");
                }
                else
                {
                    for(i = pos - 1; i < n - 1; i++)
                    {
                        arr[i] = arr[i + 1];
                    }

                    n--;

                    printf("Array after deletion:\n");
                    for(i = 0; i < n; i++)
                    {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                printf("Array elements are:\n");
                for(i = 0; i < n; i++)
                {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;

            case 4:
                printf("Enter element to search: ");
                scanf("%d", &key);

                found = 0;

                for(i = 0; i < n; i++)
                {
                    if(arr[i] == key)
                    {
                        printf("Element found at position %d\n", i + 1);
                        found = 1;
                        break;
                    }
                }

                if(found == 0)
                {
                    printf("Element not found\n");
                }
                break;

            default:
                printf("Invalid Choice\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &ch);

    } while(ch == 'y' || ch == 'Y');

    printf("Program Ended.");

    return 0;
}
