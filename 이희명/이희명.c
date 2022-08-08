#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<malloc.h>
#include<locale.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct online{
    int login;
    char logID[100];
}online;
online mem;

char english[105][2][100];

typedef struct member{
    struct member *next;
    char ID[100];
    char password[100];
    char name[100];
}member;

void add(member *target,char *ID,char *password,char *name);
void remove_mem(member *target,char *ID);
int compare_ID(char *ID);
int compare_mem(char *ID,char *password);
void save_membertxt(member *target);
void load_membertxt(member *target);
void member_join(member *target);
void member_out(member *target);
void eng_test();
void eng_txt();


void add(member *target,char *ID,char *password,char *name){
    member *new = malloc(sizeof(member));
    new->next=target->next;
    strcpy(new->name,name);
    strcpy(new->ID,ID);
    strcpy(new->password,password); 

    target->next = new;  
} //연결리스트에 회원정보 추가

void remove_mem(member *target,char *ID){
    member *t =malloc(sizeof(member));
    member *remove=malloc(sizeof(member));
    t = target;
    if(strcmp(target->ID,ID)==0){
        remove = target;
        target = target->next;
        free(remove);
    }else{
        while(t->next !=NULL){
            if (strcmp(t->next->ID,ID)==0){
                remove = t->next;
                t->next = t->next->next;
                free(remove);
                break; 
            }
            t=t->next;
        }
    }
} //연결리스트에 회원정보 삭제

int compare_ID(char *ID){
    char tmpid[100],tmppass[100],tmpname[100];
    FILE *txt = fopen("membership.txt","r");
    while (!feof(txt)){
        fscanf(txt,"%s %s %s",tmpid,tmppass,tmpname);
        if(strcmp(tmpid,ID)==0) return 1;
    }
    fclose(txt);
    return 0;
}//아이디 중복확인 <회원가입에 활용>

int compare_mem(char *ID,char *password){
    char tmpid[100],tmppass[100],tmpname[100];
    FILE *txt = fopen("membership.txt","r");
    while (!feof(txt)){
        fscanf(txt,"%s %s %s",tmpid,tmppass,tmpname);
        if(strcmp(tmpid,ID)==0&&strcmp(tmppass,password)==0) return 1;
    }
    fclose(txt);
    return 0;
}//아이디 - 비밀번호 일치 확인 <로그인에 활용>

void save_membertxt(member *target){
    member *move=malloc(sizeof(member));
    move = target->next;
    FILE *txt = fopen("membership.txt","w");
    while (move !=NULL) {
        fprintf(txt,"%s %s %s",move->ID,move->password,move->name);
        fputc('\n', txt);
        move = move->next;
    }
    fclose(txt);
    return;
}//연결리스트 내용들 텍스트에 저장

void load_membertxt(member *target){
    char tmpid[100],tmppass[100],tmpname[100];
    FILE *txt = fopen("membership.txt","r");
    while (!feof(txt)){
        fscanf(txt,"%s %s %s",tmpid,tmppass,tmpname);
        add(target,tmpid,tmppass,tmpname);
    }
    fclose(txt);
    return;
} //회원정보텍스트 연결리스트에 불러오기

void member_join(member *target){
    char tmpid[100], tmppass[100],tmpname[100];
    printf("아이디 : ");
    scanf("%s",tmpid);
    if(compare_ID(tmpid)==1) {
        printf("중복된 아이디입니다.\n");
        return ;
    }else {
        printf("비밀번호 : ");
        scanf("%s",tmppass);
        printf("이름 : ");
        scanf("%s",tmpname);
        add(target,tmpid,tmppass,tmpname);
        printf("성공하였습니다. \n");
        save_membertxt(target);
    }
    return;
}//회원가입
void member_out(member *target){
    char judge;
    if(mem.login==1){
        printf("정말 탈퇴하시겠습니까? [Y/N] ");
        scanf("%c",&judge);
        if(judge=='\n') scanf("%c",&judge);
        if(judge=='Y'||judge=='y') {
            remove_mem(target,mem.logID);
            mem.login=0;
            strcpy(mem.logID,"");
            save_membertxt(target);
            printf("탈퇴가 완료되었습니다.\n");
        }

    }
    else{
        printf("안됩니다.\n");
    }
}//회원탈퇴

