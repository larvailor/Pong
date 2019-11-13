
//----------------------------------------------------------------------
//								  Server
//----------------------------------------------------------------------
#ifndef  UNICODE
#define  UNICODE
#endif

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>
#include <time.h>

#include "GlobalVars.h"
#include "Server.h"

void ballLogic(int*, int*);

int startServer()
{
	int iResult = 0;

	//--------------------------------
	// Assign library

	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	iResult = WSAStartup(wVersionRequested, &wsaData);
	if (iResult != 0) {
		return 1;
	}

	//--------------------------------
	// Creating socket for listening

	SOCKET listenSocket;	// receiving socket

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET) {
		WSACleanup();
		return 1;
	}

	//--------------------------------
	// Addres and port initialization 	 

	SOCKADDR_IN serverAddr; // receiving addres
	int serverAddrSize = sizeof(serverAddr);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1111);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.43.218");

	//--------------------------------
	// Binding socket

	iResult = bind(listenSocket, (SOCKADDR*)&serverAddr, serverAddrSize);
	if (iResult != 0) {
		return 1;
	}

	//--------------------------------
	// Listen for incoming connection requests

	iResult = listen(listenSocket, 1);
	if (iResult == SOCKET_ERROR) {
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//--------------------------------
	// Connect client

	SOCKET acceptSocket;
	acceptSocket = accept(listenSocket, (SOCKADDR*)&serverAddr, &serverAddrSize);
	if (acceptSocket == INVALID_SOCKET) {
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//--------------------------------
	// Receiving messages

	srand(time(NULL));
	int xdir, ydir, temp;
	temp = rand() % 2;
	xdir = temp == 0 ? -1 : 1;
	temp = rand() % 2;
	ydir = temp == 0 ? -1 : 1;

	char coord[4] = " ";
	float pos;
	while (TRUE)
	{	
		// getting enemy input
		iResult = recv(acceptSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);

		playerEnemy.setTopLeftY(pos);
		iResult = recv(acceptSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);
		playerEnemy.setBottomRightY(pos);

		// sending player input
		floatToChar(playerMain.getTopLeftY(), coord);
		iResult = send(acceptSocket, coord, sizeof(coord), NULL);
		floatToChar(playerMain.getBottomRightY(), coord);
		iResult = send(acceptSocket, coord, sizeof(coord), NULL);
		
		// ball logic
		ballLogic(&xdir, &ydir);

		// sending ball
		floatToChar(ball.getX(), coord);
		iResult = send(acceptSocket, coord, sizeof(coord), NULL);
		floatToChar(ball.getY(), coord);
		iResult = send(acceptSocket, coord, sizeof(coord), NULL);
		
	}

	//--------------------------------
	// Finalization

	iResult = closesocket(listenSocket);
	if (iResult == SOCKET_ERROR) {
		return 1;
	}

	WSACleanup();

	return 0;
}



// Represent ball logic
void ballLogic(int *xdir, int *ydir)
{
	float x, y, r;
	x = ball.getX();
	y = ball.getY();
	r = ball.getRadius();

	float eWidth, ex, ey;
	eWidth = playerEnemy.getWidth();

	static float speed = 0.03;
	x = ball.getX() + (float)(*xdir * speed);
	y = ball.getY() + (float)(*ydir * speed);
	
	int iResult;
	static const int LEFT_GOAL = 0;
	static const int RIGHT_GOAL = 1;

	int checkGoal();
	iResult = checkGoal();
	switch (iResult) {
	case LEFT_GOAL:
		enemyScore++;
		Sleep(1000);
		ball.setX(win.Width  * 0.5);
		ball.setY(win.Height * 0.5);
		return;

	case RIGHT_GOAL:
		mainScore++;
		Sleep(1000);
		ball.setX(win.Width  * 0.5);
		ball.setY(win.Height * 0.5);
		return;
	}

	static const int LEFT_HIT = 0;
	static const int RIGHT_HIT = 1;

	int checkPlayerHit();
    iResult = checkPlayerHit();
	switch (iResult) {
	case LEFT_HIT:
		*xdir = 1;
		break;
	case RIGHT_HIT:
		*xdir = -1;
		break;
	}

	if (x > win.Width) { *xdir = -1; }
	if (x < 0) { *xdir = 1; }
	if (y > win.Height) { *ydir = -1; }
	if (y < 0) { *ydir = 1; }

	x = ball.getX() + (float)(*xdir * speed);
	y = ball.getY() + (float)(*ydir * speed);

	ball.setX(x);
	ball.setY(y);
}



// Check if ball hits the board
// if left  board was hitten, function returns 0
// if right board was hitten, function returns 1
int checkPlayerHit()
{
	playerMain.getTopLeftY();

	if (ball.getX() - ball.getRadius() < playerEnemy.getbottomRightX()) {
		if (ball.getY() - ball.getRadius() < playerEnemy.getBottomRightY()) {
			if (ball.getY() + ball.getRadius() > playerEnemy.getTopLeftY()) {
				return 0;
			}
		}
	}
	else {
		if (ball.getX() + ball.getRadius() > playerMain.getTopLeftX()) {
			if (ball.getY() - ball.getRadius() < playerMain.getBottomRightY()) {
				if (ball.getY() + ball.getRadius() > playerMain.getTopLeftY()) {
					return 1;
				}
			}
		}
	}
}



// Check if goal
// if goal to left  player, function returns 0
// if goal to right player, function returns 1
int checkGoal()
{
	if (ball.getX() - ball.getRadius() < 0) { return 0; }
	if (ball.getX() + ball.getRadius() > win.Width) { return 1; }
}