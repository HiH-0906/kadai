#include "FuncBullet.h"
#include <algorithm>
#include <Bullet.h>
#include <GameScene.h>

std::map<UNIT_ID, int> FuncBullet::_MaxCount = { {UNIT_ID::PL_BULLET,2},{UNIT_ID::EN_BULLET,2} };

bool FuncBullet::operator()(ActQueT& actQue, void* scene)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EN_BULLET);
	// ’e‚Ì²Ý½ÀÝ½
	if (_MaxCount[tmpID] > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj& obj) {return (*obj).unitID() == tmpID; }))
	{
		((GameScene*)scene)->_objList.emplace_back(
			new Bullet(tmpID, actQue.second.pos())
		);
		return true;
	}
	return false;
}

