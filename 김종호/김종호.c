#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//START STRUCTS

struct USER {
    char id[50];
    char pw[50];
    char name[50];
};
struct USER_NODE {
    struct USER_NODE *prev;
    struct USER_NODE *next;
    struct USER user;
};
struct USER_LIST {
	struct USER_NODE *head;
	struct USER_NODE *tail;
};

struct WORD {
    char eng[50];
    char kor[50];
};
struct WORD_NODE {
    struct WORD_NODE *prev;
    struct WORD_NODE *next;
    struct WORD word;
};
struct WORD_LIST {
	struct WORD_NODE *head;
	struct WORD_NODE *tail;
};

//END STRUCTS



//START GLOBAL VARIABLES

struct USER_LIST *user_list;
struct WORD_LIST *word_list;


struct USER *current_user = NULL;


//END GLOBAL VARIABLES



//START FUNCTIONS

void main_screen();
void login_screen();
void logout_screen();
void register_screen();
void unregister_screen();
void word_challenge_screen();


void word_new(char eng[ ], char kor[ ]) {
    struct WORD_NODE *new_word_node = malloc(sizeof(struct WORD_NODE));
    new_word_node->next = NULL;
    new_word_node->prev = NULL;
    strcpy(new_word_node->word.eng, eng);
    strcpy(new_word_node->word.kor, kor);
    if(word_list->head == NULL && word_list->tail == NULL){
        word_list->head = word_list->tail = new_word_node;
    }
    else{
        new_word_node->prev = word_list->tail;
        word_list->tail->next = new_word_node;
        word_list->tail = new_word_node;
    }
}

// void user_print(){

//     struct USER_NODE *now_user_node = user_list->head;
// 	while(now_user_node != NULL) {
//         printf("%s %s %s\n",now_user_node->user.id, now_user_node->user.pw, now_user_node->user.name);
		
//         now_user_node = now_user_node->next;
// 	}
    
// }

void user_register(char id[ ], char pw[ ], char name[ ]) {
    struct USER_NODE *new_user_node = malloc(sizeof(struct USER_NODE));
    new_user_node->next = NULL;
    new_user_node->prev = NULL;
    strcpy(new_user_node->user.id, id);
    strcpy(new_user_node->user.pw, pw);
    strcpy(new_user_node->user.name, name);
    if(user_list->head == NULL && user_list->tail == NULL){
        user_list->head = user_list->tail = new_user_node;
    }
    else{
        new_user_node->prev = user_list->tail;
        user_list->tail->next = new_user_node;
        user_list->tail = new_user_node;
    }
}

int user_login(char id[ ], char pw[ ]) {
    int valid = 0;
    struct USER_NODE *now_user_node = user_list->head;
	while(now_user_node != NULL) {
		if(strcmp(now_user_node->user.id, id) == 0 && strcmp(now_user_node->user.pw, pw) == 0){
            current_user = &now_user_node->user;
            valid = 1;
            break;
        }
		now_user_node = now_user_node->next;
	}


    return valid;
}

void user_logout(){
    current_user = NULL;
}

int user_login_check(){
    if(current_user != NULL && strcmp(current_user->id, "") != 0)
        return 1;
    else
        return 0;
}

int user_register_check(char id[ ]){
    int exist = 0;
    struct USER_NODE *now_user_node = user_list->head;
	while(now_user_node != NULL) {
		if(strcmp(now_user_node->user.id, id) == 0){
            exist = 1;
            break;
        }
        now_user_node = now_user_node->next;
	}

    return exist;
}

void user_unregister(){
    struct USER_NODE *now_user_node = user_list->head;
	while(now_user_node != NULL) {
		if(strcmp(now_user_node->user.id, current_user->id) == 0){
            struct USER_NODE *prev_user_node = now_user_node->prev;
            struct USER_NODE *next_user_node = now_user_node->next;
            if(prev_user_node != NULL)
                prev_user_node->next = now_user_node->next;
            else if(prev_user_node == NULL)
                user_list->head = now_user_node->next;

            if(next_user_node != NULL)
                next_user_node->prev = now_user_node->prev;
            else if(next_user_node == NULL)
                user_list->tail = now_user_node->prev;

            free(now_user_node);
            break;
        }
        now_user_node = now_user_node->next;
	}

}

