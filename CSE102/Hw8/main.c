#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOVE_MADE_VAL 50

typedef struct S1{
    char arr[3][3];
}puzzle_board;

void menu();

void user_play();

void initialize_board(puzzle_board *ptr);

void print_board(puzzle_board *ptr);

int win_checker(puzzle_board *ptr);

void board_fileprnt(puzzle_board *ptr);

int auto_finish(puzzle_board *ptr,int x,int y);

void clear_file(); 

int main(){
    srand(time(NULL));
    char choice;
    FILE *score_fp;
    int best_score,move_count,x,y;
    puzzle_board pc_board;

    do{
        menu();
        scanf(" %c",&choice);
        switch(choice){
            case '1': user_play();
                      break;
            case '2': initialize_board(&pc_board); /*Initializing the board that pc will solve*/
                      clear_file(); /*Clears the board.txt file*/
                      board_fileprnt(&pc_board); /*This function appends the current games boards to board.txt*/
                      printf("Board to solve: \n");
                      print_board(&pc_board);
                      for(y=0;y<3;y++){    //Here program finds the coordinates of the _ char in the board
                        for(x=0;x<3;x++){  //and sends it to the recursive function, with the boards address
                            if(pc_board.arr[y][x]=='_'){
                                move_count = auto_finish(&pc_board,x,y);
                                x=3;/*Quits the loop*/
                                y=3;
                            }
                        }
                      }
                      printf("move count: %d\n",move_count);
                      printf("Solved board:\n");
                      print_board(&pc_board); /*Prints the solved board to terminal*/
                      break;
            case '3': score_fp = fopen("best_score.txt","r");
                      if(score_fp==NULL) printf("There is no best score to show.\n");
                      else{
                        fscanf(score_fp,"%d",&best_score);
                        printf("The best score is %d...\n",best_score);
                      }
                      fclose(score_fp);
                      break;
            case '4': printf("Terminating the program...\n");
                      break;
            default: printf("Non valid input, please try again.\n");
        }
    }while(choice != '4');
    return 0;
}

void menu(){
    printf("\n(1) Play game as a user\n(2) Finish the game with PC\n(3) Show the best score\n(4) Exit\n");
    printf(">");
}

void user_play(){
    puzzle_board main;
    initialize_board(&main);
    clear_file();

    int move_count=0,win_check,x,y,legal_check;

    char num,dir;

    do{
        board_fileprnt(&main);
        print_board(&main);
        printf("Enter your move(number-direction,e.g.,2-R): ");
        scanf(" %c %*c %c",&num,&dir);

        legal_check=0;
        //Making the move ----------------------------------------------------------
        for(y=0;y<3;y++){
            for(x=0;x<3;x++){
                if(main.arr[y][x]==num){
                    switch(dir){
                        case 'U': if(y-1>=0){ 
                                      if(main.arr[y-1][x]=='_'){
                                        main.arr[y-1][x]=num;
                                        main.arr[y][x]='_';
                                        legal_check=1;
                                      }
                                   }
                                   x=3; /*This part quits the for loops*/
                                   y=3;
                                   break;
                        case 'D': if(y+1<=2){
                                      if(main.arr[y+1][x]=='_'){
                                        main.arr[y+1][x]=num;
                                        main.arr[y][x]='_';
                                        legal_check=1;
                                      }
                                   }
                                   x=3;
                                   y=3;
                                   break;
                        case 'R': if(x+1<=2){
                                      if(main.arr[y][x+1]=='_'){
                                        main.arr[y][x+1] = num;
                                        main.arr[y][x] = '_';
                                        legal_check=1;
                                      }
                                   }
                                   x=3;
                                   y=3;
                                   break;
                        case 'L': if(x-1>=0){
                                      if(main.arr[y][x-1]=='_'){
                                        main.arr[y][x-1] = num;
                                        main.arr[y][x] = '_';
                                        legal_check=1;
                                      }
                                   }
                                   x=3;
                                   y=3;
                                   break;
                    }
                }
            }
        }
        //--------------------------------------------------------------------------

        if(legal_check==0){
            printf("%c-%c is an illegal move! Please make a legal move.\n",num,dir);
            win_check=0;
        }
        else{
            move_count++;
            win_check = win_checker(&main);
        }
    }while(win_check==0);
    int curr_best,score = 1000-(10*move_count);

    board_fileprnt(&main);
    print_board(&main);
    printf("Congratulations! You finished the game!\n\nTotal number of moves: %d\n\nYour score: %d\n",move_count,score);

    FILE *score_fp = fopen("best_score.txt","r");
    if(score_fp==NULL){ 
        fclose(score_fp);
        score_fp=fopen("best_score.txt","w");
        fprintf(score_fp,"%d\n",score);
        fclose(score_fp);
    }
    else{
        fscanf(score_fp,"%d",&curr_best);
        if(score>curr_best){ //Updates the best_score.txt if the score is higher than current best
            printf("Best Score!\n\n");
            fclose(score_fp);
            score_fp=fopen("best_score.txt","w");
            fprintf(score_fp,"%d",score);
        }
        fclose(score_fp);
    }
}

