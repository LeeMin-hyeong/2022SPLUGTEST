#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_LINE_LENGTH 1000
#define WORD_COUNT 104

void opt1(void);
void opt2(void);
void opt3(void);
void opt4(void);
void opt5(void);

typedef struct ListNode {
    char id[MAX];
    char pw[MAX];
    char name[MAX];
    struct ListNode* link;
} listNode;

typedef struct {
    listNode* head;
} linkedList_h;

struct words {
    char en[MAX];
    char ko[MAX];
};

linkedList_h* createLinkedList_h(void) {
    linkedList_h* L;
    L = (linkedList_h*)malloc(sizeof(linkedList_h));
    L -> head = NULL;
    return L;
}

void insertNode(linkedList_h* L, char *id_input, char *pw_input, char *name_input) {
    listNode* newNode;
    listNode* temp;
    newNode = (listNode*)malloc(sizeof(listNode));
    strcpy(newNode -> id, id_input);
    strcpy(newNode -> pw, pw_input);
    strcpy(newNode -> name, name_input);
    newNode -> link = NULL;
    if (L -> head == NULL) {
        L -> head = newNode;
        return;
    }

    temp = L -> head;
    while (temp -> link != NULL) temp = temp -> link;
    temp -> link = newNode;
}

void deleteNode(linkedList_h* L, listNode* p) {
    listNode* pre;
    if (L -> head == NULL) return;
    if (L -> head -> link == NULL) {
        free(L -> head);
        L -> head = NULL;
        return;
    }
    else if (p == NULL) return;
    else {
        pre = L -> head;
        while (pre -> link != p) {
            pre = pre -> link;
        }
        pre -> link = p -> link;
    }
    pre -> link = p -> link;
    free(p);
}

listNode* searchNode(linkedList_h* L, char* id_cmp) {
    listNode *temp;
    temp = L -> head;
    while (temp != NULL) {
        if (strcmp(temp -> id, id_cmp) == 0) return temp;
        else temp = temp -> link;
    }
    return temp;
}

listNode* loginNode(linkedList_h* L, char* id_cmp, char* pw_cmp) {
    listNode *temp;
    temp = L -> head;
    while (temp != NULL) {
        if (strcmp(temp -> id, id_cmp) == 0 && strcmp(temp -> pw, pw_cmp) == 0) return temp;
        else temp = temp -> link;
    }
    return temp;
}

void back2Menu(char* message) {
    getchar(); // 개행삭제
    printf("%s\n\n", message);
    printf("엔터 키를 누르면 메뉴로 돌아갑니다... ");
    getchar();
    system("clear");
}
linkedList_h* L;
_Bool login = 0;
char id[MAX] = "\0";
FILE *fp;

void init(void) {
    int beginIndex = 0, endIndex=0;
    char id_accounts[MAX], pw_accounts[MAX], name_accounts[MAX];
    char *read;
    long numbytes;

    L = createLinkedList_h();

    fp = fopen("accounts.txt", "r");
    if(fp == NULL) {
        fp = fopen("accounts.txt" ,"a");
        fclose(fp);
        return;
    }
     
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);  
 
    read = (char*)calloc(numbytes, sizeof(char));   
    if(read == NULL) return;
 
    fread(read, sizeof(char), numbytes, fp);
    fclose(fp);

    while(read[beginIndex] != '\0') {
        for(int i = 0; i < 3; i++) {
            while(read[endIndex] != ';') endIndex++;
            switch (i)
            {
                case 0:
                    if(read[beginIndex] == '\n') beginIndex++;
                    strncpy(id_accounts, read+beginIndex, endIndex-beginIndex);
                    id_accounts[endIndex-beginIndex] = '\0';
                    beginIndex = ++endIndex;
                    break;
                case 1:
                    strncpy(pw_accounts, read+beginIndex, endIndex-beginIndex);
                    pw_accounts[endIndex-beginIndex] = '\0';
                    beginIndex = ++endIndex;
                    break;
                case 2:
                    strncpy(name_accounts, read+beginIndex, endIndex-beginIndex);
                    name_accounts[endIndex-beginIndex] = '\0';
                    beginIndex = ++endIndex;
                    break;
            }
        }
        insertNode(L, id_accounts, pw_accounts, name_accounts);
    }
}

