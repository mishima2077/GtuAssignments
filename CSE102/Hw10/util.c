#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/*----------------------------MAIN FUNCTIONS----------------------------*/

book * getBookData(const char *filename){
    book * list = NULL;
    book *temp,*new;
    FILE *fp = fopen(filename,"r");
    if(fp==NULL) return list;

    char isbn[20],author[40],title[40],control;
    int publicationYear,status;
    while(!feof(fp)){
        control = fgetc(fp);
        if(control=='-'){ /*The control char at the beginning of the line, - for books and + for students*/
            /*Program takes the strings until it sees the seperation char, which is |*/
            fscanf(fp,"%[^|] %*c %[^|] %*c %[^|] %*c %d %*c %d",title,author,isbn,&publicationYear,&status);

            new = (book*)malloc(sizeof(book)); /*Creating an initializing a new entry*/
            new->author = calloc(strlen(author)+1,sizeof(char));
            new->title = calloc(strlen(title)+1,sizeof(char));
            new->isbn = calloc(strlen(isbn)+1,sizeof(char));

            strcpy(new->author,author);
            strcpy(new->title,title);
            strcpy(new->isbn,isbn);
            new->year = publicationYear;
            new->status = status;
            new->next = NULL;

            if(list==NULL) list = new; /*Putting the new entry to the end of the list*/
            else{
                temp = list;
                while(temp->next!=NULL) temp = temp->next;
                temp->next = new;
            }
        }
    }
    fclose(fp);
    return list;
}

student * getStudentData(const char *filename){
    student * list = NULL;
    student *temp,*new;
    FILE *fp = fopen(filename,"r");
    if(fp==NULL) return list;

    char name[40],control,borrowed[MAX_BORROW][40];
    int ID,brw_count,i;
    while(!feof(fp)){
        fscanf(fp,"%c",&control);
        if(control=='+'){
            fscanf(fp,"%[^|] %*c %d %*c %d %*c",name,&ID,&brw_count);
            for(i=0;i<brw_count-1;i++) fscanf(fp,"%[^,] %*c",borrowed[i]);
            if(brw_count!=0) fscanf(fp,"%[^\n]",borrowed[brw_count-1]);

            new = (student*)malloc(sizeof(student));

            new->name = calloc(strlen(name)+1,sizeof(char));
            new->borrowed = (char**)calloc(brw_count,sizeof(char*));

            strcpy(new->name,name);
            new->ID = ID;
            new->brw_count = brw_count;
            for(i=0;i<brw_count;i++){
                new->borrowed[i] = calloc(strlen(borrowed[i])+1,sizeof(char));
                strcpy(new->borrowed[i],borrowed[i]);
            }
            new->next = NULL;

            if(list==NULL) list = new;
            else{
                temp = list;
                while(temp->next!=NULL) temp = temp->next;
                temp->next = new;
            }
        }
    }
    fclose(fp);
    return list;
}

void updateDatabase(const char *filename,book *b_list,student *s_list){
    FILE *fp = fopen(filename,"w");
    if(fp==NULL) return;

    while(b_list!=NULL){
        fprintf(fp,"-%s|%s|%s|%d|%d\n",b_list->title,b_list->author,b_list->isbn,b_list->year,b_list->status);
        b_list = b_list->next;
    }
    while(s_list!=NULL){
        fprintf(fp,"+%s|%d|%d|",s_list->name,s_list->ID,s_list->brw_count);
        for(int i = 0;i<s_list->brw_count;i++){
            if(i==0) fprintf(fp,"%s",s_list->borrowed[i]);
            else fprintf(fp,",%s",s_list->borrowed[i]);
        }
        fprintf(fp,"\n");
        s_list = s_list->next;
    }
    fclose(fp);
}

void student_borrowed(student *list,int ID){
    while(list!=NULL && list->ID!=ID) list = list->next;
    if(list!=NULL){
        if(list->brw_count>0){
            printf("\n");
            printf("Borrowed books: |");
            for(int i = 0;i<list->brw_count;i++) printf("%s|",list->borrowed[i]);
            printf("\n");
        }
        else printf("\nThis student currently don't have any borrowed books.\n");
    }
    else printf("\nStudent is not on the list.\n");
}

