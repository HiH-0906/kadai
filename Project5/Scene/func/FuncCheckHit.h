#pragma once
#include <scene/BaseScene.h>

struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	Vector2Dbl _lenght;				// ΞΫ¨―mΜ£
	Vector2Dbl _hitLenght;			// ΞΫ¨―mΜhit»θ£
};