int main(void) 
{
    _Bool exit = 0;
    int option;
    init();

    system("clear");

    while(!exit)
    {
        // 메뉴 출력
        printf("-------| 2022 SPLUG |-------\n");
        printf("======      메뉴      ======\n");
        printf("============================\n\n");
        if(login) printf("%s 님 환영합니다.\n\n", id);
        printf("      1. 회원가입\n");
        printf("      2. 로그인\n");
        printf("      3. 로그아웃\n");
        printf("      4. 영어 단어 맞추기\n");
        printf("      5. 회원 탈퇴\n");
        printf("      6. 프로그램 종료\n\n");
        printf("=============================\n");
        printf("입력 : ");

        scanf("%d", &option);

        system("clear");
        switch(option)
        {
            case 1:
                opt1();
                break;
            case 2:
                opt2();
                break;
            case 3:
                opt3();
                break;
            case 4:
                opt4();
                break;
            case 5:
                opt5();
                break;
            case 6:
                exit = 1;
                system("clear");
                printf("프로그램을 종료합니다...\n\n");
                break;
        }
    }
    return 0;
}

// 회원가입
void opt1(void)
{
    if(login) {
        back2Menu("***** 이미 로그인된 상태입니다. *****");
    }
    else {
        listNode *p;
        _Bool exit = 0;
        char id_input[MAX];
        char pw_input[MAX];
        char name_input[MAX];

        // 아이디 입력
        do
        {
            printf("아이디   : ");
            scanf("%s", id_input);

            // 아이디 중복 예외 처리
            p = searchNode(L, id_input);
            if(p == NULL) exit = 1;
            else printf("\n***** 중복된 아이디입니다. *****\n\n");
        } while (!exit);

        // 비밀번호 입력
        printf("비밀번호 : ");
        scanf("%s", pw_input);

        // 이름 입력
        printf("이름     : ");
        scanf("%s", name_input);             

        insertNode(L, id_input, pw_input, name_input);  

        fp = fopen("accounts.txt", "a");
        fprintf(fp, "\n%s;%s;%s;", id_input, pw_input, name_input);
        fclose(fp);

        back2Menu("\n***** 회원가입에 성공하였습니다. *****");
    }
    return;
}

// 로그인
void opt2(void)
{
    if(login) {
        back2Menu("***** 이미 로그인된 상태입니다. *****");
    }
    else {
        listNode *p;
        _Bool exit = 0, repeat = 1;
        char input;
        char id_input[MAX];
        char pw_input[MAX];

        do
        {
            printf("아이디   : ");
            scanf("%s", id_input);
            printf("비밀번호 : ");
            scanf("%s", pw_input);

            p = loginNode(L, id_input, pw_input);

            if(p == NULL) {
                printf("\n***** 회원 정보가 올바르지 않습니다. *****\n\n");
                do
                {
                    printf("메뉴로 돌아가시겠습니까? [Y/N] : ");
                    getchar(); // 개행 삭제
                    scanf("%c", &input);

                    if (input == 'Y' || input == 'y') {
                        repeat = 0;
                        exit = 1;
                        back2Menu("\n***** 로그인을 취소하였습니다. *****");
                        return;
                    }
                    else if (input == 'N' || input == 'n') {
                        system("clear");
                        repeat = 0;
                    }
                } while (repeat);
            }
                
            else
                exit = 1;

        } while (!exit);

        login = 1;
        strcpy(id, id_input);

        back2Menu("\n***** 로그인에 성공하였습니다. *****");
    }
    return;
}

