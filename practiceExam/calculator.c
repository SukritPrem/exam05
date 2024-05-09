#include "stdio.h"

#include <stdlib.h>
#include <string.h>


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


node *parsePlus(char **str)
{
    node *l = parseMulti(str);
    while(**str == '+')
    {
        node *r = parseMulti(str);
        node *n = malloc(sizeof(node));
        
    }
}
int main ()
{
    char *str = strdup("2*3+4");

    node *root = parseplus(&str);
}

