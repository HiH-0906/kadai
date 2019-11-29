#pragma once
#include <scene/BaseScene.h>

struct FuncBullet
{
	bool operator() (ActQueT& actQue, std::vector<sharedObj>& objList);
private:
	static std::map<UNIT_ID, int> _MaxCount;									// ’e”­ËÅ‘å”
};

