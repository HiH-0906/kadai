#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;											// ¸×½‚ÌÌßÛÄÀ²ÌßéŒ¾

// ±¸¼®İí•ÊŠÇ—
enum class ACT_QUE
{
	NON,													// –³‚µ –œ‚ªˆê0‚Ì’l‚ª—ˆ‚½‚É‰½‚à‚µ‚È‚¢‚æ‚¤
	SHOT													// ’e
};

using unipueBase = std::unique_ptr<BaseScene>;
//						±¸¼®İí•Ê	obj‚Ö‚ÌQÆ
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;
	virtual void RunActQue(std::vector<ActQueT> actList);
};

