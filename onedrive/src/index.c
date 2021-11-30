#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#include"definitions.h"
#include"visualiser.c"
#include"helper.c"
#include"csv_handler.c"
#include"menu_5.c"
#include"menu_4.c"
#include"menu_2_3.c"
#include"menu_1.c"


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

            if (!print_yes_or_no(is_poset == 0))
                menu_4_handler(website_names, links, website_count);
            break;

        default:
            break;
        }
        option = print_main_menu();
    }
    cleanup(website_names, /* links, */ website_count);
}