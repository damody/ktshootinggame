#pragma once
#include "common/shared_ptr.h"
class Ball;
class Behavior
{
public:
	virtual ~Behavior(){}
	virtual int UpdateBall(Ball* b, float elapsedtime) = 0;
};
SHARE_PTR(Behavior)