//This function first initializes a board on an int array,then converts it to our struct
//I initialized it on a int array because its easier to check the inversions
void initialize_board(puzzle_board *ptr){
    int arr[9];
    int x,y,inversion=0;
    char cond,valid_board;
    do{ //This loop creates a random board until the board is solvable
        for(x=0;x<9;x++){ 
            arr[x]= -1;
        }
        //Initializing the random values
        for(x=0;x<9;x++){ /*This parts main idea is, it generates a random index and checks if that address is currently untouched*/
            do{           /*If that index is untouched(if its -1 in this case) program puts the number to that place and countinues to the next number*/
                y=rand()%9;
                if(arr[y]==-1){
                    arr[y]=x;
                    cond = '1';
                }
                else{
                    cond = '0';
                }
            }while(cond=='0');
        }

        //Check for solvability
        for(x=0;x<9;x++){
            for(y=x+1;y<9;y++){
                if(arr[x]>arr[y] && arr[y]!=0){
                    inversion++;
                }
            }
        }
        if(inversion%2==0) valid_board='1';
        else valid_board='0';

        inversion=0;
    }while(valid_board=='0'); 

    int arr_index=0;
    for(y=0;y<3;y++){ //Passing the created board to our main struct 
        for(x=0;x<3;x++){
            if(arr[arr_index]!=0){
                ptr->arr[y][x] = arr[arr_index]+48; //49 is the ASCII value of '1',so to convert 1 to '1' we need to add 48
            }                                       //Its the same case for all numbers
            else{
                ptr->arr[y][x]='_'; //0 represents '_' on the int array
            }
            arr_index++;
        }
    }
}

void print_board(puzzle_board *ptr){
    int x,y;
    for(y = 0;y<3;y++){
        for(x = 0;x<3;x++){
            printf("%c ",ptr->arr[y][x]);
        }
        printf("\n");
    }
}

//returns 0 if the board is not complete, returns 1 if the board is complete
int win_checker(puzzle_board *ptr){
    int x,y;
    char checker = '1';
    for(y=0;y<2;y++){ //This loop checks the first 2 collumns, last collumn is checked manually
        for(x=0;x<3;x++){
            if(ptr->arr[y][x]!=checker){
                return 0;
            }
            else{
                checker++;
            }
        }
    }

    if(ptr->arr[2][0]=='7' && ptr->arr[2][1]=='8'){ //Last row check
        return 1;
    }
    return 0; 
}

//Adds the current board to board.txt
void board_fileprnt(puzzle_board *ptr){
    FILE *board_file;
    
    board_file = fopen("board.txt","a+");
    if(board_file==NULL){
        printf("board.txt couldn't be opened.Terminating the function\n");
        return;
    }
    fprintf(board_file,"--------\n");
    int x,y;
    for(y=0;y<3;y++){
        for(x=0;x<3;x++){
            fprintf(board_file,"%c ",ptr->arr[y][x]);
        }
        fprintf(board_file,"\n");
    }
    fprintf(board_file,"--------\n");

    fclose(board_file);
}

//Return value is the move count
int auto_finish(puzzle_board *ptr,int x,int y){
    if(win_checker(ptr)){
        //If the board is complete, program exits the recursion
        return 0;
    }
    else{
        do{
            switch(rand()%4){
                //Up movement of the '_' if legal
                case 0: if(y-1>=0){
                            ptr->arr[y][x] = ptr->arr[y-1][x];
                            ptr->arr[y-1][x] = '_';
                            printf("Move : %c-%c\n",ptr->arr[y][x],'D');
                            y = y-1; /*Updating the coordinate of the '_' char*/
                            y += MOVE_MADE_VAL; /*I made this because I didn't wanted to add an additional variable*/
                                                /*This basically suggests that a move has been made*/
                            break;              
                        }
                //Down movement of the '_' if legal
                case 1: if(y+1<=2){
                            ptr->arr[y][x] = ptr->arr[y+1][x];
                            ptr->arr[y+1][x] = '_';
                            printf("Move : %c-%c\n",ptr->arr[y][x],'U');
                            y = y+1;
                            y += MOVE_MADE_VAL;
                            break;
                        }
                //Right movement of the '_' if legal
                case 2: if(x+1<=2){
                            ptr->arr[y][x] = ptr->arr[y][x+1];
                            ptr->arr[y][x+1] = '_';
                            printf("Move : %c-%c\n",ptr->arr[y][x],'L');
                            x = x+1;
                            y += MOVE_MADE_VAL;
                            break;
                        }
                //Left movement of the '_' if legal
                case 3: if(x-1>=0){
                            ptr->arr[y][x] = ptr->arr[y][x-1];
                            ptr->arr[y][x-1] = '_';
                            printf("Move : %c-%c\n",ptr->arr[y][x],'R');
                            x = x-1;
                            y += MOVE_MADE_VAL;
                            break;
                        }                       
            }
        }while(y<=2); /*Checks whether the move has been made or not*/
        y -= MOVE_MADE_VAL; /*Returning the y coordinate to its original value*/
        board_fileprnt(ptr); /*Prints the board after the move to board.txt(append)*/
        print_board(ptr);
        return 1 + auto_finish(ptr,x,y);
    }
}
//Clears board.txt
void clear_file(){
    FILE *fp = fopen("board.txt","w");
    fclose(fp);
}
