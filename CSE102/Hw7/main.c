#include <stdio.h>
#include <string.h>
#define MAX_INPUT_WORD 100
#define MAX_WORD_SIZE 31 //There are larger strings in the input.txt than 12 characters, thus I made it larger
#define MAX_DICT_SIZE 2000 //Pdf states 300k for this value but stack is not enough for both words[] and dict[],Max amount of words on dictionary that this program can handle is 2000
#define MAX_TEXT_WORD 200000
#define MAX_VECTOR_SIZE 400
#define HIST_SIZE 22


int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);

int read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]);

void copy_string(char dest[],char start[]);

//Returns -2 if file can't be opened, -1 if the closest word is not in the threshold and returns the dissimilarity value if everyting is alright
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold,int index);

int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[],char hist[][HIST_SIZE]);

int main(int argc, char *argv[]){
    //Taking the input from the user
    char user_words[MAX_INPUT_WORD][MAX_WORD_SIZE],c;
    int user_count=0;

    printf("Enter word(s): ");
    do{
        scanf("%s",user_words[user_count]);
        c = getchar();
        user_count++;
    }while(c!='\n');
    user_words[user_count][0]='-'; //Putting the sentinel value 
    user_words[user_count][1]='\0'; 

    char hist[MAX_INPUT_WORD][HIST_SIZE]; //This will only hold the * and + for the given words
    char closest[MAX_INPUT_WORD][MAX_WORD_SIZE]; //This will hold the closest word to given one if the given one is not in input.txt
    char dict[MAX_DICT_SIZE][MAX_WORD_SIZE]; //This will hold the words from the dictionary
    char words[MAX_TEXT_WORD][MAX_WORD_SIZE]; //This will hold the words from the input.txt
    int occurances[MAX_INPUT_WORD]; //This will hold the occurance of the given word, it will hold -occurance of the closest words occurance if the given word is not in input.txt
                                    //Putting the negative of the closest words occurance is useful in histogram function, that way function knows to whether put + or *
    int text_count,dict_count,i,j,k,word_count=0,closest_index,scale;
    double diss=0,diss_check,threshold=0.01;

    char dict_name[] = "dictionary.txt";
    char text_name[] = "input.txt";
    char ignore_name[] = "ignore.txt";

    dict_count = read_dict(dict_name,dict);
    text_count = read_text(text_name,ignore_name,words);

    if(user_count == 1){
        for(i=0;i<text_count;i++){
            if(!strcmp(user_words[0],words[i])) word_count++;
        }
        if(word_count==0){
            for(i=0;i<dict_count;i++){
                if(strcmp(user_words[0],dict[i])!=0){ //Checks if they are the same word or not,
                    diss_check = dissimilarity(user_words[0],dict[i],dict,threshold,i);
                    if(diss_check>0){ //This check means everything went okay in the function and the word is in threshold
                        if(diss_check>diss){
                            diss = diss_check;
                            closest_index = i;
                        }
                    }
                }
            }
            if(diss==0){
                printf("\"%s\" doesn't appear on \"%s\"\n",user_words[0],text_name);
            }
            else{
                for(i=0;i<text_count;i++){
                    if(!strcmp(dict[closest_index],words[i])) word_count++;
                }
                if(word_count!=0) printf("\"%s\" doesn't appear in \"%s\" but \"%s\" appears %d times.\n",user_words[0],text_name,dict[closest_index],word_count);
                else printf("\"%s\" doesn't appear on \"%s\"\n",user_words[0],text_name); 
            }

        }
        else{
            printf("\"%s\" appears on \"%s\" %d times.\n",user_words[0],text_name,word_count);
        }
    }
    else{
        for(k=0;k<user_count;k++){ //This loop sets up the occurances array as I explained above
            for(i=0;i<text_count;i++){
                if(!strcmp(user_words[k],words[i])) word_count++;
            }
            if(word_count!=0){
                occurances[k] = word_count;
            }
            else{
                for(i=0;i<dict_count;i++){
                    if(strcmp(user_words[k],dict[i])!=0){
                        diss_check = dissimilarity(user_words[k],dict[i],dict,threshold,i);
                        if(diss_check>0){ 
                            if(diss_check>diss){
                                diss = diss_check;
                                closest_index = i;
                            }
                        }
                    }
                }
                if(diss==0){
                    occurances[k]=0;
                }
                else{
                    for(i=0;i<text_count;i++){
                        if(!strcmp(dict[closest_index],words[i])) word_count++;
                    }
                    copy_string(closest[k],dict[closest_index]);
                    occurances[k] = -word_count; //I put the negative of the count,this shows that this is the count of the closest word
                }
                diss = 0;
                closest_index = 0;
            }
            word_count=0;
        }
        scale = histogram(user_words,occurances,hist); //Returns the scale and sets up the histogram
        printf("Scale : %d\n",scale);
        for(k=0;k<user_count;k++){ //Prints the result in desired format
            if(occurances[k]>0){
                printf("%-26s%s\n",user_words[k],hist[k]);
            }
            else if(occurances[k]<0){
                printf("%-12s->%-12s%s\n",user_words[k],closest[k],hist[k]);
            }
            else{
                printf("%-26s%s\n",user_words[k],hist[k]);
            }
        }
    }
}

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
    FILE *fp = fopen(file_name,"r");

    if(fp ==NULL){
        printf("Failed to open %s, returning to the main.\n",file_name);
        return -1;
    }

    int num_words,i;
    fscanf(fp,"%*[^=]= %d",&num_words);
    fscanf(fp,"%*[^\n]\n");//skips the rest of the line
    for(i = 0;i<num_words;i++){
        fscanf(fp,"%s %*[^\n]\n",dict[i]); //Program takes the word and skips the rest of the line
    }

    dict[num_words][0] = '-'; //Putting the sentinel value
    dict[num_words][1] = '\0';

    fclose(fp);
    return num_words;
}

