#pragma once

#include <common/Vector2.h>

class EnemyMove
{

public:
	EnemyMove(Vector2Template<int>& pos);		// 今回はわかりやすくするために参照で受け取る 本当はGetSetがあるといい
	~EnemyMove();
	void Update(void);				// 
private:
	Vector2Template<int>& _pos;					// もらったｴﾈﾐｰのposの場所保存
};

