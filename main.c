#include "eval.c"

int main(){
    char* infix = "2*x+1";
    Expression expr = createExpression(infix);
    printf("Infix: %s\n", expr.expression);
    printf("Postfix:");
    display(expr.postfix);
    printf("Result: %d\n", evaluate(expr));
    return 0;
}

