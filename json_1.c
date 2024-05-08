#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct json{
    enum {
        MAP,
        STRING,
        NUMBER,
    } type;
    union {
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

json* parse_json(char *json_str);

void free_json(json *root);

void print_json(json *root);

void parse_map(json *root,char *json_str, int *index);

void parse_string(json *root, char *json_str, int *index);

void parse_number(json *root, char *json_str, int *index);

pair* parse_pair(char *json_str, int *index);

char* parse_key(char *json_str, int *index);

char* parse_value(char *json_str, int *index);

int main(int argc, char *argv[]) {
    
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
    json *root = parse_json(str);
    print_json(root);
    // free_json(root);
    return 0;
}

json* parse_json(char *json_str) {
    int index = 0;
    json *root = malloc(sizeof(json));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    if (json_str[index] == '{') {
        root->type = MAP;
        parse_map(root, json_str, &index);
    }
    if (json_str[index] == '"') {
        root->type = STRING;
        parse_string(root, json_str, &index);
    }
    return root;
}

void parse_map(json *root,char *json_str, int *index) {
    (*index)++; // Skip '{'
    while (json_str[*index] != '}' && json_str[*index] != '\0') {
        pair *p = parse_pair(json_str, index);
        root->map.size++;
        root->map.pairs = realloc(root->map.pairs, root->map.size * sizeof(pair));
        if (root->map.pairs == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        root->map.pairs[root->map.size - 1] = *p;
    }
    (*index)++; // Skip '}'
}

pair* parse_pair(char *json_str, int *index) {
    pair *p = malloc(sizeof(pair));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->key = parse_key(json_str, index);
    if (json_str[*index] == ':') (*index)++;
    p->value = malloc(sizeof(json));
    if (p->value == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    if (json_str[*index] == '{') {
        p->value->type = MAP;
        parse_map(p->value, json_str, index);
    } else if (json_str[*index] == '"') {
        p->value->type = STRING;
        parse_string(p->value, json_str, index);
    } else {
        p->value->type = NUMBER;
        parse_number(p->value, json_str, index);
    }
    return p;
}

char* parse_key(char *json_str, int *index) {
    char *key = NULL;
    int start = ++(*index); // Skip '"'
    while (json_str[*index] != '"') (*index)++;
    int end = *index;
    int len = end - start;
    key = malloc((len + 1) * sizeof(char));
    if (key == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(key, json_str + start, len);
    key[len] = '\0';
    (*index)++; // Skip '"'
    (*index)++; // Skip ':'
    return key;
}

void parse_string(json *root,char *json_str, int *index) {
    (*index)++; // Skip '"'
    int start = *index;
    while (json_str[*index] != '"') (*index)++;
    int end = *index;
    int len = end - start;
    root->string = malloc((len + 1) * sizeof(char));
    if (root->string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(root->string, json_str + start, len);
    root->string[len] = '\0';
    (*index)++; // Skip '"'
}

void parse_number(json *root,char *json_str, int *index) {
    int start = *index;
    while ((json_str[*index] >= '0' && json_str[*index] <= '9') || json_str[*index] == '-') (*index)++;
    int end = *index;
    int len = end - start;
    char *num_str = malloc((len + 1) * sizeof(char));
    if (num_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(num_str, json_str + start, len);
    num_str[len] = '\0';
    root->number = atoi(num_str);
    free(num_str);
}

void print_json(json *root) {
    if (root->type == MAP) {
        printf("{\n");
        for (size_t i = 0; i < root->map.size; i++) {
            printf("\"%s\": ", root->map.pairs[i].key);
            print_json(root->map.pairs[i].value);
            if (i != root->map.size - 1)
                printf(",\n");
        }
        printf("\n}");
    } else if (root->type == STRING) {
        printf("\"%s\"", root->string);
    } else if (root->type == NUMBER) {
        printf("%d", root->number);
    }
}

// void free_json(json *root) {
//     if (root->type == MAP) {
//         for (size_t i = 0; i < root->map.size; i++) {
//             free(root->map.pairs[i].key);
//             free_json(root->map.pairs[i].value);
//             free(root->map.pairs[i].value);
//         }
//         free(root->map.pairs);
//     } else if (root->type == STRING) {
//         free(root->string);
//     }
//     free(root);
// }
