#include <stdio.h>
#include <math.h>

typedef enum{RED,GREEN,BLUE,YELLOW,ORANGE} Color;

void part1();

void part2();

void part3();

Color color_gen(Color var1,Color var2);

void colorMixer(Color var1,Color var2,Color f(Color x,Color y));

float euc_distance(float arr1[],float arr2[]);

void arr_asgn(Color var,float arr[]);

Color color_asgn(char var);

void color_print(Color var);

void letter_counter(FILE *fp,int arr[]);

void count_printer(int arr[]);

int win_checker(char arr[3][3]);

void board_printer(char arr[3][3]);

int main(){
    printf("\n--------------------------------------------------------------\n\n");
    part1();
    printf("\n--------------------------------------------------------------\n\n");
    part2();
    printf("\n--------------------------------------------------------------\n\n");
    part3();
    printf("\n--------------------------------------------------------------\n\n");
}

void part1(){
    char file_name[50];
    int num_of_occurance[26],i;

    //Setting all occurances 0
    for(i = 0;i<26;i++){
        num_of_occurance[i]=0;
    }

    printf("Enter the file name: ");
    scanf("%s",file_name);

    FILE *fp;
    fp = fopen(file_name,"r");
    
    if(fp == NULL){
        printf("%s failed to open. Terminating the program.\n",file_name);
        return;
    }

    letter_counter(fp,num_of_occurance); /*Sets the occurances of each letter from index 0 -> A to 25 -> Z (case independent)*/

    count_printer(num_of_occurance); /*Prints out the array with desired output format*/

    fclose(fp);
}

void letter_counter(FILE *fp,int arr[]){
    int x;

    while(!(feof(fp))){
        x = fgetc(fp); /*I am using an integer because my algorithm uses the ASCII values of characters*/
        if(x!=EOF){
            if((x>=65)&&(x<=90)){ /*Checks for a lower case letter*/
                x -= 65;
                arr[x]++;
            }
            else if((x>=97)&&(x<=122)){ /*Checks for an upper case letter*/
                x -= 97;
                arr[x]++;
            }
        }
    }
}

void count_printer(int arr[]){
    int i;
    char letter = 'A';
    
    for(i=0;i<26;i++){
        printf("%c: %d\n",letter,arr[i]);
        letter++;
    }
}

void part2(){
    Color var1,var2;

    char ch;

    int condition;

    do{
        printf("Enter Color 1(r,g,b,y,o): ");
        scanf(" %c",&ch);
        if(ch!='r' && ch!='g' && ch!='b' && ch!='y' && ch!='o'){
            printf("Non valid input, please try again!\n");
            condition = 0;
        }
        else{
            condition = 1;
        }
    }while(condition==0);

    var1 = color_asgn(ch); /*This function assigns the color variable to desired color*/

    do{
        printf("Enter Color 2(r,g,b,y,o): ");
        scanf(" %c",&ch);
        if(ch!='r' && ch!='g' && ch!='b' && ch!='y' && ch!='o'){
            printf("Non valid input, please try again!\n");
            condition = 0;
        }
        else{
            condition = 1;
        }
    }while(condition==0);

    var2 = color_asgn(ch);

    colorMixer(var1,var2,color_gen);
}

void colorMixer(Color var1,Color var2,Color f(Color x,Color y)){
    Color res_color = f(var1,var2); /*This function finds the color result of mixing these two colors*/

    float arr1[3];
    float arr2[3];
    float arr_res[3];
    
    arr_asgn(var1,arr1); /*arr_asgn function assigns the color values to given array for the given color*/
    arr_asgn(var2,arr2);

    //Here we calculate the final colors array to print it out
    arr_res[0] = (arr1[0]+arr2[0])/2;
    arr_res[1] = (arr1[1]+arr2[1])/2;
    arr_res[2] = (arr1[2]+arr2[2])/2;

    printf("Mixed Color: ");
    color_print(res_color); /*This function just prints the name of the given color*/
    printf("[%.1f,%.1f,%.1f]\n",arr_res[0],arr_res[1],arr_res[2]);
}

void arr_asgn(Color var,float arr[]){
    switch(var){
        case RED: arr[0]=1.0;
                  arr[1]=0;
                  arr[2]=0;
                  break;
        case GREEN: arr[0]=0;
                    arr[1]=1.0;
                    arr[2]=0;
                    break;
        case BLUE:  arr[0]=0;
                    arr[1]=0;
                    arr[2]=1.0;
                    break;
        case YELLOW:arr[0]=0.5;
                    arr[1]=0.5;
                    arr[2]=0;
                    break;
        case ORANGE:arr[0]=0.5;
                    arr[1]=0.4;
                    arr[2]=0.2;
                    break;
    }
}

Color color_gen(Color var1,Color var2){
    Color res;
    
    float R[3] = {1,0,0};
    float G[3] = {0,1,0};
    float B[3] = {0,0,1};
    float Y[3] = {0.5,0.5,0};
    float O[3] = {0.5,0.4,0.2};
    
    float arr1[3];
    float arr2[3];
    float arr3[3];
    float distances[5];
    float smallest;
    int sm_index;

    arr_asgn(var1,arr1);
    arr_asgn(var2,arr2);

    arr3[0] = (arr1[0]+arr2[0])/2;
    arr3[1] = (arr1[1]+arr2[1])/2;
    arr3[2] = (arr1[2]+arr2[2])/2;

    //Here, I check the distance from my final color array to all the colors and store them
    //Then I find the smallest distance, and with the index of it I find which color it should be
    distances[0] = euc_distance(arr3,R); /*euc_distance function finds the distance between two color vector*/
    distances[1] = euc_distance(arr3,G);
    distances[2] = euc_distance(arr3,B);
    distances[3] = euc_distance(arr3,Y);
    distances[4] = euc_distance(arr3,O);

    smallest = distances[0];
    sm_index = 0;
    for(int i = 1;i<5;i++){
        if(distances[i]<smallest){
            smallest = distances[i];
            sm_index = i;
        }
    }

    switch(sm_index){
        case 0: res = RED;
                break;
        case 1: res = GREEN;
                break;
        case 2: res = BLUE;
                break;
        case 3: res = YELLOW;
                break;
        case 4: res = ORANGE;
                break;
    }

    return res;
}

