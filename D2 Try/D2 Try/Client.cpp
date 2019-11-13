
//----------------------------------------------------------------------
//								  Client
//----------------------------------------------------------------------
#ifndef  UNICODE
#define  UNICODE
#endif

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>

#include "GlobalVars.h"
#include "Client.h"

int startClient()
{

	int iResult;

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
	// Creating socket

	SOCKET clientSocket;

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
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
	// Connection

	iResult = connect(clientSocket, (SOCKADDR*)&serverAddr, serverAddrSize);
	if (iResult == SOCKET_ERROR) {
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	//--------------------------------
	// Message loop

	char coord[4] = " ";
	float pos = 0;
	while (TRUE)
	{	
		// send player input to server
		floatToChar(playerMain.getTopLeftY(), coord);
		iResult = send(clientSocket, coord, sizeof(coord), NULL);
		//Sleep(10);
		floatToChar(playerMain.getBottomRightY(), coord);
		iResult = send(clientSocket, coord, sizeof(coord), NULL);
		//Sleep(10);

		// getting enemy input
		iResult = recv(clientSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);
		playerEnemy.setTopLeftY(pos);
		iResult = recv(clientSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);
		playerEnemy.setBottomRightY(pos);

		// getting ball
		iResult = recv(clientSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);
		ball.setX(pos);
		iResult = recv(clientSocket, coord, sizeof(coord), NULL);
		charToFloat(coord, &pos);
		ball.setY(pos);
	}
	 

	//--------------------------------
	// Finalization

	iResult = closesocket(clientSocket);
	if (iResult == SOCKET_ERROR) {
		return 1;
	}

	WSACleanup();


	return 0;
}
