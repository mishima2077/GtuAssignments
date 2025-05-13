#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
}Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
}Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
}Asset4;

typedef struct{
    char str[7];
}bin_read;

void fillLinkedList(struct Node** head);

void serializeLinkedList(struct Node* head);

void deserializeLinkedList(struct Node** head);

void printLinkedList(struct Node* head);

int main(){
    struct Node *head;
    struct Node *after;

    fillLinkedList(&head);

    printf("Values of the head list.\n\n");
    printLinkedList(head);
    printf("\n");
    
    serializeLinkedList(head);

    deserializeLinkedList(&after);

    printf("Values of the after list.\n\n");
    printLinkedList(after);
    printf("\n");
}

void fillLinkedList(struct Node** head){
    srand(time(NULL));
    
    (*head) = (struct Node*) malloc(sizeof(struct Node));
    struct Node *assigner = (*head);
    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;

    int asset_num = (rand()%11)+10,i,asset_type;

    for(i=0;i<asset_num;i++){
        if(i!=0) assigner = assigner->next;
        asset_type = (rand()%4)+1;
        switch(asset_type){
            case 1: asset1 = malloc(sizeof(Asset1));
                    asset1->ivals[0] = rand()%101;
                    asset1->svals[0] = (rand()%1001)/10;
                    strcpy(asset1->type,"Asset1");
                    assigner->data = asset1;
                    break;
            case 2: asset2 = malloc(sizeof(Asset2));
                    asset2->ivals[0] = rand()%101;
                    asset2->ivals[1] = rand()%101;
                    asset2->svals[0] = (rand()%1001)/10;
                    asset2->svals[1] = (rand()%1001)/10;
                    strcpy(asset2->type,"Asset2");
                    assigner->data = asset2;
                    break;
            case 3: asset3 = malloc(sizeof(Asset3));
                    strcpy(asset3->string1,"string1_");
                    asset3->string1[8] = (rand()%10)+49;
                    asset3->string1[9] = '\0';
                    strcpy(asset3->string2,"string1_");
                    asset3->string2[8] = (rand()%10)+49;
                    asset3->string2[9] = '\0';
                    strcpy(asset3->type,"Asset3");
                    assigner->data = asset3;
                    break;
            case 4: asset4 = malloc(sizeof(Asset4));
                    asset4->value1 = (rand()%1001)/10;
                    asset4->value2 = (rand()%1001)/10;
                    asset4->value3 = (rand()%1001)/10;
                    strcpy(asset4->type,"Asset4");
                    assigner->data = asset4;
                    break;
        }
        assigner->next = (struct Node*) malloc(sizeof(Node));
    }

    free(assigner->next);
    assigner->next = NULL;
}

void serializeLinkedList(struct Node* head){
    FILE *fp = fopen("linkedlist.bin","wb");
    if(fp==NULL){
        printf("File couldn't be opened.\n");
        return;
    }

    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;
    bin_read asset_type;

    while(head!=NULL){
        asset1 = head->data;
        if(strcmp(asset1->type,"Asset1")==0){
            strcpy(asset_type.str,asset1->type);
            fwrite(&asset_type,sizeof(bin_read),1,fp);
            fwrite(asset1,sizeof(Asset1),1,fp);
            goto jump;
        }
        asset2 = head->data;
        if(strcmp(asset2->type,"Asset2")==0){
            strcpy(asset_type.str,asset2->type);
            fwrite(&asset_type,sizeof(bin_read),1,fp);
            fwrite(asset2,sizeof(Asset2),1,fp);
            goto jump;
        }
        asset3 = head->data;
        if(strcmp(asset3->type,"Asset3")==0){
            strcpy(asset_type.str,asset3->type);
            fwrite(&asset_type,sizeof(bin_read),1,fp);
            fwrite(asset3,sizeof(Asset3),1,fp);
            goto jump;
        }
        asset4 = head->data;
        if(strcmp(asset4->type,"Asset4")==0){
            strcpy(asset_type.str,asset4->type);
            fwrite(&asset_type,sizeof(bin_read),1,fp);
            fwrite(asset4,sizeof(Asset4),1,fp);
            goto jump;
        }

        jump:

        head = head->next;
    }

    printf("\n\nLinked list serialized.\n\n");
    fclose(fp);
}

void deserializeLinkedList(struct Node** head){
    FILE *fp = fopen("linkedlist.bin","rb");
    if(fp==NULL){
        printf("File couldn't be opened.\n");
        return;
    }
    
    (*head) = (struct Node*) malloc(sizeof(struct Node));
    struct Node *assigner = (*head);
    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;
    bin_read asset_type;
    int byte_num,i;

    for(i=0;i<20;i++){
        if(i!=0) assigner = assigner->next;

        byte_num = fread(&asset_type,sizeof(bin_read),1,fp);

        if(strcmp(asset_type.str,"Asset1")==0){
            asset1 = malloc(sizeof(Asset1));
            fread(asset1,sizeof(Asset1),1,fp);
            assigner->data = asset1;
        }
        else if(strcmp(asset_type.str,"Asset2")==0){
            asset2 = malloc(sizeof(Asset2));
            fread(asset2,sizeof(Asset2),1,fp);
            assigner->data = asset2;
        }
        else if(strcmp(asset_type.str,"Asset3")==0){
            asset3 = malloc(sizeof(Asset3));
            fread(asset3,sizeof(Asset3),1,fp);
            assigner->data = asset3;
        }
        else if(strcmp(asset_type.str,"Asset4")==0){
            asset4 = malloc(sizeof(Asset4));
            fread(asset4,sizeof(Asset4),1,fp);
            assigner->data = asset4;
        }
        else i=20;

        assigner->next = (struct Node*) malloc(sizeof(Node));
    }

    free(assigner->next);
    assigner->next = NULL;

    fclose(fp);
}

void printLinkedList(struct Node* head){
    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;

    while(head!=NULL){
        asset1 = head->data;
        if(strcmp(asset1->type,"Asset1")==0){
            printf("Asset type: %s ",asset1->type);
            printf("ivals[0]: %d ",asset1->ivals[0]);
            printf("svals[0]: %.2f ",asset1->svals[0]);
            goto jump;
        }
        asset2 = head->data;
        if(strcmp(asset2->type,"Asset2")==0){
            printf("Asset type: %s ",asset2->type);
            printf("ivals[0]: %d ",asset2->ivals[0]);
            printf("ivals[1]: %d ",asset2->ivals[1]);
            printf("svals[0]: %.2f ",asset2->svals[0]);
            printf("svals[1]: %.2f ",asset2->svals[1]);
            goto jump;
        }
        asset3 = head->data;
        if(strcmp(asset3->type,"Asset3")==0){
            printf("Asset type: %s ",asset3->type);
            printf("String 1: %s ",asset3->string1);
            printf("String 2: %s ",asset3->string2);
            goto jump;
        }
        asset4 = head->data;
        if(strcmp(asset4->type,"Asset4")==0){
            printf("Asset type: %s ",asset4->type);
            printf("Value 1: %.2f ",asset4->value1);
            printf("Value 2: %.2f ",asset4->value2);
            printf("Value 3: %.2f ",asset4->value3);
            goto jump;
        }

        jump:
        printf("\n");
        head = head->next;
    }
}