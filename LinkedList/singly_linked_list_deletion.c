//ii. Delete a node (first node, last node, node after a given node) Display all the nodes

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void deleteFirst()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    head = head->next;

    printf("Deleted node: %d\n", temp->data);
    free(temp);
}

void deleteLast()
{
    struct Node *temp, *prev;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL)
    {
        printf("Deleted node: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    temp = head;

    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;

    printf("Deleted node: %d\n", temp->data);
    free(temp);
}

void deleteAfter()
{
    int value;
    struct Node *temp, *deleteNode;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("Enter node value after which to delete: ");
    scanf("%d", &value);

    temp = head;

    while (temp != NULL && temp->data != value)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Given node not found.\n");
        return;
    }

    if (temp->next == NULL)
    {
        printf("No node exists after the given node.\n");
        return;
    }

    deleteNode = temp->next;
    temp->next = deleteNode->next;

    printf("Deleted node: %d\n", deleteNode->data);
    free(deleteNode);
}

void display()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    temp = head;

    printf("Linked List: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main()
{
    int n, i, value, choice;
    struct Node *newNode, *temp;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        newNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter value: ");
        scanf("%d", &value);

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }

    do
    {
        printf("\n1. Delete First Node");
        printf("\n2. Delete Last Node");
        printf("\n3. Delete Node After Given Node");
        printf("\n4. Display All Nodes");
        printf("\n5. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                deleteFirst();
                break;

            case 2:
                deleteLast();
                break;

            case 3:
                deleteAfter();
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}