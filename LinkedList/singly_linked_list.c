//i. Insert a new node (at the beginning, at the end, after a given node)
#include <stdio.h>
#include <stdlib.h>

// struct node *first = null;
struct node
{
    int data;
    struct node *next;
};
struct node *first = NULL;
struct node *create_node(int x)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = x;
    temp->next = NULL;

    return temp;
}

void display()
{
    struct node *t;
    t = first;
    while (t != NULL)
    {
        printf("%d ", t->data);
        t = t->next;
    }
}

void insert_first(int x)
{
    struct node *t;
    t = create_node(x);
    if (first == NULL)
    {
        first = t;
    }
    else
    {
        t->next = first;
        first = t;
    }
}

void delete()
{
    struct node *t;

    if (first == NULL)
    {
        printf("Linked list is empty");
    }
    else
    {
        t = first;
        first = first->next;
        free(t);
        printf("Node deleted successfully");
    }
}

void main()
{
    int n, choice;

    while (1)
    {
        printf("\n1. Insert first");
        printf("\n2. delete");
        printf("\n3. display");
        printf("\n4. exit");

        printf("\n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &n);
            insert_first(n);
            break;

        case 2:
            delete();
            break;

        case 3:
            printf("the data in linked list: ");
            display();
            break;

        case 4:
            printf("\n Program ended successfully...");
            exit(0);

        default:
            printf("Invalid choice...!");
        }
    }
}