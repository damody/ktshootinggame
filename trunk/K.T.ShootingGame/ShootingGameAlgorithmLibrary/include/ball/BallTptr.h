#pragma once
#include "Ball.h"

template <typename _Type>
class BallTptr : public Ball
{
public:
	_Type* mData;
};

