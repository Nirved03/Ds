//A. Write a program to convert an expression from infix to postfix.

#include <stdio.h>
#include <ctype.h>

#define MAX 100 

char stack[MAX];  s
int top = -1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

char peek()
{
    return stack[top];
}

int precedence(char ch)
{
    if(ch == '^')
        return 3;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

int main()
{
    char infix[MAX], postfix[MAX];
    int i, j = 0;
    char ch;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    for(i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if(isalnum(ch)) //aa check karse ke letter che ke number
        {
            postfix[j++] = ch;
        }
        else if(ch == '(')
        {
            push(ch);
        }
        else if(ch == ')')
        {
            while(top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }
            pop();
        }
        else
        {
            while(top != -1 && precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    while(top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
