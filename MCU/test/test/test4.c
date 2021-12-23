#include "stdio.h"
#define message_for(a, b) printf(#a " and  " #b " will" )

int main() {
    printf("File %s \n", __FILE__);
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    printf("Line :%d\n", __LINE__ );
    printf("ANSI :%d\n", __STDC__ );
    message_for(yy, ll);
    return 0;
}

