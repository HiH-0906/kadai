#include "FuncCheckHit.h"
#include <GameScene.h>

bool FuncCheckHit::operator()(ActQueT & actQue, void* scene)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::ENEMY : UNIT_ID::PLAYER);
	
	for (auto List : ((GameScene*)scene)->_objList)
	{
		if ((*List).unitID() == tmpID)
		{
			_lenght = abs(actQue.second.pos() - (*List).pos());										// ’e‚Æ“G‚Æ‚Ì‹——£ 
			_hitLenght = abs((actQue.second.size() - (*List).size())/2.0);							// ’e‚Æ“G‚Æ‚Ìhit‹——£
			// “G‚Æ’e‚Æ‚Ì‹——£‚ª»²½Ş‡Œv‚æ‚è‹ß‚¢‚È‚ç“–‚½‚Á‚Ä‚¢‚é”»’è
			if (std::sqrt(_lenght.x*_lenght.x + _lenght.y*_lenght.y) < std::sqrt(_hitLenght.x*_hitLenght.x + _hitLenght.y*_hitLenght.y)&&(*List).isAlive())
			{
				// “–‚½‚Á‚Ä‚¢‚½‚ç—¼µÌŞ¼Şª¸Ä”š”j
				actQue.second.SetAlive(false);
				(*List).SetAlive(false);
				return true;
			}
		}
	}
	return false;
}
