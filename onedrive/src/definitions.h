#ifndef DEFINITIONS
#define DEFINITIONS

    int print_menu_2();
    int print_menu_3();
    int print_menu_4();
    int print_menu_5();

    int is_reflexive(unsigned int* links, unsigned int side);
    int greatest_lower_bounds(unsigned int* links, unsigned int* websites, int side);
    int least_upper_bounds(unsigned int* links, unsigned int* websites, int side);
    int menu_5_handler(char* names[], unsigned int* links, unsigned int side);

    int* lub_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int side);
    int* glb_for_two_websites(unsigned int* links, int* websites_in_question, int* websites, unsigned int side);
    int* reachable_from_all(unsigned int* links, int* websites, unsigned int side);

    void menu_2_handler(char* website_names[], int* links, int website_count, int menu);
    void menu_4_handler(char* names[], unsigned int* links, unsigned int side);
    void print_website_names(char* names[], int* websites, unsigned int side);

    #define TEMP_FILE "temp_file.csv"
    
#endif 