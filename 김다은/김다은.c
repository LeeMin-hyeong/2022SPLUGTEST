#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE{
    char id[20],pw[20],name[20];
    struct NODE *next;
}NODE;

char eng[100][30], kor[100][30];
int cnt=0;

bool idcheck=0;
bool login=0;
char login_id[20];

void push(NODE *head,char id[],char pw[],char name[]){
    NODE *new = malloc(sizeof(NODE));
    new->next=head->next;
    head->next=new;
    strcpy(new->id,id);
    strcpy(new->pw,pw);
    strcpy(new->name,name);
}

void search_id(NODE *head,char check_id[])
{
    NODE *cur = malloc(sizeof(NODE));
    cur =head->next;
    while (cur != NULL){
        if(strcmp(cur->id,check_id)==0){
            printf("중복된 아이디입니다.\n");
            idcheck=1;
        }
        return;
    }
}

void search(NODE *head, char ch_id[], char ch_pw[])
{
    NODE *cur = malloc(sizeof(NODE));
    cur=head->next;
    while(cur!=NULL){
        if(strcmp(cur->id,ch_id)==0){
            if(strcmp(cur->pw,ch_pw)==0){
                login=1;
                strcpy(login_id,cur->id);
            }
            else{
                printf("비밀번호가 틀렸습니다.\n");
            }
            return;
        }
        cur=cur->next;
    }
    printf("정보를 다시 입력해주세요.\n");
}



void wordtest(){
    int len, i;
    char str[30];
    FILE *fp;
    fp = fopen("word.txt","r");
    while(fgets(str,sizeof(str),fp)){
        len=strlen(str);
        for(i=0; str[i] != ' ';i++){
            eng[cnt][i]=str[i];
        }
        i++;
        for(int k=0;i<len;i++){
            kor[cnt][k++]=str[i];
        }
        if(kor[cnt][strlen(kor[cnt])-1]=='\n'|| kor[cnt][strlen(kor[cnt])-1]==10){
            kor[cnt][strlen(kor[cnt])-1]=0;
        }
        cnt++;
    }
}

void buble(){
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt-i; j++) {
            int compare = strcmp(eng[j], eng[j + 1]);
            if (compare >= 0) {
                char ch[50],chkor[50];
                strcpy(ch, eng[j]);
                strcpy(eng[j], eng[j + 1]);
                strcpy(eng[j + 1], ch);
                strcpy(chkor, kor[j]);
                strcpy(kor[j], kor[j + 1]);
                strcpy(kor[j + 1], chkor);
            }
        }
    }
}

void delete(NODE *head){
    NODE *cur = malloc(sizeof(NODE));
    NODE *temp = malloc(sizeof(NODE));
    cur=head;
    while(cur!=NULL){
        if(strcmp(cur->next->id,login_id)==0){
            temp=cur->next;
            cur->next=cur->next->next;
            free(temp);
            return;
        }
        cur=cur->next;
    }
}

void save(NODE *head){
    char arr[40];
    NODE *cur = malloc(sizeof(NODE));
    FILE *fp;
    fp = fopen("member.txt","w");
    cur=head->next;
    while(cur != NULL){
        strcpy(arr,cur->id);
        strcat(arr," ");
        strcat(arr,cur->pw);
        strcat(arr," ");
        strcat(arr,cur->name);
        strcat(arr,"\n");
        fputs(arr,fp);
        cur=cur->next;
    }

}

int main(){
    int num=0;
    wordtest();
    buble();
    char id[20],pw[20],name[20],o,a;
    NODE *head = malloc(sizeof(NODE));
    head->next=NULL;

    while(num!=6){
        printf("==============================\n");
        if(login){
            int len=strlen(login_id);
            for(int i=0;i<30-len;i++){
                printf("=");
            }
            printf("%s\n",login_id);
        }
        else{
            printf("==============================\n");
        }
        printf("===          메뉴          ===\n      1. 회원가입\n      2. 로그인\n      3. 로그아웃\n      4. 영어 단어 맞추기\n      5. 회원 탈퇴\n      6. 프로그램종료\n==============================\n입력 : ");
        scanf("%d",&num);

        if(num==1){
            printf("아이디 : ");
            scanf("%s",id);
            search_id(head,id);
            if(idcheck==0){
                printf("비밀번호 : ");
                scanf("%s",pw);
                printf("이름 : ");
                scanf("%s",name);
                push(head,id,pw,name);
                printf("성공하였습니다.\n");
            }
        }

        if(num==2){
            printf("아이디 : ");
            scanf("%s",id);
            printf("비밀번호 : ");
            scanf("%s",pw);
            search(head,id,pw);
        }

        if(num==3){
            if(login==0){
                printf("로그인 상태가 아닙니다.\n");
            }
            else{
                printf("정말로 로그아웃 하시겠습니까? [Y/N] : ");
                while(1){
                    scanf("%s",&o);
                    if(o=='Y'||o=='N'){
                        break;
                    }
                }
                if(o=='Y'){
                    if(login){
                        login=0;
                    }
                }
            }
        }

        if(num==4){
            char word[30];
            int score=0;
            printf(">>>영어 단어 맞추기 프로그램<<<\n");
            for(int i=1;i<cnt;i++){
                if (i==5){
                    continue;
                }
                printf("%s ---> ",eng[i]);
                scanf("%s",word);
                if(strcmp(word,".quit")==0)
                    break;
                if(strcmp(word,kor[i])==0){
                    printf("correct!\n");
                    score++;
                }
                else{
                    printf("incorrect!\n");
                }
            }
            printf("당신의 점수는 %d점 입니다.\n종료합니다.\n",score);
        }

        if(num==5){
            if(login==0){
                printf("로그인 상태가 아닙니다.\n");
            }
            else{
                printf("정말 탈퇴하시겠습니까? [Y/N] : ");
                while(1){
                    scanf("%s",&a);
                    if(a=='Y' || a=='N'){
                        break;
                    }
                }
                if(a=='Y'){
                    delete(head);
                    login=0;
                    printf("탈퇴가 완료되었습니다.\n");
                }
            }
        }

    }
    if (num==6){
        save(head);
        system("clear");
        printf("프로그램을 종료합니다.\n");
    }
    return 0;
}