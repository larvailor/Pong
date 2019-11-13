
//----------------------------------------------------------------------
//					Class to represent main window
//----------------------------------------------------------------------

#pragma once

#ifndef  UNICODE
#define  UNICODE
#endif 

#include <Windows.h>
#include <windowsx.h>
#include <d2d1.h>

#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory            *pFactory;
	ID2D1HwndRenderTarget   *pRenderTarget;
	ID2D1SolidColorBrush    *pBrush;

	D2D1_RECT_F				represPlayerMain, represPlayerEnemy;
	D2D1_ELLIPSE            represBall;

	D2D1_POINT_2F			ptMouse;

	void	SetRepresPlayerMain();
	void	SetRepresPlayerEnemy();
	void	SetRepresBall();

	void	InitializeAll();

	void	PaintBall();
	void    PaintPlayerMain();
	void	PaintPlayerEnemy();
	void    PaintScore();

	void	OnLButtonDown(int, int, DWORD);
	void	OnMouseMove(int, int, DWORD);
	void	OnLButtonUp(); 
	   
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();

public:
	float		 Width, Height;

	HRESULT      hr = S_OK;

	MainWindow() :pFactory(NULL), pRenderTarget(NULL), ptMouse(D2D1::Point2F())
	{
	}

	PCWSTR  ClassName() const { return L"Game window class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};