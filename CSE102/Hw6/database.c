#include <stdio.h>
#include "database.h"

/*-----------------------------------------------------Main functions-----------------------------------------------------*/

void file_op(){
    FILE *prd = fopen("products.txt","r");
    FILE *stc = fopen("stocks.txt","r");
    int feat_num,prd_num,stc_num,choice;

    prd_num = val_counter(prd); /*Returns the number of values for given file*/
    stc_num = val_counter(stc);
    feat_num = feat_counter(prd); /*Returns the number of extra features on products file*/

    /*Arrays that the program holds and updates the data*/
    char type[MAX_ENTRY],name[MAX_ENTRY][9],brand[MAX_ENTRY][6],branch[MAX_ENTRY][16];
    double price[MAX_ENTRY];
    int curr_stock[MAX_ENTRY],s_pID[MAX_ENTRY];

    //Here, I have set the max lenght for extra feature values 20 characters. Thats why I have used 21
    char feature[MAX_ENTRY][MAX_FEAT][21],upd_name[21],feat_names[MAX_FEAT][21],frst_part[30];

    //This part takes the data to arrays--------------------------------------------------------------------------***
    char buff[60],c,ftr_part[60];
    fgets(buff,60,stc);
    fgets(buff,60,prd);
    int num=0,ind1 = 0,ind2 = 0,i,j,ftr_check,check;
    char *p;

    p = buff; /*This part takes extra features to a string array-------*/
    while(*p!='\0'){
        if(*p==','){
            num++;
            if(num>=5) *p = ' ';
        }
        p++;
    }
    sscanf(buff,"%s %[^\n]s",frst_part,ftr_part);
    for(j = 0;j<feat_num;j++){
        while(ftr_part[ind1]!='\0' && ftr_part[ind1]!=' '){
            feat_names[j][ind2] = ftr_part[ind1];
            ind1++;
            ind2++;
        }
        feat_names[j][ind2] = '\0';
        ind2 = 0;
        ind1++;
    }
    ind1 = 0;/*----------------------------------------------------------*/

    for(i = 0;i<prd_num;i++){
        fgets(buff,60,prd);
        p = buff; /*This part replaces commas with spaces for easier scanning----*/
        while(*p!='\0'){
            if(*p==','){
                *p = ' ';
            }
            p++;
        }/*----------------------------------------------------------------------*/
        sscanf(buff,"%d %c %s %s %lf %[^\n]s",&num,&type[i],name[i],brand[i],&price[i],ftr_part);
        for(j = 0;j<feat_num;j++){
            while(ftr_part[ind1]!='\0' && ftr_part[ind1]!=' '){
                feature[i][j][ind2] = ftr_part[ind1];
                ind1++;
                ind2++;
            }
            feature[i][j][ind2] = '\0';
            ind2 = 0;
            ind1++;
        }
        ind1 = 0;
    }
    for(i = 0;i<stc_num;i++){
        fgets(buff,60,stc);
        p = buff; 
        while(*p!='\0'){
            if(*p==','){
                *p = ' ';
            }
            p++;
        }
        sscanf(buff,"%d %d %s %d",&num,&s_pID[i],branch[i],&curr_stock[i]);
    }
    fclose(prd);
    fclose(stc);
    //----------------------------------------------------------------------------------------------------------------***

    do{ /*This is the main loop of the file operations, changes and additions to the data is made here*/
        /*At the end of the loop,program rewrites the files with their updated values*/

        op_menu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        ftr_check=0;
        switch(choice){
            case 1: printf("Please pay attention to the lenght limitations of your values,or your products file will be corrupted.\n");
                    printf("Enter the type of the product: ");
                    do{
                        scanf(" %c",&type[prd_num]);
                        if(type[prd_num]!='D' && type[prd_num]!='F' && type[prd_num]!='C' && type[prd_num]!='O'){
                            printf("Non valid type. Please try again: ");
                            check = 0;
                        }
                        else check = 1;
                    }while(check==0);

                    printf("Enter the name of the product: ");
                    scanf("%s",name[prd_num]);
                    printf("Enter the brand of the product: ");
                    scanf("%s",brand[prd_num]);
                    printf("Enter the price of the product: ");
                    scanf("%lf",&price[prd_num]);
                    for(i = 0;i<feat_num;i++){
                        printf("Enter the %s of the product: ",feat_names[i]);
                        scanf("%s",feature[prd_num][i]);
                    }
                    prd_num++;
                    break;

            case 2: printf("Enter pID of the product: ");
                    scanf("%d",&num);
                    if(num>prd_num) printf("Product does not exist.\n");
                    else{
                        for(i = num-1;i<prd_num-1;i++){ /*This part updates the product values*/
                            type[i] = type[i+1];
                            copy_string(name[i],name[i+1]);
                            copy_string(brand[i],brand[i+1]);
                            price[i] = price[i+1];
                            for(j = 0;j<feat_num;j++){
                                copy_string(feature[i][j],feature[i+1][j]);
                            }
                        }
                        prd_num--;

                        for(i=0;i<stc_num;i++){/*This loop deletes the stock entries for the deleted product*/
                            if(s_pID[i]==num){
                                for(j = i;j<stc_num-1;j++){
                                    s_pID[j] = s_pID[j+1];
                                    copy_string(branch[j],branch[j+1]);
                                    curr_stock[j] = curr_stock[j+1];
                                }
                                stc_num--;
                            }
                        }

                        for(i=0;i<stc_num;i++){ /*This loop updates the pID values on stocks*/
                                if(s_pID[i]>num) s_pID[i] -= 1;  
                        }
                    }
                    break;

            case 3: printf("Enter pID: ");
                    scanf("%d",&num);
                    if(num>prd_num){
                        printf("Unvalid input.\n");
                        break; /*Terminates the statement in case of non valid input*/
                    }
                    printf("Enter the feature: ");
                    scanf("%s",upd_name);
                    printf("Enter the value: ");
                    if(!compare_str(upd_name,"Type")) scanf(" %c",&type[num-1]);
                    else if(!compare_str(upd_name,"Name")) scanf("%s",name[num-1]);
                    else if(!compare_str(upd_name,"Brand")) scanf("%s",brand[num-1]);
                    else if(!compare_str(upd_name,"Price")) scanf("%lf",&price[num-1]);
                    else{
                        for(i=0;i<feat_num;i++){
                            if(!compare_str(upd_name,feat_names[i])){
                                scanf("%s",feature[num-1][i]);
                                ftr_check=1;
                            }
                        }
                        if(ftr_check==0) printf("Feature not found.\n");
                    }
                    break;

            case 4: printf("Enter the name of the feature: ");
                    scanf("%s",feat_names[feat_num]);
                    for(i = 0;i<prd_num;i++){
                        copy_string(feature[i][feat_num],"None");
                    }
                    feat_num++;
                    break;

            case 5: printf("Please pay attention to the lenght limitations of your values,or your stocks file will be corrupted.\n");
                    printf("Enter pID: ");
                    scanf("%d",&num);
                    if(num>prd_num){
                        printf("Product does not exist.\n");
                        break;
                    }
                    s_pID[stc_num] = num;
                    printf("Enter branch:\n");
                    scanf("%s",branch[stc_num]);
                    printf("Enter current stock: ");
                    scanf("%d",&curr_stock[stc_num]);
                    stc_num++;
                    break;

            case 6: printf("Enter sID of the stock: ");
                    scanf("%d",&num);
                    if(num>stc_num) printf("Stock does not exist.\n");
                    else{
                        for(i = num-1;i<stc_num-1;i++){
                            s_pID[i] = s_pID[i+1];
                            copy_string(branch[i],branch[i+1]);
                            curr_stock[i] = curr_stock[i+1];
                        }
                        stc_num--;
                    }
                    break;

            case 7: printf("Enter sID: ");
                    scanf("%d",&num);
                    if(num>stc_num){
                        printf("Unvalid input.\n");
                        break;
                    }
                    printf("Enter the feature: ");
                    scanf("%s",upd_name);
                    printf("Enter the value: ");
                    if(!compare_str(upd_name,"pID")) scanf("%d",&s_pID[num-1]);
                    else if(!compare_str(upd_name,"Branch")) scanf("%s",branch[num-1]);
                    else if(!compare_str(upd_name,"Current_stock")) scanf("%d",&curr_stock[num-1]);
                    else printf("Unknown feature.\n");
                    break;

            case 8: printf("Returning to the main menu.\n");
                    break;

            default: printf("\nnon valid input, please try again\n");
        }

        //This last part of the loop rewrites the files with their updated values----------------
        prd = fopen("products.txt","w");
        stc = fopen("stocks.txt","w");
        fprintf(prd,"pID,Type,Name,Brand,Price");
        for(j=0;j<feat_num;j++) fprintf(prd,",%s",feat_names[j]);
        fprintf(prd,"\n");
        for(i = 0;i<prd_num;i++){
            fprintf(prd,"%d,%c,%s,%s,%.2lf",i+1,type[i],name[i],brand[i],price[i]);
            for(j=0;j<feat_num;j++) fprintf(prd,",%s",feature[i][j]);
            fprintf(prd,"\n");
        }
        fprintf(stc,"sID,pID,Branch,Current_stock\n");
        for(i=0;i<stc_num;i++) fprintf(stc,"%d,%d,%s,%d\n",i+1,s_pID[i],branch[i],curr_stock[i]);
        fclose(prd);
        fclose(stc);
        //---------------------------------------------------------------------------------------
    }while(choice != 8); /*End of the main loop*/
}

