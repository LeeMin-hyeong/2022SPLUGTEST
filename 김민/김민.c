#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct User
{
    char Uid[20];
    char Upwd[10];
    char Uname[20];
    struct User *_Next;
}User;

typedef struct uinput
{
    char idin[20];
    char pwdin[10];
}uinput;

void start(char[]);
char Signin(User*);
char Login(User*);
char Logout();
char Collect();
char Getout(User*);
char End();
void sort();

char play = 1;
char mlog[20];

char eng[105][20];
char kor[105][20];


int main(void)
{
    int select; //메뉴 고르는 변수

    // 영어 맞추기 단어 얻기 & 정리
    FILE* engquiz = NULL;
    engquiz = fopen("word.txt","r");
    for(int i=0;i<104;i++)
    {
        fscanf(engquiz,"%s",eng[i]);
        fscanf(engquiz,"%s",kor[i]);
    }
    sort();
    fclose(engquiz);
    // 영어 맞추기 단어 얻기 & 정리 끝

    // 로그인 정보 초기화
    for(int i=0;i<20;i++)
    {
        mlog[i] = '\0';
    }
    // 로그인 정보 초기화 끝

    User* head = malloc(sizeof(User));       //첫 번째 노드 생성
    head->_Next = NULL;             //처음 가리키는거는 비어있음
    
    // 숫자에 따라 분기
    do
    {
        start(mlog);
        scanf(" %d",&select);
        getchar();
        switch (select)
        {
        case 1: // 회원가입
            Signin(head);
            break;
        case 2: // 로그인
            Login(head);
            break;
        case 3:
            Logout();
            break;
        case 4:
            Collect();
            break;
        case 5:
            Getout(head);
            break;
        case 6:
            printf("스플럭 화이팅!\n");
            play = 0;
            break;
        
        default:
            break;
        }
    } while (play == 1);
    free(head);
    
    return 0;
}



void start(char mlog[])
{
    if(mlog[0] == '\0')
    {
        printf("==============================\n");
        printf("==========2022 SPLUG==========\n");
        printf("=            메뉴            =\n");
        printf("==============================\n");
        printf("       1. 회원가입\n       2. 로그인\n       3. 로그아웃\n");
        printf("       4. 영어 단어 맞추기\n       5. 회원 탈퇴\n       6. 프로그램 종료\n");
        printf("==============================\n");
        printf("입력: ");
    }
    else
    {
        printf("==============================\n");
        printf("==========2022 SPLUG==========\n");
        printf("=            메뉴            =\n");
        printf("(: 안녕하세요 %s님 :)\n",mlog);
        printf("==============================\n");
        printf("       1. 회원가입\n       2. 로그인\n       3. 로그아웃\n");
        printf("       4. 영어 단어 맞추기\n       5. 회원 탈퇴\n       6. 프로그램 종료\n");
        printf("==============================\n");
        printf("입력: ");
    }
}

void sort() // 오름차순 버블정렬
{
    char temp[20];
    for (int i = 0; i < 103; i++)
    {
        for (int j = i + 1; j < 104; j++) //정렬이 한번 완료될 때마다 수행 횟수 감소
        {
            if (strcmp(eng[i], eng[j]) > 0)
            {
                strcpy(temp, eng[i]);
                strcpy(eng[i], eng[j]);
                strcpy(eng[j], temp);

                strcpy(temp, kor[i]);
                strcpy(kor[i], kor[j]);
                strcpy(kor[j], temp);
            }
        }
    }
}

