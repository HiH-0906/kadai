#pragma once
#include <memory>

class BaseScene;											// �׽���������ߐ錾

using unipueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;
};

