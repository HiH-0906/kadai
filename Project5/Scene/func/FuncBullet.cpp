#include "FuncBullet.h"
#include <algorithm>
#include <Bullet.h>

std::map<UNIT_ID, int> FuncBullet::_MaxCount = { {UNIT_ID::PL_BULLET,2},{UNIT_ID::EN_BULLET,2} };

bool FuncBullet::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EN_BULLET);
	// ’e‚Ì²Ý½ÀÝ½
	if (_MaxCount[tmpID] > std::count_if(objList.begin(), objList.end(), [&](sharedObj& obj) {return (*obj).unitID() == tmpID; }))
	{
		objList.emplace_back(
			new Bullet(tmpID, actQue.second.pos())
		);
		return true;
	}
	return false;
}