book * addBook(book *list,char* isbn, char* title, char* author, int publicationYear, int method){
    /*Creating and initializing the new entry*/
    book * new = (book*)malloc(sizeof(book));
    new->title = calloc(strlen(title)+1,sizeof(char));
    new->author = calloc(strlen(author)+1,sizeof(char));
    new->isbn = calloc(strlen(isbn)+1,sizeof(char));
    strcpy(new->title,title);
    strcpy(new->author,author);
    strcpy(new->isbn,isbn);
    new->year = publicationYear;
    new->status = 1;

    if(list==NULL || method==1){ /*LIFO, adding to the beginning of the list*/
        new->next = list;
        list = new;
    }
    else if(method==0){ /*FIFO, adding to the end of the list*/
        book *temp = list;
        while(temp->next!=NULL) temp = temp->next;
        new->next = NULL;
        temp->next = new;
    }
    return list;
}

book * deleteBook(book *list,char* isbn){
    book *pp = list;
    book *pc = list;
    while(pc!=NULL && strcmp(pc->isbn,isbn)!=0){
        pp = pc;
        pc = pc->next;
    }
    if(pc==NULL) printf("\nBook is not on the list,deletion is unsuccesful.\n");
    else{
        if(pc->status==0){
            printf("\nThis book is currently borrowed by a student, it cant be deleted.\n");
            return list;
        }
        if(pc==pp) list = list->next;
        else pp->next = pc->next;
        free(pc->author);
        free(pc->isbn);
        free(pc->title);
        free(pc);
        printf("\nDeletion is succesful.\n");
    }
    return list;
}

student * addStudent(student *list,char *name,int ID){
    student *new,*temp=list;

    /*Allocating and initializing the new entry to the list*/
    new = (student*)malloc(sizeof(student));
    new->name = calloc(strlen(name)+1,sizeof(char));

    strcpy(new->name,name);
    new->ID = ID;
    new->borrowed = 0;
    new->next = NULL;

    if(list==NULL) list = new;
    else{
        while(temp->next!=NULL) temp = temp->next;
        temp->next = new;
    } 
    return list;
}

student * deleteStudent(book * b_list,student *s_list,int ID){
    student *pc=s_list,*pp=s_list;
    while(pc!=NULL && pc->ID!=ID){
        pp = pc;
        pc = pc->next;
    }
    if(pc==NULL){
        printf("\nStudent with given ID is not on the list, deletion is unsuccesfull.\n");
        return s_list;
    }

    /*This part updates the status of the books that is borrowed by the student that will be deleted from the list*/
    /*Program makes all the books status available if the one borrowed them is deleted from the student list*/
    book * temp=b_list;
    for(int i = 0;i<pc->brw_count;i++){
        while(temp!=NULL && strcmp(temp->title,pc->borrowed[i])!=0) temp = temp->next;
        if(temp!=NULL) temp->status=1;
        free(pc->borrowed[i]); /*This part frees up the space that has been used by the string at borrowed array*/
        temp = b_list;
    }

    if(pc==pp) s_list = s_list->next;
    else pp->next = pc->next;
    free(pc->borrowed);
    free(pc->name);
    free(pc);

    return s_list;
}

void updateBook(book *list,char* isbn, char* feature, char* value){
    while(list!=NULL && strcmp(list->isbn,isbn)!=0) list = list->next;
    if(list!=NULL){
        if(strcmp(feature,"author")==0){
            free(list->author);
            list->author = calloc(strlen(value)+1,sizeof(char));
            strcpy(list->author,value);
        }
        else if(strcmp(feature,"title")==0){
            free(list->title);
            list->title = calloc(strlen(value)+1,sizeof(char));
            strcpy(list->title,value);
        }
        else if(strcmp(feature,"year")==0){
            list->year = atoi(value);
        }
        else printf("\nGiven feature name doesn't exit,update have failed.\n");
    }
    else printf("\nBook is not on the list,update have failed.\n");
}