void search_prd(){
    FILE *prd = fopen("products.txt","r");

    //f_line str array will hold the name of the features on the first line on products file
    //filters str array will hold the filter names that the user gave
    //values str array will hold the values for the filters that the user gave
    char choice,buff[60],f_line[MAX_FEAT+4][21],filters[MAX_FEAT+4][21],values[MAX_FEAT+4][21],c;

    int prd_num,i,j,ind,feat_num,check=1,filt_ind;
    double price_low,price_high,price; 
    prd_num = val_counter(prd);
    do{
        ind = 0;
        search_menu();
        printf("Enter your choice: ");
        scanf(" %c",&choice);
        switch(choice){
            case '1': for(i=0;i<prd_num+1;i++){ //Takes the line on the file to memory,then prints it
                        fgets(buff,60,prd);
                        printf("%s\n",buff);
                      }
                      rewind(prd);
                      break;
            case '2': 
                      getchar(); //Gets rid of the \n character

                      printf("Enter the features(first letter must be upper case) and their values(seperated by ,): \n");
                      do{
                            scanf("%20[^,^\n]",filters[ind]);
                            getchar();
                            if(!compare_str(filters[ind],"Price")) scanf("%lf %lf",&price_low,&price_high);
                            else scanf("%20[^,^\n]",values[ind]);
                            c = getchar();
                            ind++;
                      }while(c!='\n');

                      printf("\n");

                      feat_num = feat_counter(prd)+5; //we add +5 because feat_counter returns only the number of extra features
                      for(i=0;i<feat_num;i++){ /*This loop takes the feature names to f_line string array*/
                          fscanf(prd,"%20[^,^\n]",f_line[i]);
                          printf("%s ",f_line[i]);
                          fgetc(prd);
                      }
                      printf("\n\n");
                      
                      for(i=0;i<prd_num;i++){
                         char prod_vals[MAX_FEAT+4][21];
                         for(j=0;j<feat_num;j++){ /*This loop takes the values of the product that we currently check*/
                            if(j!=4) fscanf(prd,"%20[^,^\n]",prod_vals[j]);
                            else fscanf(prd,"%lf",&price);
                            fgetc(prd);
                         }
                         for(j=0;j<ind;j++){ /*Check is 1 before coming into this algorithm, if the said values of the said features*/
                                             /*are different from the values of the product we currently check, check is set to 0*/
                            for(filt_ind = 0;filt_ind<feat_num;filt_ind++){
                                if(!compare_str(filters[j],f_line[filt_ind])){
                                    if(!compare_str(filters[j],"Price")){
                                        if(!(price>=price_low && price_high>=price)) check = 0;
                                    }
                                    else{
                                        if(compare_str(values[j],prod_vals[filt_ind])) check = 0;
                                    }
                                }
                            }
                         }
                         if(check==1){/*If the check is passed then the product has passed the filter, so program prints it*/
                            for(j = 0;j<feat_num;j++){
                                if(j!=4) printf("%s ",prod_vals[j]);
                                else printf("%.2lf ",price);
                            }
                            printf("\n\n");
                         }
                         check = 1;
                      }
                      rewind(prd);
                      break;
            case '3': printf("\nReturning to the main menu.\n");
                      break;
            default: printf("\nNon valid input, please try again.\n");
        }
    }while(choice!='3');
    fclose(prd);
}

