#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	virtual unipueBase Update(unipueBase own) override final;
};

