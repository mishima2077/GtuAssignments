#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_OF_OPT 10
#define PRC_KEBAB 75.99
#define PRC_LAHMACUN 21.50
#define PRC_PIDE 40.00
#define PRC_DONER 55.60
#define PRC_KOLA 15.00
#define PRC_SU 5.00
#define PRC_KUNEFE 60.00
#define PRC_SUTLAC 32.50
#define PRC_HAMBURGER 50.00
#define PRC_KREP 45.00

typedef enum {rock,paper,scissors} rps;

void restaurant();

void write_menu(FILE *fp);

void read_menu(FILE *fp);

void write_receipt(FILE *fp);

void print_receipt(FILE *fp);

void rps_game();

void rps_menu();

rps rps_asgn(int num);

void rps_print(rps var);

void rps_check(rps user,rps opponent);

int main(){
    restaurant();
    rps_game();
}

void restaurant(){
    FILE *menu;
    FILE *receipt;

    menu = fopen("menu.txt","w+");
    receipt = fopen("receipt.txt","w+");

    write_menu(menu);
    rewind(menu);
    read_menu(menu);
    printf("\n");
    write_receipt(receipt);
    rewind(receipt);
    print_receipt(receipt);

    fclose(receipt);
    fclose(menu);
}

void write_menu(FILE *fp){
    fprintf(fp,"Product    Price(TL)\n\n");
    fprintf(fp,"Kebab      %.2f    \n\n",PRC_KEBAB);
    fprintf(fp,"Lahmacun   %.2f    \n\n",PRC_LAHMACUN);
    fprintf(fp,"Pide       %.2f    \n\n",PRC_PIDE);
    fprintf(fp,"Döner      %.2f    \n\n",PRC_DONER);
    fprintf(fp,"Kola       %.2f    \n\n",PRC_KOLA);
    fprintf(fp,"Su         %.2f    \n\n",PRC_SU);
    fprintf(fp,"Künefe     %.2f    \n\n",PRC_KUNEFE);
    fprintf(fp,"Sütlaç     %.2f    \n\n",PRC_SUTLAC);
    fprintf(fp,"Hamburger  %.2f    \n\n",PRC_HAMBURGER);
    fprintf(fp,"Krep       %.2f    ",PRC_KREP);
}

void read_menu(FILE *fp){
    int i,condition;
    char ch;

    //This part basically skips the first line which has "Product" and "Price(Tl)" texts
    for(i = 0;i<22;i++){
       ch = fgetc(fp);
    }

    printf("Yemek Listesi:\n\n");

    for(i = 0;i < NUM_OF_OPT;i++){
        
        printf("%d. ",i+1);

        do{   /*Prints the characters until the word is over*/
            ch = fgetc(fp);
            if(ch!=' '){                       
                printf("%c",ch);                           
                condition = 1;                             
            }
            else{
                condition = 0;
            }
        }while(condition == 1);

        printf("\n\n");

        //This parts skips to the next line that has text on it
        if(i!=(NUM_OF_OPT)-1){
            do{
                ch = fgetc(fp);
            }while(ch != '\n');
            ch = fgetc(fp);
        }
    }
}

