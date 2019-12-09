#include "FuncShake.h"
#include <GameScene.h>

bool FuncShake::operator()(ActQueT & actQue, void* scene)
{
	((GameScene*)scene)->_shakeCount = 20;
	return false;
}
