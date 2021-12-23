#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char name[100];
    char *description;
    strcpy(name,  "kingnan");
    description = (char *) malloc(30 * sizeof(char));
    printf(" === %s \n", description);


    description = (char *) realloc(description, 200 * sizeof(char));
    printf("Name = %s \n", name);
    printf("description %s \n", description);
    printf("description %lu \n", sizeof(description));
    
    free(description);
    
    return 0;
}