void user_write_to_file(){
    FILE *file_users;

    file_users = fopen("users.txt","wb");

    struct USER_NODE *now_user_node = user_list->head;
	while(now_user_node != NULL) {
        printf("%s %s %s\n",now_user_node->user.id, now_user_node->user.pw, now_user_node->user.name);
		fputs(now_user_node->user.id, file_users);
        fputs(" ", file_users);
        fputs(now_user_node->user.pw, file_users);
        fputs(" ", file_users);
        fputs(now_user_node->user.name, file_users);
        fputs("\n", file_users);
        now_user_node = now_user_node->next;
	}
    
    fclose(file_users);
}


//END FUNCTIONS


//START PROGRAM INIT

int main() {
    user_list = malloc(sizeof(struct USER_LIST));
    user_list->head = NULL;
    user_list->tail = NULL;

    word_list = malloc(sizeof(struct WORD_LIST));
    user_list->head = NULL;
    user_list->tail = NULL;

    FILE *file_users, *file_words;

    file_users = fopen("users.txt","rw");
    file_words = fopen("words.txt","r");

    struct WORD words_arr[500];
    int words_idx = 0;
    while(feof(file_words) == 0){
        char eng[50];
        char kor[50];
        if(fscanf(file_words, "%s", eng) == EOF)
            break;
        if(fscanf(file_words, "%s", kor) == EOF)
            break;  

        strcpy(words_arr[words_idx].eng, eng);
        strcpy(words_arr[words_idx].kor, kor);
        words_idx++;
        // word_new(eng, kor);
    }

    for(int i=0; i<words_idx; i++){
        for(int j=i; j<words_idx; j++){
            if(strcmp(words_arr[i].eng, words_arr[j].eng) > 0){
                struct WORD tmp;
                strcpy(tmp.eng, words_arr[i].eng);
                strcpy(tmp.kor, words_arr[i].kor);
                strcpy(words_arr[i].eng, words_arr[j].eng);
                strcpy(words_arr[i].kor, words_arr[j].kor);
                strcpy(words_arr[j].eng, tmp.eng);
                strcpy(words_arr[j].kor, tmp.kor);
            }
        }
    }

    for(int i=0; i<words_idx; i++){
        word_new(words_arr[i].eng, words_arr[i].kor);
    }

    
    while(feof(file_users) == 0){
        char id[50];
        char pw[50];
        char name[50];
        if(fscanf(file_users, "%s", id) == EOF)
            break;
        if(fscanf(file_users, "%s", pw) == EOF)
            break;
        if(fscanf(file_users, "%s", name) == EOF)
            break;

        user_register(id, pw, name);
    }

    fclose(file_users);
    fclose(file_words);

    main_screen("");

    free(user_list);
    free(word_list);

    return 0;
}

//END PROGRAM INIT



//START SCREENS

void main_screen(char message[ ]){
    system("clear");
    // user_print();

    printf("=====================================\n");
    printf("============= 2022 SPLUG ============\n");
    if(user_login_check()){
        for(int i=0; i<37 - strlen(current_user->id); i++)
            printf("=");
        printf("%s",current_user->id);
        printf("\n");
    }
    else
        printf("=====================================\n");
    printf("=                메뉴               =\n");
    printf("=====================================\n");
    printf("         1. 회원가입\n");
    printf("         2. 로그인\n");
    printf("         3. 로그아웃\n");
    printf("         4. 영어 단어 맞추기\n");
    printf("         5. 회원탈퇴\n");
    printf("         6. 프로그램 종료\n");
    printf("=====================================\n");
    if(strlen(message) != 0){
        printf("[안내] ");
        printf("%s",message);
        printf("\n");
    }

    int select;
    while(1){
        printf("입력 : ");
        scanf("%d",&select);
        if(select >= 1 && select <= 6)
            break;
        else
            printf("잘못된 입력입니다.\n");
    }

    if(select == 1){
        register_screen();
    }
    else if(select == 2){
        login_screen();
    }
    else if(select == 3){
        logout_screen();
    }
    else if(select == 4){
        word_challenge_screen();
    }
    else if(select == 5){
        unregister_screen();
    }
    else if(select == 6){
        system("clear");
        printf("2022 스플럭 화이팅 !\n");
    }
}

