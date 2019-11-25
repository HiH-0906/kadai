#include "FuncCheckHit.h"
#include <cmath>

bool FuncCheckHit::operator()(ActQueT & actQue, std::vector<sharedObj>& objList)
{
	UNIT_ID tmpID = (actQue.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::ENEMY : UNIT_ID::PLAYER);
	
	for (auto List : objList)
	{
		if ((*List).unitID() == tmpID)
		{
			_lenght = abs(actQue.second.pos() - (*List).pos());									// �e�ƓG�Ƃ̋��� 
			_lenght2.x = abs((actQue.second.size().y - (*List).size().x)/2.0);					// �e�ƓG�Ƃ�size���v
			_lenght2.y = abs((actQue.second.size().x - (*List).size().y)/2.0);
			// �G�ƒe�Ƃ̋��������ލ��v���߂��Ȃ瓖�����Ă��锻��
			if (std::sqrt(_lenght.x*_lenght.x + _lenght.y*_lenght.y) < std::sqrt(_lenght2.x*_lenght2.x + _lenght2.y*_lenght2.y)&&(*List).isAlive())
			{
				// �������Ă����痼��޼ު�Ĕ��j
				actQue.second.SetAlive(false);
				(*List).SetAlive(false);
				return true;
			}
		}
	}
	return false;
}
