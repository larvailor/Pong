
//----------------------------------------------------------------------
//						Class to represent ball
//----------------------------------------------------------------------

#pragma once

class Ball
{	
private: 
	float					positionX;
	float					positionY;
	float					radiusBall;

public:
	Ball() { };
	~Ball() { };

	void Initialization(float, float, float);

	void setX(float _positionX)       { this->positionX = _positionX; }
	void setY(float _positionY)		  { this->positionY = _positionY; }
	void setRadius(float _radiusBall) { this->radiusBall = _radiusBall; }

	float getX()      { return positionX; }
	float getY()      { return positionY; }
	float getRadius() { return radiusBall; }
};


