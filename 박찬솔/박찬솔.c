#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define STRING_SIZE 100
#define FILENAME_USER "user.txt"
#define FILENAME_WORD "word.txt"


// Linked List 구현부
typedef struct Node Node;

struct Node {
    Node *next;
    char field1[STRING_SIZE];
    char field2[STRING_SIZE];
};

Node *user_db, *word_db;

Node *init_node() {
    Node *new = malloc(sizeof(Node));
    memset(new, 0, sizeof(Node));
    return new;
}

Node *add_node(Node *root) {
    Node *new = init_node();
    while (root->next) root = root->next;
    root->next = new;
    return new;
}

Node *search_node(Node *root, char *field1, char *field2) {
    root = root->next;
    while (root) {
        if ((!field1 || !strcmp(root->field1, field1)) && (!field2 || !strcmp(root->field2, field2))) return root;
        root = root->next;
    }

    return NULL;
}

void delete_node(Node *root, Node *delete) {
    while (root) {
        if (root->next == delete) {
            root->next = root->next->next;
            free(delete);
            return;
        }
        root = root->next;
    }
}


// I/O 처리
typedef struct pair_string {
    char field1[STRING_SIZE];
    char field2[STRING_SIZE];
} pair_string;

pair_string **read_from_file(char *filename, int *length) {
    FILE *ptr = fopen(filename, "r");
    pair_string **arr = malloc(0);

    if (ptr) {
        char a[STRING_SIZE], b[STRING_SIZE];
        *length = 0;
        while (fscanf(ptr, "%s %s", a, b) == 2) {
            arr = realloc(arr, ++*length * sizeof(pair_string *));
            pair_string *temp = arr[*length - 1] = malloc(sizeof(pair_string));
            strcpy(temp->field1, a);
            strcpy(temp->field2, b);
        }
        fclose(ptr);
    }
    return arr;
}

void write_file_linked_list(char *filename, Node *root) {
    FILE *ptr = fopen(filename, "w");
    root = root->next;
    while (root) {
        fprintf(ptr, "%s %s\n", root->field1, root->field2);
        root = root->next;
    }
    fclose(ptr);
}


// 유저 처리
void init_user_db() {
    int length = 0;
    pair_string **arr = read_from_file(FILENAME_USER, &length);
    for (int i = 0; i < length; i++) {
        Node *tmp = add_node(user_db);
        strcpy(tmp->field1, arr[i]->field1);
        strcpy(tmp->field2, arr[i]->field2);

        free(arr[i]);
    }

    free(arr);
}

void save_user_db() {
    write_file_linked_list(FILENAME_USER, user_db);
}


// 영어 퀴즈 처리
int eng_word_compare(const void **a, const void **b) {
    return strcmp(((pair_string *) *a)->field1, ((pair_string *) *b)->field1);
}

void init_word_db() {
    int length = 0;
    pair_string **arr = read_from_file(FILENAME_WORD, &length);
    qsort(arr, length, sizeof(pair_string *), /*(__compar_fn_t)*/ eng_word_compare);
    for (int i = 0; i < length; i++) {
        Node *tmp = add_node(word_db);
        strcpy(tmp->field1, arr[i]->field1);
        strcpy(tmp->field2, arr[i]->field2);

        free(arr[i]);
    }

    free(arr);
}


// UI 처리
char user[STRING_SIZE];

void repeat_print(int n, char c, _Bool line_break) {
    while (n--) printf("%c", c);
    if (line_break) printf("\n");
}

void print_main_ui() {
    int width = 20;

    repeat_print(width - strlen(user), '=', 0);
    printf("%s", user);
    printf("\n");

    repeat_print(width / 2 - 6, '=', 0);
    repeat_print(4, ' ', 0);
    printf("메뉴");
    repeat_print(4, ' ', 0);
    repeat_print(width / 2 - 6, '=', 1);

    repeat_print(width, '=', 1);

    repeat_print(1, ' ', 0);
    printf("1. 회원가입\n");
    repeat_print(1, ' ', 0);
    printf("2. 로그인\n");
    repeat_print(1, ' ', 0);
    printf("3. 로그아웃\n");
    repeat_print(1, ' ', 0);
    printf("4. 영어 단어 맞추기\n");
    repeat_print(1, ' ', 0);
    printf("5. 회원 탈퇴\n");
    repeat_print(1, ' ', 0);
    printf("6. 프로그램 종료\n");

    repeat_print(width, '=', 1);
    printf("입력 : ");
}

_Bool get_answer_yn(const char *print) {
    printf("%s [Y/N] : ", print);
    int c;
    do {
        c = getchar();
        if ('a' <= c && c <= 'z') c = c - 'a' + 'A';
    } while (c < 'A' || c > 'Z');
    return c == 'Y';
}


// 메뉴 처리
void menu_user_register() {
    char id[STRING_SIZE], pw[STRING_SIZE], name[STRING_SIZE];

    printf("아이디 : ");
    scanf("%s", id);

    printf("비밀번호 : ");
    scanf("%s", pw);

    printf("이름 : ");
    scanf("%s", name);

    if (search_node(user_db, id, NULL)) printf("중복된 아이디 입니다.\n");
    else {
        Node *new = add_node(user_db);
        strcpy(new->field1, id);
        strcpy(new->field2, pw);

        save_user_db();
        printf("성공하였습니다.\n");
    }
}

void menu_user_login() {
    char id[STRING_SIZE], pw[STRING_SIZE];

    printf("아이디 : ");
    scanf("%s", id);

    printf("비밀번호 : ");
    scanf("%s", pw);

    if (search_node(user_db, id, pw)) strcpy(user, id);
    else printf("로그인 실패했습니다.\n");
}

void menu_user_logout() {
    if (!strlen(user)) {
        printf("로그인 상태가 아닙니다.\n");
        return;
    }

    if (get_answer_yn("정말로 로그아웃 하시겠습니까?")) memset(user, 0, sizeof user);
}

void menu_eng_quiz() {
    printf(">>>영어 단어 맞추기 프로그램<<<\n");
    Node *current = word_db->next;
    int score = 0;
    while (current) {
        printf("%s ---> ", current->field1);
        char a[STRING_SIZE];
        scanf("%s", a);
        if (!strcmp(a, ".quit")) break;
        if (strcmp(a, current->field2) != 0) printf("incorrect!\n");
        else {
            printf("correct!\n");
            score++;
        }

        current = current->next;
    }

    printf("당신의 점수는 %d점 입니다.\n종료합니다.\n", score);
}

void menu_user_quit() {
    if (!strlen(user)) {
        printf("로그인 상태가 아닙니다.\n");
        return;
    }

    if (get_answer_yn("정말로 탈퇴하시겠습니까?")) {
        delete_node(user_db, search_node(user_db, user, NULL));
        save_user_db();
        memset(user, 0, sizeof user);

        printf("탈퇴가 완료되었습니다.\n");
    }
}

_Noreturn void menu_exit() {
    printf("종료\n");
    exit(0);
}

int main() {
    user_db = init_node();
    word_db = init_node();

    init_user_db();
    init_word_db();

    while (1) {
        print_main_ui();

        int i;
        scanf("%d", &i);

        if (i == 1) menu_user_register();
        if (i == 2) menu_user_login();
        if (i == 3) menu_user_logout();
        if (i == 4) menu_eng_quiz();
        if (i == 5) menu_user_quit();
        if (i == 6) menu_exit();
    }
}
