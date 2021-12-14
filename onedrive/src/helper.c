#include<stdio.h>

int print_yes_or_no(int true){
    if (true)
    {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
    return true;
}

void cleanup(char* names[], unsigned int website_count) {
    for (int i = 0; i < website_count; i++)
    {
        free(names[i]);
    }
    free(names);
    // free(links);
}

int tokenizer(char* str) {
    const int len = strlen(str);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == ',' || str[i] == ' ')
        {
            str[i] = '\0';
            break;
        }
    }
    
    return i + 1;
}

void nameTokenizer(char* names[], char* str, int count){
    const int len = strlen(str);
    int i = 0, x = 0;
    for (i = 0; i < len && x < count; i++)
    {
        if (str[i] == ',' || str[i] == '\n' || str[i] == ' ') str[i] = '\0';
    }

    for (i = 0; i < len && x < count; i++)
    {
        if (str[i] == '\0')
        {
            names[x] = malloc(100 * sizeof(char));
            strcpy(names[x], &str[i + 1]);

            x += 1;
        }
    }
}


unsigned int integerify(char* number) {
    /* This function returns 0 if the string passed is "0", else it returns 1 */
    return number[0] == '0' ? 0 : 1;
}

char stringify(int number){
    /* does the exact opposite of integerify */
    return number == 1 ? '1' : '0';
}



int print_website_names_user_input(int* websites, unsigned int website_count){
    char input[5];
    int index = 0;

    printf("\nenter the websites' numbers one line at a time for details\n");
    scanf("%s", input);
    for (; input[0] !='q' ;)
    {
        sscanf(input, "%d", &index);
        if(index > 0 && index < website_count && websites[index] == 1) printf("YES");
        else printf("NO");
        
        scanf("%s", input);
    }
    
}
