/* circularQ.c*/

#include <stdio.h>//standard input/output library, 표준 입출력 라이브러리
#include <stdlib.h>//c표준 유틸리티 함수들을 모아 놓은 헤더파일

#define MAX_QUEUE_SIZE 4//MAX_QUEUE_SIZE를 4로 정의

typedef char element;//char을 별칭 element로 정의
typedef struct {//구조체 선언
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
	//구조체 멤버 선언
}QueueType;//구조체 별칭을 QueueType로 정의

/*함수 원형 선언*/
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)//메인함수
{
	QueueType *cQ = createQueue();
	//QueueType구조체 변수 선언 및 createQueue() 함수 대입
	element data;
	//data 변수 선언

	char command;//명령어 변수 선언
	printf("[----- [Jin Yuseong] [2018038022] -----]");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		//메뉴 출력

		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력 받기

		switch(command) {//스위치 문
		//소문자와 대문자 모두 입력 받기
		case 'i': case 'I'://i를 입력 받았을 때
			data = getElement();//data에 요소를 받아서 대입
			enQueue(cQ, data);//enQueue함수 실행
			break;//스위치문 끝
		case 'd': case 'D'://d를 입력 받았을 때
			deQueue(cQ,&data);//deQueue함수 실행
			break;//스위치문 끝
		case 'p': case 'P'://p를 입력 받았을 때
			printQ(cQ);//printQ함수 실행
			break;//스위치문 끝
		case 'b': case 'B'://b를 입력 받았을 때
			debugQ(cQ);
			break;//스위치문 끝
		case 'q': case 'Q'://q를 입력 받았을 때
			break;//스위치문 끝
		default://이 외의 입력을 받았을 때 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//경고문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');//q키를 사용하기 전까지 계속 반복


	return 1;//종료
}

QueueType *createQueue()//큐생성
{
	QueueType *cQ;//포인터 변수 cQ선언
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ 동적 할당
	cQ->front = 0;
	cQ->rear = 0;
	//앞, 뒤 0초기화
	return cQ;
	//cQ반환
}

int freeQueue(QueueType *cQ)//큐 할당 해제
{
    if(cQ == NULL) return 1;//cQ가 비어있을 경우 종료
    free(cQ);//cQ 할당해제
    return 1;//종료
}

element getElement()//요소 받기
{
	element item;//item 변수 선언
	printf("Input element = ");
	scanf(" %c", &item);
	//요소 입력 받기
	return item;//item 반환
}


int isEmpty(QueueType *cQ)//공간이 비었을 때
{
	if (cQ->front == cQ->rear){//앞, 뒤가 같을 경우
		printf("Circular Queue is empty!");//공간이 비었음을 알림
		return 1;//종료
	}
	else return 0;//종료
}

int isFull(QueueType *cQ)//공간이 꽉 찼을 때
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//if문을 통해 공간이 찼는지 확인
		printf(" Circular Queue is full!");//공간이 꽉 찼음을 알림
		return 1;//이상이 있음
	}
	else return 0;//정상 종료
}

void enQueue(QueueType *cQ, element item)//삽입함수
{
	if(isFull(cQ)) return;//공간이 다 찼을경우 종료
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
		//공간이 있다면 그 공간에 순서대로 삽입
	}
}

void deQueue(QueueType *cQ, element *item)//삭제함수
{
	if(isEmpty(cQ)) return;//공간이 비어있으면 종료
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		//공간 안을 삭제
		return;//종료
	}
}


void printQ(QueueType *cQ)//출력함수
{
	int i, first, last;//int형 변수 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//첫번째 값
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//마지막 값

	printf("Circular Queue : [");

	i = first;
	while(i != last){//마지막과 같기 전까지 계속 출력
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//디버그 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//for문을 통해 순차적으로 디버그
	{
		if(i == cQ->front) {//앞 값 찾기
			printf("  [%d] = front\n", i);
			continue;//반복
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}