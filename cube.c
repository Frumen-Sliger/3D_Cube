#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h> 
//#include <graphics.h>

//Алгоритм растеризации
//Алгоритм Брезенхема
//

void LineBuild(int x1, int y1, int x2, int y2) //координаты 2х точек
{
	int row, col; //оцентровка
	getmaxyx(stdscr, row, col);
	x1 = x1 + (col/2);
	x2 = x2 + (col/2);
	y1 = y1 + (row/2);
	y2 = y2 + (row/2);
	
	//printw("debug");
	
	int Y = y2-y1; //разница у
	int X = x1-x2; //разница х
	int sign;
	int dirY, dirX;
	
	/* ------	Подготовка параметров	------ */
	if (abs(Y) > abs(X))
		sign = 1;
	else				//if (abs(Y) < abs(X))
		sign = -1;
		
	if (Y < 0)
		dirY = -1;
	else				//if (deltaY < 0)
		dirY = 1;
		
	if (X < 0)
		dirX = -1;
	else				//if (deltaX < 0)
		dirX = 1;
	
	/* ------	Вывод 1 точки на нужную координату	------ */
	move(y1, x1);
	addch(' ' | A_STANDOUT);
	
	/* ------	Генерация (с выводом) линии до 2 точки	------ */
	int x =x1, y =y1, f =0;
	if (sign == -1)
	{
		do
		{
			f = f+ (Y*dirY);
			if(f > 0)
			{
				f =f- (X*dirX);
				y =y+ dirY;
			}
			x =x- dirX;
			
			move(y, x);
			addch(' ' | A_STANDOUT);
		} 
		while (x != x2 || y != y2);
	} 
	else
	{
		do
		{
			f =f+ (X*dirX);
			if(f > 0)
			{
				f =f- (Y*dirY);
				x =x- dirX;
			}
			y =y+ dirY;
			
			move(y, x);
			addch(' ' | A_STANDOUT);
		} 
		while (x != x2 || y != y2);
	}
}

//void square()

void main()
{
	int row, col;
	
	initscr();
	refresh();
	//int ColorMatrix[];
	int Depth;
	
	//printf("test");
	LineBuild(-5,-5,5,-5); 
	LineBuild(5,-5,5,5);
	LineBuild(5,5,-5,5);
	LineBuild(-5,5,-5,-5);
	
	getmaxyx(stdscr, row, col);
	mvwprintw(stdscr, row - 1, 0, "The number of rows - %d and columns - %d\n", row, col);
	
	getch();
	endwin();
}
