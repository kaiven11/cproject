#pragma once

#include <windows.h>

#define WIDE 60
#define HIGH 20

struct body
{
	int X;
	int Y;
};

//�����ߵĽṹ��

struct Snake
{
	int length;
	struct body bd[WIDE*HIGH];
}snake;


//����ʳ��ṹ��

struct Food
{
	int length;
	struct body bd[1];
}food;



int score = 0;

//����ƫ����

int offset_x = 0;
int offset_y = 0;

//�������к���

void init_snake();

void init_food();

void show_ui();

void play_game();