void write_receipt(FILE *fp){
    //Gets the time info in a format
    char formatted_time[50];
    time_t t;
    t = time(NULL);
    strftime(formatted_time,sizeof(formatted_time),"%d.%m.%Y/%H:%M",localtime(&t));
    
    fprintf(fp,"220104004048        %s\n\n",formatted_time);
    fprintf(fp,"------------------------------------\n\n");
    fprintf(fp," Product                  Price(TL) \n\n");
    fprintf(fp,"------------------------------------\n\n");

    int product,prd_num,condition,check;
    float price,VAT;
    char buf_cleaner;

    do{

        /*Inputs with validation checks ------------------------------------------------------*/
        do{
            printf("Please choose a product (1-10): ");
            scanf("%d",&product);
            if((product>=0)&&(product<=10)){
                condition = 1;
            }
            else{
                scanf("%c",&buf_cleaner); /*Clears the buffer in case of a non integer input*/
                printf("Non valid input, please try again.\n");
                condition = 0;
            }
        }while(condition == 0);

        if(product!=0){
            do{
                printf("How many servings do you want? ");
                scanf("%d",&prd_num);
                if(prd_num<0){
                    scanf("%c",&buf_cleaner); /*Clears the buffer in case of a non integer input*/
                    printf("Non valid input, please try again.\n");
                    condition = 0;
                }
                else{
                    condition = 1;
                }
            }while(condition == 0);
        }
        /*------------------------------------------------------------------------------------*/

        /*This parts checks the quit condition, if its not met it writes the desired food with its price to the receipt.txt*/
        /*----------------------------------------------------------------------------------------------------------------*/
        if((product==0)||(prd_num==0)){
            check = 0;
        }
        else{
            switch(product){
                case 1: if(prd_num==1){
                    fprintf(fp," Kebab                    %6.2f\n\n",PRC_KEBAB);
                    price += PRC_KEBAB;
                }
                else{
                    fprintf(fp," %d*Kebab                  %6.2f\n\n",prd_num,(prd_num*PRC_KEBAB));
                    price += prd_num*PRC_KEBAB;
                }
                break;
                case 2: if(prd_num==1){
                    fprintf(fp," Lahmacun                 %6.2f\n\n",PRC_LAHMACUN);
                    price += PRC_LAHMACUN;
                }
                else{
                    fprintf(fp," %d*Lahmacun               %6.2f\n\n",prd_num,(prd_num*PRC_LAHMACUN));
                    price += prd_num*PRC_LAHMACUN;
                }
                break;
                case 3: if(prd_num==1){
                    fprintf(fp," Pide                     %6.2f\n\n",PRC_PIDE);
                    price += PRC_PIDE;
                }
                else{
                    fprintf(fp," %d*Pide                   %6.2f\n\n",prd_num,(prd_num*PRC_PIDE));
                    price += prd_num*PRC_PIDE;
                }
                break;
                case 4: if(prd_num==1){
                    fprintf(fp," Döner                    %6.2f\n\n",PRC_DONER);
                    price += PRC_DONER;
                }
                else{
                    fprintf(fp," %d*Döner                  %6.2f\n\n",prd_num,(prd_num*PRC_DONER));
                    price += prd_num*PRC_DONER;
                }
                break;
                case 5: if(prd_num==1){
                    fprintf(fp, " Kola                     %6.2f\n\n",PRC_KOLA);
                    price += PRC_KOLA;
                }
                else{
                    fprintf(fp," %d*Kola                   %6.2f\n\n",prd_num,(prd_num*PRC_KOLA));
                    price += prd_num*PRC_KOLA;
                }
                break;
                case 6: if(prd_num==1){
                    fprintf(fp," Su                       %6.2f\n\n",PRC_SU);
                    price += PRC_SU;
                }
                else{
                    fprintf(fp," %d*Su                     %6.2f\n\n",prd_num,(prd_num*PRC_SU));
                    price += prd_num*PRC_SU;
                }
                break;
                case 7: if(prd_num==1){
                    fprintf(fp," Künefe                   %6.2f\n\n",PRC_KUNEFE);
                    price += PRC_KUNEFE;
                }
                else{
                    fprintf(fp," %d*Künefe                 %6.2f\n\n",prd_num,(prd_num*PRC_KUNEFE));
                    price += prd_num*PRC_KUNEFE;
                }
                break;
                case 8: if(prd_num==1){
                    fprintf(fp," Sütlaç                   %6.2f\n\n",PRC_SUTLAC);
                    price += PRC_SUTLAC;
                }
                else{
                    fprintf(fp," %d*Sütlaç                 %6.2f\n\n",prd_num,(prd_num*PRC_SUTLAC));
                    price += prd_num*PRC_SUTLAC;
                }
                break;
                case 9: if(prd_num==1){
                    fprintf(fp," Hamgurger                %6.2f\n\n",PRC_HAMBURGER);
                    price += PRC_HAMBURGER;
                }
                else{
                    fprintf(fp," %d*Hamburger              %6.2f\n\n",prd_num,(prd_num*PRC_HAMBURGER));
                    price += prd_num*PRC_HAMBURGER;
                }
                break;
                case 10: if(prd_num==1){
                    fprintf(fp," Krep                     %6.2f\n\n",PRC_KREP);
                    price += PRC_KREP;
                }
                else{
                    fprintf(fp," %d*Krep                   %6.2f\n\n",prd_num,(prd_num*PRC_KREP));
                    price += prd_num*PRC_KREP;
                }
                break;
            }
        }
        /*----------------------------------------------------------------------------------------------------------------*/

    }while(check != 0);

    //Later part of this function deals with the price information, calculates the prices and discounts and writes them
    char std_check;
    do{
        printf("Are you a student? (Y/N): ");
        scanf(" %c",&std_check);
        if((std_check=='Y')||(std_check=='N')){
            check = 1;
        }
        else{
            printf("Non valid input! Try again\n");
            check = 0;
        }
    }while(check == 0);

    fprintf(fp," Total:                   %6.2f\n\n",price);

    if(std_check=='Y'){
        float std_disc;
        std_disc = (price * 12.5)/100.0;
        fprintf(fp," Student Discount         %6.2f\n\n",-std_disc);
        price = price - std_disc;
    }

    if(price > 150.0){
        fprintf(fp," Additional Discount      %6.2f\n\n",-((price*10.0)/100.0));
        price = price - ((price*10.0)/100.0);
    }

    fprintf(fp,"------------------------------------\n\n");

    fprintf(fp," Price:                   %6.2f\n\n",price);

    VAT = (price*18.0)/100.0;
    price += VAT;

    fprintf(fp," Price + VAT              %6.2f\n\n",price);
}

