#include"definitions.h"

int print_menu_2() {
    char input = ' ';

    printf("Do you want to visualise how the network will look if we add minimum links to satisfy the property? [y/n]\n");
    printf("\n> ");
    scanf("%c", &input);

    if (input == 'n') return 0;
    else return 1;
}

int print_menu_3() {
    char input = ' ';

    printf("Do you want to know the nodes in each piece? [y/n]\n");
    printf("\n> ");
    scanf("%c", &input);

    if (input == 'n') return 0;
    else return 1;
}


void menu_2_handler(char* website_names[], int* links, int website_count, int menu){
    printf("\nDo you want to know how the network will look like if we add minimum links to satisfy property? [y/n]");

    char c;
    scanf(" %c", &c);
    if(c == 'n') return;

    switch(menu){
        case 1:
            to_self_linking_websites(links, website_count);
            break;
        case 2:
            to_symmetric(links, website_count);
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
