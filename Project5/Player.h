#pragma once
#include "Obj.h"
class Player :
	public Obj
{
public:
	Player();
	Player(Vector2 pos, Vector2 size);
	void Update(void) override;
	~Player();
private:
	void Init(void);
};

