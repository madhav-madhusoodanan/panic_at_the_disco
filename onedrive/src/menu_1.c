

int is_transitive(unsigned int* links, unsigned int side){
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            for(int k = 0; k < side; k++){
                if(
                    links[i * side + j] &&
                    links[j * side + k]
                ) 
                if(!links[i * side + k])
                    return 0;
            }
        }
    }
    return 1;
}


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
            if(is_there_a_shortcut(links, side, i, j) == 0) return 0;
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

void to_symmetric(unsigned int* links, unsigned int side) {
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
                
                links[(i * side) + j] = 1;
                links [(j * side) + i] = 1;
            }
        }
    }
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

void to_self_linking_websites(unsigned int* links, int side){
    for(int i = 0; i < side; i++){
        links[(side + 1) * i] = 1;
    }
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
