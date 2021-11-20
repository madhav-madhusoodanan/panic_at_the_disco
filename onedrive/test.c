#include<stdio.h>
#include<string.h>

void main(){
    /* char str[] = {'1', '1', '\0', '3', '5'};
    printf("%ld", strlen(str)); */

    char str[] = {'\0', '2', ',', '4'};
    strcat(str, ",");
    printf("%s", str);
}