void check_stc(){
    FILE *stc = fopen("stocks.txt","r");
    FILE *prd = fopen("products.txt","r");

    //curr_branch str will hold the name of the Branch that the program checks at that moment
    char choice,branch_inpt[16],curr_branch[16];
    int pID_inpt,prd_num=val_counter(prd),stc_num=val_counter(stc),values[3],i,stock;
    do{
        stock = 0;
        check_menu();
        printf("Enter your choice: ");
        scanf(" %c",&choice);
        switch(choice){
            case '1': printf("Enter pID: ");
                      scanf("%d",&pID_inpt);
                      if(pID_inpt>prd_num){
                        printf("Product does not exist.\n");
                        break;
                      }
                      printf("Enter the Branch: ");
                      scanf("%s",branch_inpt);

                      fscanf(stc, "%*[^\n]\n"); /*Just skips a line on stocks file*/
                      for(i=0;i<stc_num;i++){
                        fscanf(stc,"%d %*c %d %*c %16[^,] %*c %d",&values[0],&values[1],curr_branch,&values[2]);
                        if(values[1]==pID_inpt && !compare_str(branch_inpt,curr_branch)){
                            stock+=values[2];
                        }
                      }
                      printf("Current stock of product with pID %d on branch %s is: %d\n",pID_inpt,branch_inpt,stock);
                      rewind(stc);
                      break;
            case '2': printf("Enter the branch you want to list: ");
                      scanf("%s",branch_inpt);
                      fscanf(stc, "%*[^\n]\n"); /*Just skips a line on stocks file*/
                      printf("\nsID,pID,Branch,Current_stock\n");
                      for(i=0;i<stc_num;i++){
                        fscanf(stc,"%d %*c %d %*c %16[^,] %*c %d",&values[0],&values[1],curr_branch,&values[2]);
                        if(!compare_str(branch_inpt,curr_branch)){
                            printf("%d,%d,%s,%d\n",values[0],values[1],curr_branch,values[2]);
                        }
                      }
                      rewind(stc);
                      break;
            case '3': printf("Enter the branch for out of product check: ");
                      scanf("%s",branch_inpt);
                      fscanf(stc, "%*[^\n]\n"); /*Just skips a line on stocks file*/
                      printf("Out of stock product pIDs on %s branch with its sID \n",branch_inpt);
                      for(i=0;i<stc_num;i++){
                        fscanf(stc,"%d %*c %d %*c %16[^,] %*c %d",&values[0],&values[1],curr_branch,&values[2]);
                        if(values[2]==0 && !compare_str(branch_inpt,curr_branch)){
                            printf("pID:%d on %d. stock\n",values[1],values[0]);
                        }
                      }
                      printf("\n");
                      rewind(stc);
                      break;
            case '4': printf("\nReturning to the main menu.\n");
                      break;
            default: printf("\nNon valid input. Try again.\n\n");
        }
    }while(choice!='4');
    fclose(prd);
    fclose(stc);
}

