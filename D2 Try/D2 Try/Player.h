
//----------------------------------------------------------------------
//						Class to represent player
//----------------------------------------------------------------------

#pragma once

class Player
{
private:
	float topLeftX;
	float topLeftY;
	float bottomRightX;
	float bottomRightY;
	float width;
	float height;

public:
	void Initialization(float, float, float, float);

	// setters
	void setWidth(float _width)   { width  = _width; }
	void setHeight(float _height) { height = _height; }

	void setTopLeftX(float _topLeftX)         { topLeftX = _topLeftX; }
	void setTopLeftY(float _topLeftY)         { topLeftY = _topLeftY; }
	void setBottomRightX(float _bottomRightX) { bottomRightX = _bottomRightX; }
	void setBottomRightY(float _bottomRightY) { bottomRightY = _bottomRightY; }

	// getters
	float getWidth()  { return width; }
	float getHeight() { return height; }

	float getTopLeftX()     { return topLeftX; }
	float getTopLeftY()     { return topLeftY; }
	float getbottomRightX() { return bottomRightX; }
	float getBottomRightY() { return bottomRightY; }
};