void login(member *target){
    char SID[100],Spass[100];
    printf("아이디 : ");
    scanf("%s",SID);
    printf("비밀번호 : ");
    scanf("%s",Spass);
    if(compare_mem(SID,Spass)==1){
        strcpy(mem.logID,SID);
        mem.login=1;
    }
    else{
        printf("옳지않은 계정입니다.\n");
    }
    return;

}//로그인

void eng_txt(){
    char en[100],ko[100];
    int ct=0;
    FILE *eng = fopen("word.txt","r");
    while (!feof(eng)){
        fscanf(eng,"%s %s",en,ko);
        strcpy(english[ct][0],en);
        strcpy(english[ct][1],ko);
        ct++;
    }
    fclose(eng);
    for(int i=0;i<104;i++){
        for(int j=0;j<103;j++){
            char temp [100] ={0},temp1[100]={0};
            if(strcmp(english[j+1][0], english[j][0])<0){ 
                strcpy(temp, english[j][0]);
                strcpy(temp1, english[j][1]);
                strcpy(english[j][0],english[j+1][0]);
                strcpy(english[j][1],english[j+1][1]);
                strcpy(english[j+1][0],temp);
                strcpy(english[j+1][1],temp1);
            }
        }
    }
    return;
}//영단어 텍스트 배열에 불러오기 및 정렬

void eng_test(){
    int i=0,score=0;
    printf(">>>영어 단어 맞추기 프로그램<<<\n");
    while(1){
        char ans[100]={0,};
        printf("%s ---> ",english[i][0]);
        scanf("%s",ans);
        
        if(strcmp(ans,english[i][1])==0) {
            printf("correct! \n");
            score++;
        }

        else if(strcmp(ans,".quit")==0){
            printf("당신의 점수는 %d점 입니다.\n",score);
            printf("종료합니다\n");
            break;
        }

        else printf("incorrect! \n");
        i++;
    }
    return;

}//영단어 맞추기


int main(void){
    setlocale(LC_ALL, "korean");
    member *head = malloc(sizeof(member));
    head->next = NULL;
    FILE *txt = fopen("membership.txt","a");
    fclose(txt);
    load_membertxt(head);
    eng_txt();
    while(1){
        int a =0;
        if(mem.login==1) printf("%s\n",mem.logID);
        else printf("\n");
        printf("       === 메뉴 ===      \n");
        printf("    1. 회원 가입\n");
        printf("    2. 로그인\n");
        printf("    3. 로그아웃\n");
        printf("    4. 영어 단어 맞추기\n");
        printf("    5. 회원 탈퇴\n");
        printf("    6. 프로그램 종료\n");
        printf("입력 : ");
        scanf("%d",&a);
        switch(a){

            case 1:{
                if(mem.login==0) member_join(head);
                else printf("로그아웃후 회원가입해주시길바랍니다.\n");
                break;
            }

            case 2:{
                if(mem.login==0) login(head);
                else printf("로그인 상태입니다.\n");
                break;
            }

            case 3:{
                char jge;
                
                if(mem.login==1){
                    printf("정말 로그아웃하시겠습니까? [Y/N] ");
                    scanf("%c",&jge);
                    if(jge=='\n') scanf("%c",&jge);
                    if(jge=='Y'||jge=='y'){
                    mem.login=0;
                    strcpy(mem.logID,"");
                    printf("로그아웃 완료\n");
                    }
                }
                else{
                    printf("로그인 상태가 아닙니다.\n");
                }
                break;
            }

            case 4:{
                if(mem.login==1) eng_test();
                else printf("로그인 상태가 아닙니다.\n");
                break;
            }

            case 5:{
                member_out(head);
                break;
            }

            case 6:{
                system("clear");
                member *cut=malloc(sizeof(member));
                member *Do=malloc(sizeof(member));
                cut = head->next;
                while(cut !=NULL){
                    Do=cut->next;
                    free(cut);
                    cut=Do;
                }
                free(head);
                printf("\n2022 스플럭 화이팅!!!\n");
                return 0;
            }
            
        }
    }
}
