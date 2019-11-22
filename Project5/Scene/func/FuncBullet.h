#pragma once
#include <scene/BaseScene.h>

struct FuncBullet
{
	bool operator() (ActQueT& actQue, std::vector<sharedObj>& objList);
};

