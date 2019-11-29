#include "FuncCheckHit.h"
#include <cmath>

bool FuncCheckHit::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::ENEMY : UNIT_ID::PLAYER);
	
	for (auto List : objList)
	{
		if ((*List).unitID() == tmpID)
		{
			_lenght = abs(actQue.second.pos() - (*List).pos());										// 弾と敵との距離 
			_hitLenght = abs((actQue.second.size() - (*List).size())/2.0);							// 弾と敵とのhit距離
			// 敵と弾との距離がｻｲｽﾞ合計より近いなら当たっている判定
			if (std::sqrt(_lenght.x*_lenght.x + _lenght.y*_lenght.y) < std::sqrt(_hitLenght.x*_hitLenght.x + _hitLenght.y*_hitLenght.y)&&(*List).isAlive())
			{
				// 当たっていたら両ｵﾌﾞｼﾞｪｸﾄ爆破
				actQue.second.SetAlive(false);
				(*List).SetAlive(false);
				return true;
			}
		}
	}
	return false;
}
