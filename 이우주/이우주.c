#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Len 20

int login = 0;
char login_ID[Len];     //로그인 성공한 ID 를 전역변수로 저장 : 프로그램 전체 내에서 사용하기 위해.
//초기화면
void screen_nologin(void)
{   printf("================================\n");
    printf("===========2022 SPLUG===========\n");
    printf("================================\n");
    printf("=            메 뉴             =\n");
    printf("      1.  회원가입\n");
    printf("      2.  로그인\n");
    printf("      3.  로그아웃\n");
    printf("      4.  영어 단어 맞추기\n");
    printf("      5.  회원 탈퇴\n");
    printf("      6.  프로그램 종료\n");
    printf("================================\n");
    printf("입력 : ");
}
void screen_login(void)
{   printf("================================\n");
    printf("===========2022 SPLUG===========\n");
    printf("================================%s\n", login_ID);
    printf("=            메 뉴             =\n");
    printf("      1.  회원가입\n");
    printf("      2.  로그인\n");
    printf("      3.  로그아웃\n");
    printf("      4.  영어 단어 맞추기\n");
    printf("      5.  회원 탈퇴\n");
    printf("      6.  프로그램 종료\n");
    printf("================================\n");
    printf("입력 : ");
}
    //파일포인터 (회원파일 : M_fp 단어파일 : W_fp)
    //파일을 'r'모드로 열어서 그 위치를 M_fp, W_fp가 기억
    // rt는 파일을 읽고 쓸 수 있고, 존재하지 않는 경우 새로운 파일을 생성합니다.
    //존재하는 경우 데이터 추가 입력 시 원래 파일에 덮어씌워집니다.
//*******************************************************************************************
//회원관리
struct Member
{
    char MemberId[Len];
    char MemberPwd[Len];
    char MemberName[Len];
    struct Member *next;
};

void Signup()   //회원가입하기
{
    FILE *M_fp;
    M_fp = fopen("member.txt", "a+");
    struct Member *head = malloc(sizeof(struct Member));
    struct Member *curr = head;
    struct Member *link;

    while( !feof(M_fp) )   
    {
        link = malloc(sizeof(struct Member));
        curr->next = link;
        // fscanf(M_fp, "%s %s %s", link->MemberId, link->MemberPwd, link->MemberName);
        if(fscanf(M_fp, "%s", link->MemberId) == EOF)
            break;
        if(fscanf(M_fp, "%s", link->MemberPwd) == EOF)
            break;
        if(fscanf(M_fp, "%s", link->MemberName) == EOF)
            break;
        curr = curr->next;
    }

    char Id[Len];
    char Pwd[Len];
    char Name[Len];
    printf("아이디 : ");
    scanf("%s", Id);
    
    curr = head->next;
    while( 1 )
        {
            if( strcmp(curr->MemberId, Id) == 0 )
            {
                printf("중복된 아이디입니다.\n");
                return;
            }
            if(curr->next == NULL)
                break;
            curr = curr->next;
        }
    printf("비밀번호 : ");
    scanf("%s", Pwd);
    printf("이름 : ");
    scanf("%s", Name); 

    link = malloc(sizeof(struct Member));
    curr->next = link;
    curr = curr->next;

    strcpy(curr->MemberId, Id);
    strcpy(curr->MemberPwd, Pwd);
    strcpy(curr->MemberName, Name);
    //printf("%s\n", curr->MemberId);
    fprintf(M_fp, "%s %s %s\n", curr->MemberId, curr->MemberPwd, curr->MemberName);
    fclose(M_fp);       //저장하는 느낌!
}
//********************************
void Login()    //로그인하기
{
    FILE *M_fp = fopen("member.txt", "r");
    struct Member *head = malloc(sizeof(struct Member));
    struct Member *curr = head;
    struct Member *link;

    while( !feof(M_fp) )    
    {
        link = malloc(sizeof(struct Member));
        curr->next = link;
        if(fscanf(M_fp, "%s", link->MemberId) == EOF)
            break;
        if(fscanf(M_fp, "%s", link->MemberPwd) == EOF)
            break;
        if(fscanf(M_fp, "%s", link->MemberName) == EOF)
            break;
        curr = curr->next;
    }   

    char Id[Len];
    char Pwd[Len];
    char Name[Len];
    printf("아이디 : ");
    scanf("%s", Id);
    printf("비밀번호 : ");
    scanf("%s", Pwd);

    curr = head->next;
    while( curr!=NULL )
    {
        if( strcmp(curr->MemberId, Id)==0 && strcmp(curr->MemberPwd, Pwd)==0 )
        {
            printf("로그인 성공!\n");
            login = 1;
            strcpy(login_ID, curr->MemberId);
            return;
        }
        curr = curr->next;
    }
    printf("정보를 다시 확인해주세요.\n");
    fclose(M_fp);
}
//*****************************
void Logout()   //로그아웃하기
{
    char ans;
    printf("정말로 로그아웃 하시겠습니까? [Y/N] : \n");
    getchar();      //개행문자 삭제
    scanf("%c", &ans);
    if(ans == 'Y')
    {
        printf("\n");
        login = 0;
    }
}
//******************************
void Signout()  //회원탈퇴하기
{
    FILE *M_fp = fopen("member.txt", "r");
    struct Member *head = malloc(sizeof(struct Member));
    struct Member *curr = head;
    struct Member *link;

    while( !feof(M_fp) )    
    {
        link = malloc(sizeof(struct Member));
        curr->next = link;
        fscanf(M_fp, "%s %s %s", link->MemberId, link->MemberPwd, link->MemberName);
        curr = curr->next;
    }
    fclose(M_fp);

    M_fp = fopen("member.txt", "w");
    curr = head;
    while( 1 )
        {
            if( strcmp(curr->next->MemberId, login_ID) == 0 )   //지우는 노드 : curr->next
            {   
                struct Member *Removenode = curr->next;
                curr->next = curr->next->next;      //지우는노드 앞의 next와 지우는 노드 뒤를 연결
                free(Removenode);                         
                login = 0;

                curr = head->next;
                while( curr != NULL)
                {
                    fprintf(M_fp, "%s %s %s\n", curr->MemberId, curr->MemberPwd, curr->MemberName);
                    curr = curr->next;
                }
                fclose(M_fp);
                return;
            }
            curr = curr->next;
        }
}
//*************************************************************************************
//  <영단어 시작>
struct Word
{
    char English[Len];
    char Meaning[Len];
    struct Word *next;
};

