
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



int menu_5_handler(char* names[], unsigned int* links, unsigned int website_count){
    int option;
    option = print_menu_5();
    int websites[website_count];
    int websites_in_question[2];
    switch (option)
    {
        case 1:
            lub_for_two_websites(links, websites_in_question, websites, website_count);
            print_website_names(names, websites, website_count);
            break;
    
        case 2:
            glb_for_two_websites(links, websites_in_question, websites, website_count);
            print_website_names(names, websites, website_count);
            break;

        case 3:
            break;

        default:
            break;
    }
}

int* lub_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int website_count){
    /* websites in question have the indices of the websites in question, not 0 or 1 */
    /* they are of size 2, (a and b) */

    for (int i = 0; i < website_count; i++)
    {
        /* 1. find out websites that are common destination
            2. find out if all 3 have the same destinations including the 3rd one */
        websites[i] = 0;

        int a_coordinate = websites_in_question[0] * website_count + i;
        int b_coordinate = websites_in_question[1] * website_count + i;
        if(links[a_coordinate] && links[b_coordinate]) websites[i] = 1;
    }

    websites[websites_in_question[0]] = 1;
    websites[websites_in_question[1]] = 1;
    
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if(websites[j]){
                if(!links[j * website_count + i] && j != websites_in_question[0] && j != websites_in_question[1])
                    websites[j] = 0;
            }
        }
    }
    
    websites[websites_in_question[0]] = 0;
    websites[websites_in_question[1]] = 0;

    return websites;
}

int* glb_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int website_count){
    /* websites in question have the indices of the websites in question, not 0 or 1 */
    /* they are of size 2, (a and b) */

    for (int i = 0; i < website_count; i++)
    {
        /* 1. find out websites that are common destination
            2. find out if all 3 have the same destinations including the 3rd one */
        websites[i] = 0;

        int a_coordinate = websites_in_question[0] + website_count * i;
        int b_coordinate = websites_in_question[1] + website_count * i;
        if(links[a_coordinate] && links[b_coordinate]) websites[i] = 1;
    }

    websites[websites_in_question[0]] = 1;
    websites[websites_in_question[1]] = 1;
    
    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if(websites[j]){
                if(!links[i * website_count + j] && j != websites_in_question[0] && j != websites_in_question[1])
                    websites[j] = 0;
            }
        }
    }
    
    websites[websites_in_question[0]] = 0;
    websites[websites_in_question[1]] = 0;

    return websites;
}
