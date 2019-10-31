#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size);				// ﾌﾟﾚｲﾔｰ配置引数付きｺﾝｽﾄﾗｸﾀｰ
	void Update(void) override;
	~Player();
private:
	void Init(void);
	std::shared_ptr<InputState>_input;				// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言
};

