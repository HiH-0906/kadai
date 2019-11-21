#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(Vector2Dbl pos);
	void Update(void) override;
	~Bullet();
private:
	void init();
};