float euc_distance(float arr1[],float arr2[]){
    float distance;

    distance = pow((arr1[0]-arr2[0]),2) + pow((arr1[1]-arr2[1]),2) + pow((arr1[2]-arr2[2]),2);
    distance = sqrt(distance); 

    return distance;
}

void color_print(Color var){
    switch(var){
        case RED: printf("RED");
                  break;
        case GREEN: printf("GREEN");
                  break;
        case BLUE: printf("BLUE");
                  break;
        case YELLOW: printf("YELLOW");
                  break;
        case ORANGE: printf("ORANGE");
                  break;
    }
}

Color color_asgn(char var){
    Color res;
    
    switch(var){
        case 'r': res = RED;
                  break;
        case 'g': res = GREEN;
                  break;
        case 'b': res = BLUE;
                  break;
        case 'y': res = YELLOW;
                  break;
        case 'o': res = ORANGE;
                  break;
    }

    return res;
}

void part3(){
    char gm_board[3][3],ply_again;
    int row,col,condition,check;
    char buf_cleaner;

    do{
    
    //Seting up the game board
    for(row = 0;row<3;row++){
        for(col=0;col<3;col++){
            gm_board[row][col]='_';
        }
    }

    //Main game loop
    do{
        do{
            printf("Player 1(X), please enter your move(row,vol): ");
            scanf("%d%d",&row,&col);
            if((row>2)||(row<0)||(col>2)||(col<0)){
                printf("Non valid input, please try again!\n");
                condition = 0;
            }
            else if(gm_board[row][col]!='_'){
                printf("You can't make a move there, try again.\n");
                condition = 0;
            }
            else{
                condition = 1;
            }
        }while(condition==0);

        gm_board[row][col] = 'X';

        board_printer(gm_board); /*This function prints out the current game board*/

        //This check function returns 0 if no one has won yet
        //Returns 1 if player 1 has won and returns 2 if player 2 has won
        //Finally, returns 3 if the game is a tie
        check = win_checker(gm_board);
        
        if(check == 0){
            do{
                printf("Player 2(O), please enter your move(row,vol): ");
                scanf("%d%d",&row,&col);
                if((row>2)||(row<0)||(col>2)||(col<0)){
                    printf("Non valid input, please try again!\n");
                    condition = 0;
                }
                else if(gm_board[row][col]!='_'){
                    printf("You can't make a move there, try again.\n");
                    condition = 0;
                }
                else{
                    condition = 1;
                }
            }while(condition==0);

            gm_board[row][col] = 'O';

            board_printer(gm_board);

            check = win_checker(gm_board);
        }

    }while(check == 0);

    do{
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c",&ply_again);
        if(((ply_again!='Y')&&(ply_again!='N'))&&((ply_again!='y')&&(ply_again!='n'))){
            scanf("%c",&buf_cleaner); /*Clears the \n character*/
            printf("Non valid input, please try again.\n");
            condition = 0;
        }
        else{
            condition = 1;
        }
    }while(condition == 0);

    }while((ply_again=='Y')||(ply_again=='y'));
}

int win_checker(char arr[3][3]){
    int row,col;
    int tie_checker=1;

    //Checks the same row type wins
    for(row=0;row<3;row++){
        if((arr[row][0]==arr[row][1])&&(arr[row][0]==arr[row][2])){
            if(arr[row][0]=='X'){
                printf("Player 1 (X) wins!\n");
                return 1;
            }
            else if(arr[row][0]=='O'){
                printf("Player 2 (O) wins!\n");
                return 2;
            }
        }
    }

    //Checks the same column type wins
    for(col=0;col<3;col++){
        if((arr[0][col]==arr[1][col])&&(arr[0][col]==arr[2][col])){
            if(arr[0][col]=='X'){
                printf("Player 1 (X) wins!\n");
                return 1;
            }
            else if(arr[0][col]=='O'){
                printf("Player 2 (O) wins!\n");
                return 2;
            }
        }
    }

    //checks the diagonal type wins
    if((arr[0][0]==arr[1][1])&&(arr[0][0]==arr[2][2])){
        if(arr[0][0]=='X'){
            printf("Player 1 (X) wins!\n");
            return 1;
        }
        else if(arr[0][0]=='O'){
             printf("Player 2 (O) wins!\n");
             return 2;
        }
    }
    if((arr[0][2]==arr[1][1])&&(arr[0][2]==arr[2][0])){
        if(arr[0][2]=='X'){
            printf("Player 1 (X) wins!\n");
            return 1;
        }
        else if(arr[0][2]=='O'){
             printf("Player 2 (O) wins!\n");
             return 2;
        }
    }

    //If there are no _ characters on the board and no one has won, its a tie
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            if(arr[row][col]=='_'){
                tie_checker = 0;
                break;
            }
        }
    }
    
    if(tie_checker==1){
        printf("Its a tie!\n");
        return 3;
    }

    //If no one has won yet and its not a tie, function returns 0
    return 0; 
}

void board_printer(char arr[3][3]){
    int row,col;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            printf("%c ",arr[row][col]);
        }
        printf("\n");
    }
}