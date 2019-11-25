#pragma once
#include <scene/BaseScene.h>

struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, std::vector<sharedObj>& objList);
private:
	Vector2Dbl _lenght;
	Vector2Dbl _lenght2;
};

