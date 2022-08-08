#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void AddNode();
void DeleteUSER();
void RemoveSearchData(char[]);
void POSSIBLE(char[]);
void plus(char[]);
void PPLUS();

typedef struct USER
{
	char ID[20];
        char PASSWORD[20];
	char NAME[20];
}USER;

typedef struct NODE
{
	USER user;
	struct NODE* pNext;
}Node;

Node* pHead=NULL;
Node* pTail=NULL;

void ReadFile(void)
{
FILE *USER_INFO=fopen("user.txt","r+");
USER user;
char tmpID[20]={0};
char tmpNAME[20]={0};
char tmpPASSWORD[20]={0};
int IDLENGTH;
int PASSWORDLENGTH;
int NAMELENGTH;

while(! feof(USER_INFO))
{
	fscanf(USER_INFO,"%s",tmpID);
	IDLENGTH=strlen(tmpID);
	strcpy(user.ID,tmpID);

	fscanf(USER_INFO,"%s",tmpPASSWORD);
	PASSWORDLENGTH=strlen(tmpPASSWORD);
	strcpy(user.PASSWORD,tmpPASSWORD);
	
	fscanf(USER_INFO,"%s",tmpNAME);
	NAMELENGTH=strlen(tmpNAME);
	strcpy(user.NAME,tmpNAME);

	AddNode(user);
	memset(tmpID,0,sizeof(tmpID));
}
fclose(USER_INFO);
}

void AddNode(USER _USER)
{
	Node* NewNode=(Node*)malloc(sizeof(Node));
	NewNode->user=_USER;
	NewNode->pNext=NULL;

	if(pHead==NULL) pHead = NewNode;
	else            pTail->pNext = NewNode;
	
	pTail = NewNode;
}

void DeleteAllData(void)
{
	Node* pCur=pHead;
	Node* pDel=NULL;

	if(pHead==NULL)
		return;
	while(pCur != NULL)
	{
		pDel=pCur;
		pCur=pCur->pNext;
		DeleteUSER(&(pDel->user));
		free(pDel);
	}
	pHead=pTail=NULL;
}

void DeleteUSER(USER* _pUSER)
{
	int w;
	if(_pUSER->ID != NULL)
		free(_pUSER->ID);
	if(_pUSER->PASSWORD != NULL)
		free(_pUSER->PASSWORD);
        if(_pUSER->NAME != NULL)
		free(_pUSER->NAME);
}

void(RemoveSearchData(char presentID[]))
{
Node* Remove=NULL;
Node* pCur=pHead;
Node* pBefore=pHead;

if(pHead==NULL)
return;


if(strcmp(pHead->user.ID,presentID)==0)
{
Remove =pHead;
pHead = pHead->pNext;
}

else
{
	while(pCur!=NULL)
	{
		if((strcmp(presentID,pCur->user.ID))==0)
		{
			Remove =pCur;
			pBefore->pNext=pCur->pNext;
			break;
		}
		pBefore=pCur;
		pCur=pCur->pNext;
	}
}


if(Remove != NULL)
{
 DeleteUSER(&(Remove->user));
 free(Remove);
}
}


void POSSIBLE(char kkkword[] )
{
	Node* pCur =pHead;
	int i;
	while(pCur !=NULL)
	{
		if(strcmp(pCur->user.ID,kkkword)==0)
		{
			printf("이미 존재하는 아이디입니다.\n");
			return;
		}
               plus(kkkword);
		
}
}

void plus(char kkkkword[])
{
	Node*pCur =pHead;

	Node* NewNode =(Node*)malloc(sizeof(Node));
	NewNode->pNext =NULL;

	PPLUS(&NewNode->user);

	while(pCur !=NULL)
	{
		if(strcmp(pCur->user.ID,kkkkword)==0)
		{
			NewNode->pNext = pCur->pNext;
			pCur->pNext=NewNode;
			break;
		}
		pCur=pCur->pNext;
	}
}

void PPLUS(USER*_pAct)
{
	char buf[256]={0};
	char buf2[256]={0};
	char buf3[256]={0};
	int i;

	printf("아이디 재입력=>");
	scanf("%s",buf);
	strcpy(_pAct->ID,buf);

	printf("비밀번호 입력=>");
	scanf("%s",buf3);
	strcpy(_pAct->PASSWORD,buf3);

	printf("이름 입력=>");
	scanf("%s",buf2);
	strcpy(_pAct->NAME,buf2);
}


int main()
{	ReadFile();
	FILE *USER_INFO=fopen("user.txt","r+");
	FILE *WORD_INFO=fopen("word.txt","r+");
	int menu=0;
	char tmp[20];
	int login=0;
	char nowID[20];
	char false_id[20];
	fclose(USER_INFO);
	while(menu!=6)
	{
		printf("1:회원가입\n");
		printf("2:로그인\n");
		printf("3:로그아웃\n");
		printf("4:단어게임\n");
		printf("5.회원탈퇴\n");
		printf("6.프로그램종료\n");
		printf("입력:");
		if(login==1)
		printf("%s\n",nowID);
		scanf("%d",&menu);
 ReadFile();
		switch(menu){
		case 1:{
		       printf("아이디:");
		       scanf("%s",false_id);
		       POSSIBLE(false_id);
			break;}
		case 2:
			break;
		case 3:
			{if(login==0)
			 printf("로그인 상태가 아닙니다!\n");
			 else
			 login=0;
			break;}
		case 4:
			{char WORD_GAME[104][2][100];
			 for(int i=0;i<104;i++)
		        fscanf(WORD_INFO,"%s %s",WORD_GAME[i][0],WORD_GAME[i][1]);
		        for(int a=1;a<=103;a++){
				for(int b=0;b<104-a;b++){
					if((strcmp(WORD_GAME[b][0],WORD_GAME[b+1][0]))>=0)		{
				strcpy(tmp,WORD_GAME[b+1][0]);
				strcpy(WORD_GAME[b+1][0],WORD_GAME[b][0]);
				strcpy(WORD_GAME[b][0],tmp);
				strcpy(tmp,WORD_GAME[b+1][1]);
				strcpy(WORD_GAME[b+1][1],WORD_GAME[b][1]);
				strcpy(WORD_GAME[b][1],tmp);
			}}}

			char answer[100];
			char quit[10]=".quit";
			int score=0;
			for(int j=0;j<104;j++)
			{printf("%12s--->\n",WORD_GAME[j][0]);
		         scanf("%s",answer);
				if((strcmp(answer,quit))==0)
				break;
			 	
 				if((strcmp(WORD_GAME[j][1],answer))==0)
       				{
				printf("correct!\n");
				score++;}
				
				else
				printf("incorrect!\n");
			}
			printf("당신의 점수는 %d점입니다.\n",score);
			printf("종료합니다.\n");
					
				break;}
			case 5:{
				       if(login==0)
					  printf("로그인 상태가 아닙니다.\n");
                                       else
					  RemoveSearchData(nowID);
				login=0;
				break;}
			case 6:
				printf("스플럭 화이팅!\n");
				break;
			}
	}
	fclose(WORD_INFO);
	
	DeleteAllData();
	return 0;
}
