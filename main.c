#include <stdio.h>
#include <stdlib.h>

char expr[20]; 
char stack[20];

//returns true if precedence of operator a is more or equal to than that of b
int precedence(char a, char b)
{
    if (((a == '+') || (a == '-')) && ((b == '*') || (b == '/')))
        return 0;
    else
        return 1;
}

int i;
int ctr;
int top = -1;     //top of postfix stack
int top_oper = -1; //top of operator stack

int operate(int a, int b, char oper)
{
    int res = 0;
    switch (oper)
    {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break; //return result of evaluation
    case '/':
        res = a / b;
        break;
    }
    return res;
}

void postfix()
{ //function to convert in postfix form
    char top_symb, operator_stack[20];
    ctr = 0;

    while (expr[ctr] != '\0')
    { //read till the end of input
        if (expr[ctr] >= '0' && expr[ctr] <= '9')
            stack[++top] = expr[ctr]; //add numbers straightaway
        else
        {
            while (top_oper >= 0 && precedence(operator_stack[top_oper], expr[ctr]))
            { //check for the operators of higher precedence and then add them to stack
                top_symb = operator_stack[top_oper--];
                stack[++top] = top_symb;
            }
            operator_stack[++top_oper] = expr[ctr];
        }
        ctr++;
    }
    while (top_oper >= 0) //add remaining operators to stack
        stack[++top] = operator_stack[top_oper--];
    printf("Postfix expression: \n%s\n", stack);
}

int main()
{
    scanf("%s", expr);
    postfix(); 
    char oper;
    int op1, op2;
    ctr = 0;
    int result[2]; //stack to keep storing results
    int rTop = -1; //top of result stack
    while (stack[ctr] != '\0')
    {
        oper = stack[ctr];
        if (oper >= '0' && oper <= '9')
            result[++rTop] = (int)(oper - '0'); //add numbers
        else
        { //if an operator is encountered than pop twice and push the result of operation to the stack
            op1 = result[rTop--];
            op2 = result[rTop--];
            result[++rTop] = operate(op2, op1, oper);
        }
        ctr++;
    }
    printf("Result is\n%d\n", result[0]);
    getc(stdin);
}