
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct json{
    enum {
        MAP,
        STRING,
        NUMBER,
    } type;
    union
    {
        struct {
            struct pair *pairs;
            size_t size;
            
        } map;
        char *string;
        int number;
    };
    
} json;

typedef struct pair{
    char *key;
    json *value;
} pair;

pair *parsePair(char **str);
json *parseValue(char **str);
json *parseMap(char **str);
json *parseString(char **str);
json *parseNumber(char **str);

pair *parsePair(char **str)
{
    pair *p = malloc(sizeof(pair));
    p->key = parseValue(str)->string;
    if(**str != ':') {
        printf("Error\n");
        exit(1);
    }
    (*str)++;
    p->value = parseValue(str);
    return p;
}

json *parseValue(char **str)
{
    if(**str == '{') {
        return parseMap(str);
    } else if(**str == '"') {
        return parseString(str);
    } else {
        return parseNumber(str);
    }
}

json *parseMap(char **str)
{
    json *j = malloc(sizeof(json));
    j->type = MAP;
    j->map.size = 0;
    j->map.pairs = NULL;
    (*str)++;
    while(**str != '}') {
        j->map.size++;
        j->map.pairs = realloc(j->map.pairs, j->map.size * sizeof(pair));
        j->map.pairs = parsePair(str);
        if(**str == ',') {
            (*str)++;
        }
    }
    (*str)++;
    return j;
}

json *parseString(char **str)
{
    json *j = malloc(sizeof(json));
    j->type = STRING;
    (*str)++;
    char *start = *str;
    while(**str != '"') {
        (*str)++;
    }
    j->string = malloc(*str - start + 1);
    strncpy(j->string, start, *str - start);
    j->string[*str - start] = '\0';
    (*str)++;
    return j;
}

json *parseNumber(char **str)
{
    json *j = malloc(sizeof(json));
    j->type = NUMBER;
    j->number = 0;
    while(**str >= '0' && **str <= '9') {
        j->number = j->number * 10 + **str - '0';
        (*str)++;
    }
    return j;
}

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error\n");
        return 1;
    }
    int i = 0;
    char c;

    char *str = malloc(500);
    while((c = fgetc(f)) != EOF) {
        str[i++] = c;
    }
    str[i] = '\0';
    fclose(f);
    pair *p = parsePair(&str);
    printf("%s\n", p->key);
    printf("%s\n", p->value->map.pairs[0].key);
    


    return 0;
}