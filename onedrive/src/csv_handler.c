#include"definitions.h"
#include<stdio.h>
void convert_to_csv(char* websites[], unsigned int* links, unsigned int website_count);
void extract(char* websites[], unsigned int* links, char* file);

void convert_to_csv(char* websites[], unsigned int* links, unsigned int website_count){
    FILE* fp;
    fp = fopen(TEMP_FILE, "w+");
    for (int i = 0; i < website_count; i++)
    {
        fprintf(fp, ",%s", websites[i]);

    }
    fprintf(fp, "\n");


    /* TODO the code after this is segfaulting. Find out why */
    for (int i = 0; i < website_count; i++)
    {
        /* output to csv file */
        fprintf(fp, "%s", websites[i]);
        printf("%s", websites[i]);
        for(int j = 0; j < website_count; j++)
        {
            fprintf(fp, ",%d", links[i * website_count + j]);

        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void extract(char* websites[], unsigned int* links, char* file) {
    /* This function tries to extract the relation matrix from the csv file */

    FILE* fp;
    char input[500];
    char* temp = NULL;

    unsigned int website_count = count_number_of_websites(file);
    unsigned int i = 0;

    fp = fopen(file, "r");

    /* Extract the very first line, the list of all websites */
    
    fscanf(fp, "%s", input);

    nameTokenizer(websites, input, website_count);
    
    /* Go in a loop and extract all the data from each line */
    for(int i = 0; i < website_count; i++) {
        fscanf(fp,"%s", input);
        temp = input;   

        /* dropping the first string which is the website name */
        temp = temp + tokenizer(temp);

        for (int j = 0; j < website_count; j++){
            links[i * website_count + j] = integerify(temp);
            temp = temp + tokenizer(temp);
        }
        // printf("\n");
    }
}