char Signin(User *ptr) //회원가입
{
    char compare[20];
    User* prev;
    prev = ptr;
    while (ptr->_Next != NULL)
    {
        ptr = ptr->_Next;
    }

    ptr->_Next = malloc(sizeof(User)); //새로운 노드 생성
    ptr = ptr->_Next;

    printf("아이디: ");
    scanf(" %19s",ptr->Uid);
    strcpy(compare,ptr->Uid);
    while(prev->_Next != NULL)
    {
        prev = prev->_Next;
        if(!(strcmp(compare,prev->Uid)) && prev!=ptr)
        {
            printf("중복된 아이디 입니다.\n\n");
            return 0;
        }
    }


    printf("비밀번호: ");
    scanf(" %4s",ptr->Upwd);
    printf("이름: ");
    scanf(" %19s",ptr->Uname);

    FILE* fp = NULL;
    fp = fopen("practice.txt","a");

    fputs("이름: ",fp);
    fputs(ptr->Uname,fp);
    fputs("\n",fp);
    fputs("아이디: ",fp);
    fputs(ptr->Uid,fp);
    fputs("\n",fp);
    fputs("비밀번호: ",fp);
    fputs(ptr->Upwd,fp);
    fputs("\n\n",fp);

    fclose(fp);
    ptr->_Next = NULL;
    printf("회원가입에 성공하였습니다.\n\n");
    return 0;
}

char Login(User *ptr)
{
    uinput logtry;
    printf("아이디: ");
    scanf(" %19s",logtry.idin);
    printf("비밀번호: ");
    scanf(" %9s",logtry.pwdin);


    if(ptr->_Next == NULL)
    {
        printf("\n잘못된 입력정보입니다.\n\n");
        return 0;
    }
    else
    while(ptr->_Next != NULL)
    {
        ptr = ptr->_Next;
        if(!(strcmp(logtry.idin,ptr->Uid)))
        {
            if(!(strcmp(logtry.pwdin,ptr->Upwd)))
            {
                printf("로그인에 성공하였습니다.\n\n");
                strcpy(mlog,ptr->Uname); 
                return 0;
            }
        }
    }
    printf("잘못된 입력정보입니다.\n\n");
    return 0;
}

char Logout()
{
    char answer;
    if(mlog[0] != '\0')
    {
        printf("정말로 로그아웃 하시겠습니까? (y/n): ");
        scanf(" %c",&answer);
        if(answer == 'y')
        {
            printf("로그아웃 되셨습니다.\n\n");
            for(int i=0;i<20;i++)
            {
                mlog[i] = '\0';
            }
            return 0;
        }
        else if(answer == 'n')
        {
            printf("\n");
            return 0;
        }
        printf("잘못된 입력입니다.\n\n");
        return 0;
    }
    else
    {
        printf("로그인 상태가 아닙니다.\n\n");
        return 0;
    }
    return 0;
}

char Collect()
{
    char corr = 0; // 영어 맞추기용
    char kanswer[20];
    printf(">>> 영어 단어 맞추기 프로그램 <<<\n");
    for(int i=0;i<104;i++)
    {
        for(int i=0;i<10;i++)
            kanswer[i] = '\0';
        printf("%s >>> ",eng[i]);
        scanf(" %s",kanswer);

        if(!(strcmp(kanswer,".quit")))
        {
            printf("당신의 점수는 %d점 입니다.\n\n",corr);
            for(int i=0;i<10;i++)
                kanswer[i] = '\0';
            return 0;
        }

        if(!(strcmp(kor[i],kanswer)))
        {
            printf("correct!\n");
            corr+=1;
        }
        else
        {
            printf("incorrect!\n");
            continue;
        }
    }
    return 0;
}

char Getout(User *ptr)
{
    if(mlog[0] == '\0')
    {
        printf("로그인 상태가 아닙니다.\n\n");
        return 0;
    }
    User* prev;
    
    while(ptr->_Next != NULL)
    {
        prev = ptr;
        ptr = ptr->_Next;

        if(strcmp(mlog,ptr->Uname))
        {
            prev->_Next = ptr->_Next;
            free(ptr);
            break;
        }
    }
    printf("텍스트 파일에서 사라지는건 구현하지 못했습니다 ㅠㅠ\n\n");
    return 0;
}