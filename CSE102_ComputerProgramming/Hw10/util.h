#ifndef _UTIL_H_
#define _UTIL_H_
#define MAX_BORROW 10

/*----------------------------STRUCTS-----------------------------------*/

typedef struct student{
    char *name;
    char **borrowed; /*String array that contains the titles of the books that are borrowed by the student*/
    int brw_count; /*Number of borrowed books by the student*/
    int ID; 
    struct student *next;
}student;

typedef struct book{
    int year;
    int status; // 1 -> Avaliable  0 -> Borrowed
    char *title,*author,*isbn;
    struct book *next;
}book;

/*----------------------------MAIN FUNCTIONS----------------------------*/

book * getBookData(const char *filename);

student * getStudentData(const char *filename);

void updateDatabase(const char *filename,book *b_list,student *s_list);

void student_borrowed(student *list,int ID);

book * addBook(book *list,char* isbn, char* title, char* author, int publicationYear, int method);

book * deleteBook(book *list,char* isbn);

student * addStudent(student *list,char *name,int ID);

student * deleteStudent(book *b_list,student *s_list,int ID);

void updateBook(book *list,char* isbn, char* feature, char* value);

void filterAndSortBooks(book * list,int filterChoice, char* filter, int sortChoice);

book * reverseBookList(book * list);

void searchBooks(book * list, int searchChoice, char* searchValue);

void borrowBooks(book *b_list,student *s_list,char *isbn,int ID);

void returnBooks(book *b_list,student *s_list,char *isbn,int ID);

/*----------------------------HELPER FUNCTIONS--------------------------*/

void menu();

void sortByYear(book **arr,int size);

void sortByAuthor(book **arr,int size);

void sortByTitle(book **arr,int size);

void displayBooks(book *list);

void displayStudents(student *list);

void printBook(book *node);

#endif 