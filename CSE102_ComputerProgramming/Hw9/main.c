#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point{
    int row;
    int col;
}point;

typedef struct block{
    char type;
    int value;
}block;

block*** init_board();

void play(block*** board);

void draw_board(block*** board,point* snake,int size);

char move(point* snake,int size); /*Return value is the move that has been made*/

int check_status(point* snake,int size,block*** board); /*Returns 1 if the game is over,0 if its not*/

point* update(point* snake,int* size,block*** board,int move_count,char move); /*Returns the snakes pointer*/

int main(){
    srand(time(NULL));

    block ***board = init_board(); /*Initializing the board*/
    play(board); /*Main play function*/

    return 0;
}

block*** init_board(){
    int i,j,k;
    //Creating the dynamic array
    block*** board = (block***) malloc(10 * sizeof(block**));
    for(i=0;i<10;i++){
        board[i] = (block**) malloc(10 * sizeof(block*));
        for(j=0;j<10;j++){
            board[i][j] = (block*) malloc(1 * sizeof(block)); /*At first, every z value of the board is 1*/
        }
    }

    //Initializing the dynamic array
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            board[i][j][0].type='e';
            board[i][j][0].value=0;
        }
    }

    //Initializing the obstacle
    char check;
    int rand_x,rand_y,height;
    do{
        rand_x = rand()%10;
        rand_y = rand()%10;
        if(rand_x==0 && rand_y==0) check = '0';
        else{
            board[rand_x][rand_y][0].type='o';
            board[rand_x][rand_y][0].value=1;
            check = '1';
        }
    }while(check=='0');

    //Initializing the bait
    do{
        rand_x = rand()%10;
        rand_y = rand()%10;
        if((rand_x==0 && rand_y==0)||(board[rand_x][rand_y][0].type!='e')) check = '0';
        else{
            board[rand_x][rand_y][0].type = 'b';
            board[rand_x][rand_y][0].value = 0;
            check = '1';
        }
    }while(check=='0');

    return board;
}

void draw_board(block*** board,point* snake,int size){
    char temp[10][10]; /*Temporary character array,this will be printed*/
    int i,j;
    for(i=0;i<10;i++){ /*Setting the values for the board values*/
        for(j=0;j<10;j++){
            if(board[i][j][0].type=='o') temp[i][j] = (board[i][j][0].value)+48;
            else if(board[i][j][0].type=='b') temp[i][j] = '.';
            else temp[i][j] = ' ';
        }
    }

    temp[snake->row][snake->col]='O';/*Setting the values for the snake values*/
    for(i=1;i<size;i++){
        temp[snake[i].row][snake[i].col]='X';
    }

    for(i=0;i<12;i++) printf("--"); /*Printing to terminal in desired format*/
    printf("\n");
    for(i=0;i<10;i++){
        printf("|");
        for(j=0;j<10;j++){
            printf(" %c",temp[j][i]);
        }
        printf(" |\n");
    }
    for(i=0;i<12;i++) printf("--");
    printf("\n");
}

void play(block*** board){
    int snake_size = 1,game_check,move_count=0,i,j;
    char last_move;

    point* snake = (point*) malloc(sizeof(point)); /*Initializing the snake with lenght 1*/
    snake->col = 0;
    snake->row = 0;
    do{
        draw_board(board,snake,snake_size); /*Drawing the board*/

        last_move = move(snake,snake_size); /*Making the move*/
        move_count++;

        game_check=check_status(snake,snake_size,board);
        if(game_check!=1) snake = update(snake,&snake_size,board,move_count,last_move);
    }while(game_check==0);
    printf("GAME OVER!\n");
    printf("Move count: %d\n",move_count);
    printf("Snake size: %d\n",snake_size);

    /*Freeing the space used by dynamic arrays*/
    free(snake);
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
}

char move(point* snake,int size){
    char move;
    do{
      printf("Make your move :  ");
      scanf(" %c",&move);
      switch(move){ /*I have used size==1 check because if the size is 1, every one of the four moves is valid*/
                    /*So there is no need to check for the body collisions*/
              case 'U':if((size==1)||((snake[0].col)-1 != snake[1].col)){
                          snake[0].col = (snake[0].col)-1;
                      }
                      else move = 'X'; /*This means invalid input, no update will be made on the snakes body*/
                      break;
              case 'D':if((size==1)||((snake[0].col)+1 != snake[1].col)){
                          snake[0].col = (snake[0].col)+1;
                      }
                      else move = 'X';
                      break;
              case 'R':if((size==1)||((snake[0].row)+1 != snake[1].row)){
                          snake[0].row = (snake[0].row)+1;
                      }
                      else move = 'X';
                      break;
              case 'L':if((size==1)||((snake[0].row)-1 != snake[1].row)){
                          snake[0].row = (snake[0].row)-1;
                      }
                      else move = 'X';
                      break;
              default: move='X';
      }
      if(move=='X') printf("Invalid move!\n");
    }while(move=='X');
    return move;
}

int check_status(point* snake,int size,block*** board){
    int i;
    for(i=1;i<size-1;i++){ /*Checking for the body collisions,I have used size-1 because logically*/
                           /*we shouldn't check the last body part,it will not be there when the move has been made*/
        if((snake[i].row==snake[0].row)&&(snake[i].col==snake[0].col)) return 1;
    }  

    //Checking for the wall collisions
    if((snake->col>9)||(snake->col<0)||(snake->row>9)||(snake->row<0)) return 1;

    //Checking for the obstacle collisions,if the obstacle has the same or greater size the game is over
    if(board[snake->row][snake->col][0].type=='o'){
        if(board[snake->row][snake->col][0].value > size) return 1;
    }

    return 0;
}

