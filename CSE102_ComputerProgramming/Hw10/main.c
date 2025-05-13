#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(){
    char *filename = "database.txt";
    book * book_list = getBookData(filename); /*Takes the data from the text file and stores it on the linked lists*/
    student * student_list = getStudentData(filename);

    char isbn[20],author[40],title[40]; /*This variables are only for the input part*/
    int publicationYear,ID;             /*Program holds every data ,including strings ,dynamically on linked lists*/

    char choice,check,method;
    int filterChoice,sortChoice;
    char feature[10],filterValue[40];
    do{
        menu();
        scanf(" %c",&choice);
        switch(choice){
            case '1': printf("Enter the isbn number of the book: ");
                      scanf("%*c%[^\n]s",isbn);
                      printf("Enter the title of the book: ");
                      scanf("%*c%[^\n]s",title);
                      printf("Enter name of the author of the book: ");
                      scanf("%*c%[^\n]s",author);
                      printf("Enter the publication year of the book: ");
                      scanf("%d",&publicationYear);
                      do{
                        printf("Enter the management method(0:FIFO 1:LIFO): ");
                        scanf(" %c",&method);
                        if(method!='0' && method!='1'){
                            printf("Non valid method, try again.\n");
                            check = '0';
                        }
                        else check='1';
                      }while(check=='0');
                      book_list = addBook(book_list,isbn,title,author,publicationYear,method-48);
                      break;
            case '2': printf("Enter the isbn number of the book that will be deleted: ");
                      scanf("%*c%[^\n]s",isbn);
                      book_list = deleteBook(book_list,isbn);
                      break;
            case '3': printf("ISBN of the book that will be updated: ");
                      scanf("%*c%[^\n]s",isbn);
                      printf("Enter the feature that will be updated(author,title or year): ");
                      scanf("%s",feature);
                      printf("Enter a new value for your feature: ");
                      scanf("%*c%[^\n]s",filterValue);
                      updateBook(book_list,isbn,feature,filterValue);
                      break;
            case '4': printf("Enter your filter choice(0:Author 1:Year): ");
                      scanf("%d",&filterChoice);
                      printf("Enter the value for your filter: ");
                      scanf("%*c%[^\n]s",filterValue);
                      printf("Enter your sort choice(0:Title 1:Author 2:Year): ");
                      scanf("%d",&sortChoice);
                      filterAndSortBooks(book_list,filterChoice,filterValue,sortChoice);
                      break;
            case '5': book_list = reverseBookList(book_list);
                      break;
            case '6': printf("Choice of search(0:ISBN 1:Author 2:Title): ");
                      scanf("%d",&filterChoice);
                      printf("Value for your criteria: ");
                      scanf("%*c%[^\n]s",filterValue);
                      searchBooks(book_list,filterChoice,filterValue);
                      break;
            case '7': printf("ISBN of the book you want to borrow: ");
                      scanf("%*c%[^\n]s",isbn);
                      printf("Enter your student ID: ");
                      scanf("%d",&ID);
                      borrowBooks(book_list,student_list,isbn,ID);
                      break;
            case '8': printf("ISBN of the book you want to return: ");
                      scanf("%*c%[^\n]s",isbn);
                      printf("Enter your student ID: ");
                      scanf("%d",&ID);
                      returnBooks(book_list,student_list,isbn,ID);
                      break;
            case '9': displayBooks(book_list);
                      break;
            case '+': displayStudents(student_list);
                      break;
            case '*': printf("Enter the ID of the student: ");
                      scanf("%d",&ID);
                      student_borrowed(student_list,ID);
                      break;
            case 'a': printf("Enter the name of the student: ");
                      scanf("%*c%[^\n]",author);
                      printf("Enter the ID of the student: ");
                      scanf("%d",&ID);
                      student_list = addStudent(student_list,author,ID);
                      break;
            case 'd': printf("Enter the ID of the student that will be deleted: ");
                      scanf("%d",&ID);
                      student_list = deleteStudent(book_list,student_list,ID);
                      break;
            case '0': printf("\nTerminating the program.\n");
                      break;
            default: printf("Non valid input, please try again.\n");
        }
        updateDatabase(filename,book_list,student_list); /*Writing the updated data on our text file*/
    }while(choice!='0');

    return 0;
}