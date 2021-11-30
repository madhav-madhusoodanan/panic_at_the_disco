#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#include"hasse.c"
#include"menu_4.c"
#include"menu_5.c"

#define TEMP_FILE "temp_file.csv"


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

unsigned int count_number_of_websites(char* file) {
    /* 
     * Just counting the number of websites will be taking into consideration
     * I'll simply count the number of lines, subtract 1 and return
     * ( because the 1st line displays the list of the websites, 
     * while the rest of the lines shows the links of each of the websites)
     * 
     *  */

    unsigned int count = 0;
    char dummy[100];
    FILE *fp = fopen(file, "r");

    while (fscanf(fp, "%s", dummy) == 1){
        count += 1;
    }

    return (count - 1);
}

unsigned int integerify(char* number) {
    /* This function returns 0 if the string passed is "0", else it returns 1 */
    return number[0] == '0' ? 0 : 1;
}

char stringify(int number){
    /* does the exact opposite of integerify */
    return number == 1 ? '1' : '0';
}

int is_transitive(unsigned int* links, unsigned int side){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            for(int k = 0; k < side; k++){
                if(
                    !links[i * side + j] || 
                    !links[j * side + k] || 
                    !links[i * side + k]
                ) 
                    return 0;
            }
        }
    }
    return 1;
}

int to_transitive(unsigned int* links, unsigned int side){}

int is_there_a_shortcut(unsigned int* links, unsigned int side, unsigned int start, unsigned int end){
    if(start == end) return 1;
    else if(links[start* side + end]) return 1;

    for(int i = 0; i < side; i++){
        if(links[start * side + i] && is_there_a_shortcut(links, side, i, end)) return 1;
    }
    return 0;
}

int check_if_all_have_shortcuts(unsigned int* links, unsigned int side){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            if(is_there_a_shortcut(links, side, i, j) == 0)return 0;
        }
    }
    return 1;
}

int is_anti_symmetric(unsigned int* links, unsigned int side){
    for(int i = 0; i < side; i++) {
        for(int j = i + 1; j < side; j++) {
            if(links[(i * side) + j] == 1 && links [(j * side) + i] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

int is_symmetric(unsigned int* links, unsigned int side) {
    /* 
     * Symmetric matrices means a matrix whose transpose will equal itself.
     * the speciality of this matrix is that it is possible to go to the previous website from the current website
     * in one go.
     * 
     * For a minimum add, we must make it symmetric.
     * 
     *  */

    for(int i = 0; i < side; i++) {
        for(int j = i + 1; j < side; j++) {
            if(links[(i * side) + j] != links [(j * side) + i]) {
                return 0;
            }
        }
    }
    return 1;
}



int* reachable_to_all(unsigned int* links, int* websites, unsigned int side){
    /* returns an array, 1 for websites which can be reached from all, and 0 for those which can't */

    for (int i = 0; i < side; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < side; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(links[j] != 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}

int self_linking_websites(unsigned int* links, unsigned int side){
    for(int i = 0; i < side; i++){
        if(links[i * (side + 1)] == 1) return 1;
    }
    return 0;
}

void to_self_linking_websites(unsigned int* links){
    links[0] = 1;
}

int* self_centred_websites_from(unsigned int* links, int* websites, unsigned int side){

    for (int i = 0; i < side; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < side; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(i != j && links[i * side + j] == 1) {
                websites[j] = 0;
                break;
            }
            if(i == j && links[i * side + j] == 0){
                websites[j] = 0;
                break;
            }
        }

    }

    return websites;
}

int* lub_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int side){
    /* websites in question have the indices of the websites in question, not 0 or 1 */
    /* they are of size 2, (a and b) */

    for (int i = 0; i < side; i++)
    {
        /* 1. find out websites that are common destination
            2. find out if all 3 have the same destinations including the 3rd one */
        websites[i] = 0;

        int a_coordinate = websites_in_question[0] * side + i;
        int b_coordinate = websites_in_question[1] * side + i;
        if(links[a_coordinate] && links[b_coordinate]) websites[i] = 1;
    }

    websites[websites_in_question[0]] = 1;
    websites[websites_in_question[1]] = 1;
    
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if(websites[j]){
                if(!links[j * side + i] && j != websites_in_question[0] && j != websites_in_question[1])
                    websites[j] = 0;
            }
        }
    }
    
    websites[websites_in_question[0]] = 0;
    websites[websites_in_question[1]] = 0;

    return websites;
}

int* glb_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int side){
    /* websites in question have the indices of the websites in question, not 0 or 1 */
    /* they are of size 2, (a and b) */

    for (int i = 0; i < side; i++)
    {
        /* 1. find out websites that are common destination
            2. find out if all 3 have the same destinations including the 3rd one */
        websites[i] = 0;

        int a_coordinate = websites_in_question[0] + side * i;
        int b_coordinate = websites_in_question[1] + side * i;
        if(links[a_coordinate] && links[b_coordinate]) websites[i] = 1;
    }

    websites[websites_in_question[0]] = 1;
    websites[websites_in_question[1]] = 1;
    
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if(websites[j]){
                if(!links[i * side + j] && j != websites_in_question[0] && j != websites_in_question[1])
                    websites[j] = 0;
            }
        }
    }
    
    websites[websites_in_question[0]] = 0;
    websites[websites_in_question[1]] = 0;

    return websites;
}

