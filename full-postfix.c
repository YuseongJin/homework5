/* postfix.c*/

#include <stdio.h>//standard input/output library, 표준 입출력 라이브러리
#include <stdlib.h>//c표준 유틸리티 함수들을 모아 놓은 헤더파일
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10//MAX_STACK_SIZE를 10으로 정의
#define MAX_EXPRESSION_SIZE 20//MAX_EXPRESSION_SIZE를 20으로 정의

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{//열거형 구조체 선언
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;//구조체 별칭 정의

/*함수 원형 선언*/
char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()//메인 함수
{
	char command;//명령어 변수 선언
    printf("[----- [Jin Yuseong] [2018038022] -----]\n");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");
        //메뉴 출력

		printf("Command = ");
		scanf(" %c", &command);
        //명령어 입력 받기

		switch(command) {//스위치문 
        //소문자 대문자 모두 입력 받기
		case 'i': case 'I'://i를 입력했을때
			getInfix();//getinfix 함수
			break;//스위치문 끝
		case 'p': case 'P'://p를 입력했을때
			toPostfix();//toPostfix함수
			break;//스위치문 끝
		case 'e': case 'E'://e를 입력했을때
			evaluation();//evaluation함수
			break;//스위치문 끝
		case 'd': case 'D'://d를 입력했을때
			debug();//debug 함수
			break;//스위치문 끝
		case 'r': case 'R'://r를 입력했을때
			reset();//reset 함수
			break;//스위치문 끝
		case 'q': case 'Q'://q를 입력했을때
			break;//스위치문 끝
		default://그 외 입력 했을때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//주의문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');//q키를 사용하기 전까지 계속 반복

	return 1;//종료


}

void postfixPush(char x)//postfix push 함수
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfix pop 함수
{
	char x;//char형 변수 x 선언
    if(postfixStackTop == -1)//postfixStackTop이 -1이라면
        return '\0';//null값 반환
    else {//그외
    	x = postfixStack[postfixStackTop--];
    }
    return x;//x반환
}

void evalPush(int x)//계산 push함수
{
    evalStack[++evalStackTop] = x;
}

int evalPop()//계산 pop함수
{
    if(evalStackTop == -1)//evalStackTop이 -1이라면
        return -1;//-1 반환
    else
        return evalStack[evalStackTop--];
}




void getInfix()//infix 입력 받는 함수
{
    printf("Type the expression >>> ");
 //infix expression을 입력받는다.
    scanf("%s",infixExp);
 //infixExp에는 입력된 값을 저장한다.
}

precedence getToken(char symbol)//token 얻기
{
	switch(symbol) {//스위치문을 통하여 값을 반환
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)//우선순위 함수
{
	return getToken(x);//얻은 토큰값 반환
}

/* 문자하나를 전달받아, postfixExp에 추가*/
void charCat(char* c)//
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//문자열 복사
	else
		strncat(postfixExp, c, 1);//문자열 붙여넣기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')//null 값이 아니라면 실행
	{
		if(getPriority(*exp) == operand)//getPriority(*exp)이 operand와 같을때
		{
			x = *exp;
        	charCat(&x);
		}
        else if(getPriority(*exp) == lparen) {//getPriority(*exp)이 lparen와 같을때

        	postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen)//getPriority(*exp)이 rparen와 같을떄
        {
        	while((x = postfixPop()) != '(') {//'('와 다를때
        		charCat(&x);
				//x값 붙여넣기
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
            	x = postfixPop();//x에 postfixPop 값 대입
            	charCat(&x);
				//x값 붙여넣기
            }
            postfixPush(*exp);
        }
        exp++;//exp값 증감
	}

    while(postfixStackTop != -1)//postfixStackTop이 -1가 다르다면
    {
    	x = postfixPop();//postfixPop값 대입
    	charCat(&x);//x 붙여넣기
    }

}

void debug()//디버그 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);//infixExp 출력
	printf("postExp =  %s\n", postfixExp);//postExp 출력
	printf("eval result = %d\n", evalResult);//eval result 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)//for문을 이용하여 postfixStack를 순차적으로 출력
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()//초기화 함수
{
	infixExp[0] = '\0';//infixExp[0]에 null값 대입
	postfixExp[0] = '\0';//postfixExp[0]에 null값 대입 
//'\0'=null
	for(int i = 0; i < MAX_STACK_SIZE; i++)//for문을 이용하여 null값으로 초기화
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;//postfixStackTop -1대입
	evalStackTop = -1;//evalStackTop -1 대입
	evalResult = 0;//evalResult 0대입
}
void evaluation()//입력값 계산 함수
{
	int opr1, opr2, i;//int형 변수로 선언

	int length = strlen(postfixExp);//length에 postfixExp문자열 길이값 대입
	char symbol;//char형 변수 선언
	evalStackTop = -1;//-1로 초기화

	for(i = 0; i < length; i++)//for문을 활용한 출력
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {//토큰 얻은값이 피연산자와 같다면 
			evalPush(symbol - '0');
		}
		else {
			opr2 = evalPop();
			opr1 = evalPop();
			//pop값을 피연산자에 대입
			switch(getToken(symbol)) {
			//스위치 문을 활용하여 조건에 따라 출력
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;//
			//break: 중지
			}
		}
	}
	evalResult = evalPop();//계산 결과값에 계산pop값 대입
}
