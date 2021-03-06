#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>

class Player :
	public Obj
{
public:
	Player(Vector2Dbl pos, Vector2Dbl size);		// ﾌﾟﾚｲﾔｰ配置引数付きｺﾝｽﾄﾗｸﾀｰ
	void Update(sharedObj plObj) override final;
	~Player();
	void Draw(void)override;
private:
	int _glowID;
	void Init(void);
	std::shared_ptr<InputState>_input;				// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言
};

