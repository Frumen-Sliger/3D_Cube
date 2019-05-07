#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ncurses.h> 

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

void main()
{
	int a, b, c;
	int x, y, z; //  x,y,z
	int centre[3] = {0,0,0}; //центр
	
	initscr();
	int row, col; //оцентровка
	getmaxyx(stdscr, row, col);
	
	x = col; //по х идентично ширине экрана
	y = row; //по y идентично высоте экрана
	z = x;   //по z идентично х, (ширина = глубина)
	
	char *Space[x][y][z]; //создание 3хмерного пространства
	
	row = row/2; //деление элементов для поиска центра
	col = col/2;
	
	centre[0] = col; //запись центра
	centre[1] = row;
	centre[2] = col;
	
	
	ColorGen();
	refresh();
	
	//Заполнение пространства нулями
	for (a = 0; a < x; a++)
	{
		for (b = 0; b < y; b++)
		{
			for (c = 0; c < z; c++)
			{
				Space[a][b][c] = "o";
			}
		}	
	}
	
	//Вывод пространства
	for (b = 0; b < y; b++)
	{
		for (a = 0; a < x; a++)
		{
			for (c = 0; c < z; c++)
			{
				mvwprintw(stdscr, b, a, "%c", Space[a][b][c]);
				//getchar();
			}
		}	
	}
	
	mvwprintw(stdscr, centre[1], centre[0], "%c", Space[a][b][c]);
	attron(COLOR_PAIR(GRAY10));
	
	getmaxyx(stdscr, row, col);
	mvwprintw(stdscr, 0, 0, "The number of rows - %d and columns - %d\n", row, col);
	
	getch();
	endwin();
}
