#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int option();
void option1();
void option2();
void option3();
void option4();
void option5();
void option6();

struct info     //정보 node
{
   struct info *next;
   char id[20];
   int pw;
   char name[20];
};

void addfirst(struct info *target, char id[20], int pw, char name[20])  //정보 추가 함수 
{
   struct info *newinfo=malloc(sizeof(struct info));
   newinfo->next = target->next;
   strcpy(newinfo->id,id);
   newinfo->pw=pw;
   strcpy(newinfo->name,name);

   target->next=newinfo;
   return;
}

struct info *head = NULL;
struct info *tail = NULL;

void function()
{
   head=malloc(sizeof(struct info));
}

char login_id[20]="====================";    //option2()함수에서 사용할 전역 변수 

int main(void)
{

struct info *tail = malloc(sizeof(struct info));
function();
   head->next=NULL;
   struct info *curr=head->next;
   while(1){
      switch(option()){
         case 1:
               option1();
               printf("\n");
               break;
         case 2:
               option2();
               printf("\n");
               break;
         case 3:
               option3();
               printf("\n");
               break;
         case 4:
               option4();
               printf("\n");
               break;
         case 5:
               option5();
               printf("\n");
               break;
         case 6:
               option6();
               printf("\n");
               goto finish;
         default:
            printf("없는 번호 입니다\n");
            break;
         }
   }
finish:
   while (curr !=NULL)
   {
      struct info *next=curr->next;
      free(curr);
      curr=next;
   }
   free(head);
   return 0;
}

int option()
{
   for(int i=0;i<30;i++)
      printf("=");
   printf("\n");
   printf("==========2022 SPLUG==========\n");
   for(int i=0;i<10;i++)
      printf("=");
   printf("%s", login_id);
   printf("\n");
   printf("=            메뉴            =\n");
   for(int i=0;i<30;i++)
      printf("=");
   printf("\n");
   printf("     1. 회원가입\n     2. 로그인\n     3. 로그아웃\n     4. 영어 단어 맞추기\n     5. 회원 탈퇴\n     6. 프로그램 종료\n");
   for(int i=0;i<30;i++)
      printf("=");
   printf("\n");
   printf("입력 : ");
   int num;
   scanf("%d", &num);
   return num;
}

void option1()
{
   struct info *p = head;
   struct info *user_search = head;
   while(1){
      char ID[20]={0};
      int pw;
      char name[20]={0};
start:
      printf("아이디 : ");
      scanf("%s", ID);
      while(user_search != NULL)
      {
         if(strcmp(user_search->id,ID)==0)
         {
         printf("중복된 아이디 입니다.\n");
            user_search = head;
         goto start;
         }
         user_search = user_search->next;
      }
   
      printf("비밀번호 : ");
      scanf("%d", &pw);
      printf("이름 : ");
      scanf("%s", name);

      addfirst(head, ID, pw, name); 
      break;
   }   
   FILE *fp = fopen("information.txt", "w");

   while (p !=NULL)     //파일에 구조체 등록하는 코드 
   {
      fwrite((void*)p,sizeof(struct info),1,fp);
      p=p->next;
   }
   fclose(fp);
   
   return;
}

void option2()
{
   struct info *p=head;
   struct info *user_search = head;
   while(1)
   {
      char ID[20]={0};
      int pw;
      char name[20]={0};

      printf("아이디 : ");
      scanf("%s", ID);
      while(user_search != NULL)
      {
            if(strcmp(user_search->id,ID)==0)
            {
again_pw:
            printf("비밀번호 : ");
            scanf("%d", &pw);
            if(user_search->pw==pw)
            {
again_name:
               printf("이름 : ");
               scanf("%s", name);
               if(strcmp(user_search->name,name)==0)
               {
                  strcpy(login_id,user_search->id);
                  goto out;
               }
               printf("올바르지 않는 이름입니다.\n");
               goto again_name;
            }
            printf("올바르지 않는 비밀번호 입니다.\n");
            goto again_pw;
         }
            user_search = user_search->next;
      }
      printf("회원가입되지 않은 아이디입니다.\n");
      break;
   }
out:
   return;
}

void option3()
{
   char a;
   if(strcmp(login_id,"===================")!=0)
   {
      printf("정말로 로그아웃 하시겠습니까? [Y/N] :");
      scanf("%s", &a);
      if (a=='Y')
         strcpy(login_id,"===================");
   }
   else
      printf("로그인 되어 있지 않습니다.\n");
   return;
}

