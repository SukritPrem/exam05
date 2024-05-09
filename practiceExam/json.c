#include "stdio.h"
#include "stdlib.h"

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

json *parseJson(char *str, int *index);
char *parseString(char *str, int *index);
int parseInt(char *str, int *index);
int ftatoi(char *str);

int ftisdigit(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}

int ftatoi(char *str)
{
    if(*str == '\0')
        return 0;
    else
        return (*str - '0') * 10 + ftatoi(str + 1);
}

int peek(char *str,int *index, int c)
{
    while(str[*index] == ' ')
        (*index)++;
    return str[*index] == c;
}
int parseInt(char *str, int *index)
{
    int start = *index;
    while(1)
    {
        if(ftisdigit(str[*index]))
            *index++;
        else
            break;
        if(str[*index == '}'])
            break;
    }
    int end = *index;
    int len = end - start;
    char *tmpStr = malloc(sizeof(char) * len);
    int i = 0;
    while(i < len)
    {
        tmpStr[i++] = str[start++];
    }
    tmpStr[i] = '\0';
    return ftatoi(tmpStr);
}

void parseIntToJson(char *str, int *index, json *root)
{
    root->interger = parseInt(str, index);
}

void parseStringToJson(char *str, int *index, json *root)
{
    root->string = parseString(str,index);
}

char *parseString(char *str, int *index)
{
    (*index)++; //skip "
    int start = *index;
    while(1)
    {
        if(str[*index] == '\"')
            break;
        if(str[*index] == '\0')
        {
            printf("error string null\n");
            break;
        }
        (*index)++;
    }
    if(str[*index] != '\"')
    {
        printf("error end \" \n");
        return NULL;
    }   
    int end = *index;
    int len = (end - start);
    int i = 0;
    char *tmpStr = malloc(sizeof(char) * len);
    while(i < len)
    {
        tmpStr[i] = str[start];
        i++;
        start++;
    }
    (*index)++;//skip "
    return tmpStr;
}

void parsePair(char *str,int *index, json *root)
{
    (*index)++;//skip "{"
    pair *map = malloc(sizeof(pair));
    map->key = parseString(str, index);
    // printf("key = %s\n",map->key);
    // printf("index = %c\n",str[*index]);
    if(str[*index] != ':')
        return;
    (*index)++;//skip ":"
    json *value = parseJson(str, index);
    map->value = *value;
    root->map.data = map;
    root->map.size++;
    // printf("map = %s\n",map->key);
    if(str[*index] != '}')
        return;
    (*index)++;//skip "}"
}

json *parseJson(char *str, int *index)
{
    json *root = malloc(sizeof(json));
    if(str[*index] == '{')
    {
        root->type = MAP;
        parsePair(str,index,root);
        return root;
    }
    if(str[*index] == '"')
    {
        root->type = STRING;
        parseStringToJson(str,index,root);
        return root;
    }
    if(isdigit(str[*index]))
    {
        root->type = INTEGER;
        parseIntToJson(str,index,root);
        return root;
    }

    return NULL;
    // printf("root type = %d\n",root->type);
}
int argo(json *dst, FILE *stream)
{
    char *str ;
    char c;
    int i = 0;
    // c = getc(stream);
    while(1)
    {
        i++;
        c = getc(stream);
        if(c == -1)
            break;
        str = realloc(str, i);
        str[i - 1] = c;
    }
    str[i] = 0;
    int index = 0;
    // printf("str : %s\n",str);
    // printf("str :%c\n",str[0]);
    // dst = parseJson(str, &index);
    // printf("index : %d\n",index);
    // printf("dst = %s\n",dst->map.data->value.map.data->value.string);
    return 0;
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
        printf("");
    }
}
