#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "stack.c"


/****************************
 *    STRUCT DEFINITIONS    *
 ****************************/

typedef struct Expression{
    char *expression;                                                                               // string of original infix expression 
    Stack postfix;                                                                                  // the postfix expression generated from the infix expression
}Expression;  



/****************************                           
 *    FUNCTION PROTOTYPES   *                           
 ****************************/   

Expression  createExpression(char *expression);                                                     // function to create a new Expression struct
Stack       infixToPosfix(char *expression);                                                        // function to convert an infix expression to postfix notation
int         isOperator(char c);                                                                     // function to check if a character is an operator
int         isOperand(char c);                                                                      // function to check if a character is an operand
int         precedence(char operator);                                                              // function to get the precedence of an operator
int         ctoi(char c);                                                                           // function to convert a character to an integer
int         count_digits(int n);                                                                    // function to count the number of digits in an integer
int         evaluate(Expression expr);                                                              // function to evaluate an expression


/****************************                           
 *   FUNCTION DEFINITIONS   *                           
 ****************************/  

Expression createExpression(char *expression){                          
    Expression newExpression;                                                                       // reference: https://www.geeksforgeeks.org/structures-c/
    newExpression.expression = expression;                                                          // set the expression pointer of the new Expression struct to the given expression
    newExpression.postfix    = infixToPosfix(expression);                                           // generate the postfix expression from the given expression and set it in the new Expression struct
    return newExpression;                                                                           // return the new Expression struct 
}                           

                                                                                                    // reference: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
                                                                                                    
Stack infixToPosfix(char *expression){                          
    Stack stack = createStack();                                                                    // create a new stack
    Stack postfix = createStack();                                                                  // create a new stack to hold the postfix expression
    int i = 0;                          

    while(expression[i] != '\0'){                                                                   // loop through each character in the expression until the null terminator is reached
        if(isOperand(expression[i])){                                                               // if the character is an operand
            if (isdigit(expression[i])){                                                            // if the operand is a digit (not a variable)
                int temp = ctoi(expression[i]);                                                     // convert the first digit to an integer
                while(isdigit(expression[i + 1]))                                                   // while there are still digits in the next iteration of the loop    https://www.geeksforgeeks.org/convert-string-to-integer-without-using-any-in-built-functions/
                    temp = temp * 10 + ctoi(expression[++i]);                                       // add the next digit to the integer and increment the index of the expression string
                                                                                                   
                                                                    // if the next character is a decimal point 
                                                                                           // increment the index of the expression string to skip the decimal point
                char *str = (char *)malloc(sizeof(char) * count_digits(temp) + 1);                  // allocate memory for the string to hold the integer (number of digits + 1 for the null terminator)
                sprintf(str, "%d", temp);                                                           // convert the integer to a string and store it in the string variable (reference: https://www.geeksforgeeks.org/convert-number-to-string-in-c/)
                push(&postfix, str);                                                                // push the string onto the postfix stack 
                if(expression[i + 1] == '(' || isalpha(expression[i + 1]))
                    push(&stack, "*");
            }else{                                                                                  // if the operand is a variable (not a digit)
                push(&postfix, c_to_str(expression[i]));                                            // push the operand onto the postfix stack 
                if(expression[i + 1] == '(' || isalpha(expression[i + 1]))
                    push(&stack, "*");
                    
                
            }                           
        }                           
        else if(expression[i] == '('){                                                              // if the character is an opening parenthesis 
            push(&stack, c_to_str(expression[i]));                                                  // push it onto the stack 
        }                           
        else if(expression[i] == ')'){                                                              // if the character is a closing parenthesis 
            while(!isEmpty(&stack) && stack.top->data[0] != '(')                                    // while the stack is not empty and the top element is not an opening parenthesis 
                push(&postfix, pop(&stack));                                                        // pop the top element from the stack and push it onto the postfix stack 
                                   
            pop(&stack);                                                                            // pop the opening parenthesis from the stack 
        }                           
        else if(isOperator(expression[i])){                                                         // if the character is an operator
            while(!isEmpty(&stack) && precedence(stack.top->data[0]) >= precedence(expression[i]))  // while the stack is not empty and the top element has higher or equal precedence than the current operator 
                push(&postfix, pop(&stack));                                                        // pop the top element from the stack and push it onto the postfix stack 
                                           
            push(&stack, c_to_str(expression[i]));                                                  // push the operator onto the stack 
        }                               
        i++;                                                                                        // move to the next character in the expression string
    }                               
    while(!isEmpty(&stack)){                                                                        // while there are still elements in the stack 
        push(&postfix, pop(&stack));                                                                // pop the top element from the stack and push it onto the postfix stack 
    }                           
    return reverse(postfix);                                                                        // return the reversed postfix stack since the postfix expression is generated in reverse order
}

