#pragma once
#include "Ball.h"

template <typename _Type>
class BallTdata : public Ball
{
public:
	_Type* mData;
};

