#pragma once

#include <common/Vector2.h>

class EnemyMove
{

public:
	EnemyMove(Vector2Dbl& pos);		// ����͂킩��₷�����邽�߂ɎQ�ƂŎ󂯎�� �{����GetSet������Ƃ���
	~EnemyMove();
	void Update(void);				// 
private:
	Vector2Dbl& _pos;					// ���������а��pos�̏ꏊ�ۑ�
};

