#include <stdio.h>
#include <math.h>

void leap_year(void);

void enhanced_calc(void);

void grade_calc(void);

double factorial(int num);

double calculate(double operand1,double operand2,int op_1,int op_2, char operation);

//This function returns the number of decimals on a float (till the units digit)
int get_decimal(double x);

int main(){
    printf("****************************************\n");
    leap_year();
    printf("****************************************\n");
    enhanced_calc();
    printf("****************************************\n");
    grade_calc();
    return (0);
}

void leap_year(void){
    int year;

    printf("Please enter a year: ");
    scanf("%d",&year);

    if(year%4 == 0){
        if(year%100 == 0 && year%400 != 0){  /*If a year can be divided by 100 and not by 400 is not a leap year*/
            printf("%d is not a leap year\n",year);
        }
        else{
            printf("%d is a leap year\n",year);
        }
    }
    else{
        printf("%d is not a leap year\n",year);
    }
}

void enhanced_calc(void){
    char format,operation;
    int m,n;
    double operand1,operand2,result;
    int op_1,op_2; // These variables are for ! and % operations
    int round; //I have used this variable to round double typed numbers
    
    int check; /*I have used this variable to check if the user typed a desired value/character*/

    int times_ten; /*This variable is used to store the e value for scientific format*/

    /*Input and validation checks ----------------------------------------------------- */

    do{
        printf("Enter the format output(S or I): ");
        scanf(" %c",&format);
        if(format!='S' && format!='I'){
            printf("Enter a valid format!\n");
            check = 0;
        }
        else{
            check = 1;
        }
        fflush(stdin); /* Clearing the buffer, without this it would scan new line as a character*/
    } while (check == 0);

    if(format == 'S'){
        do{
            printf("Enter m and n values: ");
            scanf("%d%d",&m,&n);
            if(n>m){
                printf("n value can't be greater that m value!\n");
                check = 0;
            }
            else{
                check = 1;
            }
        } while (check == 0);
    }

    do{
        printf("Enter the operation(+,-,/,*,%c,!,^): ",'%');
        scanf(" %c",&operation);
        if(operation!='+' && operation!='-' && operation!='/' && operation!='*' && operation!='%' && operation!='!' && operation!='^'){
            printf("Enter a valid operation!\n");
            check = 0;
        }
        else{
            check = 1;
        }
    } while (check == 0);

    if(operation == '!'){
        printf("Enter the operand: ");
        scanf("%d",&op_1);
    }
    else if(operation == '%'){
        printf("Enter the first operand: ");
        scanf("%d",&op_1);
        printf("Enter the second operand: ");
        scanf("%d",&op_2);
    }
    else{
        printf("Enter the first operand: ");
        scanf("%lf",&operand1);
        printf("Enter the second operand: ");
        scanf("%lf",&operand2);
    }

    //Here, I round down to operands, if the format is integer only
    if(format=='I'){
        round = operand1;
        operand1 = round;
        round = operand2;
        operand2 = round;
    }

    /*Calculation ----------------------------------------------------- */

    result = calculate(operand1,operand2,op_1,op_2,operation);
    
    /*Output --------------------------------------------------------- */

    if(format == 'S'){
        //This section multiplies or divides the result by 10 to achieve the desired m and n value output
        times_ten = get_decimal(result) - (m-n);
        if(times_ten>0){
            for(int i = 0;i < times_ten;i++){
                result /= 10;
            }
        }
        if(times_ten<0){
            for(int i = 0;i > times_ten;i--){
                result *= 10;
            }
        }

        if(operation=='!'){
            printf("%d! = %.*fe%d\n",op_1,n,result,times_ten);
        }
        else if(operation == '%'){
            printf("%d%c%d = %.*fe%d\n",op_1,'%',op_2,n,result,times_ten);
        }
        else{
            printf("%.0lf%c%.0lf = %.*fe%d\n",operand1,operation,operand2,n,result,times_ten);
        }
    }
    else{
        if(operation=='!'){
            printf("%d! = %.0lf\n",op_1,result);
        }
        else if(operation == '%'){
            printf("%d %c %d = %.0lf\n",op_1,'%',op_2,result);
        }
        else{
            printf("%.0lf %c %.0lf = %.0lf\n",operand1,operation,operand2,result);
        }
    }
}

double calculate(double operand1,double operand2,int op_1,int op_2, char operation){
    double result;

    switch (operation){
        case '!': result = factorial(op_1);
                  break;

        case '+': result = operand1 + operand2;
                  break;

        case '-': result = operand1 - operand2;
                  break;

        case '/': result = operand1 / operand2;
                  break;

        case '*': result = operand1 * operand2;
                  break;
        
        case '%': result = op_1 % op_2;
                  break;

        case '^': result = pow(operand1,operand2);
                  break;
    }
    return result;
}

int get_decimal(double x){
    int decimal = 0;
    while (x>=1){
        x/=10;
        decimal ++;
    }
    return decimal;
}

void grade_calc(void){
    double exam1,exam2,exam3,asgn1,asgn2,final_grade;
    int check;

    do{
        printf("Enter 3 exam grades of student: ");
        scanf("%lf%lf%lf",&exam1,&exam2,&exam3);
        if((exam1<=100 && exam1>=0)&&(exam2<=100 && exam2>=0)&&(exam3<=100 && exam3>=0)){
            check = 1;
        }
        else{
            printf("Please enter valid values!\n");
            check = 0;
        }
    }while(check==0);
    
    do{
        printf("Enter 2 assignment grades of student: ");
        scanf("%lf%lf",&asgn1,&asgn2);
        if((asgn1<=100 && asgn1>=0)&&(asgn2<=100 && asgn2>=0)){
            check = 1;
        }
        else{
            printf("Please enter valid values!\n");
            check = 0;
        }
    }while(check==0);

    final_grade = ((exam1+exam2+exam3)/3.0) * 0.6 + ((asgn1+asgn2)/2.0)*0.4;

    if(final_grade >= 60.0){
        printf("Final Grade: %.1f Passed!\n",final_grade);
    }
    else{
        printf("Final Grade: %.1f Failed!\n",final_grade);
    }
}

double factorial (int num){
    if(num == 1){
        return 1;
    }
    else if (num > 1){
        return num * factorial(num-1);
    }
    else{
        return 0;
    }
}
