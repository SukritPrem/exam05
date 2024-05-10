#include "stdlib.h"
#include "stdio.h"

typedef struct json{
    enum {
        MAP,
        INTEGER,
        STRING
    } type;

    union 
    {
       struct 
       {
            struct pair *data;
            size_t size;
       } map;
       int interger;
       char *string;     
    };
    
} json;

typedef struct pair{
    char *key;
    json value;
} pair;


char *parseString(char **str, int *index)
{
    if(!str[0][*index] != '\"')
        return NULL;
    (*index)++; //skip "
    int start = *index;
    while(str[0][*index] != '\"' && str[0][*index] != '\0')
        (*index)++;
    int end = *index;
    int len = end - start;
    int i = 0;
    char *tmp = malloc(sizeof(char) * (len + 1));
    while(i < len)
    {
        tmp[i++] = str[0][start++]
    }
    tmp[i] = '\0';
    if(str[0][*index] != '\"')
        return NULL;
    (*index)++;//skip "
    return tmp;
}

void parsePair(char **str,int *index, json *root)
{
    (*index)++; //skip {
    pair *p = malloc(sizeof(pair));
    p->key = parseString(str,index);
    if(str[0][*index] != ':')
    {
        printf("ERROR :")
        return;
    }
    (*index)++; //skip :
    p->vlaue = parse_json(str,index);
    (*index)++; //skip }
}

json *parse_json(char **str,int *index)
{
    json *root = malloc(sizeof(json));
    if(str[0][*index] == '{')
    {
        root->type = MAP;
        parsePair(str,index, root);

    }
    else if(str[0][*index] == '\"')
    {
        root->type = STRING;
        parseStringToJson(str,index, root);  
    }
    else if(ft_isdigit(str[0][*index]))
    {
        root->type = INTEGER;
        parseIntToJson(str,index, root);
    }  

    return root;
}

int argo(json *dst, FILE *stream)
{
    char c;
    char *str = NULL;
    int i= 0;

    while(1)
    {
        i++;
        c = getc(stream);
        if(c < 0)
            break;
        str = realloc(str,i);
        str[i - 1] = c;
    }
    str[i] = 0;
    int index = 0;
    printf("%s\n",str);
}


int main (int argc, char *argv[])
{
    if(argc != 2)
        return 1;
    char *filename = argv[1];

    FILE *stream = fopen(filename,"r");
    json file;
    if(argo(&file,stream) != 1)
    {
        // printf("");
    }
}