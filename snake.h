#pragma once

#include <windows.h>

#define WIDE 60
#define HIGH 20

struct body
{
	int X;
	int Y;
};

//定义蛇的结构体

struct Snake
{
	int length;
	struct body bd[WIDE*HIGH];
}snake;


//定义食物结构体

struct Food
{
	int length;
	struct body bd[1];
}food;



int score = 0;

//定义偏移量

int offset_x = 0;
int offset_y = 0;

//定义运行函数

void init_snake();

void init_food();

void show_ui();

void play_game();