// 로그아웃
void opt3(void)
{
    if(!login) {
        back2Menu("***** 로그인 상태가 아닙니다. *****");
    }
    else {
        login = 0;
        strcpy(id, "\0");
        back2Menu("***** 로그아웃에 성공하였습니다. *****");
        return;
    }
}

// 영어 단어 맞추기
void opt4(void)
{
    int i, j;
    int beginIndex = 0, endIndex=0, point=0;
    char en_word[MAX], ko_word[MAX];
    char *read_word;
    char temp_en[MAX];
    char temp_ko[MAX];
    char input[MAX];
    long numbytes;
    struct words word[WORD_COUNT];

    fp = fopen("word.txt", "r");
    if(fp == NULL) return;
     
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);  
 
    read_word = (char*)calloc(numbytes, sizeof(char));   
    if(read_word == NULL) return;
 
    fread(read_word, sizeof(char), numbytes, fp);
    fclose(fp);

    i=0;
    while(read_word[beginIndex] != '\0') {
        while(read_word[endIndex] != ' ') endIndex++; {
            if(read_word[beginIndex] == '\n') beginIndex++;
            strncpy(en_word, read_word+beginIndex, endIndex-beginIndex);
            en_word[endIndex-beginIndex] = '\0';
            beginIndex = ++endIndex;
        }
        while(read_word[endIndex] != '\n') endIndex++; {
            strncpy(ko_word, read_word+beginIndex, endIndex-beginIndex);
            ko_word[endIndex-beginIndex] = '\0';
            beginIndex = ++endIndex;
        }
        strcpy(word[i].en, en_word);
        strcpy(word[i].ko, ko_word); 
        i++;
    }
    for(i=0; i<WORD_COUNT-1; i++) {
        for(j=0; j<WORD_COUNT-1-i; j++) {
            if(strcmp(word[j].en, word[j+1].en) > 0) {
                strcpy(temp_en, word[j].en);
                strcpy(temp_ko, word[j].ko);

                strcpy(word[j].en, word[j+1].en);
                strcpy(word[j].ko, word[j+1].ko);

                strcpy(word[j+1].en, temp_en);
                strcpy(word[j+1].ko, temp_ko);
            }
        }
    }

    system("clear");

    printf(">>> 영어 단어 맞추기 프로그램 <<<\n");
    i = 0;
    while(i<WORD_COUNT) {
        printf("%s ---> ", word[i].en);
        scanf("%s", input);

        if(strcmp(input, ".quit") == 0) {
            break;
        }
        else if(strcmp(input, word[i].ko) == 0) {
            point += 5;
            printf("correct!\n");
        }
        else printf("incorrect!\n");
        i++;
    }
    printf("당신의 점수는 %d점 입니다.\n", point);
    printf("종료합니다.\n");
    back2Menu("");
    return;
}

// 회원 탈퇴
void opt5(void)
{
    listNode *p;
    char input;
    _Bool exit = 0;

    if(!login) {
        back2Menu("***** 로그인 상태가 아닙니다. *****");
    }
    else {
        system("clear");

        do
        {
            printf("정말로 탈퇴하시겠습니까? [Y/N] : ");
            getchar();  // 개행삭제
            scanf("%c", &input);

            if (input == 'Y' || input == 'y') {
                p = searchNode(L, id);
                deleteNode(L, p);

                fp = fopen("accounts.txt", "w");
                p = L -> head;
                while (p != NULL) {
                    fprintf(fp, "\n%s;%s;%s;", p -> id, p -> pw, p -> name);
                    p = p -> link;
                }

                fclose(fp);

                login = 0;
                strcpy(id, "\0");

                back2Menu("\n***** 탈퇴가 완료되었습니다. *****");

                exit = 1;
            }
            else if (input == 'N' || input == 'n') {
                system("clear");
                back2Menu("***** 회원탈퇴를 취소하셨습니다. *****");
                exit = 1;
            }
        } while (!exit);
    }
    return;
}