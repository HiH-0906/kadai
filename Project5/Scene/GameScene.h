#pragma once
#include <vector>
#include "BaseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unipueBase Update(unipueBase own) override final;
private:
	std::vector<Obj*>obj;
};

