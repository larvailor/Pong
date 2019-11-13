
//----------------------------------------------------------------------
//				 Representation of MainWindow class 
//----------------------------------------------------------------------
#include <cstring>

#include "MainWindow.h"
#include "DPI.h"
#include "GlobalVars.h"
#include "SafeRelease.h"

//----------------------------------------------------------------------
// set default to all & create graphics resources

void MainWindow::InitializeAll()
{
	hr = CreateGraphicsResources();

	if (pRenderTarget != NULL) {

		D2D1_SIZE_F size = pRenderTarget->GetSize();

		// save window size
		Width = size.width;
		Height = size.height;		
	}
}



// creating graphics resources (render target & brushes)
HRESULT MainWindow::CreateGraphicsResources()
{
	if (pRenderTarget == NULL) {
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
											  D2D1::HwndRenderTargetProperties(m_hwnd, size),
											  &pRenderTarget);

		if (SUCCEEDED(hr)) {
			D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::LightCyan);

			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
		}
	}
	return hr;
}



//----------------------------------------------------------------------
// Drawing part

// represent the ball for painting
void MainWindow::SetRepresBall()
{
	represBall = D2D1::Ellipse(D2D1::Point2F(ball.getX(),
		ball.getY()),
		ball.getRadius(),
		ball.getRadius());
}



// represent main player for painting
void MainWindow::SetRepresPlayerMain()
{
	represPlayerMain = D2D1::Rect(playerMain.getTopLeftX(),
		playerMain.getTopLeftY(),
		playerMain.getbottomRightX(),
		playerMain.getBottomRightY());
}



// represent enemy player for painting
void MainWindow::SetRepresPlayerEnemy()
{
	represPlayerEnemy = D2D1::Rect(playerEnemy.getTopLeftX(),
		playerEnemy.getTopLeftY(),
		playerEnemy.getbottomRightX(),
		playerEnemy.getBottomRightY());
}



// draw ball
void MainWindow::PaintBall()
{
	SetRepresBall();
	pRenderTarget->FillEllipse(represBall, pBrush);
}



// draw player
void MainWindow::PaintPlayerMain()
{
	SetRepresPlayerMain();
	pRenderTarget->FillRectangle(represPlayerMain, pBrush);
}


// drawing enemy 
void MainWindow::PaintPlayerEnemy()
{
	SetRepresPlayerEnemy();
	pRenderTarget->FillRectangle(represPlayerEnemy, pBrush);
}



void MainWindow::OnPaint()
{	
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();
		 
		// draw background
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateGray));

		// draw all things
		PaintBall();
		PaintPlayerMain();
		PaintPlayerEnemy();
		//PaintScore();

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}



// Draw score
void MainWindow::PaintScore()
{
	static RECT leftScore, rightScore, middle;
	leftScore.left = 0.4 * win.Width;
	leftScore.top = 0.9 * win.Height;
	leftScore.right = 0.45 * win.Width;
	leftScore.bottom = 0.95 * win.Height;
	
	static LPCTSTR score;
	switch (enemyScore) {
	case 0:	score = L"0";	break;
	case 1:	score = L"1";	break;
	case 2:	score = L"2";	break;
	case 3:	score = L"3";	break;
	case 4:	score = L"4";	break;
	case 5:	score = L"5";	break;
	case 6:	score = L"6";	break;
	case 7:	score = L"7";	break;
	case 8:	score = L"8";	break;
	case 9:	score = L"9";	break;
	}
	DrawText(GetDC(m_hwnd), score, 3, &leftScore, NULL);

	middle.left = 0.48 * win.Width;
	middle.top = 0.9 * win.Height;
	middle.right = 0.52 * win.Width;
	middle.bottom = 0.95 * win.Height;

	score = L":";
	DrawText(GetDC(m_hwnd), score, 1, &middle, NULL);

	rightScore.left = 0.55 * win.Width;
	rightScore.top = 0.9 * win.Height;
	rightScore.right = 0.6 * win.Width;
	rightScore.bottom = 0.95 * win.Height;

	switch (mainScore) {
	case 0:	score = L"0";	break;
	case 1:	score = L"1";	break;
	case 2:	score = L"2";	break;
	case 3:	score = L"3";	break;
	case 4:	score = L"4";	break;
	case 5:	score = L"5";	break;
	case 6:	score = L"6";	break;
	case 7:	score = L"7";	break;
	case 8:	score = L"8";	break;
	case 9:	score = L"9";	break;
	}
	DrawText(GetDC(m_hwnd), score, 2, &rightScore, NULL);

}



//----------------------------------------------------------------------
// Control part

// store start position
void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
	SetCapture(m_hwnd);
	ShowCursor(FALSE);
	ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
}



// calculate new position & repaint
void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	if (flags & MK_LBUTTON)
	{
		float prevX = ptMouse.x;
		float prevY = ptMouse.y;
		ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);

		D2D1_POINT_2F currDips = DPIScale::PixelsToDips(pixelX, pixelY);

		float difference = currDips.y - prevY;
		difference = difference;

		playerMain.setTopLeftY(playerMain.getTopLeftY() + difference);
		playerMain.setBottomRightY(playerMain.getBottomRightY() + difference);

		if (playerMain.getTopLeftY() < 0) {
			playerMain.setTopLeftY(0);
			playerMain.setBottomRightY(playerMain.getTopLeftY() + playerMain.getHeight());
		}
		else 
			if (playerMain.getBottomRightY() > Height) {
				playerMain.setBottomRightY(Height);
				playerMain.setTopLeftY(playerMain.getBottomRightY() - playerMain.getHeight());
			}

		SetRepresPlayerMain();

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}



// release capture
void MainWindow::OnLButtonUp()
{
	ShowCursor(TRUE);
	ReleaseCapture();
}

//----------------------------------------------------------------------
// Other

// message handler
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int count = 0;
	switch (uMsg) {
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
			return -1;
		}
		DPIScale::Initialize(pFactory);
		InitializeAll();
		return 0;

	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		OnPaint();
		InvalidateRect(m_hwnd, NULL, FALSE);
		return 0;

	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;

	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;

	case WM_LBUTTONUP:
		OnLButtonUp();
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}



void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
}