int brand_stock(double arr[][MAX_STOCK]){
    FILE *prd = fopen("products.txt","r");
    FILE *stc = fopen("stocks.txt","r");

    //stock_count var is set to 2 because program starts to set stock values from arr[][2].
    //Essentially, I used it as an index number to set and print stock values
    int prd_num = val_counter(prd),i,j,arr_ind=0,stc_num = val_counter(stc),stock_count=2,x;
    double control_pID,control_price,control_stock;
    char input_brand[6],control_brand[6];
    
    fscanf(prd, "%*[^\n]\n"); /*This section skips the first line for products and stocks files*/
    fscanf(stc, "%*[^\n]\n");

    printf("Enter the brand name: ");
    scanf("%s",input_brand);
    
    for(i=0;i<prd_num;i++){ //This loop sets the pID and price values on the main array
        fscanf(prd,"%lf %*c %*c %*c %*[^,] %*c %6[^,] %*c %lf %*s",&control_pID,control_brand,&control_price);
        if(!compare_str(control_brand,input_brand)){
            arr[arr_ind][0] = control_pID;
            arr[arr_ind][1] = control_price;
            arr_ind++; //Essentially, arr_ind value becomes the size for the used space in our main array
        }
    }

    for(i=0;i<arr_ind;i++){ 
        for(j=0;j<stc_num;j++){
            fscanf(stc,"%*d %*c %lf %*c %*[^,] %*c %lf",&control_pID,&control_stock);
            if(arr[i][0]==control_pID){
                arr[i][stock_count] = control_stock;
                stock_count++;
            }
        }
        stock_count = 2;
        rewind(stc);
        fscanf(stc, "%*[^\n]\n"); /*Again,skips the first line*/
    }

    printf("\npID,Price,Current_stock values\n");
    for(i=0;i<arr_ind;i++){
        printf("%.0lf , %.2lf ,",arr[i][0],arr[i][1]);
        while(arr[i][stock_count]>-0.5 && stock_count < MAX_STOCK){ //If the value is different from the initialized value
                                                                     //then we know there is a stock value there
            printf(" %.0lf",arr[i][stock_count]);
            stock_count++;
        }
        printf("\n");
        stock_count = 2;
    }
    printf("\n");
    fclose(prd);
    fclose(stc);
    return arr_ind; 
}

