#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 1000
#define MAZE_SIZE 10

int returnHM = 0;

typedef struct {		// 교체!
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
	{
		return s->data[(s->top)--];
	}
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 


element here = { 1,0 }, entry = { 1,0 };




char maze[MAZE_SIZE][MAZE_SIZE] = {

		{'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'}

};

// 위치를 스택에 삽입
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}
// 미로를 화면에 출력한다. 
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
int checkCanMove(int r, int c) {
	if ((maze[r + 1][c] == '1' || maze[r + 1][c] == '.')
		&& (maze[r - 1][c] == '1' || maze[r - 1][c] == '.')
		&& (maze[r][c + 1] == '1' || maze[r][c + 1] == '.')
		&& (maze[r][c - 1] == '1' || maze[r][c - 1] == '.'))
	{
		return 1;  //막혔다.
	}
	else {
		return 0;

	}
}

int main(void)
{
	int r, c;
	StackType s;
	StackType road;
	StackType road_sort;

	init_stack(&s);
	init_stack(&road);
	init_stack(&road_sort);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		

		push(&road, here);  //지나온 길 넣기

		

		printf("\n현재 위치 [%d %d] \n",r,c);

		maze_print(maze);
		
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		
		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else {
			if (checkCanMove(r, c) == 1)
			{

				while (1)
				{
					element tmp1 = peek(&s);
					element tmp2 = peek(&road);

					if (checkCanMove(tmp1.r, tmp1.c) == 1)
					{
						if (tmp1.r == tmp2.r && tmp1.c == tmp2.c)
						{
							pop(&road);
						}
						pop(&s);
					}
					else {
						here = pop(&s);
						break;
					}
				}
			}
			else {
				here = peek(&s);  //이동
			}
			
		}
			
	}
	push(&road, here);  //지나온 길 넣기

	while (is_empty(&road) != 1)   //출력
	{
		element tmp = pop(&road);
		push(&road_sort, tmp);
	}
	while (is_empty(&road_sort) != 1)
	{
		element tmp = pop(&road_sort);
		printf("[%d,%d]", tmp.r, tmp.c);
	}

	printf("성공\n");
	return 0;
}
