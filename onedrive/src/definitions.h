#ifndef DEFINITIONS
#define DEFINITIONS

    int print_menu_2();
    int print_menu_3();
    int print_menu_4();
    int print_menu_5();

    int is_reflexive(unsigned int* links, unsigned int website_count);
    int greatest_lower_bounds(unsigned int* links, unsigned int* websites, int website_count);
    int least_upper_bounds(unsigned int* links, unsigned int* websites, int website_count);
    int menu_5_handler(char* names[], unsigned int* links, unsigned int website_count);
    int print_main_menu();
    int is_transitive(unsigned int* links, unsigned int website_count);
    int to_transitive(unsigned int* links, unsigned int website_count);
    int is_there_a_shortcut(unsigned int* links, unsigned int website_count, unsigned int start, unsigned int end);
    int self_linking_websites(unsigned int* links, unsigned int website_count);
    int check_if_all_have_shortcuts(unsigned int* links, unsigned int website_count);
    int is_anti_symmetric(unsigned int* links, unsigned int website_count);
    int is_symmetric(unsigned int* links, unsigned int website_count);
    
    int* lub_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int website_count);
    int* glb_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int website_count);
    int* reachable_from_all(unsigned int* links, int* websites, unsigned int website_count);
    int* reachable_to_all(unsigned int* links, int* websites, unsigned int website_count);
    int* self_centred_websites_from(unsigned int* links, int* websites, unsigned int website_count);
    int* check_for_lattice(unsigned int* links, int* websites, unsigned int website_count);
    int* check_for_fully_linked_pieces(unsigned int* links, int* websites, unsigned int website_count);
    int* self_centred_websites_to(unsigned int* links, int* websites, unsigned int website_count);

    void menu_2_handler(char* website_names[], int* links, int website_count, int menu);
    void menu_4_handler(char* names[], unsigned int* links, unsigned int website_count);
    void convert_to_csv(char* websites[], unsigned int* links, unsigned int website_count);
    void extract(char* websites[], unsigned int* links, char* file);
    void print_website_names(char* names[], int* websites, unsigned int website_count);
    void to_self_linking_websites(unsigned int* links, int website_count);
    void matrix_to_hasse(unsigned int* links, unsigned int* hasse_links, int website_count);
    void to_symmetric(unsigned int* links, unsigned int website_count);

    #define TEMP_FILE "temp_file.csv"

#endif 