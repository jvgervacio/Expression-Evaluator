#include <stdio.h>
#include <stdlib.h>


/****************************
 *     STRUCT DEFINITIONS   *
 ****************************/

typedef struct StackNode{
    char* data;                                                     // pointer to the data stored in the node
    struct StackNode *next;                                         // pointer to the next node in the stack
}StackNode;                 

typedef struct Stack{                   
    StackNode* top;                                                 // pointer to the top node of the stack
}Stack;




/****************************
 *    FUNCTION PROTOTYPES   *
 ****************************/

StackNode*  createStackNode(char *data);                            // function to create a new stack node
Stack       createStack();                                          // function to create a new stack
int         isEmpty(Stack *stack);                                  // function to check if a stack is empty
void        push(Stack *stack, char *data);                         // function to push data onto a stack
char*       pop(Stack *stack);                                      // function to pop data from a stack
char*       peek(Stack *stack);                                     // function to peek at the top element of a stack
void        display(Stack stack);                                   // function to display the contents of a stack
char*       c_to_str(char c);                                       // function to convert a character to a string




/****************************
 *   FUNCTION DEFINITIONS   *
 ****************************/

StackNode *createStackNode(char *data){                             // function to create a new stack node
    StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));    // allocate memory for the new node
    newNode->data = data;                                           // set the data pointer of the new node to the given data
    newNode->next = NULL;                                           // set the next pointer of the new node to NULL
    return newNode;                                                 // return the new node
}

Stack createStack(){                                                // function to create a new stack
    Stack newStack;                                                 // create a new stack
    newStack.top = NULL;                                            // set the top pointer of the new stack to NULL
    return newStack;                                                // return the new stack
}

int isEmpty(Stack *stack){                                          // function to check if a stack is empty
    return stack->top == NULL;                                      // return 1 if the top pointer of the stack is NULL, 0 otherwise
}

void push(Stack* stack, char* data){                                // function to push data onto a stack
    StackNode* newNode = createStackNode(data);                     // create a new node with the given data
    newNode->next = stack->top;                                     // set the next pointer of the new node to the current top node of the stack
    stack->top = newNode;                                           // set the top pointer of the stack to the new node
}

char* c_to_str(char c){                                             // function to convert a character to a string
    char *str = (char *)malloc(sizeof(char) * 2);                   // allocate memory for the string
    str[0] = c;                                                     // set the first character of the string to the given character
    str[1] = '\0';                                                  // set the second character of the string to the null terminator
    return str;                                                     // return the string
}

char* pop(Stack *stack){                                            // function to pop data from a stack
    if(isEmpty(stack))                                              // if the stack is empty
        return NULL;                                                // return NULL
    
    StackNode* temp = stack->top;                                   // create a temporary pointer to the top node of the stack
    stack->top      = stack->top->next;                             // set the top pointer of the stack to the next node in the stack
    char* data      = temp->data;                                   // get the data from the top node of the stack
    free(temp);                                                     // free the memory allocated for the top node of the stack
    return data;                                                    // return the data
}

char* peek(Stack* stack){                                           // function to get the data at the top of a stack without removing it
    if(isEmpty(stack))                                              // if the stack is empty
        return NULL;                                                // return NULL
    
    return stack->top->data;                                        // return the data from the top node of the stack
}

Stack reverse(Stack stack){                                         // function to reverse the order of a stack
    StackNode* ptr = stack.top;                                     // create a pointer to the top node of the stack
    Stack newStack = createStack();                                 // create a new stack
    while(ptr != NULL){                                             // loop through each node in the stack
        push(&newStack, ptr->data);                                 // push the data from the current node onto the new stack
        ptr = ptr->next;                                            // move to the next node in the stack
    }
    return newStack;                                                // return the reversed stack
}

void display(Stack stack){                                          // function to display the contents of a stack
    StackNode* ptr = stack.top;                                     // create a pointer to the top node of the stack
    while(ptr != NULL){                                             // loop through each node in the stack
        printf("%s ", ptr->data);                                   // print the data from the current node
        ptr = ptr->next;                                            // move to the next node in the stack
    }
    printf("\n");                                                   // print a newline character
}