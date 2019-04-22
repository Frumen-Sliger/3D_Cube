#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

#define typeof __typeof__
#define roundf(x) floor(x + 0.5f)
#define SWAP(x,y) do {	\
	__typeof__(x) _x = x;	\
	__typeof__(y) _y = y;	\
	x = _y;          	\
	y = _x;          	\
} while(0)

#define Def 0
#define GRAY1 1
#define GRAY2 2
#define GRAY3 3
#define GRAY4 4
#define GRAY5 5
#define GRAY6 6
#define GRAY7 7
#define GRAY8 8
#define GRAY9 9
#define GRAY10 10

#define BLACK1 11
#define BLACK2 12
#define BLACK3 13
#define BLACK4 14
#define BLACK5 15
#define BLACK6 16
#define BLACK7 17
#define BLACK8 18
#define BLACK9 19
#define BLACK10 20


void triangleRast(int x1, int y1, int x2, int y2, int x3, int y3)
{ 
	int row, col; //оцентровка
	getmaxyx(stdscr, row, col);
	x1 = x1 + (col/2);
	x2 = x2 + (col/2);
	x3 = x3 + (col/2);
	y1 = y1 + (row/2);
	y2 = y2 + (row/2);
	y3 = y3 + (row/2);
	
	move(y1, x1);
	addch(' ' | A_STANDOUT);
	move(y2, x2);
	addch(' ' | A_STANDOUT);
	move(y3, x3);
	addch(' ' | A_STANDOUT);
	
	//Упорядочивание точек
	if (y2 < y1) 
	{
		SWAP(y1, y2);
		SWAP(x1, x2);
	}
	if (y3 < y1) 
	{
		SWAP(y1, y3);
		SWAP(x1, x3);
	}
	if (y2 > y3) 
	{
		SWAP(y2, y3);
		SWAP(x2, x3); 
	}
	
	float dx13 = 0, dx12 = 0, dx23 = 0;
	
	//сравнение точек на схожесть и уравнивание 
	if(y3 != y1)
	{
		dx13 = x3 - x1;
		dx13 /= y3 - y1;
	}
	else {dx13 = 0;}
	
	if(y2 != y1)
	{
		dx12 = x2 - x1;
		dx12 /= y2 - y1;
	}
	else {dx12 = 0;}
	
	if(y3 != y2)
	{
		dx23 = x3 - x2;
		dx23 /= y3 - y2;
	}
	else {dx23 = 0;}
	
	float wx1 = x1;
	float wx2 = wx1;
	float _dx13 = dx13;
	
	if (dx13 > dx12)
	{
		SWAP(dx13, dx12);
	}
	
	int i,j, d;
	//раст 1 половины треугольника

	
	for (i = y1; i < y2; i++)
	{
		for (j = wx1; j <= wx2; j++)
		{ 
			move(i, j);
			addch(' ' | A_STANDOUT);
		}
		wx1 += dx13;
		wx2 += dx12;
		
		/*for(d = 0; d < i; d++)
		{
			getch();
			mvprintw(d,1,"Debug!");
		}*/
	}
	
	if(y1 == y2)
	{
		wx1 = x1;
		wx2 = x2;
	}
	
	if(_dx13 < dx23)
	{
		SWAP(_dx13, dx23);
	}
	
	//раст 2 половины треугольника
	for (i = y2; i <= y3; i++)
	{
		for (j = wx1; j <= wx2; j++)
		{ 
			move(i, j);
			addch(' ' | A_STANDOUT);
		}
		
		wx1 += _dx13;
		wx2 += dx23;
		
		/*for(d = 0; d < i; d++)
		{
			getch();
			mvprintw(d,1,"%d, %d, %d, %d", i, j, wx1, wx2);
		}*/
	}
	
	mvaddch(y1, x1, '+' | A_STANDOUT);
	mvaddch(y2, x2, '+' | A_STANDOUT);
	mvaddch(y3, x3, '+' | A_STANDOUT);
}
void ColorGen()
{
	start_color();
	init_color(BLACK1, 100, 100, 100);
	init_pair(GRAY1, BLACK1, COLOR_BLACK);
	init_color(BLACK2, 200, 200, 200);
	init_pair(GRAY2, BLACK2, COLOR_BLACK);
	init_color(BLACK3, 300, 300, 300);
	init_pair(GRAY3, BLACK3, COLOR_BLACK);
	init_color(BLACK4, 400, 400, 400);
	init_pair(GRAY4, BLACK4, COLOR_BLACK);
	init_color(BLACK5, 500, 500, 500);
	init_pair(GRAY5, BLACK5, COLOR_BLACK);
	init_color(BLACK6, 600, 600, 600);
	init_pair(GRAY6, BLACK6, COLOR_BLACK);
	init_color(BLACK7, 700, 700, 700);
	init_pair(GRAY7, BLACK7, COLOR_BLACK);
	init_color(BLACK8, 800, 800, 800);
	init_pair(GRAY8, BLACK8, COLOR_BLACK);
	init_color(BLACK9, 900, 900, 900);
	init_pair(GRAY9, BLACK9, COLOR_BLACK);
	init_color(BLACK10, 1000, 1000, 1000);
	init_pair(GRAY10, BLACK10, COLOR_BLACK);
	
	init_pair(Def, COLOR_WHITE, COLOR_BLACK);
}

void coloredTriangle(uint8_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
	attron(COLOR_PAIR(color)); 
	triangleRast(x1, y1, x2, y2, x3, y3);
	attroff(COLOR_PAIR(color));
}

void dobColoredSquare(uint8_t color1, uint8_t color2, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	coloredTriangle(color1, x1, y1, x2, y2, x3, y3);
	coloredTriangle(color2, x1, y1, x4, y4, x3, y3);
}

void main()
{
	initscr();
	int row, col; //оцентровка
	getmaxyx(stdscr, row, col);
	row = row/2;
	col = col/2;
	
	
	ColorGen();
	refresh();
	//int ColorMatrix[];
	int Depth;
	//1- 0, 0 
	//2- 0, 10
	//3- 10, 5
	//4- 10, -5
	dobColoredSquare(GRAY4, GRAY3, 0, 10, 10, 5, 10, -5, 0, 0);
	dobColoredSquare(GRAY5, GRAY6, -10, -5, -10, 5, 0, 10, 0, 0);
	dobColoredSquare(GRAY7, GRAY8, -10, -5, 0, -10, 10, -5, 0, 0);
	
	attron(COLOR_PAIR(GRAY10));
	mvaddch(row, col,'*' | A_STANDOUT);
	getmaxyx(stdscr, row, col);
	mvwprintw(stdscr, row - 1, 0, "The number of rows - %d and columns - %d\n", row, col);
	
	getch();
	endwin();
}
