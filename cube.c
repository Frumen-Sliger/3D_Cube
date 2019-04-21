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
	int x =x1, y =y1, f =0;
	int dirY, dirX;
	
	int deltaX = abs(x2-x1); //разница х
	int deltaY = abs(y2-y1); //разница у
	int delta;
	
	/* ------		  Подготовка параметров  		------ */
	if (deltaY > 0)
		dirY = 1;
	else				//if (deltaY < 0)
		dirY = -1;
		
	if (deltaX > 0)
		dirX = 1;
	else				//if (deltaX < 0)
		dirX = -1;
		
	if (deltaY > deltaX)
		delta = 1;
	else				//if (deltaY < deltaX)
		delta = -1;
	
	/* ------   Вывод 1 точки на нужную координату   ------ */
	mvwprintw(stdscr, y1, x1, "");
	addch('1' | A_STANDOUT);
	
	/* ------ Генерация (с выводом) линии до 2 точки ------ */
	for (x = x1; x < x2; x++)
	{
		if (delta == -1)
		{
			do
			{
				f += deltaY*dirY;
				if(f > 0)
				{
					f -= deltaX*dirX;
					y += deltaY;
				}
			x -= deltaX;
			
			mvwprintw(stdscr, y, x, "");
			addch('1' | A_STANDOUT);
			} 
			while (x != x2 || y != y2);
		} 
		else
		{
			do
			{
				f += deltaX*dirX;
				if(f > 0)
				{
					f -= deltaY*dirY;
					x += deltaX;
				}
			y -= deltaY;
			
			mvwprintw(stdscr, y, x, "");
			addch('1' | A_STANDOUT);
			} 
			while (x != x2 || y != y2);
		}
	}
}

//void square()

void main()
{
	int row, col;
	//int ColorMatrix[];
	int Depth;
	
	initscr(); //Вход в ncurses, создание основного окна
	
	getmaxyx(stdscr, row, col);
	mvwprintw(stdscr, row - 1, 0, "The number of rows - %d and columns - %d\n", row, col);
	
	LineBuild(2,2,8,10);
	
	refresh(); //проверка буфера
	
	getch(); //ожидание нажатия
	
	endwin(); //закрытие окна и приложения
}
