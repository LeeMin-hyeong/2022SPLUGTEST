#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct member{
    char ID[256];
    char PW[256];
    char name[256];
    struct member *next;
}Member;

typedef struct word{
    char English[256];
    char Korean[256];
    struct word *next;
}Word;

void First();
void Second();
void Third();
void Fourth();
void Fifth();
void Load();
void Save();
void VocaOpen();
void SortWord(Word*ptr, int);
void Swap(Word*ptr1, Word*ptr2);
void ShowVoca(Word*ptr, int);

int loginstate=0;
char tempid[256]={0};
int length=0;

Member*head=NULL;
Word*start=NULL;




int main(){
    int choice;
    Load();

    
    while(1){
        printf("\n\n\t\t2022 SPLUG\n");
        printf("\t\t\t\t%s\n", (loginstate)?(tempid):(" "));
        printf("\t\tMENU\n\n");
        printf("1. 회원가입\n");
        printf("2. 로그인\n");
        printf("3. 로그아웃\n");
        printf("4. 영어 단어 맞추기\n");
        printf("5. 회원 탈퇴\n");
        printf("6. 프로그램 종료\n");
        printf("입력 : ");
	scanf("%d", &choice);

        switch(choice){
            case 1 : First(); break;
            case 2 : Second(); break;
            case 3 : Third(); break;
            case 4 : Fourth(); break;
            case 5 : Fifth(); break;
            case 6 :
                Save();
                printf("프로그램을 종료합니다.\n");
                exit(0);
        }
    }
    return 0;
}



void Load(){
    FILE*load=fopen("member.txt", "rt");
    if (load!=NULL){
        Member*Bridge=NULL;
        while (feof(load)==0){
            Bridge=(Member*)malloc(sizeof(Member));
            Bridge->next=NULL;
            fscanf(load, "%s %s %s\n", Bridge->ID, Bridge->PW, Bridge->name);

            if (head==NULL)
                head=Bridge;
            else{
                Member*temp=head;
                while(temp->next!=NULL){
                    temp=temp->next;
		}
                temp->next=Bridge;
            }
        }
    }
    fclose(load); 
}



void Save(){
    FILE*save=fopen("member.txt", "wt");
    if (head!=NULL){
        while(head->next!=NULL){
            fprintf(save, "%s %s %s\n", head->ID, head->PW, head->name);
            head=head->next;
        }
        fprintf(save, "%s %s %s", head->ID, head->PW, head->name);
        free(head);
        fclose(save); 
    }
}



void First(){
    Member *person1=NULL;
    person1=(Member*)malloc(sizeof(Member));
    Member*current=NULL;
    current=(Member*)malloc(sizeof(Member));
    current=head;

    
    printf("아이디 : "); scanf("%s", person1->ID); 

    if (strcmp(head->ID, person1->ID)==0){
        printf("중복된 아이디 입니다.\n");
        return;
        }
    else{
        while(current!=NULL){
            if (strcmp(current->ID, person1->ID)==0){
                printf("중복된 아이디 입니다.\n");
                return;
            }
            current=current->next;
        }
    }

    printf("비밀번호 : "); scanf("%s", person1->PW);
    printf("이름 : "); scanf("%s", person1->name);
    person1->next=NULL;

    if(head==NULL){
        head=person1;
    }
    else{
        Member*temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=person1;
    }
    printf("회원가입 성공\n");
}



void Second(){

    
    char temppw[256];
    Member*current=NULL;
    current=(Member*)malloc(sizeof(Member));
    current=head;

    printf("아이디 : "); scanf("%s", tempid);

    if (strcmp(head->ID, tempid)==0){
        printf("비밀번호 : "); scanf("%s", temppw);
        if (strcmp(head->PW, temppw)==0){
            printf("로그인 완료.\n");
            loginstate=1;
	    return;
        }
        else{
            printf("잘못된 비밀번호입니다.\n");
            return;
        }
    }

    else{
        while(current!=NULL){
            if (strcmp(current->ID, tempid)==0){
                printf("비밀번호 : "); scanf("%s", temppw);
                if (strcmp(current->PW, temppw)==0){
                    printf("로그인 완료.\n");
                    loginstate=1;
                    return;
                }
                else{
                    printf("잘못된 비밀번호입니다.\n");
                    return;
                }
            }
            current=current->next;
        }
        printf("없는 아이디 입니다.\n");
    }

}



