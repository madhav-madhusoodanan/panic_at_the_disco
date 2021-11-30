int* reachable_from_all(unsigned int* links, int* websites, unsigned int side);
void menu_4_handler(char* names[], unsigned int* links, unsigned int side);
int is_reflexive(unsigned int* links, unsigned int side);
void print_website_names(char* names[], int* websites, unsigned int side);
int priint_menu_4();

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

void menu_4_handler(char* names[], unsigned int* links, unsigned int side){

    int option, bool;
    int websites[side];
    option = print_menu_4();

    while(option > 0 && option < 9){
        switch(option){
            case 1:
                /* display the hasse diagram */
                break;

            case 2:
                reachable_from_all(links, websites, side);
                print_website_names(names, websites, side);
                break;

            case 3:
                reachable_to_all(links, websites, side);
                print_website_names(names, websites, side);
                break;


            case 4:
                self_centred_websites_to(links, websites, side);
                print_website_names(names, websites, side);
                break;

            case 5:
                self_centred_websites_from(links, websites, side);
                print_website_names(names, websites, side);
                break;

            case 6:
                reachable_from_all(links, websites, side);
                print_website_names(names, websites, side);
                print_website_names_user_input(websites, side);
                break;

            case 7:
                reachable_to_all(links, websites, side);
                print_website_names(names, websites, side);
                print_website_names_user_input(websites, side);
                break;

            case 8:
            /* check for lattice */
                bool = greatest_lower_bounds(links, websites, side) && 
                             least_upper_bounds(links, websites, side);

                if(print_yes_or_no(bool))
                    menu_5_handler(names, links, side);
                break;

            default:
                break;
        }
    }

}

int is_reflexive(unsigned int* links, unsigned int side) {
    /* 
     *  Self linking websites are those websites which have a link to itself
     *  This is represented by having a "1" on the diagonal, at the coordinates that correspond to the 
     *  index of the website.
     * 
     *  For a minimum add, we only have to replace a "0" with a "1" at any point in the diagonal.
     */

    for (int i = 0; i < side; i++)
    {
        if(links[(side + 1) * i] == 0) {
            return 0;
        }
    }
    return 1;
}

int* reachable_from_all(unsigned int* links, int* websites, unsigned int side){
    /* returns an array, 1 for websites which can be reached from all, and 0 for those which can't */
    for (int i = 0; i < side; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < side; i++){
        /* i is the index of the destination we are gonna check */

        for(int j=0; j < side; j++){
            /* the looping */
            if(links[side * j + i] != 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}

void print_website_names(char* names[], int* websites, unsigned int side){
    for(int i = 0; i < side; i++){
        if(websites[i] == 1){
            printf("%d.: %s\n", i + 1, names[i]);
        }
    }
}