// create reverse postfix
                                                                                                    
                                                                                                    // reference: https://youtu.be/u3paQa8KXu0?si=ndznaZU_UoRsGmy2
int evaluate(Expression expr){                              
    Stack postfix = expr.postfix;                                                                   // get the postfix expression from the Expression struct 
    Stack stack = createStack();                                                                    // create a new stack to hold the values of the postfix expression 
    StackNode *current = postfix.top;                                                               // create a pointer to the top node of the postfix stack 
    int *val[26] = {NULL};                                                                          // create an array of integer pointers to hold variable values (26 letters in the alphabet) and initialize all values to NULL (no variables have been assigned values yet)
    while(current != NULL){                                                                         // loop through each node in the postfix stack 
        if(isOperand(current->data[0])){                                                            // if the node contains an operand 
            if(isalpha(current->data[0])){                                                          // if the operand is a variable 
                int index = ctoi(current->data[0]);                                                 // get the index of the variable
                
                if(val[index] == NULL){                                                             // if the variable has not been assigned a value yet
                    printf("Enter the value of %s: ", current->data);                               // prompt the user to enter a value for the variable 
                    int temp = 0;
                    scanf("%d", &temp);                                                             // read the value from the user 
                    val[index] = &temp;                                                             // store the value in the array of integer pointers 
                }                                                                                  
                char *str = (char *)malloc(sizeof(char) * count_digits(*val[index]) + 1);           // allocate memory for the string;          reference: https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
                sprintf(str, "%d", *val[index]);                                                    // convert the integer to a string and store it in the string variable (reference: https://www.geeksforgeeks.org/convert-number-to-string-in-c/)
                push(&stack, str);                                                                  // push the string onto the stack 
            }
            else{
                push(&stack, current->data);                                                        // push the operand onto the stack 
            }
        }
        else if(isOperator(current->data[0])){                                                      // if the node contains an operator 
            int operand1 = atoi(pop(&stack));                                                       // pop the top element from the stack and convert it to an integer 
            int operand2 = atoi(pop(&stack));                                                       // pop the next element from the stack and convert it to an integer 
            int result;

            switch(current->data[0]){                                                               // perform the operation based on the operator 
                case '+':
                    result = operand2 + operand1;
                    break;
                case '-':
                    result = operand2 - operand1;
                    break;
                case '*':
                    result = operand2 * operand1;
                    break;
                case '/':
                    result = operand2 / operand1;
                    break;
                case '^':
                    result = pow(operand2, operand1);
                    break;
            }

            char *str = (char *)malloc(sizeof(char) * 10);                                           // allocate memory for the string
            sprintf(str, "%d", result);                                                              // convert the integer to a string
            push(&stack, str);                                                                       // push the string onto the stack
        }                            
        current = current->next;                                                                     // move to the next node in the postfix stack
    }                            
    return atoi(pop(&stack));                                                                        // pop the top element from the stack and convert it to an integer, then return it
}                            
                            
                            
int isOperator(char c){                          
   return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';                                  // return 1 if the character is an operator, 0 otherwise
}

int precedence(char operator){    
    if (operator == '+' || operator == '-')                                                          // if the operator is + or -)                                                                            
        return 1;
    else if (operator == '*' || operator == '/')                                                     // if the operator is * or /)                                                                            
        return 2;
    else if (operator == '^')                                                                        // if the operator is ^)                                                                            
        return 3;
    else                                                                                             // if the operator is not +, -, *, /, or ^)                                                                            
        return -1;                                                                                   // return -1 (invalid operator)
}                            
                             
int isOperand(char c){                                                                      
    return isalpha(c) || isdigit(c);                                                                 // return 1 if the character is an alphabetic or numeric character, 0 otherwise
}                            
                             
int ctoi(char c){                                                                                    // reference: https://stackoverflow.com/a/5029840
    return c - '0';                                                                                  // convert the character to an integer and return it
}                            

// count digits
int count_digits(int num){                                                                          
    int count = 0;                                                                                   // initialize the count to 0
    while(num != 0){                                                                                 // while the number is not 0
        num /= 10;                                                                                   // divide the number by 10
        count++;                                                                                     // increment the count
    }                            
    return count;                                                                                    // return the count
}



