#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>

class Player :
	public Obj
{
public:
	Player(Vector2Dbl pos, Vector2Dbl size);		// ÌßÚ²Ô°”z’uˆø”•t‚«ºİ½Ä×¸À°
	void Update(sharedObj plObj) override final;
	~Player();
private:
	void Init(void);
	std::shared_ptr<InputState>_input;				// ²İÌß¯Ä‚ÌÕÆ°¸Îß²İÀéŒ¾
};