int* check_for_lattice(unsigned int* links, int* websites, unsigned int side){
    return websites;
}

int* check_for_fully_linked_pieces(unsigned int* links, int* websites, unsigned int side){
    /* check for pieces */
    return websites;
}

int* self_centred_websites_to(unsigned int* links, int* websites, unsigned int side){

    for (int i = 0; i < side; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < side; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(i != j && links[i * side + j] == 1) {
                websites[i] = 0;
                break;
            }
            if(i == j && links[i * side + j] == 0){
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}

int least_upper_bounds(unsigned int* links, unsigned int* websites, int side){
    int i;
    for (i = 0; i < side; i++)
    {
        websites[i] = 1;
    }

    for(int i=0; i < side; i++){
        /* i is the index of the destination we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(links[side * j + i] == 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    int count = 0;
    for (i = 0; i < side; i++)
    {
        count += websites[i];
    }
    
    return (count == 1);
}

int greatest_lower_bounds(unsigned int* links, unsigned int* websites, int side){
    int i;
    for (i = 0; i < side; i++)
    {
        websites[i] = 1;
    }

    for(int i=0; i < side; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(links[j] == 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    int count = 0;
    for (i = 0; i < side; i++)
    {
        count += websites[i];
    }
    
    return (count == 1);
}

void convert_to_csv(char* websites[], unsigned int* links, unsigned int website_count){
    FILE* fp;
    fp = fopen(TEMP_FILE, "w+");
    for (int i = 0; i < website_count; i++)
    {
        fprintf(fp, ",%s", websites[i]);

    }
    fprintf(fp, "\n");


    /* TODO the code after this is segfaulting. Find out why */
    for (int i = 0; i < website_count; i++)
    {
        /* output to csv file */
        fprintf(fp, "%s", websites[i]);
        printf("%s", websites[i]);
        for(int j = 0; j < website_count; j++)
        {
            fprintf(fp, ",%d", links[i * website_count + j]);

        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void matrix_to_hasse(unsigned int* links, unsigned int* hasse_links, int side){
    for (int i = 0; i < side; i++)
    {
        links[(side + 1) * i] = 0;
    }

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if(i == j) break;

            for (int k = 0; k < side; k++)
            {
                if(j == k || i == k)
                    break;

                if(links[i * side + j] && links[j * side + k] && links[i * side + k]) 
                    links[i * side + k] = 0;
            }
        }
    }
}

void extract(char* websites[], unsigned int* links, char* file) {
    /* This function tries to extract the relation matrix from the csv file */

    FILE* fp;
    char input[500];
    char* temp = NULL;

    unsigned int website_count = count_number_of_websites(file);
    unsigned int i = 0;

    fp = fopen(file, "r");

    /* Extract the very first line, the list of all websites */
    
    fscanf(fp, "%s", input);

    nameTokenizer(websites, input, website_count);
    
    /* Go in a loop and extract all the data from each line */
    for(int i = 0; i < website_count; i++) {
        fscanf(fp,"%s", input);
        temp = input;   

        /* dropping the first string which is the website name */
        temp = temp + tokenizer(temp);

        for (int j = 0; j < website_count; j++){
            links[i * website_count + j] = integerify(temp);
            temp = temp + tokenizer(temp);
        }
        // printf("\n");
    }
}


int print_yes_or_no(int true){
    if (true)
    {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
    return true;
}

int print_main_menu() {
    printf("1. Does every website has a link to itself?\n");
    printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
    printf("3. Does every website has all th links to the websites which are reachable from it?\n");
    printf("4. Does there exist any website that contains a link to itself?\n");
    printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
    printf("6. Is it impossible to return to the previous website from the current website in one step (excluding the cases where the current and previous website is the same)?\n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that place?\n");
    printf("8. Is this relation an example of poset?\n");
    printf("9. Exit\n");

    printf("\n> ");
    
    int option;
    scanf("%d", &option);
    return option;
}

int print_menu_2() {
    char input = ' ';

    printf("Do you want to visualise how the network will look if we add minimum links to satisfy the property? [y/n]\n");
    printf("\n> ");
    scanf("%c", &input);

    if (input == 'n') return 0;
    else return 1;
}

void cleanup(char* names[], unsigned int website_count) {
    for (int i = 0; i < website_count; i++)
    {
        free(names[i]);
    }
    free(names);
    // free(links);
}

int print_menu_3() {
    char input = ' ';

    printf("Do you want to know the nodes in each piece? [y/n]\n");
    printf("\n> ");
    scanf("%c", &input);

    if (input == 'n') return 0;
    else return 1;
}


int print_website_names_user_input(int* websites, unsigned int side){
    char input[5];
    int index = 0;

    printf("\nenter the websites' numbers one line at a time for details\n");
    scanf("%s", input);
    for (; input[0] !='q' ;)
    {
        sscanf(input, "%d", &index);
        if(index > 0 && index < side && websites[index] == 1) printf("YES");
        else printf("NO");
        
        scanf("%s", input);
    }
    
}


void menu_2_handler(char* website_names[], int* links, int website_count, int menu){
    printf("\nDo you want to know how the network will look like if we add minimum links to satisfy property? [y/n]");

    char c;
    scanf("%c", &c);
    if(c == 'n') return;

    switch(menu){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 7:
            break;

        default:
            break;
    }

    convert_to_csv(website_names, links, website_count);
    plot(TEMP_FILE);
}


int main() {
    unsigned int website_count = count_number_of_websites("SampleInput.csv");
    char* website_names[website_count];
    unsigned int links[website_count * website_count];
    extract(website_names, links, "SampleInput.csv");
    
    int option = 0;
    option = print_main_menu();
    int is_poset;

    while (option > 0 && option < 9) {
        switch (option)
        {
        case 1:
            if (print_yes_or_no(is_reflexive(links, website_count) == 0))
                menu_2_handler(website_names, links, website_count, 1);
            break;
        
        case 2:
            if (print_yes_or_no(is_symmetric(links, website_count) == 0))
                menu_2_handler(website_names, links, website_count, 2);
            break;

        case 3: 
            /* just confirm what the question actually means... */
            if (print_yes_or_no(check_if_all_have_shortcuts(links, website_count) == 0))
                    menu_2_handler(website_names, links, website_count, 3);
            exit(0);

        case 4:
            print_yes_or_no(self_linking_websites(links, website_count) == 0);
            break;

        case 5:
            print_yes_or_no(is_symmetric(links, website_count) == 1);
            break;

        case 6:
        /* TODO confirm what the question means */
            plot(TEMP_FILE);

        case 7: 
            /* complete this */
            if(1)
                menu_2_handler(website_names, links, website_count, 7);
            break;

        case 8:
            is_poset = is_transitive(links, website_count) && 
                           is_anti_symmetric(links, website_count) && 
                           is_reflexive(links, website_count);

            if (print_yes_or_no(is_poset))
                menu_4_handler(website_names, links, website_count);
            break;

        default:
            break;
        }
        option = print_main_menu();
    }
    cleanup(website_names, /* links, */ website_count);
}


/* 

* * * * * * *
* * * * * * *
* * * * * * *
* * * * * * *
* * * * * * *

 */

/* TODO:

1. finish up menu 4 */

/* HARD THINGS
1. menu 5
2. hasse diagrams */

