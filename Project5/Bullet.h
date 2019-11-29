#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet(UNIT_ID unitID,Vector2Dbl pos);
	void Update(sharedObj plObj) override;
	~Bullet();
private:
	bool init();
};

