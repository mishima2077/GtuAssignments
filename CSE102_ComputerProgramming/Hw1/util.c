#include <stdio.h>
#include "util.h"

void gcd(void){
    int n1,n2;
    printf("Type two numbers: \n");
    scanf("%d%d",&n1,&n2);

    //Failsafe for non positive numbers
    if ((n1<=0)||(n2<=0))
    {
        printf("Error, invalid number");
        return;
    }
    
    //These variables will be used when printing out the result
    int backup_1,backup_2;
    backup_1 = n1;
    backup_2 = n2;

    while (n1!=n2)
    {
        if(n1>n2){
            n1 = n1 - n2;
        }
        else{
            n2 = n2 - n1;
        }
    }
    
    printf("Gcd of %d and %d is: %d\n",backup_1,backup_2,n1);
}

void arithmetic_sum(void){
    int n1,n2,sum;
    printf("Type two numbers: \n");
    scanf("%d%d",&n1,&n2);

    sum = n1 + n2;

    printf("First number: %d\nSecond number: %d\nResult:\n%7d\n%7d\n+\n-------\n%7d\n",n1,n2,n1,n2,sum);
}

void arithmetic_multiplication(void){
    int n1,n2,mult;
    printf("Type two numbers: \n");
    scanf("%d%d",&n1,&n2);

    mult = n1 * n2;

    int greater,latter;
    if (n1>n2)
    {
        greater = n1;
        latter = n2;
    }
    else{
        greater = n2;
        latter = n1;
    }

    printf("First number: %d\nSecond number: %d\nResult: \n%10d\n%10d\nx\n----------\n",n1,n2,greater,latter);
    
    /* latter%10 gives the last digit of the smaller number
      Also, dividing a number by 10 basically removes the last digit
      so this time we get the digit before that */

    if (10 > latter)
    {
        printf("%10d\n",greater*(latter%10));
    }
    else if (100>latter)
    {
        printf("%10d\n%9d\n",greater*(latter%10),greater*((latter/10)%10));
        printf("+\n----------\n%10d\n",mult);
    }
    else if (1000>latter)
    {
        printf("%10d\n%9d\n%8d\n",greater*(latter%10),greater*((latter/10)%10),greater*((latter/100)%10));
        printf("+\n----------\n%10d\n",mult);
    }
}

void num_check(void){
    int number;
    printf("Type a number between 1 and 10(1 and 10 included): ");
    scanf("%d",&number);

    printf("\n");

    if (number>10 || 1>number)
    {
        printf("Invalid input\n");
    }
    else if(number > 5){
        printf("The integer you entered is greater than 5\n");
    }
    else{
        printf("The integer you entered is less than or equal to 5\n");
    }
}
