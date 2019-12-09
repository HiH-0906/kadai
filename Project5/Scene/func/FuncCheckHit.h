#pragma once
#include <scene/BaseScene.h>

struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	Vector2Dbl _lenght;				// ‘ÎÛ•¨“¯m‚Ì‹——£
	Vector2Dbl _hitLenght;			// ‘ÎÛ•¨“¯m‚Ìhit”»’è‹——£
};