void Quiz()
{
    FILE *W_fp = fopen("word.txt", "r");
    struct Word *head = malloc(sizeof(struct Word));
    struct Word *curr = head;
    struct Word *link;

    while( !feof(W_fp) )    //파일의 끝을 만날때까지 루프 (feof는 파일 끝이 아닐 때 0 반환)
    {
        link = malloc(sizeof(struct Word));
        curr->next = link;
        fscanf(W_fp, "%s %s", link->English, link->Meaning);
        curr = curr->next;
    }
    fclose(W_fp);

    curr = head->next;
    struct Word *cmp = malloc(sizeof(struct Word));    //정렬을 위한 비교 구조체 선언
    cmp = curr->next;

    //만들어진 Word 연결리스트를 알파벳 순서로 정렬하기
    char temp[Len];

    while( curr->next != NULL )
    {
        if(cmp->next == NULL)
        {
            curr = curr->next;
            cmp = curr->next;
            continue;
        }
        if(strcmp(curr->English, cmp->English) > 0)
        {
            strcpy(temp, curr->English);
            strcpy(curr->English, cmp->English);
            strcpy(cmp->English, temp);
            strcpy(temp, curr->Meaning);
            strcpy(curr->Meaning, cmp->Meaning);
            strcpy(cmp->Meaning, temp);
        }
        cmp = cmp->next;
    }

    curr = head->next;

    //영어 단어 맞추기 

    int score = 0;
    char answ[Len];
    printf(">>>영어 단어 맞추기 프로그램<<<\n");
    while( (curr != NULL)) 
    {
        printf("%s --->", curr->English);
        scanf("%s", answ);
        if( strcmp(answ, ".quit") == 0 || curr->next == NULL)
        {
            printf("당신의 점수는 %d 입니다.\n", score);
            printf("종료합니다.\n");
            break;
        }
        if(strcmp(curr->Meaning, answ) == 0)
        {
            printf("correct!\n");
            score++;
        }
        else
            printf("incorrect\n");
        curr = curr->next;
    }
    //왜 이자리에 fclose() 를 하면 오류가 나는 것인가??????

}
//  <영단어 끝>
//*************************************************************************
//main 함수
int main(void)
{
    int flag = 1;
    int input;
    char id[Len], pwd[Len], name[Len];

    while(flag)
    {
        if(login == 0)
        {
            screen_nologin();   //초기화면 출력 함수

            scanf("%d", &input);    
            
            switch(input)
            {
                case 1:
                    Signup();
                    break;
                case 2:
                    Login();
                    break;
                case 3:
                    printf("로그인 상태가 아닙니다.\n");
                    break;
                case 4:
                    printf("로그인 상태가 아닙니다.\n");
                    break;
                case 5:
                    printf("로그인 상태가 아닙니다.\n");
                    break;
                case 6:
                    printf("2022 스플럭 화이팅!\n");
                    flag = 0;
                    break;
            }
        }
        else    //login == 1 인 상태
        {
            screen_login();

            scanf("%d", &input);

            switch(input)
            {
                case 1:
                    Signup();
                    break;
                case 2:
                    printf("로그인 상태입니다.\n");
                    break;
                case 3:
                    Logout();
                    break;
                case 4:
                    Quiz();
                    break;
                case 5:
                    Signout();
                    break;
                case 6:
                    printf("2022 스플럭 화이팅!\n");
                    flag = 0;
                    break;
            }
        }
    }
}