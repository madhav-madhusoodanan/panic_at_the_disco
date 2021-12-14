

int is_transitive(unsigned int* links, unsigned int website_count){
    for(int i = 0; i < website_count; i++){
        for(int j = 0; j < website_count; j++){
            for(int k = 0; k < website_count; k++){
                if(
                    links[i * website_count + j] &&
                    links[j * website_count + k]
                ) 
                if(!links[i * website_count + k])
                    return 0;
            }
        }
    }
    return 1;
}


int is_there_a_shortcut(unsigned int* links, unsigned int website_count, unsigned int start, unsigned int end){
    if(links[start * website_count + end]) return 1;

    printf("\n%d\t%d", start, end);
    for(int i = 0; i < website_count; i++)
        if(links[start * website_count + i]) 
            if(is_there_a_shortcut(links, website_count, i, end))
                return 1;

    return 0;
}

int check_if_all_have_shortcuts(unsigned int* links, unsigned int website_count){
    for(int i = 0; i < website_count; i++)
        for(int j = 0; j < website_count; j++)
            if(is_there_a_shortcut(links, website_count, i, j) == 0) 
                return 0;

    return 1;
}

int is_anti_symmetric(unsigned int* links, unsigned int website_count){
    for(int i = 0; i < website_count; i++) {
        for(int j = i + 1; j < website_count; j++) {
            if(i != j && links[(i * website_count) + j] && links [(j * website_count) + i]) {
                return 0;
            }
        }
    }
    return 1;
}

int is_symmetric(unsigned int* links, unsigned int website_count) {
    /* 
     * Symmetric matrices means a matrix whose transpose will equal itself.
     * the speciality of this matrix is that it is possible to go to the previous website from the current website
     * in one go.
     * 
     * For a minimum add, we must make it symmetric.
     * 
     *  */

    for(int i = 0; i < website_count; i++) {
        for(int j = i + 1; j < website_count; j++) {
            if(links[(i * website_count) + j] != links [(j * website_count) + i]) {
                return 0;
            }
        }
    }
    return 1;
}

void to_symmetric(unsigned int* links, unsigned int website_count) {
    /* 
     * Symmetric matrices means a matrix whose transpose will equal itself.
     * the speciality of this matrix is that it is possible to go to the previous website from the current website
     * in one go.
     * 
     * For a minimum add, we must make it symmetric.
     * 
     *  */

    for(int i = 0; i < website_count; i++) {
        for(int j = i + 1; j < website_count; j++) {
            if(links[(i * website_count) + j] != links [(j * website_count) + i]) {
                
                links[(i * website_count) + j] = 1;
                links [(j * website_count) + i] = 1;
            }
        }
    }
}

int* reachable_to_all(unsigned int* links, int* websites, unsigned int website_count){
    /* returns an array, 1 for websites which can be reached from all, and 0 for those which can't */

    for (int i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < website_count; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(links[j] != 1) {
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}

int self_linking_websites(unsigned int* links, unsigned int website_count){
    for(int i = 0; i < website_count; i++){
        if(links[i * (website_count + 1)] == 1) return 1;
    }
    return 0;
}

void to_self_linking_websites(unsigned int* links, int website_count){
    for(int i = 0; i < website_count; i++){
        links[(website_count + 1) * i] = 1;
    }
}

int* self_centred_websites_from(unsigned int* links, int* websites, unsigned int website_count){

    for (int i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < website_count; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(i != j && links[i * website_count + j] == 1) {
                websites[j] = 0;
                break;
            }
            if(i == j && links[i * website_count + j] == 0){
                websites[j] = 0;
                break;
            }
        }

    }

    return websites;
}


int* check_for_lattice(unsigned int* links, int* websites, unsigned int website_count){
    return websites;
}

int* check_for_fully_linked_pieces(unsigned int* links, int* websites, unsigned int website_count){
    /* check for pieces */
    return websites;
}

int* self_centred_websites_to(unsigned int* links, int* websites, unsigned int website_count){

    for (int i = 0; i < website_count; i++)
    {
        websites[i] = 1;
    }
    

    for(int i=0; i < website_count; i++){
        /* i is the index of the source we are gonna check */

        for(int j=0; j < website_count; j++){
            /* the looping */
            if(i != j && links[i * website_count + j] == 1) {
                websites[i] = 0;
                break;
            }
            if(i == j && links[i * website_count + j] == 0){
                websites[i] = 0;
                break;
            }
        }

    }

    return websites;
}



void matrix_to_hasse(unsigned int* links, unsigned int* hasse_links, int website_count){
    for (int i = 0; i < website_count; i++)
    {
        links[(website_count + 1) * i] = 0;
    }

    for (int i = 0; i < website_count; i++)
    {
        for (int j = 0; j < website_count; j++)
        {
            if(i == j) break;

            for (int k = 0; k < website_count; k++)
            {
                if(j == k || i == k)
                    break;

                if(links[i * website_count + j] && links[j * website_count + k] && links[i * website_count + k]) 
                    links[i * website_count + k] = 0;
            }
        }
    }
}



int print_main_menu() {
    printf("\n1. Does every website has a link to itself?\n");
    printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
    printf("3. Does every website has all the links to the websites which are reachable from it?\n");
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
