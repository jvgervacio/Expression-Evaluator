#include "eval.c"

int main(){
    char* infix = "2x+1+";
    Expression expr = createExpression(infix);
    printf("Infix: %s\n", expr);
    printf("Postfix: %s\n", expr.postfix);
    printf("Result: %f\n", evaluate(expr));
    return 0;
}

