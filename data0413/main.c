#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 1000
#define MAZE_SIZE 10

int returnHM = 0;

typedef struct {		// ��ü!
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
	{
		return s->data[(s->top)--];
	}
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 


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

// ��ġ�� ���ÿ� ����
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
// �̷θ� ȭ�鿡 ����Ѵ�. 
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
		return 1;  //������.
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
		

		push(&road, here);  //������ �� �ֱ�

		

		printf("\n���� ��ġ [%d %d] \n",r,c);

		maze_print(maze);
		
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		
		if (is_empty(&s)) {
			printf("����\n");
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
				here = peek(&s);  //�̵�
			}
			
		}
			
	}
	push(&road, here);  //������ �� �ֱ�

	while (is_empty(&road) != 1)   //���
	{
		element tmp = pop(&road);
		push(&road_sort, tmp);
	}
	while (is_empty(&road_sort) != 1)
	{
		element tmp = pop(&road_sort);
		printf("[%d,%d]", tmp.r, tmp.c);
	}

	printf("����\n");
	return 0;
}
