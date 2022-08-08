#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

char login_id[20], wordlist[200][2][25];
int size=0;
bool islogin=0;

typedef struct wNODE{
    struct wNODE *next;
    char english[15], korean[15];
}wNODE;
// 영단어 목록에 대한 연결리스트를 만들기 위한 구조체 선언

typedef struct NODE{
    struct NODE *next, *pre;
    char name[20], id[20], pw[20];
}NODE;
// 회원 정보에 대한 연결리스트를 만들기 위한 구조체 선언

void Wpush(wNODE *head, char *c1, char *c2)
{
    wNODE *new = malloc(sizeof(wNODE));
    new->next=head->next;
    head->next=new;
    strcpy(new->english,c1);
    strcpy(new->korean,c2);
}
// 단어목록 연결리스트에 데이터를 추가하는 함수

void delete_enter(char *split)
{
    int end = strlen(split);
    for(int i=end-1; ; i--)
    {
        if(split[i]==13 || split[i]==10)
            split[i]=0;
        else
            break;
    }
}
// 개행 문자를 없애주는 함수

void push(NODE *head, char *c1, char *c2, char *c3)
{
    NODE *new = malloc(sizeof(NODE));
    head->next->pre=new;
    new->next=head->next;
    head->next=new;
    new->pre=head;
    strcpy(new->name,c1);
    strcpy(new->id,c2);
    strcpy(new->pw,c3);
}
// 회원정보 연결리스트에 데이터를 추가하는 함수

void pop(NODE *cur)
{
    NODE *del = malloc(sizeof(NODE));
    del=cur;
    cur->pre->next=del->next;
    del->next->pre=cur->pre;
    free(del);
}
// 회원정보 연결리스트에서 데이터를 삭제하는 함수

void printing(int k, char c)
{
    for(int i=0; i<k; i++)
        printf("%c", c);
}
// 인터페이스 함수를 만드는데 쓰임

void interface()
{
    int len;
    printf("\n");
    printing(30, '=');
    printf("\n");

    printing(10, '=');
    printf("2022 SPLUG");
    printing(10, '=');
    printf("\n");

    if(islogin)
    {
        len=strlen(login_id);
        printing(30-len, '=');
        printf("%s", login_id);
    }
    else
        printing(30, '=');

    printf("\n=");
    printing(28, ' ');
    printf("=\n");
    printing(30, '=');
    printf("\n");

    printf("%7d. 회원가입\n", 1);
    printf("%7d. 로그인\n", 2);
    printf("%7d. 로그아웃\n", 3);
    printf("%7d. 영어 단어 맞추기\n", 4);
    printf("%7d. 회원 탈퇴\n", 5);
    printf("%7d. 프로그램 종료\n", 6);

    printing(30, '=');
    printf("\n");
}
// 인터페이스를 출력해주는 함수

void memlist_loading(NODE *head)
{
    char c[70];
    char names[20], ids[20], pws[20];
    int e=0;
    FILE *fp;
    fp = fopen("member.txt", "r");
    if(fp==NULL)
        return;
    while(fgets(c,sizeof(c),fp))
    {
        char *split = strtok(c," ");
        strcpy(names, split);

        split = strtok(NULL," ");
        strcpy(ids, split);

        split = strtok(NULL," ");
        delete_enter(split);
        strcpy(pws, split);
        push(head, names, ids, pws);
    }
    fclose(fp);
}
// 프로그램을 시작할 때, 외부 txt파일에서 회원정보를 불러와 연결리스트에 저장하는 함수

void bubble()
{
    char temp1[25], temp2[25];
    for(int i=size-1; i>0; i--)
        for(int k=0; k<i; k++)
            if(strcmp(wordlist[k][0],wordlist[k+1][0])<0)
            {
                strcpy(temp1,wordlist[k][0]);
                strcpy(temp2,wordlist[k][1]);
                strcpy(wordlist[k][0],wordlist[k+1][0]);
                strcpy(wordlist[k][1],wordlist[k+1][1]);
                strcpy(wordlist[k+1][0],temp1);
                strcpy(wordlist[k+1][1],temp2);
            }
}
// 문자열을 오름차순으로 정렬시키는 함수

void wordlist_loading(wNODE *whead)
{
    char c[50];
    FILE *fp;
    fp = fopen("word.txt", "r");
    while(fgets(c,sizeof(c),fp))
    {
        char *split = strtok(c," ");
        strcpy(wordlist[size][0], split);
        split = strtok(NULL, " ");
        delete_enter(split);
        strcpy(wordlist[size++][1], split);
    }
    bubble();
    for(int i=0; i<size; i++)
        Wpush(whead,wordlist[i][0],wordlist[i][1]);
    fclose(fp);
}
// 외부 txt파일에서 단어목록을 읽어 단어목록연결리스트에 저장하는 함수

