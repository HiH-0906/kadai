#pragma once

#include <common/Vector2.h>

class EnemyMove
{

public:
	EnemyMove(Vector2Dbl& pos);		// 今回はわかりやすくするために参照で受け取る 本当はGetSetがあるといい
	~EnemyMove();
	void Update(void);				// 
private:
	Vector2Dbl& _pos;					// もらったｴﾈﾐｰのposの場所保存
};

