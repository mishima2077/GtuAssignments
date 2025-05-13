#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define UP1 'w'
#define UP2 'W'
#define DOWN1 's'
#define DOWN2 'S'
#define LEFT1 'a'
#define LEFT2 'A'
#define RIGHT1 'd'
#define RIGHT2 'D'

void menu(void);

void help(void);

void puzzle_game(void);

void print_screen(int cx, int cy, int dx, int dy, int sz);

void movement(int *char_x,int *char_y,int *door_x,int *door_y,char *move,int *size,int *mv_counter);

int status_control(int cx, int cy, int dx, int dy);

int main(){
    printf("Welcome to the 2D puzzle game!\n");
    
    int selection;
    menu();
    scanf("%d",&selection);

    while(1){
        switch(selection){
            case 1 : puzzle_game();
                    break;
            case 2 : help();
                    break;
            case 3 : printf("Thanks for playing 2d Puzzle game!\n");
                    return(0);
                    break;
            default: printf("Non valid input, please try again: ");
                            break;
        }
        menu();
        scanf("%d",&selection);
    }
}

void menu(void){
    printf("1. New game\n");
    printf("2. Help\n");
    printf("3. Exit\n");
    printf("Select: ");
}

void help(void){
    printf("Your character is shown as 'C', and your objective is to reach the door which is shown as 'D'.\n");
    printf("You are able to move your character with w,a,s,d keys. Use w to go up, s to go down, d to go right and a to go left.\n");
}

void puzzle_game(void){
    int size;
    int check = 0; /*General status control variable*/
    char move;
    char test;
    int mv_counter = 0;
    srand(time(NULL));
    
    //Setting up the parameters
    printf("Enter the size of the room (min:5 max:10): ");
    do{
	 scanf("%d",&size);
        if(size>=5 && size<=10){
            check = 1;
        }
        else{
            check = 0;
            printf("Please enter a valid size: ");
        }
    }while(check==0);

    int door_x,door_y,char_x,char_y;

    door_x = rand()%(size);
    door_y = rand()%(size);
    char_x = rand()%(size);
    
    do{
        char_y = rand()%(size);
        if((door_x == char_x)&&(door_y == char_y)){
            check = 0;
        }
        else{
            check = 1;
        }
    }while(check==0);

    do{
        print_screen(char_x,char_y,door_x,door_y,size);
        printf("\nMove: ");
        scanf(" %c",&move);

        //This part makes sure that user only can enter one valid input, so character can't move diagonally
        scanf("%c",&test);
        if(test != 10){ /*If the char after the first one isn't '\n' then it means users input is invalid*/
            move = ' ';
        }

        movement(&char_x,&char_y,&door_x,&door_y,&move,&size,&mv_counter);
        
        check = status_control(char_x,char_y,door_x,door_y);
    }while(!check);

    printf("Congratulations! \nThe game has ended. You have made %d moves.\n",mv_counter);
}

void print_screen(int cx, int cy, int dx, int dy, int sz){
    for(int i = 0;i<(sz*2)+1;i++){
        printf("-");
    }
    printf("\n");

    for(int i = 0;i < sz;i++){
        printf("|");
        for(int z = 0;z < sz;z++){
            if(z==dx && i==dy){
                printf("D|");
            }
            else if(z==cx && i==cy){
                printf("C|");
            }
            else{
                printf(" |");
            }
        }
        printf("\n");
    }

    for(int i = 0;i<(sz*2)+1;i++){
        printf("-");
    }
    printf("\n");
}

void movement(int *char_x,int *char_y,int *door_x,int *door_y,char *move,int *size,int *mv_counter){
    switch(*move){
            case UP1:
            case UP2: if(*char_y==0){
                        printf("You can't move into that direction!\n");
                    }
                    else{
                        *char_y = *char_y - 1; /*My print_screen algoritm takes the top left corner as (0,0) and downwards as positive, thats why I decrement y value here*/
                        *mv_counter = *mv_counter + 1;
                    }
                    break;
            case DOWN1:
            case DOWN2: if(*char_y==(*size-1)){
                        printf("You can't move into that direction!\n");
                    }
                    else{
                        *char_y = *char_y + 1;
                        *mv_counter = *mv_counter + 1;
                    }
                    break;
            case LEFT1:
            case LEFT2: if(*char_x==0){
                        printf("You can't move into that direction!\n");
                    }
                    else{
                        *char_x = *char_x - 1;
                        *mv_counter = *mv_counter + 1;
                    }
                    break;
            case RIGHT1:
            case RIGHT2: if(*char_x==(*size-1)){
                        printf("You can't move into that direction!\n");
                    }
                    else{
                        *char_x = *char_x + 1;
                        *mv_counter = *mv_counter + 1;
                    }
                    break;
            default: printf("Please enter a valid input\n");
                    break;
        }
}

int status_control(int cx, int cy, int dx, int dy){
    if((cx == dx)&&(cy == dy)){
        return 1;
    }
    else{
        return 0;
    }
}