void filterAndSortBooks(book * list,int filterChoice, char* filter, int sortChoice){
    book **filtered_arr = NULL; /*Dynamic pointer array that holds the pointers to the filtered books*/
    int filtered_count = 0;

    /*This part filters the book list and stores the pointers of filtered values in the dynamic pointer array*/
    if(filterChoice==0){
        while(list!=NULL){
            if(strcmp(list->author,filter)==0){
                filtered_count++;
                filtered_arr = (book**) realloc(filtered_arr,filtered_count * sizeof(book*));
                filtered_arr[filtered_count-1] = list;
            }
            list = list->next;
        }
    }
    else if(filterChoice==1){
        while(list!=NULL){
            if(list->year == atoi(filter)){
                filtered_count++;
                filtered_arr = (book**) realloc(filtered_arr,filtered_count * sizeof(book*));
                filtered_arr[filtered_count-1] = list;
            }
            list = list->next;
        }
    }

    /*This part sorts the pointer array according to the desired parameter,then prints the sorted values*/
    if(filtered_count==0) printf("\nThere are no books in desired filter.\n");
    else{
        switch(sortChoice){
            case 0: sortByTitle(filtered_arr,filtered_count);
                    break;
            case 1: sortByAuthor(filtered_arr,filtered_count);
                    break;
            case 2: sortByYear(filtered_arr,filtered_count);
                    break;
        }
        printf("\nFiltered and sorted results:\n\n");
        for(int i = 0;i<filtered_count;i++){
            printBook(filtered_arr[i]);
        }
        printf("\n");
    }
}

book * reverseBookList(book * list){
    book *pp,*pc,*last;
    int size=0,i,j;
    last = list;
    if(last==NULL) return list;

    /*This part finds the lenght of the list,and also the last entry of the list*/
    while(last->next!=NULL){
        size++;
        last = last->next;
    }
    size++;

    if(size==1) return list;

    /*Main algortihm for reversing the pointers*/
    for(i=0;i<size-1;i++){
        pp = list;
        pc = list->next;
        for(j=0;j<size-2-i;j++){
            pp = pp->next;
            pc = pc->next;
        }
        pc->next = pp;
    }
    pp->next = NULL;

    return last;
}

void searchBooks(book * list, int searchChoice, char* searchValue){
    int valid_check,results=0;
    printf("\nFound books that matches your search inputs:\n\n");
    while(list!=NULL){
        valid_check=0;
        switch(searchChoice){
            case 0: if(strcmp(list->isbn,searchValue)==0) valid_check=1;
                    break;
            case 1: if(strcmp(list->author,searchValue)==0) valid_check=1;
                    break;
            case 2: if(strcmp(list->title,searchValue)==0) valid_check=1;
                    break;
        }
        if(valid_check){
            printBook(list);
            results++;
        }
        list = list->next;
    }
    if(results==0) printf("\nNo results found.\n");
}

void borrowBooks(book *b_list,student *s_list,char *isbn,int ID){
    //This part finds the pointers to the Student and the Book that will be updated
    while(b_list!=NULL && strcmp(b_list->isbn,isbn)!=0) b_list = b_list->next; 
    while(s_list!=NULL && s_list->ID!=ID) s_list = s_list->next;

    if(b_list==NULL) printf("\nThe book with given isbn is not on the list.\n");
    else if(s_list==NULL) printf("\nThe student with given ID is not on the list.\n");
    else{
        if(s_list->brw_count>=MAX_BORROW) printf("\nThis student can't borrow any more books, the limit is %d books.\n",MAX_BORROW);
        else if(b_list->status==1){
            b_list->status = 0; /*Updating the book status*/
            s_list->brw_count = s_list->brw_count + 1; /*Updating the borrowed count status*/

            /*Dynamically allocating a space in the string array that holds the titles of the borrowed books*/
            s_list->borrowed = (char**)realloc(s_list->borrowed,(s_list->brw_count)*sizeof(char*)); 
            s_list->borrowed[s_list->brw_count-1] = (char*)calloc(strlen(b_list->title)+1,sizeof(char));

            /*Copying the title of the book to the string array*/
            strcpy(s_list->borrowed[s_list->brw_count-1],b_list->title);
        }
        else printf("\nThis book is currently not available.\n");
    }
}