int read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){
    FILE *txt = fopen(text_file,"r");
    FILE *ignore = fopen(ignore_file,"r");
    if(txt == NULL){
        printf("%s cannot be opened.Returning to main.",text_file);
        return -1;
    }
    if(ignore == NULL){
        printf("%s cannot be opened.Returning to main.",ignore_file);
        return -2;
    }

    char ignore_words[100][MAX_WORD_SIZE]; //This part takes the words that will be ignored into an string array
    int ign_word_count=0;
    while(!feof(ignore)){
        fscanf(ignore,"%s",ignore_words[ign_word_count]);
        ign_word_count++;
    }
    ign_word_count--;//because the last entry of ignore_words contains only the \n char,so we don't use that

    char *token,buff[100];
    char delim[] = "\"\'()-_.:;,\n\t !?’"; //Set of characters that we will exclude
    int word_count=0,check=0,i;
    while(!feof(txt)){
        fscanf(txt,"%s",buff);
        token = strtok(buff,delim); //This part divides the string we took by the characters on delim array
        while(token != NULL){
            for(i=0;i<ign_word_count;i++){//Checks if the word if its on ignore.txt or not
                if(strcmp(token,ignore_words[i])==0){
                    check=1;
                }
            }
            if(check==0){//If the word is not one of the words that will be ignored,program puts it into the words array
                copy_string(words[word_count],token);
                word_count++;
            }

            token = strtok(NULL,delim);
            check = 0;
        }
    }

    words[word_count][0]='-'; //Adding the sentinel value to the array
    words[word_count][1]='\0';

    fclose(ignore);
    fclose(txt);
    return word_count;
}

void copy_string(char dest[],char start[]){ /*Copies the start string to the dest string*/
    int ind=0;
    while(start[ind]!='\0'){
        dest[ind]=start[ind];
        ind++;
    }
    dest[ind] = '\0';
}

double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold,int index){
    FILE *fp = fopen("dictionary.txt","r");
    if(fp==NULL){
        printf("Couldn't open dictionary.txt.\n");
        return -2;
    }

    int vector_num,dict_num,i,j;
    fscanf(fp,"%*[^=]= %d %*[^=]= %d",&dict_num,&vector_num);
    fscanf(fp,"%*[^\n]\n");//skips the rest of the line

    double vectors[2][MAX_VECTOR_SIZE],diss=0;
    char dict_word[MAX_WORD_SIZE];

    for(i = 0;i < dict_num;i++){ //Finds the word on the dictionary and takes its vector values
        fscanf(fp,"%s",dict_word);
        if(!strcmp(w1,dict_word)){
            for(j=0;j<vector_num;j++){
                fscanf(fp,"%lf",&vectors[0][j]);
            }
            i= dict_num;
        }
        fscanf(fp,"%*[^\n]\n");
    }
    rewind(fp);

    //For the second word, we use the index of it in the dict array,because there are multiple vector values for the same word
    //and they represent different meanings of the same word, so we have to check every one of them
    for(i = 0;i<index+1;i++){ //Here we skip to the of our word
        fscanf(fp,"%*[^\n]\n");
    }
    fscanf(fp,"%s",dict_word);
    if(!strcmp(w2,dict_word)){ //Just to be sure that we have the correct word
            for(j=0;j<vector_num;j++){
                fscanf(fp,"%lf",&vectors[1][j]);
            }
            i= dict_num;
        }

    for(i=0;i<vector_num;i++){
        //printf("1st %lf 2nd %lf\n",vectors[0][i],vectors[1][i]);
        diss += (vectors[0][i]-vectors[1][i])*(vectors[0][i]-vectors[1][i]);
    }
    diss = 1/diss;

    fclose(fp);

    if(diss>threshold){
        return diss;
    }
    else return -1;//Indicates that its not on the threshold
}

int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[],char hist[][HIST_SIZE]){
    int word_count,i,j,biggest,scale;
    for(i=0;words[i][0]!='-';i++) word_count=i;
    word_count++;
    
    //negative occurance means that words closest matchs occurance
    if(occurrences[0]<0) biggest = occurrences[0]*-1;
    else biggest = occurrences[0];


    for(i=0;i<word_count;i++){
        if(occurrences[i]<0){
            if((occurrences[i]*-1)>biggest) biggest = occurrences[i]*-1;
        }
        else{
            if(occurrences[i]>biggest) biggest = occurrences[i];
        }
    }

    //Setting up the histogram
    if(biggest%20==0) scale = biggest/20;
    else scale =(biggest/20) + 1;
    for(i=0;i<word_count;i++){
        if(occurrences[i]>0){
            for(j=0;j<occurrences[i]/scale;j++){
                hist[i][j] = '*';
            }
            hist[i][occurrences[i]/scale] = '\0';
        }
        else if(occurrences[i]<0){
            for(j=0;j<(occurrences[i]*-1)/scale;j++){
                hist[i][j] = '+';
            }
            hist[i][(occurrences[i]*-1)/scale]='\0';
        }
        else if(occurrences[i]==0){
            copy_string(hist[i],"NO MATCHES");
        }
    }
    return scale;
}

