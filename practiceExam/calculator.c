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
node *parseValue(char **str, int *index);
node *parsePlus(char **str, int *index);
node *parseMulti(char **str, int *index);

node *parsePlus(char **str, int *index)
{
    node *l = parseMulti(str, index);
    while((str[0][*index]) == '+')
    {
        (*index)++;//skip +
        node *r = parseMulti(str, index);
        node *n = malloc(sizeof(node));
        n->type = ADD;
        n->l = l;
        n->r = r;
        l = n;
    }
    return l;
}

node *parseMulti(char **str, int *index)
{
    node *l = parseValue(str, index);
    while((str[0][*index]) == '*')
    {
        (*index)++;//skip *
        node *r = parseValue(str, index);
        node *n = malloc(sizeof(node));
        n->type = MULTI;
        n->l = l;
        n->r = r;
        l = n;
    }
    return l;
}

int ft_isdigit(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}


int ft_atoi(char *str)
{
    if(*str == '\0' || *str == '*' || *str == '+')
    {
        return 0;
    }    
    else
    {
        int tmp = (*str  - '0') + 10 * ft_atoi(str + 1);
        return tmp;
    }
}

node *parseValue(char **str,int *index)
{
    if(**str == '(')
    {
        node *n = parsePlus(str, index);

        return n;
    }
    int start = *index;
    int tmpstart = *index;
    while(1)
    {
        if(ft_isdigit(str[0][*index]))
            (str[0][*index]);
        else
            break;
        (*index)++;

    }
    if(!(str[0][*index] == '\0' || str[0][*index]== '*' || str[0][*index]== '+'))
    {
        return NULL;
    }
    int end = *index;
    int len = end - start;
    char *tmpStr = malloc(sizeof(char) * (len + 1));
    int i = 0;
    while(i < len)
    {
        tmpStr[i++] = str[0][start++];
    }
    tmpStr[i] = '\0';
    node *n = malloc(sizeof(node));
    printf("tmp : %s\n",tmpStr);
    n->type = VAR;
    n->var = ft_atoi(tmpStr);
    printf("var = %d\n",n->var);
    // (*index)++;
    return n;
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

int main ()
{
    char *str = strdup("2*3+4");
    int index = 0;
    node *head = parsePlus(&str, &index);
    // printf("head r : %d\n",head->r->type);
    printf("ans : %d\n",eval(head));
}

