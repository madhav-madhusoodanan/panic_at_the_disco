
int print_menu_5() {
    printf("1. Given two websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach.\n");
    printf("2. Given two websites A and B, display the website which can reach to both A and B and is also reachable from all such websites that can reach to both A and B\n");
    printf("3. is the lattice distributable?\n");
    printf("4. Return to menu 4\n");

    printf("\n> ");

    int option;
    scanf("%d", &option);
    return option;
}



int menu_5_handler(char* names[], unsigned int* links, unsigned int side){
    int option;
    option = print_menu_5();
    int websites[side];
    int websites_in_question[2];
    switch (option)
    {
        case 1:
            lub_for_two_websites(links, websites_in_question, websites, side);
            print_website_names(names, websites, side);
            break;
    
        case 2:
            glb_for_two_websites(links, websites_in_question, websites, side);
            print_website_names(names, websites, side);
            break;

        case 3:
            break;

        default:
            break;
    }
}