void option4()
{
   char eng[][20]={"splug", "cat", "pigeon", "grass", "apple", "orange", "watermelon", "computer", "algorithm", "bag", "money", "college", "car", "airplane", "lion", "tiger", "red", "blue", "green", "black", "purple", "rain", "snow", "sun", "earth", "mars", "jupiter", "saturn", "universe", "iron", "cupper", "atom", "moon", "guitar", "piano", "equation", "gravity", "velocity", "force", "mass", "energy", "light", "photon", "poet", "tomato", "flower", "barin", "yellow", "pink", "mask", "volcano", "math", "english", "culture" ,"water", "school", "tree", "scale", "january", "febrary" ,"march", "april", "may", "june", "july", "august", "september", "october", "november", "december", "spring", "summer", "autumn", "winter", "war", "dog", "kakao", "chocolate", "example", "grade", "success", "robot", "art", "music", "life", "window", "input", "output", "blueberry", "sound", "alphabet", "time", "flag", "night", "morning", "death", "bomb", "gun", "granade", "bullet", "cloud", "sky", "star", "insert"};
   char kor[][20]={"스플럭", "고양이", "비둘기", "잔디", "사과", "오렌지", "수박", "컴퓨터", "알고리즘", "가방", "돈", "대학교", "자동차", "비행기", "사자", "호랑이", "빨강", "파랑", "초록", "검정", "보라", "비", "눈", "해", "지구", "화성", "목성", "토성", "우주", "철", "구리", "원자", "달", "기타", "피아노", "방정식", "중력", "속도", "힘", "질량", "에너지", "빛", "광자", "시", "토마토", "꽃", "뇌", "노랑", "분홍", "마스크", "화산", "수학", "영어", "문화", "물", "학교", "나무", "크기", "1월", "2월", "3월", "4월", "5월", "6월", "7월", "8월", "9월", "10월", "11월", "12월", "봄", "여름", "가을", "겨울", "전쟁", "개", "카카오", "초콜릿", "예시", "등급", "성공", "로봇", "미술", "음악", "삶", "창문", "입력", "출력", "블루베리", "소리", "알파벳", "시간", "깃발", "밤", "아침", "죽음", "폭탄", "총", "수류탄", "총알",  "구름", "하늘", "별", "삽입"};
   char temp_eng[20]={0,};
   char temp_kor[20]={0,};
   int count, count1;        //count는 단어 개수를 의미
   count=sizeof(eng)/sizeof(eng[0]);
   count1=sizeof(kor)/sizeof(kor[0]);
   for (int j=0; j<count;j++)      //영어단어 순서대로 매기기 
   {
      for (int i=0; i<count-1; i++)     
   {
      if(strcmp(eng[i],eng[i+1])>0)
      {
         strcpy(temp_eng,eng[i]);
         strcpy(temp_kor,kor[i]);
         strcpy(eng[i],eng[i+1]);
         strcpy(kor[i],kor[i+1]);
         strcpy(eng[i+1],temp_eng);
         strcpy(kor[i+1],temp_kor);
      }
   }
   }

   for(int j=0;j<count;j++)
   {
      char quit[]=".quit";
      char str[20]={0};
      printf("%s ---> ", eng[j]);
      scanf("%s", str);
      for(int i=0; i<count;i++)
      {
         if(strcmp(str,kor[i])==0)
         {
            if(strcmp(eng[j],eng[i])==0)
               printf("correct!\n");
            else
               printf("incorrect!\n");
            break;
         }
         else if (strcmp(str,quit)==0)
         {
            printf("당신의 점수는 15점 입니다.\n");
            goto end;
         }
      }
   }   
   end:
   return;
}

void option5()
{
   struct info *rm_user = head -> next;
   printf("%s", rm_user->next->id);
   struct info *pre_user = head;
   printf("%s", pre_user->next->id);
   char b;
if(strcmp(login_id,"===================")!=0){
   //로그인 되어 있는 상태일때
      printf("정말 탈퇴하시겠습니까? [Y/N] :");
      scanf("%s", &b);
      //printf("%s", b);
      if(b=='Y'){
         while(rm_user!=NULL){
            if(strcmp(rm_user->id,login_id)==0){
               if(head->next==rm_user){
                  head->next = rm_user->next;
               }
               else if(tail==rm_user->next){
                  pre_user->next=tail;
               }
               else{
                  pre_user->next=rm_user->next;
               }
               break;
            }
            pre_user=rm_user;
            rm_user=rm_user->next;
            //printf("%s", rm_user->id);
         } 
         strcpy(login_id,"===================");
      }
      //printf("%s", head->next->id);
      //printf("%s", head->next->next->id);
      
}
else 
      printf("로그인 상태가 아닙니다.\n");
   return;
}

void option6()
{
   printf("2022 SPLUG 화이팅!\n");
   return;
}

