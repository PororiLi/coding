/* OS final project HAMHOUSE
*problem : make 2 hamburger with proc M(RR), Mem M(LRU), disk M(SSTF) algorithm
*Developer : porori
*Date : 2019.06.13
*/

//include
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include <unistd.h>//write, close함수

//define
#define A_MEMSIZE 50//창고 A 크기 50
#define OPENTIME 32400//오전 9시 초단위
#define CALLORDER 3//전화 주문
#define MEETORDER 5//방문 주문
#define PAYMENT 5//결제 시간 5초
#define BAEDAL 200//배달 시간 200초

//function def
typedef struct whouse{//LRU
	char *contain;
	int pno;
	int pcnt;
}whouse;

whouse changB_make()//changB 채우기
{
	whouse changB[8];
	changB[0].contain = "0";
	changB[1].contain = "pickle";
	changB[2].contain = "shrimp";
	changB[3].contain = "beef";
	changB[4].contain = "bread";
	changB[5].contain = "lettuce";//상추
	changB[6].contain = "cheese";
	changB[7].contain = "tomato";
	
	return *changB;
}

void LRU_insert(whouse memory[], int pnum, char str[])//LRU 창고에 집어 넣고 LRU 대로 정렬하기
{
	for(int i=0; i<A_MEMSIZE; i++)
	{
		if(memory[i].pno == 0)
		{
			strcpy(memory[i].contain ,str);
			memory[i].pno = pnum;
			memory[i].pcnt +=1;//pcnt 1 증가
			break;
		}
		else if(strcmp(memory[i].contain, str)==0)//같다면 0하고 pcnt 1 증가
		{
			memory[i].pcnt += 1;
			break;
		}
	}

	// 정렬 : cnt 가 높은 것이 높은 인덱스에 오게 정렬 따라서 제거 할 때는 높은 인덱스부터 빼고 다른것 채워 넣기
	whouse tmp;
	for(int i = 0; i <A_MEMSIZE; i++)
	{
		if(memory[i].pcnt < memory[i+1].pcnt)
		{
			tmp = memory[i];
			memory[i] = memory[i+1];
			memory[i+1] = tmp;
		}
	}
	if(memory[2].pno != 0 && strcmp(memory[2].contain, str)!=0)
	{
		strcpy(memory[2].contain, str);
		memory[2].pno = pnum;
		memory[2].pcnt = 1;
	}
	// LRU_print(memory);	
}

void LRU_print(whouse memory[])//LRU 출력
{
	printf("Contain	Pageno	Pagecount\n");
	for(int i = 0; i<A_MEMSIZE; i++)
	{
		printf("%s", memory[i].contain);
		printf("	%d	%d\n", memory[i].pno, memory[i].pcnt);
		if(memory[i].pno==0)
			break;
	}
}

//main
int main(int argc, char *argv[])
{
	int time = OPENTIME;//time에 maketime 계속 더해주기
	int maketime = 0;
	whouse changB[8] = {0,};
	
	whouse chickenB[6];
	whouse shrimpB[6];
	
	//file 읽기
	int fd;	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf ("[ERROR]Can't open the file %s\n", argv[1]);
		return -1;
	}else{//https://shaeod.tistory.com/295
		printf ("[*]File Open success! FD is : %d \n" , fd);
		//파일에서 특정 문자열만 읽기
	}
 
	//fd.getline();//특정 라인만 읽기 함수
	//https://sunyzero.tistory.com/144
	
	//메모리 생성 후 초기화
	whouse	changA[A_MEMSIZE+1] = {0,};
	for(int i=0; i < A_MEMSIZE; i++) 
	{
		changA[i].contain = (char*)malloc(20);
		changA[i].pno = 0;
		changA[i].pcnt = 0;
	}
	
	*changB = changB_make();
		
	// LRU_insert(changA, pnum, str);//여기 string 은 changB에서 가져오기
	LRU_print(changA);
	LRU_print(changB);
	
	//program exit
	if(time > 86400 || time == 86400){//시간이 24시보다 크다면 프로그램 종료
		for(int i=0; i < A_MEMSIZE; i++) //memory free
		free(changA[i].contain);
		//file 출력 해주기
		close(fd);
		return 0;
	}
}
