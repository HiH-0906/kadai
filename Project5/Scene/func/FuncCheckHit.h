#pragma once
#include <scene/BaseScene.h>

struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	Vector2Dbl _lenght;				// �Ώە����m�̋���
	Vector2Dbl _hitLenght;			// �Ώە����m��hit���苗��
};

