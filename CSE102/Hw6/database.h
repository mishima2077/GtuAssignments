#ifndef _DATABASE_H_
#define _DATABASE_H_
#define MAX_ENTRY 200 //Max amount of entries allowed 
#define MAX_FEAT 10 //Max number of extra features allowed
#define MAX_STOCK 20 //Max number of stock values the report will handle

/*-----------------------------------------------------Main functions-----------------------------------------------------*/

void file_op();

void search_prd();

void check_stc();

int brand_stock(double arr[][MAX_STOCK]); //Return value is the size of the used spaced on the array

void export(double arr[][MAX_STOCK],int size);

/*-----------------------------------Support functions-----------------------------------*/

void copy_string(char dest[],char start[]); /*Copies the start string to the dest string*/

int compare_str(const char arr1[],const char arr2[]); /*Returns 0 if strings are same, 1 if they are not same*/

int val_counter(FILE *fp);

int feat_counter(FILE *fp);

double find_median(double arr[],int size);

void op_menu();

void search_menu();

void menu();

void check_menu();

#endif