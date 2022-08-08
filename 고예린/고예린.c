#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define N 30
# define M 30


struct Node
{
    char id[N];
    char pw[N];
    char name[N];
    struct Node*next;
    
};

struct Quiz
{
    char eng[M];
    char kor[M];
    struct Quiz*next2;
};

void removeid(struct Node *target)    
{
    struct Node *removeNode = target->next;    
    

    target->next = removeNode->next;     

    free(removeNode);    
}

int is_logged_in = 0;
char logged_id[50];
void ShowMenu(void);

int main(void){
    while(1){
        int num;
        char id2[N];
        char pw2[N];

        FILE*fp;
        fp=fopen("join.txt","r+");
        char id1[N];
        struct Node *head=malloc(sizeof(struct Node));
        struct Node *curr=head;
        struct Node *word;

        ShowMenu();
        printf("입력:");
        scanf("%d",&num);
                while(!feof(fp)){
                word=malloc(sizeof(struct Node));
                word->next = NULL;
                fscanf(fp,"%s %s %s\n",word->id,word->pw,word->name);  
                curr->next=word;
                curr=word;
                }
        
        if(num==1){
            while(1){
                printf("아이디: ");
                scanf("%s",id1);
                struct Node *curr = head->next;    
                int is_avail = 1; 
                while(curr!=NULL){
                    if(strcmp(id1,curr->id)==0){
                        printf("중복된 아이디 입니다.\n");
                        is_avail = 0;
                        break;
                    }
                    curr=curr->next;
                }

                if(is_avail)
                    break;
                }

                printf("비밀번호: ");
                scanf("%s",word->pw);
                printf("이름: ");
                scanf("%s",word->name);
                                
                FILE*fp=fopen("join.txt","a+");

                fputs(id1,fp);
                fputs(" ",fp);
                fputs(word->pw,fp);
                fputs(" ",fp);
                fputs(word->name,fp);
                fputs("\n",fp);
                printf("성공하였습니다.\n");

                fclose(fp);
                

        }
        if(num==2){
            printf("아이디 : ");
            scanf("%s",id2);
            printf("비밀번호 : ");
            scanf("%s",pw2);
            struct Node*curr;
            curr=head->next;
            int is_valid = 1; 

            while(curr!=NULL){
                if(strcmp(id2,curr->id)==0&&strcmp(pw2,curr->pw)==0){
                    is_logged_in = 1;
                    strcpy(logged_id, id2);
                    printf("로그인 되었습니다.\n");
                    is_valid=0;
                }
                curr=curr->next;

            }
                if(is_valid){
                    printf("로그인 실패\n");
                    
                }                

            
        }

        if(num==3){
            char y_n[30];
            if(is_logged_in!=1){
                printf("로그인이 된 상태에서만 로그아웃이 가능합니다.\n");
            }
            else{
                printf("정말로 로그아웃 하시겠습니까? [Y/N] : ");
                scanf("%s",y_n);
                if(strcmp(y_n,"Y")==0||strcmp(y_n,"y")==0){
                    printf("로그아웃 되었습니다.\n");
                    is_logged_in = 0;
                }
                if(strcmp(y_n,"N")==0||strcmp(y_n,"n")==0){
                    printf("로그아웃이 취소되었습니다.\n");
                }
            }

            //ShowMenu();
        }
        if(num==4){
            char tmp[M];
            FILE*wd=fopen("word.txt","r");
            struct Quiz*head2=malloc(sizeof(struct Quiz));
            struct Quiz*curr2=head2;
            struct Quiz*word2;
            while(!feof(wd)){
                word2=malloc(sizeof(struct Quiz));
                curr2->next2=word2;
                fscanf(wd,"%s %s",word2->eng,word2->kor);
                curr2=curr2->next2;
            }
    
            curr2=head2->next2;
            struct Quiz*link=malloc(sizeof(struct Quiz));
            link=curr2->next2;
            while(curr2->next2!=NULL){
                    if(link->next2==NULL){
                        curr2=curr2->next2;
                        link=curr2->next2;
                        continue;                
                    }
            if(strcmp(curr2->eng,link->eng)>0){
                strcpy(tmp,curr2->eng);                
                strcpy(curr2->eng,link->eng);
                strcpy(link->eng,tmp);
                strcpy(tmp,curr2->kor);                
                strcpy(curr2->kor,link->kor);
                strcpy(link->kor,tmp);
            }
                link=link->next2;

            }
            char mean[M];
            int score=0;
            printf(">>>영어 단어 맞추기 프로그램<<<\n");
            curr2=head2->next2;
            while(curr2->next2!=NULL){
                printf("%s---> ",curr2->eng);
                scanf("%s",mean);
                if(strcmp(mean,curr2->kor)==0){
                    printf("correct!\n");
                    score+=1;
                    curr2=curr2->next2;
                    continue;
                }
                    
                if(strcmp(mean,".quit")==0){
                    break;
                }
                if(strcmp(mean,curr2->kor)!=0){
                    printf("incorrect!\n");
                    curr2=curr2->next2;        
                    continue;
                }
            }
            printf("당신의 점수는 %d점 입니다.\n",score);
            printf("종료합니다.\n");
        }

        if(num==5){
            curr=head;
            word=curr->next;
            char YN[N];
            if(is_logged_in!=1){
                printf("로그인 상태가 아닙니다.\n");
            }
			if(is_logged_in==1){
                printf("정말 탈퇴하시겠습니까? [Y/N] : ");
                scanf("%s",YN);
                if(strcmp(YN,"Y")==0||strcmp(YN,"y")==0){
                    while(curr->next!=NULL){
                        if(strcmp(id2,curr->next->id)==0){
                            removeid(curr);
                            curr=head->next;
                            FILE*fp=fopen("join.txt","w+");
                            while(curr!=NULL){
                                fprintf(fp,"%s %s %s\n",curr->id,curr->pw,curr->name);
                                curr=curr->next;      
                            }
                            is_logged_in = 0;

                            fclose(fp);
                            printf("탈퇴가 완료되었습니다.\n");
                            break;                            
                        }
                        curr=curr->next;
                    }
                }

            if(strcmp(YN,"Y")!=0&&strcmp(YN,"y")!=0){
                printf("탈퇴가 취소되었습니다.\n");

                }
                
            }

        }

        if(num==6){
            printf("2022 스플럭 화이팅!\n");
            break;
        }       

    }
    return 0;
    
}



void ShowMenu(void)
{
	printf("================================\n");
    printf("===========2022 SPLUG===========\n");
    if(is_logged_in)
        printf("===========================%s\n",logged_id);
    else
        printf("================================\n");
	printf("=             메뉴             =\n");
	printf("================================\n");
	printf("         1. 회원가입\n");
	printf("         2. 로그인\n");
	printf("         3. 로그아웃\n");
	printf("         4. 영어 단어 맞추기\n");
	printf("         5. 회원 탈퇴\n");
	printf("         6. 프로그램 종료\n");
	printf("================================\n");
}


