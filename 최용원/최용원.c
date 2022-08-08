#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
typedef struct Node {
	char ID[MAX];
	char PASS[MAX];
	char NAME[MAX];
	struct Node* next;
}NODE;
NODE* head=NULL;

void Menu();
void JoinMember();
void LogIn();
void LogOut();
void Delete();
int CheckID(char* str);
int CheckPASS(char* str);
void insert(NODE* end, NODE* newnode);
void SaveData();
void Free_all();
char buffer[MAX];
char LoginID[MAX] = { "temp" };
typedef struct _node {
	char Word[MAX];
	char Sense[MAX];
}node;
void Eword();
int main() {

	int N = 0;
	while (N != 6) {
		Menu();
		printf("입력 :");
		scanf("%d", &N);
		while (getchar() != '\n');
		switch (N)
		{
		case 1:
			JoinMember();
			break;
		case 2 :
			LogIn();
			break;
		case 3 :
			LogOut();
			break;
		case 4 :
			Eword();
			break;
		case 5 :
			Delete();
			break;
		case 6 :
			SaveData();
			system("clear"); 
			printf("2022 스플럭 화이팅!\n");
			break;
		}
	}
	Free_all();
}

void Menu()
{
	printf("============================\n");
	printf("==========2022 SPLUG========\n");
	if (strcmp(LoginID, "temp") != 0)
		printf("======================%s\n", LoginID);
	else
		printf("============================\n");
	printf("             메 뉴\n");
	printf("============================\n");
	printf("             1. 회 원 가 입\n");
	printf("             2. 로 그 인\n");
	printf("             3. 로 그 아 웃\n");
	printf("             4. 영 어 단 어 맞 추 기\n");
	printf("             5. 회 원 탈 퇴\n");
	printf("             6. 프 로 그 램 종 료\n");
	printf("============================\n");
}
void Eword()
{
	int score = 0;
	printf(">>>>단어 맞추기 게임 <<<< \n");
	char ttmp1[MAX];
	char ttmp2[MAX];
	FILE* fp = fopen("word.txt", "r");
	node s[105];
	for (int i = 0; i < 105; i++) {
		fscanf(fp, "%s", s[i].Word);
		fscanf(fp, "%s", s[i].Sense);
	}
	for (int j = 1; j < 105; j++) {
		for (int k = 0; k < 104 - j; k++) {
			if (strcmp(s[k].Word, s[k + 1].Word) > 0) {
				strcpy(ttmp1, s[k].Word);
				strcpy(s[k].Word, s[k + 1].Word);
				strcpy(s[k + 1].Word, ttmp1);
				strcpy(ttmp2, s[k].Sense);
				strcpy(s[k].Sense, s[k + 1].Sense);
				strcpy(s[k + 1].Sense, ttmp2);
			}

		}
	}
	char end[10] = { ".quit" };
	char Ans[MAX];
	for (int i = 0; i < 105; i++) {
		printf("%s => ", s[i].Word);
		scanf("%s", Ans);
		if (strcmp(s[i].Sense, Ans) == 0) {
			printf("correct!\n");
			score++;
		}
		else
			printf("incorrect!\n");
		if (strcmp(end, Ans) == 0) {
			printf("당신의 점수는 %d점 입니다.\n", score);
			printf("종료합니다.\n");
			return;
		}
	}
	fclose(fp);
}
void JoinMember()
{

	NODE* cur = NULL;
	NODE* newnode = NULL;
	if (head == NULL) {
		newnode = (NODE*)malloc(sizeof(NODE));
		newnode->next = NULL;
		head = newnode;
		printf("아이디 : ");
		scanf("%s", buffer);
		strcpy(newnode->ID, buffer);
		while (getchar() != '\n');
		printf("비밀번호 : ");
		scanf("%s", buffer);
		strcpy(newnode->PASS, buffer);
		while (getchar() != '\n');
		printf("이름 : ");
		scanf("%s", buffer);
		strcpy(newnode->NAME, buffer);
		while (getchar() != '\n');
		printf("성공하였습니다.\n");
		return;
	}
	else {
		newnode = (NODE*)malloc(sizeof(NODE));
		newnode->next = NULL; //새로생성된 노드를 가리킴
		for (cur = head; cur->next != NULL; cur = cur->next);
		insert(cur, newnode);
	
	}
}
void insert(NODE* end, NODE* newnode)
{
	end->next = newnode;
	printf("아이디 : ");
	scanf("%s", buffer);
	int stop = CheckID(buffer);
	if (stop == 1) {
		printf("중복된 아이디입니다.\n");
		return;
	}
	strcpy(newnode->ID, buffer);
	while (getchar() != '\n');
	printf("비밀번호 : ");
	scanf("%s", buffer);
	strcpy(newnode->PASS, buffer);
	while (getchar() != '\n');
	printf("이름 : ");
	scanf("%s", buffer);
	strcpy(newnode->NAME, buffer);
	while (getchar() != '\n');
	printf("성공하였습니다.\n");

}