void export(double arr[][MAX_STOCK],int size){
    FILE *rpt = fopen("report.txt","w");
    fprintf(rpt,"pID , Min_stock , Max_stock , Median_stock\n");
    int i,stock_ind=2;
    double min,max,med,stock_values[MAX_STOCK];
    for(i=0;i<size;i++){
        while(arr[i][stock_ind]> -0.5 && stock_ind < MAX_STOCK){    //If the value is different from the initialized value
                                                                   //then we know there is a stock value there
            stock_values[stock_ind-2] = arr[i][stock_ind];
            stock_ind++;
        } 
        if(stock_ind>2){ /*This checks if there are any stock values to calculate or not*/
            med = find_median(stock_values,stock_ind-2);   /*This function also sorts the array*/
            min = stock_values[0];    /*thus first value becomes min and last value becomes max*/
            max = stock_values[stock_ind-3];
        }
        else{
            med = 0;
            min = 0;
            max = 0;
        }
        
        stock_ind = 2;
        fprintf(rpt,"%.0lf , %.0lf , %.0lf , %.2lf\n",arr[i][0],min,max,med);
        med = 0;
    }
    fclose(rpt);
}

/*-----------------------------------Support functions-----------------------------------*/

void copy_string(char dest[],char start[]){ /*Copies the start string to the dest string*/
    int ind=0;
    while(start[ind]!='\0'){
        dest[ind]=start[ind];
        ind++;
    }
    dest[ind] = '\0';
}

int compare_str(const char arr1[],const char arr2[]){ /*Returns 0 if strings are same, 1 if they are not same*/
    int ind=0,res=0;
    while(arr1[ind]!='\0' && arr2[ind]!='\0'){
        if(arr1[ind]!=arr2[ind]){
            res=1;
        }
        ind++;
    }
    if(arr1[ind]!=arr2[ind]){
        res=1;
    }
    return res;
}

int val_counter(FILE *fp){ /*This function returns the number of values for given file*/
    char buf[60],c;        /*My program uses the values from this function as pID and sID*/
    int val,val_num=0;
    while(!feof(fp)){
        c = fgetc(fp);
        val = c;
        fgets(buf,60,fp);
        if((c!=EOF) && (val>=49 && val<=57)){
            val_num++;
        }
    }
    rewind(fp);
    return val_num;
}

int feat_counter(FILE *fp){ /*This function returns the number of extra features*/
    char buf[60];
    char c;
    int counter=0;
    fgets(buf,60,fp);
    for(int i = 0;i<60;i++){
        if(buf[i]==','){
            counter ++;
        }
    }
    counter -= 4; /*Function essentially counts the commas on the first line*/
    rewind(fp);   /*there are already 4 commas for the main features thats why progam subtracts 4*/
    return counter;
}

double find_median(double arr[],int size){
    int i,j;
    double temp,median;
    for(i=0;i<size-1;i++){
        for(j=0;j<(size-1-i);j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if(size%2==0){
        median = arr[(size/2)-1] + arr[size/2];
        median /= 2;
    }
    else{
        median = arr[((size+1)/2)-1];
    }
    return median;
}

void search_menu(){
    printf("1-List all products\n2-Filter products by brand, type, price, or a user-defined feature\n3-Back to main menu.\n");
}

void check_menu(){
    printf("1-Stock Query\n2-List by Branch\n3-List out of stock\n4-Return to main menu\n");
}

void menu(){
    printf("1-File Operations\n2-Query products\n3-Check stock status\n4-Stock control by brand\n5-Export report\n");
}

void op_menu(){
    printf("1-Add a new product\n2-Delete a product\n3-Update a product\n4-Add feature to products\n5-Add a new stock entry\n");
    printf("6-Delete a stock entry\n7-Update a stock entry\n8-Back to main menu\n");
}