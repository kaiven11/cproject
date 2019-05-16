#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sys/types.h>
#include "snake.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include<conio.h>
#include <stdlib.h>


void init_snake() {
	
	snake.bd[0].X = WIDE /2;
	snake.bd[0].Y = HIGH /2;
	snake.bd[1].X = WIDE /2 -1;
	snake.bd[1].Y = HIGH /2;
	snake.length = 2;
}

void init_food() {
	food.length = 1;
	food.bd[0].X = rand() % WIDE;
	food.bd[0].Y = rand() % HIGH;
}

void show_ui()
{
	//初始化

	COORD coord;
	for (int i = 0; i < snake.length; i++)
	{

		coord.X = snake.bd[i].X;
		coord.Y = snake.bd[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if (i == 0)
		{
			printf("%c", '@');
		}
		else {

			printf("%s", "*");
		};

	}

	coord.X = snake.bd[snake.length-1].X+offset_x;
	coord.Y = snake.bd[snake.length-1].Y+offset_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	putchar(' ');



	//初始化食物位置
	/*init_food();*/
	coord.X = food.bd[0].X;
	coord.Y = food.bd[0].Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%s", "#");

}

void play_game()
{
	//初始化界面，蛇的位置和食物位置

	init_snake();
	init_food();
	
	
	
	//设置蛇的边界值


	char key = 'D';
	while (snake.bd[0].X > 0 && snake.bd[0].X < WIDE && snake.bd[0].Y>0 && snake.bd[0].Y < HIGH) 
	{	
		//显示界面
		
		show_ui();

		
		//判断是否有键盘输入
		if (_kbhit())
		{
			key = _getch();
		}

		switch (key)
		{
		case 'D':case 'd':
			offset_y = 0;
			offset_x = 1;
			break;
		case 'A':case 'a':
			offset_y = 0;
			offset_x = -1;
			break;
		case 'S':case 's':
			offset_y = 1;
			offset_x = 0;
			break;
		case 'W':case 'w':
			offset_y = -1;
			offset_x = 0;
			break;
		}


		//判断和自身相撞

		for (int i = 1; i < snake.length; i++)
		{
			if (snake.bd[0].X == snake.bd[i].X && snake.bd[0].Y == snake.bd[i].Y) {
			
				return;
			}
		}


		//判断和食物相撞

		if (snake.bd[0].X == food.bd[0].X && snake.bd[0].Y== food.bd[0].Y)
		{
			//更新蛇身长度
			snake.length += 1;
			//更新分数
			score += 10;

			//食物随机

			init_food();
		
		}

		//更新蛇身坐标
		//结构体数值赋值
		for ( int i = snake.length-1; i >0; i--)
		{
			snake.bd[i].X = snake.bd[i-1].X;
			snake.bd[i].Y = snake.bd[i-1].Y;
		}

		//更新蛇头坐标

		snake.bd[0].X += offset_x;
		snake.bd[0].Y += offset_y;
		


		Sleep(500);
		



	}



}



int main(void) {

	srand((size_t)time(NULL));

	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < HIGH; j++) {
			if (i == 0 || j == 0 || j==HIGH-1)
			{
				putchar('*');
			}

		}
	}
	play_game();
	//展示边界
	printf("您当前的分数为：%d", score);
	getchar();
	return 0;

}