void LogIn()
{
	char t_ID[MAX];
	char t_PASS[MAX];
	if (strcmp(LoginID, "temp") != 0) {
		printf("로그인 상태입니다.\n");
		return;
	}

	printf("아이디 : ");
	scanf("%s", t_ID);
	while (getchar() != '\n');
	printf("비밀번호 : ");
	scanf("%s", t_PASS);

	int stop = CheckID(t_ID);
	if (stop == 1)//아이디가 존재하면
	{

		int pas = CheckPASS(t_PASS);
		if (pas != 1) {
			printf("정보를 다시 확인 해 주세요.\n");
			return;
		}
		else
			strcpy(LoginID, t_ID);
		
	}
	else
		printf("정보를 다시 확인 해 주세요.\n");
}
void LogOut()
{
	if (strcmp(LoginID, "temp") != 0) {

		printf("정말로 로그아웃 하시겠습니까? [Y/N] : ");
		char ch;
		scanf("%c", &ch);
		if (ch == 'N')
			return;
		else if (ch == 'Y')
			strcpy(LoginID, "temp"); // 초기조건
	}
	else
	{
		printf("로그인 상태가 아닙니다.\n");
		return;
	}
	
}

int CheckID(char* str)
{
	NODE* cur = NULL;
	for (cur = head; cur != NULL; cur = cur->next) {
		if (strcmp(cur->ID, str) == 0)
			return 1;
	}
}
int CheckPASS(char* str)
{
	NODE* cur = NULL;
	for (cur = head; cur != NULL; cur = cur->next) {
		if (strcmp(cur->PASS, str) == 0)
			return 1;
	}
}
void Delete()
{
	if(strcmp(LoginID,"temp")==0)
		printf("로그인 상태가 아닙니다.\n");
	else
	{
	printf("정말 탈퇴하시겠습니까? [Y/N] : ");
	char ch;
	scanf("%c", &ch);
	if (ch == 'Y')
	{
		if (head->next == NULL)
		{
			free(head);
			head = NULL;
			strcpy(LoginID, "temp"); //노드가 하나인경우
			return;
		}
		else
		{
		
			NODE* cur; //노드가 하나이상
			for (cur = head; cur != NULL; cur = cur->next) {
				if (strcmp(cur->ID, LoginID) == 0) {
					if (cur->next == NULL) { //만약 마지막노드였다면 
						for (cur = head; cur->next->next != NULL; cur = cur->next);
						free(cur->next);
						cur->next = NULL;
						strcpy(LoginID, "temp");
						return;
					}
				}
				else if (strcmp(cur->next->ID, LoginID) == 0)
				{
						NODE* del;
						del = cur->next;
						cur->next = cur->next->next;
						free(del);
						strcpy(LoginID, "temp");
						return;
				}
					
			}
		}
	}
	}

}
void Free_all()
{
	NODE* cur;
	NODE* del = head;
	if (head == NULL)
		return;
	else if (head->next = NULL)
	{
		free(head);
	
	}
	
	else {
		for (cur = head->next; cur != NULL; cur = cur->next)
		{
			free(del);
			del = cur;
		}
		free(del);
	}
	head = NULL;
}

void SaveData()
{
	FILE* fp = fopen("member.txt", "w+");
	NODE* cur = NULL;
	for (cur = head; cur != NULL; cur = cur->next) {
		fprintf(fp, "%s %s %s\n", cur->ID, cur->PASS, cur->NAME);
	}
	fclose(fp);
}
