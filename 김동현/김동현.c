#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login;
char inid[100];
char inpw[100];
char inname[100];
int sel;

typedef struct {
	char adata[100];
	char eng[100];
	char kor[100];
}element;

typedef struct ListNode {
	element data;
	struct Listnode* link;
}ListNode;

ListNode* insertFirst(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	
	p->data = value;		
	p->link = head;			
	head = p;			
	return head;
}

void writefile(ListNode *head)
{
	ListNode *ptr=head;
	FILE *fp=fopen("registerid.txt","w");
	if(ptr==NULL)
		return;
	else
	{
		while(ptr!=NULL)
		{
			fputs(ptr->data.adata,fp);
			if(ptr->link==NULL)
			return;
			else{
			fputs(" ",fp);
			ptr=ptr->link;
			}
		}
	}
	fclose(fp);
	return;
}

void Searchregist(ListNode* head, char idid[100])
{
    ListNode* cur = head; 

    if (cur->data.adata == NULL) 
    {
        printf("비밀번호 : ");
		scanf("%s",inpw);
		printf("이름 : ");
		scanf("%s",inname);
    }
    else
    {
        while (cur->link != NULL) 
        {
            if (strcmp(cur->data.adata,idid)==0)
            {
                printf("중복된 id가 있습니다!\n"); 
                return;
            }
            cur = cur->link;
        }
        if (cur->link == NULL){
			printf("비밀번호 : ");
			scanf("%s",inpw);
			printf("이름 : ");
			scanf("%s",inname);
		}
    }
}

void Searchlogin(ListNode* head, char idid[100])
{
    ListNode* cur = head; 

    if (cur->data.adata == NULL) 
    {
        printf("저장된 데이터가 없습니다 !\n");
    }
    else
    {
        while (cur->link != NULL)
        {
            if (strcmp(cur->data.adata,idid)==0)
            {
				printf("비밀번호 : ");
				scanf("%s",inpw);
				cur = cur->link;
				if(strcmp(cur->data.adata,inpw)==0){
					login=1;
					return;
				}
				else{
					printf("비밀번호가 다릅니다.\n");
					return;
				}
            }
            cur = cur->link;
        }
        if (cur->link == NULL){
			printf("일치하는 아이디가 없습니다.\n");
		}
    }
}
ListNode* delete_pre(ListNode* head, ListNode* pre) {
	ListNode* removed; 
	removed = pre->link; 
	pre->link = removed->link;
	free(removed); 
	return head; 
}

void Searchbye(ListNode* head)
{
    ListNode* cur = head; 

    if (cur->data.adata == NULL) 
    {
        printf("저장된 데이터가 없습니다 !\n");
    }
	else if(strcmp(cur->data.adata,head)==0){
		ListNode *front = head;
        head= head->link;
		free(front);
		return;
	}
    else 
    {
        while (cur->link != NULL)
        {
            if (strcmp(cur->link,inid)==0) 
			{
				
					delete_pre(head,cur);
					return;
				
            }
            cur = cur->link;
        }
    }
} 

void Searchbye2(ListNode* head)
{
    ListNode* cur = head; 

    if (cur->data.adata == NULL) 
    {
        printf("저장된 데이터가 없습니다 !\n");
    }
    else
    {
        while (cur->link != NULL)
        {
            if (strcmp(cur->data.adata,inpw)==0) 
            {
				delete_pre(head,cur);
				return;
            }
            cur = cur->link;
        }
    }
} 

void Searchbye3(ListNode* head)
{
    ListNode* cur = head; 

    if (cur->data.adata == NULL) 
    {
        printf("저장된 데이터가 없습니다 !\n");
    }
    else
    {
        while (cur->link != NULL)
        {
            if (strcmp(cur->link,inpw)==0)
            {
				delete_pre(head,cur);
				return;
            }
            cur = cur->link;
        }
    }
} 

void bubble(ListNode* head) {
	ListNode* p, * q;
	element tmp;

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (strcmp(q->data.eng,p->data.eng)<0)
			{
				tmp = p->data;
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
}

void exam(ListNode* head){
	ListNode* p=head;
	char cor[100];
	int score=0;
	while(1){
		if(p==NULL) break;
		printf("%s ---> ",p->data.eng);
		scanf("%s",cor);
		if(strcmp(cor,".quit")==0) break;
		else{
			if(strcmp(cor,p->data.kor)==0){
				printf("correct!\n");
				score=score+5;
			}
			else{
			printf("incorrect!\n");
			}
			p=p->link;
		}
	}
	printf("당신의 점수는 %d점입니다.\n",score);
}

int main(){
	ListNode* head = NULL;
	ListNode* word = NULL;
	element data;
	char id1[100];
	char pw1[100];
	char name1[100];
	int k;
	FILE *fp;
	fp = fopen("registerid.txt","r");
		while(!feof(fp)){
		k=fscanf(fp,"%s %s %s",id1,pw1,name1);
		if(k==-1) break;
		strcpy(data.adata, name1);
		head = insertFirst(head, data);
		strcpy(data.adata, pw1);
		head = insertFirst(head, data);
		strcpy(data.adata, id1);
		head = insertFirst(head, data);
	}
	fclose(fp);
	while(1){ 
	printf("================================\n");
	printf("===========2022 SPLUG===========\n");
	if(login==1)
		printf("%s\n",inid);
	else
		printf("================================\n");
	printf("=             메뉴             =\n");
	printf("================================\n");
	printf("      1. 회원가입\n      2. 로그인\n      3. 로그아웃\n      4. 영어 단어 맞추기\n      5. 회원 탈퇴\n      6. 프로그램 종료\n");
	printf("================================\n");
	printf("입력 : ");
	scanf("%d",&sel);
	if(sel==1){
		if(login==1)
			printf("로그인 상태입니다.\n");
		else{
        printf("아이디 : ");
		scanf("%s",inid);
		Searchregist(head,inid);
		strcpy(data.adata, inname);
		head = insertFirst(head, data);
		strcpy(data.adata, inpw);
		head = insertFirst(head, data);
		strcpy(data.adata, inid);
		head = insertFirst(head, data);
		printf("성공하였습니다!\n");
		}
	}
	else if(sel==2){
		if(login==1)
			printf("이미 로그인 상태입니다.\n");
		else{
		printf("아이디 : ");
		scanf("%s",inid);
		Searchlogin(head,inid);
		}
	}
	else if(sel==3){
		if(login==0)
			printf("로그인 상태가 아닙니다.\n");
		else{
			printf("정말로 로그아웃 하시겠습니까? [Y/N]\n");
			getchar();
			char out=getchar();
			if(out=='Y')
				login--;
		}
	}
	else if(sel==4){
		FILE *fp = fopen("word.txt","r");
		char imsi1[100];
		char imsi2[100];
		while(!feof(fp)){
		fscanf(fp,"%s %s",imsi1,imsi2);
		strcpy(data.eng, imsi1);
		strcpy(data.kor, imsi2);
		word = insertFirst(word, data);
		}		
		bubble(word);
		printf("영단어 맞추기 프로그램\n");
		exam(word);
		fclose(fp);
	}
	else if(sel==5){
		if(login==0)
			printf("로그인 상태가 아닙니다.\n");
		else{
			printf("정말로 탈퇴하시겠습니까? [Y/N]\n");
			getchar();
			char bye=getchar();
			if(bye=='Y'){
				login--;
				Searchbye(head);
				Searchbye2(head);
				Searchbye3(head);
			}
		}
	}
	else{
		printf("2022 splug 화이팅!\n");
        writefile(head);
		break;
	}
}
}