void login_screen(){
        if(user_login_check()){
            main_screen("이미 로그인되어 있습니다.");
            return;
        }
        char id[50];
        char pw[50];
        printf("아이디 : ");
        scanf("%s",id);
        printf("비밀번호 : ");
        scanf("%s",pw);
        if(user_login(id, pw)){
            main_screen("로그인 되었습니다.");
        }else{
            printf("아이디 또는 비밀번호가 일치하지 않습니다.\n\n");
            login_screen();
        }
}

void logout_screen(){
    if(!user_login_check()){
        main_screen("로그인된 상태에서만 로그아웃하실 수 있습니다.");
    }
    else{
        printf("정말 로그아웃하시겠습니까? [Y/N] : ");
        char yn;
        while(1){
            scanf(" %c",&yn);
            if(yn == 'Y' || yn == 'N' || yn == 'y' || yn == 'n')
                break;
            else
                printf("잘못된 입력입니다.\n");
        }
        if(yn == 'Y' || yn == 'y'){
            user_logout();
            main_screen("로그아웃 되었습니다.");
        }
        else{
            main_screen("로그아웃이 취소되었습니다.");
        }
    }
}

void register_screen(){
    if(user_login_check()){
        main_screen("이미 로그인되어 있습니다.");
    }
    else{
        char id[50];
        char pw[50];
        char name[50];
        while(1){
            printf("아이디 : ");
            scanf("%s",id);

            if(!user_register_check(id))
                break;
            else
                printf("중복된 아이디 입니다.\n");
        }
        printf("비밀번호 : ");
        scanf("%s",pw);
        printf("이름 : ");
        scanf("%s",name);
        user_register(id, pw, name);
        user_write_to_file();
        main_screen("회원가입 되었습니다.");
    }
}

void unregister_screen(){
    if(!user_login_check()){
        main_screen("로그인된 상태에서만 회원탈퇴 하실 수 있습니다.");
    }
    else{
        printf("정말 탈퇴하시겠습니까? [Y/N] : ");
        char yn;
        while(1){
            scanf(" %c",&yn);
            if(yn == 'Y' || yn == 'N' || yn == 'y' || yn == 'n')
                break;
            else
                printf("잘못된 입력입니다.\n");
        }
        if(yn == 'Y' || yn == 'y'){
            user_unregister();
            user_write_to_file();
            user_logout();
            main_screen("회원탈퇴 되었습니다.");
        }
        else{
            main_screen("회원탈퇴가 취소되었습니다.");
        }

    }
}

void word_challenge_screen(){
    system("clear");
    printf(">>>>>> 영어 단어 맞추기 프로그램 <<<<<<\n\n");

    int score = 0;
    struct WORD_NODE *now_word_node = word_list->head;
    while(now_word_node != NULL) {
        printf("%s ---> ",now_word_node->word.eng);
        char ans[50];
        scanf("%s",ans);
        if(strcmp(ans, ".quit") == 0)
            break;
        
        if(strcmp(ans, now_word_node->word.kor) == 0){
            score++;
            printf("Correct !\n");
        }
        else{
            printf("Incorrect !\n");
        }
        
        now_word_node = now_word_node->next;
    }


    for(int i=3; i>=1; i--){
        system("clear");
        printf("당신의 점수는 %d점 입니다.\n",score);
        printf("%d초 뒤 메인 화면으로 이동합니다.\n",i);
        sleep(1);
    }

    main_screen("");
}



//END SCREENS