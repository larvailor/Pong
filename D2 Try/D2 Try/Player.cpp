
//----------------------------------------------------------------------
//					 Representation Player class
//----------------------------------------------------------------------

#include "Player.h"

// set default
void Player::Initialization(float _topLeftX, float _topLeftY, 
							float _width, float _height)
{
	setTopLeftX(_topLeftX);
	setTopLeftY(_topLeftY);

	setWidth(_width);
	setHeight(_height);

	setBottomRightX(_topLeftX + _width);
	setBottomRightY(_topLeftY + _height);
}
