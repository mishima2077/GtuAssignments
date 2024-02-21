#include <stdio.h>
#include "database.h"

int main(){
    int choice,arr_size=-1; //I have set the arr_size -1, to check if its used later on or not
    double brand_stock_arr[MAX_ENTRY][MAX_STOCK];
    
    //Here, I have initialized all the values for the array -1.
    //This will be useful later on when we need to check 
    //How many current_stock values are there for a product.
    for(int i = 0;i<MAX_ENTRY;i++){
        for(int j = 0;j<MAX_STOCK;j++){
                brand_stock_arr[i][j] = -1;
        }
    }

    do{
        menu();
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: file_op();
                    break;
            case 2: search_prd();
                    break;
            case 3: check_stc();
                    break;
            case 4: arr_size = brand_stock(brand_stock_arr);
                    break;
            case 5: if(arr_size==-1) printf("Your array is not ready to export, terminating the program now.\n\n");
                    else{
                        export(brand_stock_arr,arr_size);
                        printf("Your report has been exported to report.txt. Terminating the program now.\n");
                    }
                    break;
            default: printf("Non valid input, returning to main menu.\n");
                     choice = 0;
        }
    }while(choice!=5);
    return (0);
}