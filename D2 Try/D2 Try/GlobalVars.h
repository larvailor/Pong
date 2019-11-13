#pragma once

#include "Player.h"
#include "Ball.h"
#include "MainWindow.h"

extern MainWindow win;

extern Player playerMain, playerEnemy;
extern Ball   ball;
extern int    enemyScore, mainScore;

inline void floatToChar(float pos, char* coord); 

inline void charToFloat(char* coord, float* pos);

// Convert float value to the array of char
inline void floatToChar(float pos, char* coord)
{
	char temp;

	temp = (char)(pos / 1000);
	pos -= temp * 1000;
	coord[0] = temp + '0';

	temp = (char)(pos / 100);
	pos -= temp * 100;
	coord[1] = temp + '0';

	temp = (char)(pos / 10);
	pos -= temp * 10;
	coord[2] = temp + '0';

	temp = (char)(pos / 1);
	pos -= temp * 1;
	coord[3] = temp + '0';
}



// Convert array of char to float
inline void charToFloat(char* coord, float* pos)
{
	float temp = 0;
	temp += (coord[0] - '0') * 1000;
	temp += (coord[1] - '0') * 100;
	temp += (coord[2] - '0') * 10;
	temp += (coord[3] - '0') * 1;
	*pos = temp;
}