
int print_menu_4() {
    printf("1. Display the hasse diagram\n");
    printf("2. Display the website whose link is avaliable in every website\n");
    printf("3. Display the website which has links of every website\n");
    printf("4. Display the websites that do not have links to any other website except itself\n");
    printf("5. Display the websites which can't be reached from any other website except itself\n");
    printf("6. Given some websites, display the websites which are reachable from all of them\n");  /* User input enter krna pdega */
    printf("7. Given some websites, display the websites from which you can reach all those websites\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to main menu\n");

    printf("\n> ");

    int option;
    scanf("%d", &option);
    return option;
}

void menu_4_handler(char* names[], unsigned int* links, unsigned int website_count){

    int option, bool;
    int websites[website_count];
    option = print_menu_4();
    int hasse_links[website_count * website_count];

    for(int i = 0; i < website_count * website_count; i++){
        hasse_links[i] = 0;
    }

    while(option > 0 && option < 9){
        extract(names, links, "SampleInput.csv");   
        switch(option){
            case 1:
                /* display the hasse diagram */
                matrix_to_hasse(links, hasse_links, website_count);
                convert_to_csv(names, hasse_links, website_count);
                plot_hasse(TEMP_FILE);
                break;

            case 2:
                reachable_from_all(links, websites, website_count);
                print_website_names(names, websites, website_count);
                break;

            case 3:
                reachable_to_all(links, websites, website_count);
                print_website_names(names, websites, website_count);
                break;


            case 4:
                self_centred_websites_to(links, websites, website_count);
                print_website_names(names, websites, website_count);
                break;

            case 5:
                self_centred_websites_from(links, websites, website_count);
                print_website_names(names, websites, website_count);
                break;

            case 6:
                reachable_from_all(links, websites, website_count);
                print_website_names(names, websites, website_count);
                print_website_names_user_input(websites, website_count);
                break;

            case 7:
                reachable_to_all(links, websites, website_count);
                print_website_names(names, websites, website_count);
                print_website_names_user_input(websites, website_count);
                break;

            case 8:
            /* check for lattice */
                bool = greatest_lower_bounds(links, websites, website_count) && 
                             least_upper_bounds(links, websites, website_count);

                if(print_yes_or_no(bool))
                    menu_5_handler(names, links, website_count);
                break;

            default:
                break;
        }
        option = print_menu_4();
    }

}

int is_reflexive(unsigned int* links, unsigned int website_count) {
    /* 
     *  Self linking websites are those websites which have a link to itself
     *  This is represented by having a "1" on the diagonal, at the coordinates that correspond to the 
     *  index of the website.
     * 
     *  For a minimum add, we only have to replace a "0" with a "1" at any point in the diagonal.
     */

    for (int i = 0; i < website_count; i++)
    {
        if(links[(website_count + 1) * i] == 0) {
            return 0;
        }
    }
    return 1;
}

int* reachable_from_all(unsigned int* links, int* websites, unsigned int website_count){
    /* returns an array, 1 for websites which can be reached from all, and 0 for those which can't */
    for (int i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < website_count; i++){
        /* i is the index of the destination we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(links[website_count * j + i] != 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}

void print_website_names(char* names[], int* websites, unsigned int website_count){
    for(int i = 0; i < website_count; i++){
        if(websites[i] == 1){
            printf("%d.: %s\n", i + 1, names[i]);
        }
    }
}

int least_upper_bounds(unsigned int* links, unsigned int* websites, int website_count){
    int i;
    for (i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }

    for(int i=0; i < website_count; i++){
        /* i is the index of the destination we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(links[website_count * j + i] == 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    int count = 0;
    for (i = 0; i < website_count; i++)
    {
        count += websites[i];
    }
    
    return (count == 1);
}

int greatest_lower_bounds(unsigned int* links, unsigned int* websites, int website_count){
    int i;
    for (i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }

    for(int i=0; i < website_count; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(links[j] == 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    int count = 0;
    for (i = 0; i < website_count; i++)
    {
        count += websites[i];
    }
    
    return (count == 1);
}

