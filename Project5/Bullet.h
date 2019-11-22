#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID,Vector2Dbl pos);
	void Update(void) override;
	~Bullet();
private:
	bool init();
};