void wordtest(wNODE *whead)
{
    wNODE *cur = malloc(sizeof(wNODE));
    cur=whead->next;
    char ans[25];
    int O=0,X=0,score;
    while(cur!=NULL)
    {
        printf("%s ---> ", cur->english);
        scanf("%s", ans);
        if(ans[strlen(ans)-1]==' ')
            ans[strlen(ans)-1]=0;
        if(strcmp(ans, ".quit")==0)
            break;
        if(strcmp(ans, cur->korean)==0)
        {
            printf("correct!\n");
            O++;
        }
        else
        {
            printf("incorrect!\n");
            X++;
        }
        cur=cur->next;
    }
    score = (O*100) / (O+X);
    printf("당신의 점수는 %d점 입니다.\n", score);
    printf("종료합니다.\n");
}
// 단어시험에 대한 함수

void signup(NODE *head)
{
    NODE *cur = malloc(sizeof(NODE));
    char names[20], ids[20], pws[20];
    printf("아이디 : ");
    scanf("%s", ids);
    cur=head->next;
    while(cur!=NULL)
    {
        if(strcmp(cur->id,ids)==0)
        {
            printf("중복된 아이디 입니다.\n");
            return;
        }
        cur=cur->next;
    }
    printf("비밀번호 : ");
    scanf("%s", pws);
    printf("이름 : ");
    scanf("%s", names);
    push(head, names, ids, pws);
    printf("성공하였습니다.\n");
}
// 회원가입에 대한 함수

void login(NODE *head)
{
    NODE *cur = malloc(sizeof(NODE));
    char ids[20], pws[20];
    char correct_pw[20];
    int valid=0;
    printf("아이디 : ");
    scanf("%s", ids);
    printf("비밀번호 : ");
    scanf("%s", pws);
    cur=head->next;
    while(cur!=NULL)
    {
        if(strcmp(cur->id,ids)==0)
        {
            valid=1;
            strcpy(correct_pw, cur->pw);
            break;
        }
        cur=cur->next;
    }
    if(valid==0)
    {
        printf("존재하지 않는 아이디 입니다.\n");
        return;
    }
    if(strcmp(correct_pw, pws)==0)
    {
        islogin=1;
        strcpy(login_id, ids);
        printf("로그인 되었습니다.\n");
    }
    else
        printf("비밀번호가 일치하지 않습니다.\n");
}
// 로그인에 대한 함수

void logout()
{
    char c;
    if(!islogin)
    {
        printf("로그인 상태가 아닙니다.\n");
        return;
    }

    printf("정말로 로그아웃 하시겠습니까? [Y/N] : ");
    while(1)
    {
        scanf("%c", &c);
        if(c == 'Y' || c == 'N')
            break;
    }
    if(c=='N')
    {
        printf("로그아웃 되지 않았습니다.\n");
        return;
    }

    memset(login_id,0,sizeof(login_id));
    islogin=0;
    printf("로그아웃 되었습니다.\n");
}
// 로그아웃에 대한 함수

void withdraw(NODE *head)
{
    char c;
    if(!islogin)
    {
        printf("로그인 상태가 아닙니다.\n");
        return;
    }
    printf("정말로 탈퇴하시겠습니까? [Y/N] : ");
    while(1)
    {
        scanf("%c", &c);
        if(c == 'Y' || c == 'N')
            break;
    }
    if(c=='N')
    {
        printf("탈퇴되지 않았습니다.\n");
        return;
    }

    NODE *cur = malloc(sizeof(NODE));
    cur=head->next;
    while(cur!=NULL)
    {
        if(strcmp(cur->id,login_id)==0)
        {
            pop(cur);
            printf("탈퇴가 완료되었습니다.\n");
            memset(login_id,0,sizeof(login_id));
            islogin=0;
            return;
        }
        cur=cur->next;
    }
}
// 회원탈퇴에 대한 함수

void list_backup(NODE *head, NODE *tail)
{
    char s[100];
    int namelen, idlen, pwlen;
    FILE *fp;
    fp = fopen("member.txt", "w");
    NODE *cur = malloc(sizeof(NODE));
    cur=head->next;
    while(cur != tail)
    {
        fputs(cur->name, fp);
        fputc(' ', fp);
        fputs(cur->id, fp);
        fputc(' ', fp);
        fputs(cur->pw, fp);
        fputc('\n', fp);
        cur=cur->next;
    }
    fclose(fp);
}
// 프로그램 종료 시, 회원정보 연결리스트에 있는 정보들을 외부 txt 파일에 저장하는 함수

int main()
{
    wNODE *whead = malloc(sizeof(wNODE));
    whead->next=NULL;
    wordlist_loading(whead);

    NODE *head = malloc(sizeof(NODE));
    NODE *tail = malloc(sizeof(NODE));
    head->next=tail;
    head->pre=NULL;
    tail->pre=head;
    tail->next=NULL;
    memlist_loading(head);
    
    int index;
    bool end=0;
    while(1)
    {
        interface();
        printf("입력 : ");
        scanf("%d", &index);
        switch (index)
        {
            case 1:
                signup(head);
                break;
            case 2:
                login(head);
                break;
            case 3:
                logout();
                break;
            case 4:
                wordtest(whead);
                break;
            case 5:
                withdraw(head);
                break;
            case 6:
                end=1;
                break;
        }
        if(end)
        {
            list_backup(head, tail);
            system("clear");
            printf("프로그램이 종료되었습니다!\n");
            break;
        }
    }
    return 0;
}