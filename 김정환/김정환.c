#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
typedef struct Game {
	char Word[15];
	char Meaning[15];
}Game;
typedef struct Member {
	char MemberId[20];
	char MemberPw[20];
	char MemberName[20];
	struct Member* next;
}Member;
Member* First = NULL;
Member* makenode(void);
void AddMember(Member**, char*, char*, char*);
void DeleteMember(char*);
int txtload(void);
void txtsave(void);
int printmenu(char*, int);
int IdCheck(char*);//성공 0 실패-1
int login(char*, char*);
int logout(int);
void PlayGame(void);
void myFlush(void);
void PrintMember(void);
int main(void)
{
	Member* tmp = First;
	char MemberId1[20] = { 0 };
	char MemberPw1[20] = { 0 };
	char MemberName1[20] = { 0 };
	char YN;
	int menu = 0, loginC = 0, IdCheck1 = 1, score = 0;
	txtload();
	while (1)
	{
		IdCheck1 = 1;
		menu = printmenu(MemberId1, loginC);
		switch (menu)
		{
		case 1:
			while (IdCheck1)
			{
				printf("아이디 : ");
				scanf("%s", MemberId1);
				myFlush();
				IdCheck1 = IdCheck(MemberId1);
				if (IdCheck1 == -1)
				{
					printf("중복된 아이디 입니다.\n");
				}
			}
			printf("비밀번호 : ");
			scanf("%s", MemberPw1);
			myFlush();
			printf("이름 : ");
			scanf("%s", MemberName1);
			myFlush();
			AddMember(&First, MemberId1, MemberPw1, MemberName1);
			printf("회원가입에 성공하였습니다.\n");
			break;
		case 2:
			if (loginC == -1)
			{
				printf("이미 로그인 되어있습니다.\n");
				break;
			}
			myFlush();
			printf("아이디 : ");
			scanf("%s", MemberId1);
			myFlush();
			printf("비밀번호 : ");
			scanf("%s", MemberPw1);
			myFlush();
			loginC = login(MemberId1, MemberPw1);
			if (loginC == -1)
			{
				printf("성공적으로 로그인 되었습니다.\n");
				break;
			}
			else
			{
				printf("잘못 입력하셨습니다.\n");
				break;
			}
		case 3:
			if (loginC != -1)
			{
				printf("로그인 상태가 아닙니다.\n");
				break;
			}
			loginC = logout(loginC);
			printf("로그아웃 되었습니다.\n");
			break;
		case 4:
			printf("1초 뒤 게임을 시작합니다.\n");
			PlayGame();
			sleep(1);
			break;
		case 5:
			if (loginC == -1)
			{
				while (1) {
					printf("정말 탈퇴하시겠습니까? [Y/N] : ");
					myFlush();
					scanf("%c", &YN);
					if (YN == 'Y'||YN=='y')
					{
						printf("탈퇴가 완료되었습니다.\n");
						DeleteMember(MemberId1);
						loginC = 0;
						break;
					}
					else if (YN == 'N' || YN == 'n')
					{
						printf("초기화면으로 돌아갑니다.\n");
						break;
					}
					else
					{
						printf("다시 입력하세요.\n");
					}
					myFlush();
				}
				break;
			}
			else
			{
				printf("로그인 상태가 아닙니다.\n");
				break;
			}
		case 6:
			system("clear");
			printf("프로그램이 종료되었습니다.\n");
			printf("소프트웨어학부 1학년 김정환입니다.\n");
			txtsave();
			return 0;
		case 7:
			printf("등록된 회원을 출력합니다.\n");
			PrintMember();
			sleep(2);
			break;
		default:
			printf("다시 입력하세요\n");
			myFlush();
			break;
		}
		printf("잠시 기다려주세요.\n");
		sleep(1);
		system("clear");
	}
	free(First);
	return 0;
}
Member* makenode(void)
{
	Member* tmp = (Member*)malloc(sizeof(Member));
	tmp->next = NULL;
	return tmp;
}
void AddMember(Member** head, char MemberId[], char MemberPw[], char MemberName[])
{
	if (!*head)
	{
		*head = makenode();
		strcpy((*head)->MemberId, MemberId);
		strcpy((*head)->MemberPw, MemberPw);
		strcpy((*head)->MemberName, MemberName);
		return;
	}
	AddMember(&(*head)->next, MemberId, MemberPw, MemberName);
}
void DeleteMember(char MemberId[])
{
	Member* list = First;
	if (First == NULL)
		return;
	else if (strcmp(First->MemberId, MemberId) == 0) { 
		First = First->next;
		return;
	}
	else { 
		while (list->next != NULL) 
		{
			if (strcmp(list->next->MemberId, MemberId) == 0) {
				list->next = list->next->next;
				return;
			}
			list = list->next;
		}
	}
}
int txtload(void)
{
	int countA = 0;
	FILE* load = fopen("Member.txt", "rt");
	if (load != NULL)
	{
		Member* MidNode = NULL;
		int loadfp, count = 0;
		while (feof(load) == 0)
		{
			MidNode = (Member*)malloc(sizeof(Member));
			MidNode->next = NULL;
			fscanf(load, "%s %s %s\n", MidNode->MemberId, MidNode->MemberPw, MidNode->MemberName);
			countA++;
			if (First == NULL)
			{
				First = MidNode;
			}
			else
			{
				Member* temp = First;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = MidNode;
			}
		}
	}
	return countA;
}
void txtsave(void)
{
	myFlush();
	FILE* save = fopen("Member.txt", "wt");
	if (First != NULL)
	{
		while (First->next != NULL)
		{
			Member* al = First;
			fprintf(save, "%s %s %s\n", al->MemberId, al->MemberPw, al->MemberName);
			First = First->next;
		}
		fprintf(save, "%s %s %s\n", First->MemberId, First->MemberPw, First->MemberName);
	}
}
int printmenu(char MemberId[], int loginC)
{
	int menu = 0;
	printf("======================\n");
	printf("=========Menu=========\n");
	if (loginC == -1)
	{
		printf("===============%s\n", MemberId);
	}
	else
	{
		printf("======================\n");
		loginC = 0;
	}
	printf("    1. 회원가입\n");
	printf("    2. 로그인 \n");
	printf("    3. 로그아웃\n");
	printf("    4. 영어 단어 맞추기\n");
	printf("    5. 회원 탈퇴\n");
	printf("    6. 프로그램 종료\n");
	printf("    7. 회원 출력\n");
	printf("======================\n");
	printf("입력 : ");
	scanf("%d", &menu);
	return menu;
}
int IdCheck(char* MemberId)
{
	Member* temp;
	temp = First;
	if (temp == NULL)
	{
		return 0;
	}
	Member* curr = First->next;
	while (curr != NULL)
	{
		if (strcmp(curr->MemberId, MemberId) == 0)
			return -1;
		curr = curr->next;
	}
	return 0;
}
int login(char* MemberId1, char* MemberPw1)
{
	Member* temp;
	temp = First;
	if (temp == NULL)
	{
		return 0;
	}
	if (strcmp(temp->MemberId, MemberId1) == 0 && strcmp(temp->MemberPw, MemberPw1) == 0)
	{
		return -1;
	}
	Member* curr = First->next;
	while (curr != NULL)
	{
		if (strcmp(curr->MemberId, MemberId1) == 0 && strcmp(curr->MemberPw, MemberPw1) == 0)
			return -1;
		curr = curr->next;
	}
	return 0;
}
int logout(int loginC)
{
	int logout = 0;
	loginC = logout;
	return loginC;
}
void PlayGame(void)
{
	FILE* save = fopen("word.txt", "rt");
	Game ary[104];
	Game temp;
	time_t start, end;
	double result;
	int correct = 0, incorrect = 0;
	sleep(1);
	system("clear");
	for (int i = 0; i < 104; i++)
	{
		fscanf(save, "%s %s\n", ary[i].Word, ary[i].Meaning);
	}
	for (int i = 0; i < 103; i++) {
		for (int j = i + 1; j < 104; j++) {
			if (strcmp(ary[i].Word, ary[j].Word) > 0) {
				strcpy(temp.Word, ary[i].Word);
				strcpy(temp.Meaning, ary[i].Meaning);
				strcpy(ary[i].Word, ary[j].Word);
				strcpy(ary[i].Meaning, ary[j].Meaning);
				strcpy(ary[j].Word, temp.Word);
				strcpy(ary[j].Meaning, temp.Meaning);
			}
		}
	}
	start = time(NULL);
	printf(">>>> 영어 단어 맞추기 프로그램 <<<<\n");
	for (int k = 0; k < 104; k++)
	{
		printf("%d. %s ----> ", k + 1, ary[k].Word);
		scanf("%s", temp.Meaning);
		if (strcmp(temp.Meaning, ".quit") == 0)
		{
			end = time(NULL);
			result = (double)(end - start);
			printf("%.2lf초 걸렸습니다.\n", result);
			printf("당신의 점수는 %d점 입니다.\n", correct);
			printf("종료합니다.\n");
			return;
		}
		if (strcmp(temp.Meaning, ary[k].Meaning) == 0)
		{
			printf("correct!\n");
			correct++;
		}
		else
		{
			printf("incorrect!\n");
			incorrect++;
		}

	}
	end = time(NULL);
	result = (double)(end - start);
	printf("%.2lf초 걸렸습니다.\n", result);
	printf("당신의 점수는 %d점 입니다.\n", correct);
	printf("종료합니다.\n");
	return;
}
void myFlush(void)
{
	while (getchar() != '\n')
	{
		;
	}
}
void PrintMember(void)
{
	Member* tmp = First;

	while(tmp!= NULL) {
		printf("ID: %s Name: %s\n", tmp->MemberId,tmp->MemberName);
		tmp= tmp->next;
	}
}
