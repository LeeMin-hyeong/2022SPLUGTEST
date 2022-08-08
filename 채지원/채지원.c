#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000

typedef struct Node{ //노드 구조체 선언
	struct Node *next;
	char id[max];
	char passwd[max];
	char name[max];
}Node;
char str[max];
char cprstr[max];
int login = 0;

int main(){
	int k;
	Node *head = (Node *)malloc(sizeof(Node));//헤드 노드
	Node *membership = (Node *)malloc(sizeof(Node)); //새로운 노드 메모리 할당
	head->next = membership;
	FILE *storage = NULL; 
	FILE *temp_storage = NULL; 
	char Log[max] = "================================\n";
	
	while(1){
	printf("================================\n");
	printf("===========2022 SPLUG===========\n");
	printf("================================\n");
	printf("=             메뉴             =\n");
	printf("%s",Log);
	printf("       1. 회원가입\n");
	printf("       2. 로그인\n");
	printf("       3. 로그아웃\n");
	printf("       4. 영어 단어 맞추기\n");
	printf("       5. 회원 탈퇴\n");
	printf("       6. 프로그램 종료\n");
	printf("================================\n");
	printf("입력 : ");
	scanf("%d", &k);


	//1. 회원가입
	if(k==1){
		int i=0;
		storage = fopen("storage.txt","a"); //파일 열기
		if(storage == NULL){
			printf("파일 생성 오류\n");
			return 0;
		}
re:
		storage = fopen("storage.txt","r");
		printf("\n\n아이디 : ");
		scanf("%s", membership->id);

		while(1){ //아이디 중복 확인
			if(fgets(str, max, storage) == NULL)
				break;
			strncpy(cprstr, str, strlen(membership->id));
			if(strstr(cprstr, membership->id) != NULL){
				printf("중복된 아이디 입니다.");
				goto re;
			}
		}	
	


		storage = fopen("storage.txt","a");
		while(1){ //파일에 아이디 저장
			if(membership->id[i] != '\0')
				fputc(membership->id[i], storage);
			else 
				break;
			i++;
		}
		fputc(' ', storage); //구분자(공백문자)



		i=0;
		printf("비밀번호 : ");
		scanf("%s", membership->passwd);
		while(1){ //파일에 비밀번호 저장
			if(membership->passwd[i] != '\0')
				fputc(membership->passwd[i], storage);
			else 
				break;
			i++;
		}
		fputc(' ', storage); //구분자(공백문자)



		i=0;
		printf("이름 : ");
		scanf("%s", membership->name);
		while(1){ // 파일에 이름 저장
			if(membership->name[i] != '\0')
				fputc(membership->name[i], storage);
			else 
				break;
			i++;
		}
		fputc('\n', storage); //마지막(개행문자)



		printf("성공하였습니다.\n\n");
		fclose(storage);
		continue;
	}


	//2. 로그인
	else if(k==2){
		if(login==1){ //예외처리
			printf("이미 로그인 중입니다.\n\n");
			continue;
		}
id:
		printf("아이디 : "); 
		scanf("%s", membership->id);
		storage = fopen("storage.txt","r"); 
		while(1){
			if(fgets(str, max, storage) == NULL){ //파일 끝까지 찾아봤는데 해당 아이디가 없는 경우 예외처리
				printf("정보를 다시 확인해 주세요.\n");
				goto id;
			}
			strncpy(cprstr, str, strlen(membership->id)); //입력받은 문자열의 길이만큼 파일 내부 문자열 탐색
			if(strstr(cprstr, membership->id) != NULL) //입력받은 문자열과 동일 문자열 찾은 경우 반복문 벗어남
				break;
			}
		fclose(storage);
		char replace[max];
		strcat(membership->id, " ");//구분자(공백문자열)
		


passwd:
		strcpy(replace, membership->id);
		printf("비밀번호 : ");
		scanf("%s", membership->passwd);
		strcat(replace, membership->passwd);
		strcat(replace, " ");//구분자(공백문자열)
		if(strstr(str, replace) == NULL){ //동일 문자열 못 찾은 경우 예외처리
			printf("비밀번호가 잘못됐습니다. 다시 입력해 주세요.\n");
			goto passwd;
		}



		int i=0;
		while(strlen(membership->id)-1-i){ //메인화면 아이디 출력 구현
			Log[31-i] = membership->id[strlen(membership->id)-2-i];
			i++;
		}



		login++; //login == 1 --> 로그인 상태
		printf("환영합니다.\n\n");
		continue;
	}


	//3. 로그아웃
	else if(k==3){
		if(login == 0){ //예외 처리
			printf("로그인 상태가 아닙니다\n\n");
			continue;
		}

		while(1){
			getchar(); //반복시 버퍼 제거
			printf("정말로 로그아웃 하시겠습니까? [Y/N] : ");
			char a = getchar();

			if(a == 'y' || a == 'Y'){
				login--;
				for(int i=0; i<32; i++)
					Log[i] = '=';
				Log[32] = '\n';
				break;
			}



			else if(a == 'n' || a == 'N'){
				login = 1;
				break;
			}



			else{
				printf("잘못된 입력. 다시 입력하세요.\n");
				continue;
			}
		}
		
		printf("\n\n");
		continue;
	}


	//4. 영어 단어 맞추기
	else if(k==4){
		
		if(login == 0){ //예외 처리
			printf("로그인 상태가 아닙니다.\n\n");
			continue;
		}
		char **quiz = (char **)malloc(105*sizeof(char *));// 메모리 할당
		for(int i=0; i<105; i++)
			quiz[i] = (char *)malloc(sizeof(char)*30); 
		char *english[105];
		char *korean[105];
		char answer[30];
		char temp[30];
		int score = 0;



		printf(">>>영어 단어 맞추기 프로그램<<<\n");
		storage = fopen("word.txt","r");
		int m=0;
		for(int i=0; i<104; i++) //파일 -> 배열로 이동
			quiz[i] = fgets(quiz[i], 30, storage);



		for(int j = 0; j < 103; j++){ //알파벳순 정렬
			for(int k = j+1; k < 104; k++){
				if(strcmp(quiz[j], quiz[k])>0){
					strcpy(temp, quiz[j]);
					strcpy(quiz[j], quiz[k]);
					strcpy(quiz[k], temp);
				}
			}
		}



		for(int i=0; i<104; i++){ //배열 자르기
			english[i] = strtok(quiz[i], " ");
			korean[i] = strtok(NULL, " ");
		}



		for(int i=0; i<104; i++){ //문제 제시
			printf("%s ---> ",english[i]);
			scanf("%s", answer);
			strcat(answer,"\n"); //korean값에 개행문자까지 포함되어 있기 때문에 개행문자 추가



			if(strstr(korean[i], answer)){
				printf("correct!\n");
				score++; //한 문제 맞출 때마다 1점 추가
			}



			else if(strstr(korean[i], answer)==NULL && strstr(answer, ".quit\n") == NULL) //틀리면 incorrect!
				printf("incorrect!\n");
			if(strstr(answer, ".quit\n")){ //.quit으로 종료 예외처리
				printf("\n당신의 점수는 %d점 입니다.\n",score);
				printf("종료합니다.\n\n"); 
				break;
			}
		}
		if(strstr(answer, ".quit\n") == NULL)
			printf("\n당신의 점수는 %d점 입니다.\n\n",score); //104문제를 모두 푼 경우



		for(int i=0; i<105; i++) // 메모리 할당 해제
			free(quiz[i]);
		free(quiz);
		fclose(storage);
		continue;   
	}


	//5. 회원 탈퇴
	else if(k==5){
		if(login == 0){ //예외 처리
			printf("로그인 상태가 아닙니다\n\n");
		}



		else if(login ==1){
			while(1){
			printf("정말로 탈퇴하시겠습니까? [Y/N] : ");
			getchar(); //반복시 버퍼 제거
			char b = getchar();



			if(b == 'y' || b == 'Y'){
				login--;
				for(int i=0; i<32; i++)
					Log[i] = '=';
				Log[32] = '\n';
				storage = fopen("storage.txt","r");



				char *cp1 = (char *)malloc(max*sizeof(char));
				memset(cp1, '\0', max*sizeof(char)); //배열 초기화
				char *cp2 = (char *)malloc(max*sizeof(char));
				while(1){
					fgets(str, max, storage);
					strncpy(cprstr, str, strlen(membership->id));//로그인 했을 때 memebership->id에 저장
					if(strstr(cprstr, membership->id) != NULL)
						break;
					strcpy(cp2, str);
					strcat(cp1, cp2);
				}



				char *cp3 = (char *)malloc(max*sizeof(char));
				memset(cp3, '\0', max*sizeof(char)); //배열 초기화
				char *cp4 = (char *)malloc(max*sizeof(char));
				while(1){
					if(fgets(str, max, storage) == NULL)
						break;
					strcpy(cp4, str);
					strcat(cp3, cp4);
				}



				fclose(storage);
				temp_storage = fopen("temp_storage.txt","w");
				fputs(cp1, temp_storage);
				fputs(cp3, temp_storage);
				remove("storage.txt");
				rename("temp_storage.txt","storage.txt");



				fclose(temp_storage);
				free(cp1);
				free(cp2);
				free(cp3);
				free(cp4);
				printf("정상적으로 탈퇴처리 되었습니다.\n\n");
				break;
			}

			else if(b == 'n' || b == 'N')
				break;

			else{ //다른 문자 입력시 질문 반복
				printf("잘못된 입력. 다시 입력하세요.\n");
				continue;
			}
			}
		}
		continue;
	}


	//6. 프로그램 종료
	else if(k==6){
		printf("2022 스플럭 화이팅!\n");
		free(membership);
		free(head);
		exit(0);
	}


	else{
		printf("잘못된 값을  입력하셨습니다. 다시 입력해주세요.\n");
		continue;
	}
	}
}
