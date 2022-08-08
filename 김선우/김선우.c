#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <fcntl.h>

int logined = 0;
char now[100];

void showMenu();
void record();
int checkRecord(char temp[]);
void login();
void logout();
void quiz();
int checkLogin(char temp[], int n);
void del();
void fileChanege();

int checkLogin(char temp[], int n)
{
	FILE* fp = fopen("info.txt", "r");
	char* ptr;
	char* buff = malloc(sizeof(char) * 256);
	char* buff2;
	int line = 0;

	while (fgets(buff, 256, fp) != NULL)
	{
		buff2 = strtok(buff, "\n");
		ptr = strtok(buff2, " ");
		line++;
		while (ptr != NULL)
		{
			if (strcmp(ptr, temp) == 0 && n == line) {
				fclose(fp);
				return line;
			}
			ptr = strtok(NULL, " ");
		}
	}

	fclose(fp);
	free(buff);
	return 0;
}

int checkRecord(char temp[])
{
	FILE* fp= fopen("info.txt", "r");
	char* ptr;
	char* buff = malloc(sizeof(char) * 256);
	char *buff2;
	int line = 0;

	while (fgets(buff, 256, fp) != NULL) 
	{
		buff2 = strtok(buff, "\n");
		ptr = strtok(buff2, " ");
		line++;
		while (ptr != NULL)
		{
			if (strcmp(ptr, temp) == 0) {
				fclose(fp);
				return line;
			}
			ptr = strtok(NULL, " ");
		}
	}
	
	fclose(fp);
	free(buff);
	return 0;
}

void record()
{
	FILE* fp = fopen("info.txt", "a");
	char* id = malloc(sizeof(char) * 100);
	char* password = malloc(sizeof(char) * 100);
	char* name = malloc(sizeof(char) * 100);

	printf("아이디: ");
	scanf("%s", id);
	if (checkRecord(id)) {
		printf("중복된 아이디\n");
		return;
	}
	fputs(id, fp);
	fputs(" ", fp);

	printf("비밀번호: ");
	scanf("%s", password);
	fputs(password, fp);
	fputs(" ", fp);

	printf("이름: ");
	scanf("%s", name);
	fputs(name, fp);
	fputs("\n", fp);

	free(id);
	free(password);
	free(name);
	fclose(fp);
}

void login()
{
	char *id = malloc(sizeof(char) * 100);
	char *password = malloc(sizeof(char) * 100);
	int len;
	
	printf("아이디: ");
	scanf("%s", id);
	if (checkRecord(id) == 0) {
		printf("틀린 아이디\n");
		return;
	}

	printf("비밀번호: ");
	scanf("%s", password);
	len = checkRecord(id);
	if (len != checkLogin(password, len)) {
		printf("틀린 비밀번호\n");
		return;
	}
	logined = 1;
	strcpy(now, id);
	free(id);
	free(password);
}

void logout()
{
	if (logined) {
		logined = 0;
	}
	else {
		printf("이미 로그아웃 되었습니다\n");
	}
	
}

char *eng[100];
char *kor[100];

typedef struct
{
	char word[100];
	char ans[100];
}element;

typedef struct
{
	element data;
	struct NODE* link;
}NODE;

void push(NODE *head, element d)
{
	if(head->link == NULL) {
		NODE *next = malloc(sizeof(NODE));
		next->data = d;
		next->link = NULL;
		head->link = next;
	}
	else {
		NODE *cur = head;
		while(cur->link != NULL) {
			cur = cur->link;
		}
		NODE *next = malloc(sizeof(NODE));
		next->data = d;
		next->link = NULL;
		cur->link = next;
	}
}

void printList(NODE *head)
{
	int sum = 0;
	char *choi = malloc(sizeof(char) * 100);
	for(NODE *p = head->link; p != NULL; p = p->link) {
		printf("%s -> ",p->data.word);
		scanf("%s",choi);
		if(strcmp(choi, ".quit") == 0) {
			printf("점수: %d\n", sum);
			free(choi);
			return;
		}
		if(strcmp(choi, p->data.ans) == 0){
			printf("correct!\n");
			sum++;
		}
		else {
			printf("incorrect! 정답은: %s\n", p->data.ans);
		}
	}
	printf("점수: %d\n", sum);
	free(choi);
}

void sortList()
{
	char *tempE = malloc(sizeof(char) * 100);
	char *tempK = malloc(sizeof(char) * 100);
	int i, j;
	for(i = 103; i > 0; i--) {
		for(j = 0; j < i; j++) {
			if(strcmp(eng[j], eng[j + 1]) > 0) {
				strcpy(tempE, eng[j]);
				strcpy(tempK, kor[j]);
				strcpy(eng[j], eng[j + 1]);
				strcpy(kor[j], kor[j + 1]);
				strcpy(eng[j + 1], tempE);
				strcpy(kor[j + 1], tempK);
			}
		}
	}
	free(tempE);
	free(tempK);
}

void quiz()
{
	NODE *head = malloc(sizeof(NODE));
	element data;

	FILE *fp = fopen("word.txt", "r");
	char* ptr;
	char* buff = malloc(sizeof(char) * 256);
	char* buff2;
	int i = 0;

	while(fgets(buff, 256, fp) != NULL)
	{
		buff2 = strtok(buff, "\n");
		ptr = strtok(buff2, " ");
		eng[i] = (char*)malloc(strlen(ptr) + 1);
		strcpy(eng[i], ptr);

		ptr = strtok(NULL, " ");
		kor[i] = (char*)malloc(strlen(ptr) + 1);
		strcpy(kor[i], ptr);
		i++;
	}
	sortList();
	for(int i = 0; i < 104; i++) {
		strcpy(data.word, eng[i]);
		strcpy(data.ans, kor[i]);
		push(head, data);
	}
	printList(head);
	//free(*eng[i]);
	//free(*kor[i]);
	free(buff);
	free(head);
	fclose(fp);
}

void delete()
{
	FILE* fp = fopen("info.txt", "r");
	FILE* newf = fopen("new.txt", "w");

	char* buff = malloc(sizeof(char) * 256);
	int cnt = 0;
	
	while (fgets(buff, 256, fp) != NULL) {
		cnt = 0;
		for (int i = 0; i < strlen(now); i++) {
			if (buff[i] == now[i]) {
				cnt++;
			}
		}
		if (cnt == strlen(now)) {
			continue;
		}
		else {
			fputs(buff, newf);
		}
	}

	logined = 0;
	fclose(fp);
	fclose(newf);
	free(buff);

	fileChanege();
}

void fileChanege()
{
	remove("info.txt");
	rename("new.txt", "info.txt");
}

int main()
{
	while (1)
	{
		showMenu();
		int choi;
		scanf("%d", &choi);

		switch (choi)
		{
		case 1:
			record();
			break;
		case 2:
			login();
			break;
		case 3:
			logout();
			break;
		case 4:
			quiz();
			break;
		case 5:
			if (logined) {
				printf("탈퇴 완료\n");
				delete();
			}
			else {
				printf("탈퇴할 수 없습니다\n");
			}
			break;
		case 6:
			printf("종료합니다\n");
			exit(0);
			break;
		}
	}

	return 0;
}

void showMenu()
{
	if (logined) {
		printf(" ==%s==\n", now);
	}
	else {
		printf("==================\n");
	}
	printf("1. 회원가입\n");
	printf("2. 로그인\n");
	printf("3. 로그아웃\n");
	printf("4. 영어단어 맞추기\n");
	printf("5. 회원탈퇴\n");
	printf("6. 종료\n");
}