void returnBooks(book *b_list,student *s_list,char *isbn,int ID){
    //This part finds the pointers to the Student and the Book that will be updated
    while(b_list!=NULL && strcmp(b_list->isbn,isbn)!=0) b_list = b_list->next; 
    while(s_list!=NULL && s_list->ID!=ID) s_list = s_list->next;

    if(b_list==NULL) printf("\nThe book with given isbn is not on the list.\n");
    else if(s_list==NULL) printf("\nThe student with given ID is not on the list.\n");
    else{
        if(b_list->status==0){
            int brw_index=-1,i;
            for(i=0;i<s_list->brw_count;i++){ /*Finding the index of the book that will be returned on the borrowed array*/
                if(strcmp(s_list->borrowed[i],b_list->title)==0){
                    brw_index = i;
                    break;
                }
            }
            if(brw_index!=-1){ /*If the value of the variable is changed,that means the book that will be returned is on out array*/
                b_list->status = 1; /*Updating the books status*/
                free(s_list->borrowed[brw_index]);
                for(i=brw_index;i<s_list->brw_count;i++){ /*Taking the emptied space to the end of the array*/
                    s_list->borrowed[i] = s_list->borrowed[i+1];
                }
                s_list->brw_count = s_list->brw_count-1;
                s_list->borrowed = realloc(s_list->borrowed,(s_list->brw_count)*sizeof(char*)); /*Shrinking the dynamic string array*/
            }
            else printf("\nThe book is not borrowed by this student.Please enter the correct ID\n");
        }
        else printf("\nThis book is returned already.\n");
    }
}

/*----------------------------HELPER FUNCTIONS--------------------------*/

void menu(){
    printf("\n1-Add Book\n");
    printf("2-Delete Book\n");
    printf("3-Update Book\n");
    printf("4-Filter And Sort Books\n");
    printf("5-Reverse Books List\n");
    printf("6-Search Books\n");
    printf("7-Borrow Book\n");
    printf("8-Return Book\n");
    printf("9-Display Books\n");
    printf("+-Display Students\n");
    printf("*-Display Borrowed Books\n");
    printf("a-Add Student\n");
    printf("d-Delete Student\n");
    printf("0-Exit\n");
    printf(">");
}

void displayBooks(book *list){
    printf("\n");
    while(list!=NULL){
        printBook(list);
        list = list->next;
    }
    printf("\n");
}

void displayStudents(student *list){
    printf("\n");
    while(list!=NULL){
        printf("Student Name: %s - ",list->name);
        printf("ID: %d\n",list->ID);
        list = list->next;
    }
}

void printBook(book *node){
    if(node!=NULL){
        printf("Title: %s - ",node->title);
        printf("Author: %s - ",node->author);
        printf("Publication Year: %d - ",node->year);
        printf("ISBN: %s - ",node->isbn);
        if(node->status==1) printf("Available\n");
        else if(node->status==0) printf("Borrowed\n");
    }
}

//All sort functions use the insertion sort algorithm
void sortByYear(book **arr,int size){
    int i,j;
    book *temp;
    for(i=1;i<size;i++){
        for(j=i;j>0;j--){
            if(arr[j]->year < arr[j-1]->year){
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
            else j=0;
        }
    }
}

void sortByAuthor(book **arr,int size){
    int i,j;
    book *temp;
    for(i=1;i<size;i++){
        for(j=i;j>0;j--){
            if(strcmp(arr[j]->author,arr[j-1]->author)<0){
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
            else j=0;
        }
    }
}

void sortByTitle(book **arr,int size){
    int i,j;
    book *temp;
    for(i=1;i<size;i++){
        for(j=i;j>0;j--){
            if(strcmp(arr[j]->title,arr[j-1]->title)<0){
                temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
            else j=0;
        }
    }
}