void Third(){
    char A;
    if(loginstate){
        getchar();
        printf("로그아웃 하시겠습니까? [Y/N] : "); 
        scanf("%c", &A);
        if ((A=='Y')||(A=='y')){
            loginstate=0;
            return;
        }
        else if ((A=='N'||A=='n'))
            return;
    }
    printf("로그인 상태가 아닙니다.\n");
}



void Fifth(){
    char A;
    if(loginstate){
        getchar();
        printf("탈퇴하시겠습니까? [Y/N] : ");
        scanf("%c", &A);

        if ((A=='Y')||(A=='y')){
            loginstate=0;
            Member*remove=NULL;
            remove=(Member*)malloc(sizeof(Member));
            Member*current=head;
            Member*before=head;

            
            if (strcmp(head->ID, tempid)==0){
                remove=head;
                head=head->next;
            }
            else{
                while(current!=NULL){
                    if (strcmp(current->ID, tempid)==0){
                        remove=current;
                        before->next=current->next;
                        break;
                        }
                    before=current;                   
                    current=current->next;
                }
            }           
            free(remove);           
        printf("탈퇴가 완료되었습니다.\n");
	return;
        }

        else if ((A=='N'||A=='n'))
            return;
    }
    
    printf("로그인상태가 아닙니다.\n");
}



void Fourth(){
    
    VocaOpen(); 
    SortWord(start, length);
    ShowVoca(start, length); 
    free(start);

}



void VocaOpen(){  
    FILE*word=fopen("word.txt", "rt");
    if (word!=NULL){
        Word*Bridge=NULL;
        while (feof(word)==0){
            Bridge=(Word*)malloc(sizeof(Word));
            Bridge->next=NULL;
            fscanf(word, "%s %s\n", Bridge->English, Bridge->Korean);

            if (start==NULL){
                start=Bridge;
                length+=1;
            }
            else{
                Word*temp=start;
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                temp->next=Bridge;
                length+=1;
            }
        }
    }
    fclose(word); 

}



void SortWord(Word*ptr, int size){
    Word*current=NULL;
    current=(Word*)malloc(sizeof(Word));
    current=ptr;

    for (int i=0; i<size; i++){
        if(current->next==NULL){
            break;
        }   
        for(int j=0; j<size-i-1; j++){
            if(strcmp(current->English, current->next->English)>0)
                Swap(current, current->next);
            current=current->next;
        }
        current=ptr;
    }
}



void Swap(Word*ptr1, Word*ptr2){
    char temp[256];
    strcpy(temp, ptr1->English);
    strcpy(ptr1->English, ptr2->English);
    strcpy(ptr2->English, temp);

    strcpy(temp, ptr1->Korean);
    strcpy(ptr1->Korean, ptr2->Korean);
    strcpy(ptr2->Korean, temp);    
}



void ShowVoca(Word*ptr, int size){
    Word*current=NULL;
    current=(Word*)malloc(sizeof(Word));
    current=ptr;

    char temp[256];
    int score=0;

    while(current!=NULL){
        for (int i=0; i<size; i++){
            printf("%s : ", current->English); scanf("%s", temp);
            if (strcmp(current->Korean, temp)==0){
                printf("correct.\n");
                score+=1;
            }
            else if (strcmp(temp, ".quit")==0){
                printf("socre : %d \n quit.\n", score);
                return;
            }
            else
                printf("incorrect.\n");
            current=current->next;
        }
    }
    printf("score : %d \n quit. \n", score);
}


