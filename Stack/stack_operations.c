//prectical 3

#include <stdio.h>

#define MAX 5

int stack[MAX];
int top = -1;

// Push Operation
void push()
{
    int value;

    if(top == MAX - 1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        printf("Enter value to push: ");
        scanf("%d", &value);

        top++;
        stack[top] = value;

        printf("%d pushed into stack.\n", value);
    }
}

// Pop Operation
void pop()
{
    if(top == -1)
    {
        printf("Stack Underflow\n");
    }
    else
    {
        printf("Deleted element is %d\n", stack[top]);
        top--;
    }
}

// Peek Operation
void peek()
{
    if(top == -1)
    {
        printf("Stack is Empty\n");
    }
    else
    {
        printf("Top element is %d\n", stack[top]);
    }
}

// Display Operation
void display()
{
    int i;

    if(top == -1)
    {
        printf("Stack is Empty\n");
    }
    else
    {
        printf("Stack elements are:\n");

        for(i = top; i >= 0; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n----- STACK MENU -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                push();
                break;

            case 2:
                pop();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 5);

    return 0;
}
