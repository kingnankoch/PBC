#include "stdio.h"

// int main(){
//     FILE *fp = NULL;
//     fp = fopen("text.txt", "w+");
//     fprintf(fp, "This is testing for fprintf...\n");
 
//     // fscanf(fp, "%s", buff);
//     // printf("1: %s\n", buff );
//     fputs("This is testing for fputs...\n", fp);
//     fclose(fp);
// }



int main()
{
   FILE *fp = NULL;
   char buff[255];
 
   fp = fopen("test.txt", "r");
   fscanf(fp, "%s", buff);
   printf("1: %s\n", buff );
 
//    fgets(buff, 255, (FILE*)fp);
//    printf("2: %s\n", buff );
   
//    fgets(buff, 255, (FILE*)fp);
//    printf("3: %s\n", buff );
   fclose(fp);
 
}