point* update(point* snake,int* size,block*** board,int move_count,char move){
    int curr_x,curr_y,prev_x,prev_y,i,j;
    int bait_check = (board[snake[0].row][snake[0].col][0].type=='b'); 
    if(bait_check){ /*If the bait has been eaten*/
        *(size) = *(size) + 1;
        board[snake[0].row][snake[0].col][0].type='e';

        point* temp = (point*) malloc((*size)*sizeof(point)); /*Creating a new snake with one more body part*/
        temp->col=snake->col; /*Initializing the head*/
        temp->row=snake->row;
        switch(move){ /*Initializing the first body part according to the move*/
            case 'U': temp[1].row=snake[0].row;
                      temp[1].col=(snake[0].col)+1;
                      break;
            case 'D': temp[1].row=snake[0].row;
                      temp[1].col=(snake[0].col)-1;
                      break;
            case 'R': temp[1].col=snake[0].col;
                      temp[1].row=snake[0].row-1;
                      break;
            case 'L': temp[1].col=snake[0].col;
                      temp[1].row=snake[0].row+1;
                      break;
        }
        for(i=2;i<(*size);i++){ /*Body parts starting from the second one will be same,thus we just copy the original one*/
            temp[i].row = snake[i-1].row;
            temp[i].col = snake[i-1].col;
        }
        free(snake); /*Freeing the space used by the original snake*/
        snake = temp; /*Setting our new snake to be the main one*/
    }
    else{
        if((*size)!=1){
            curr_x = snake[1].row; /*Storing the values that the body part after first one will come*/
            curr_y = snake[1].col;
            switch(move){ /*Moving the first body part according to the move*/
                case 'U': snake[1].row=snake[0].row;
                        snake[1].col=(snake[0].col)+1;
                        break;
                case 'D': snake[1].row=snake[0].row;
                        snake[1].col=(snake[0].col)-1;
                        break;
                case 'R': snake[1].col=snake[0].col;
                        snake[1].row=snake[0].row-1;
                        break;
                case 'L': snake[1].col=snake[0].col;
                        snake[1].row=snake[0].row+1;
                        break;
            }
            for(i=2;i<(*size);i++){ /*The parts after the first one just gets copied to the place of the part ahead of them*/
                prev_x = snake[i].row; /*Storing the coordinates*/
                prev_y = snake[i].col;
                snake[i].row = curr_x; /*Moving to the place of the part ahead of it*/
                snake[i].col = curr_y;
                curr_x = prev_x; /*Setting the coordinate values for the part after it*/
                curr_y = prev_y;
            }
        }
    }
    

    if(board[snake[0].row][snake[0].col][0].type=='o'){ //Clears the obstacle
        free(board[snake[0].row][snake[0].col]); /*Freeing the space used by the nested obstacle*/
        board[snake[0].row][snake[0].col] = (block*) malloc(sizeof(block)); /*Allocating and initializing the space for the board*/
        board[snake[0].row][snake[0].col][0].type='e';
        board[snake[0].row][snake[0].col][0].value=0;
    }

    int bait_x,bait_y,valid_bait;
    if(bait_check){ /*Replacing the bait according to the rules if its eaten*/
        do{
            valid_bait=1;
            bait_x = rand()%10;
            bait_y = rand()%10;
            for(i=0;i<(*size);i++){
                if((snake[i].col==bait_y)&&(snake[i].row==bait_x)) valid_bait=0;
            }
            if(board[bait_x][bait_y][0].type!='e') valid_bait=0;
        }while(valid_bait==0);
        board[bait_x][bait_y][0].type='b';
        board[bait_x][bait_y][0].value=0;
    }

    if(move_count%5==0){/*Updating the obstacles in every 5 move*/
        int obs_count=0;
        for(i=0;i<10;i++){ /*This series of loops count the obstacles*/
                           /*Also,there is a %50 chance for an obstacle to be nested*/
            for(j=0;j<10;j++){
                if(board[i][j][0].type=='o'){
                    obs_count++;
                    if((board[i][j][0].value<9)&&(rand()%2)){ /*This part nests an obstacle to the current one,%50 chance to enter this part*/
                        board[i][j] = (block*)realloc(board[i][j],(board[i][j][0].value + 1)*sizeof(block)); /*Reallocating with increased height value*/
                        board[i][j][board[i][j][0].value].type = 'o'; /*Initializing the new part*/
                        board[i][j][board[i][j][0].value].value = 0;
                        board[i][j][0].value = board[i][j][0].value+1; /*Increasing the height value hold by the first obstacle*/
                    }
                }
            }
        }
        if(obs_count<3){ /*If the obstacle count is less then 3,adds a new obstacle with height 1 according to the rules*/
            int obs_x,obs_y,valid_obs;
            do{
                valid_obs=1;
                obs_x = rand()%10;
                obs_y = rand()%10;
                for(i=0;i<(*size);i++){
                    if((snake[i].col==obs_y)&&(snake[i].row==obs_x)) valid_obs=0;
                }
                if(board[obs_x][obs_y][0].type!='e') valid_obs = 0;
            }while(valid_obs==0);
            board[obs_x][obs_y][0].type = 'o';
            board[obs_x][obs_y][0].value = 1;
        }
    }

    return snake;
}
