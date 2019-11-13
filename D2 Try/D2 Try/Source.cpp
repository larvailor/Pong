
//----------------------------------------------------------------------
//									Main
//----------------------------------------------------------------------

#ifndef  UNICODE
#define  UNICODE
#endif

#define SERVER 0
#define CLIENT 1

#include <Windows.h>
#include <windowsx.h>

#pragma comment(lib, "d2d1")

#include "GlobalVars.h"
#include "Server.h"
#include "Client.h"

MainWindow win;
Ball   ball;
Player playerMain, playerEnemy;

int enemyScore = 0;
int mainScore = 0;
float gameStatus = 0;
float endGameMsg = 9999;

void InitBallAndPlayers(float Width, float Height, int serverOrClient);

// Main program function
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	if (!win.Create(L"My game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU)) {
		return 0;
	}
	   
	int msgBoxRez = MessageBox(NULL, L"Create game? - Press \"Yes\" \n Join game? - Press \"No\"", L"Start menu", MB_YESNO);
	switch (msgBoxRez) {
	case IDYES: 
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startServer, NULL, NULL, NULL);	
		InitBallAndPlayers(win.Width, win.Height, SERVER);
		break;
	case IDNO:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startClient, NULL, NULL, NULL);
		InitBallAndPlayers(win.Width, win.Height, CLIENT);
		break;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



// Initialization positions
void InitBallAndPlayers(float Width, float Height, int serverOrClient)
{
	//--------------------------------
	// Ball

	// initialize ball
	ball.Initialization(Width  * 0.5,
		Height * 0.5,
		min(Width * 0.02, Height * 0.02));

	//--------------------------------
	// Players

	switch (serverOrClient)	{
	case SERVER:

		// initialize main player
		playerMain.Initialization(Width  * 0.95,
			Height * 0.4,
			Width  * 0.01,
			Height * 0.2);

		// initialize enemy player
		playerEnemy.Initialization(Width  * 0.05,
			Height * 0.4,
			Width  * 0.01,
			Height * 0.2);

		break;

	case CLIENT:

		// initialize main player
		playerMain.Initialization(Width  * 0.05,
			Height * 0.4,
			Width  * 0.01,
			Height * 0.2);

		// initialize enemy player
		playerEnemy.Initialization(Width  * 0.95,
			Height * 0.4,
			Width  * 0.01,
			Height * 0.2);

		break;
	}

}