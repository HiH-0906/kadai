#pragma once
#include <memory>

class BaseScene;											// ¸×½‚ÌÌßÛÄÀ²ÌßéŒ¾

using unipueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;
};

