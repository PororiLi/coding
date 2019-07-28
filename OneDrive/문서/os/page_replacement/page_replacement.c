#include<stdio.h>
#include<string.h>

#define MEMSIZE 3
//LRU

typedef struct mem{
	char *contain;
	int pno;
	int pcnt;
}mem;

void mem_insert(mem memory[], int pnum, char str[])
{
	for(int i=0; i<MEMSIZE; i++)
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

	// 정렬
	mem tmp;
	for(int i = 0; i <MEMSIZE; i++)
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

}

int main()
{
	int choice, pnum;
	char str[10];
	mem	memory[MEMSIZE+1] = {0,};

	for(int i=0; i < MEMSIZE; i++)
	{	
		memory[i].contain = (char*)malloc(20);
		memory[i].pno = 0;
		memory[i].pcnt = 0;
	}

	while(1){
			
		puts("");
		puts("1.Insert");
		puts("2.Show");
		puts("3.Exit");
		printf("Enter Your Choice : ");
		puts("");
		puts("");

		scanf("%d", &choice);

		switch(choice){
			case 1://insert
				printf("Enter page no between 1 to 10 :");
				scanf("%d", &pnum);
				puts("");
				scanf("%s", str);
				mem_insert(memory, pnum, str);
				break;
			case 2://show
				printf("Contain	Pageno	Pagecount\n");
				for(int i = 0; i<MEMSIZE; i++){
					printf("%s", memory[i].contain);
					printf("	%d	%d\n", memory[i].pno, memory[i].pcnt);
					if(memory[i].pno==0)
						break;
				}
				break;
			case 3://exit
				puts("Exit program...");
				return 0;
			default:
				puts("invalid choice");
				return 0;
		}
	}
}