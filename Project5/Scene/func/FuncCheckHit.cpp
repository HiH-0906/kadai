#include "FuncCheckHit.h"
#include <cmath>

bool FuncCheckHit::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::ENEMY : UNIT_ID::PLAYER);
	
	for (auto List : objList)
	{
		if ((*List).unitID() == tmpID)
		{
			_lenght = abs(actQue.second.pos() - (*List).pos());									// 弾と敵との距離 
			_lenght2.x = abs((actQue.second.size().y - (*List).size().x)/2.0);					// 弾と敵とのsize合計
			_lenght2.y = abs((actQue.second.size().x - (*List).size().y)/2.0);
			// 敵と弾との距離がｻｲｽﾞ合計より近いなら当たっている判定
			if (std::sqrt(_lenght.x*_lenght.x + _lenght.y*_lenght.y) < std::sqrt(_lenght2.x*_lenght2.x + _lenght2.y*_lenght2.y)&&(*List).isAlive())
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
