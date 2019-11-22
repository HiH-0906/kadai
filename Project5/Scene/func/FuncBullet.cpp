#include "FuncBullet.h"
#include <Bullet.h>

bool FuncBullet::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EN_BULLET);
	// ’e‚Ì²Ý½ÀÝ½
	objList.emplace_back(
		new Bullet(tmpID, actQue.second.pos())
	);
	return true;
}
