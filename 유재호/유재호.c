#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list{
	char nname[10];
	char iid[10];
	char ppass[10];
	struct list* next;
};

struct list* head;

void createLIST()
{
	struct list* newList = (list*)malloc(sizeof(list));
	list* temp;
	char name[10];
	char id[10];
	char pass[10]; 

	printf("이름 : ");
	scanf("%s",name);
	fflush(stdin);
	printf("아이디 : ");
	scanf("%s: ",id);
	fflush(stdin);
	printf("비밀번호: ");
	scanf("%s: ",pass);

	strcpy(newList->nname,name);
	strcpy(newList->iid,id);
	strcpy(newList->ppass,pass);
	newList->next =NULL;
	temp = head;

	while(temp->next != NULL)
	{
		temp = temp->next;
	}

	if(head->next == NULL){
		head->next = newList;
	}else{
		temp->next = newList;
	}
}

void printLIST()

{
	list* p = head->next;
	for(;p;p=p->next){
		printf("%s %s %s\n",p->nname,p->iid,p->ppass);
	}
}

void Exit() {  
	FILE * save = fopen("List.txt", "wt");
	if (head != NULL) {
		while (head->next != NULL) {
			list *al = head;
			fprintf(save, "%s %s %s \n", al->nname, al->iid, al->ppass);
			head = head->next;
		}
		fprintf(save, "%s %s %s ", head->nname, head->iid, head->ppass);
		free(head);
	}
}

int main()
{
	int flag=0;
	head =  (list *)malloc(sizeof(list));
	head->next = NULL;

	while(1){
		printf("1.회원가입 2.프로그램 종료 \n입력 ::");
		scanf("%d",&flag);
		switch(flag){
			case 1:
				createLIST();
				break;
			case 2:
				printLIST();
				Exit();
				system("pause>null");
				printf("부족하지만 열심히 하겠습니다 스플럭화이팅!!");
				exit(0);
			default :
				printf("잘못 입력하셧습니다.\n");
				break;
		}
	}
}
