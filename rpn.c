#include <stdio.h>
#include <stdlib.h>
// nice explanation of the Reverse Polish Notation: https://isaaccomputerscience.org/concepts/dsa_toc_rpn

//global variables
int stack[1000];
char ch;
int top = -1;


// prototypes
void push(int number);
void pop(char ch); /* I don't need to include the char ch paramter, but it makes the code more readable*/
void finish_stack(void);
int make_number(char ch);

// functions
int main(void)
{
    printf("This ");
    printf("Enter an RPN expression: ");
    while(1){
        ch = getchar();
        if (ch == ' '){
            continue;
        }
        if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^')){
            pop(ch);
            continue;
        }
        if (ch == '='){
            finish_stack();
            exit(0);
        }
        if (ch == '\n'){
            printf("ERROR: Missing '=' at the end of expression\nExiting...\n");
            exit(0);
        }
        else if (((int)ch > 47) && ((int)ch < 58)){
            int number = make_number(ch);
            push(number);
        }
        else{
            printf("ERROR: Invalid characters (not an RPN expression)\nExiting...\n");
            exit(0);
        }
        // DEBUG
        //printf("top: %d\n", top);
        // DEBUG
    }
    printf("ERROR: Missing '=' at the end of expression.");
    return 0;
}

int make_number(char ch)
{
    int temp;
    int number = 0;
    while(1){
        if (ch == ' '){
            break;
        }
        // This could be done more effectively, but this method is easier to grasp and ASCII independent
        switch(ch){
            case '0': temp = 0; break;
            case '1': temp = 1; break;
            case '2': temp = 2; break;
            case '3': temp = 3; break;
            case '4': temp = 4; break;
            case '5': temp = 5; break;
            case '6': temp = 6; break;
            case '7': temp = 7; break;
            case '8': temp = 8; break;
            case '9': temp = 9; break;
        }
        number *= 10;
        number += temp;
        ch = getchar();
    }
        // DEBUG
        //printf("Returned number: %d\n", number);
        // DEBUG
    return number;
}

void push(int number)
{
    top++;
    if (top > 999){
        printf("ERROR: Expression is too complex (stack overflow)\nExiting...\n");
        exit(0);
    }
    stack[top] = number;
    // DEBUG
    //printf("Number succefully pushed: %d\n", stack[top]);
    // DEBUG
}

void pop(char ch)
{
    if ((top-1) < 0){
        printf("ERROR: Too many operators (cannot evaluate expression)\nExiting...\n");
        exit(0);
    }
    int temp = 1;
    switch(ch){
        case '+' :
            stack[top-1] = (stack[top-1] + stack[top]);
            break;
        case '-' :
            stack[top-1] = (stack[top-1] - stack[top]);
            break;
        case '*' :
            stack[top-1] = (stack[top-1] * stack[top]);
            break;
        case '/' :
            stack[top-1] = (stack[top-1] / stack[top]);
            break;
        case '^' :
            for (int i = 1; i <= stack[top]; i++){
                temp *= stack[top-1];
            }
            stack[top-1] = temp;
            break;
    }
    top--;
}

void finish_stack(void)
{
    if (top > 0){
        printf("ERROR: Not enough operands in expression (cannot evaluate expression)\nExiting...\n ");
        exit(0);
    }
    printf("Value of expression: %d\n", stack[top]);
}
