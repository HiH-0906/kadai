#pragma once

#include <common/Vector2.h>

class EnemyMove
{

public:
	EnemyMove(Vector2Template<int>& pos);		// ����͂킩��₷�����邽�߂ɎQ�ƂŎ󂯎�� �{����GetSet������Ƃ���
	~EnemyMove();
	void Update(void);				// 
private:
	Vector2Template<int>& _pos;					// ���������а��pos�̏ꏊ�ۑ�
};