//This function just prints the whole receipt to the terminal
void print_receipt(FILE *fp){
    char x;
    int y;
    printf("\n");
    x = fgetc(fp);
    y = x;
    while((x != EOF)&&(y != 255)){ /*I had to add y!=255 check*/
        printf("%c",x);            /*because EOF check didn't stop*/
        x = fgetc(fp);             /*the loop on Ubuntu, I manually checked*/
        y = x;                     /*the last characters ascii and used it*/
    }                              
}

void rps_game(){
    srand(time(NULL));
    
    char cln_buffer;
    char check='Y';
    int choice,condition;
    rps user,opponent;

    while(check == 'Y'){
        rps_menu();
        do{
            scanf("%d",&choice);
            if((choice!=1)&&(choice!=2)&&(choice!=3)){
                
                scanf("%c",&cln_buffer); /*Clearing the buffer in case of non integer input*/

                printf("\nNon valid input! Please try again.\n\n");
                condition = 0;
            }
            else{
                condition = 1;
            }
        }while(condition == 0);

        //Assigning rock,paper,scissors values to the variables
        user = rps_asgn(choice);
        opponent = rps_asgn((rand()%3)+1); 

        printf("You chose ");
        rps_print(user);
        printf(". I chose ");
        rps_print(opponent);
        printf(".");

        //Prints out the result of the game
        rps_check(user,opponent);

        do{
            printf("Do you want to play again? (Y/N): ");
            scanf(" %c",&check);
            if((check!='Y')&&(check!='N')){
                printf("\nNon valid input! Try again.\n\n");
                condition = 0;
            }
            else{
                condition = 1;
            }
            printf("\n");
        }while(condition == 0);
    }

}

void rps_menu(){
    printf("Please make a choice!\n\n");
    printf("1: Rock, 2: Paper, 3: Scissors\n\n");
}

rps rps_asgn(int num){
    rps var;
    switch(num){
        case 1: var = rock;
                break;
        case 2: var = paper;
                break;
        case 3: var = scissors;
                break;
    }
    return var;
}

void rps_print(rps var){
    switch(var){
        case rock: printf("Rock");
                    break;
        case paper: printf("Paper");
                    break;
        case scissors: printf("Scissors");
                    break;
    }
}

void rps_check(rps user,rps opponent){
    if(user == opponent){
        printf("It's a tie!\n\n");
    }
    else if(((user == rock)&&(opponent == scissors))||((user == scissors)&&(opponent == paper))||((user == paper)&&(opponent == rock))){
        printf("You won!\n\n");
    }
    else{
        printf("I won!\n\n");
    }
}
