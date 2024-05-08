

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
enum {
MULTI,
ADD,
VAR
} type;
int var;
struct node *l;
struct node *r;
} node;

node *parsePlus(char **str);
node *parseVar(char **str);
node *parseMult(char **str);

void trim(char **str) {
    while (**str == ' ') {
        (*str)++;
    }
}

node *parsePlus(char **str) {
    node *l = parseMult(str);
    while (**str == '+') {
        (*str)++;
        node *r = parseMult(str);
        node *n = malloc(sizeof(node));
        n->type = ADD;
        n->l = l;
        n->r = r;
        l = n;
    }
    return l;
}

node *parseMult(char **str) {
    node *l = parseVar(str);
    while (**str == '*') {
        (*str)++;
        node *r = parseVar(str);
        node *n = malloc(sizeof(node));
        n->type = MULTI;
        n->l = l;
        n->r = r;
        l = n;
    }
    return l;
}

node *parseVar(char **str) {
    if(**str == '(') {
        (*str)++;
        node *n = parsePlus(str);
        if(**str != ')') {
            printf("Error\n");
            exit(1);
        }
        (*str)++;
        return n;
    }
    else {
        node *n = malloc(sizeof(node));
        n->type = VAR;
        n->var = **str - '0';
        (*str)++;
        return n;
    }
}




int eval(node *n) {
    switch (n->type) {
    case MULTI :
        return eval(n->l) * eval(n->r);
    case ADD :
        return eval(n->l) + eval(n->r);
    case VAR :
        return n->var;
    }
    return 0;
}

int main()
{
    char *str = "1+2*(3+5)*8";

    node *n = parsePlus(&str);
    printf("%d\n", eval(n));
}
