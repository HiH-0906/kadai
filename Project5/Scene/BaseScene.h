#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;											// ｸﾗｽのﾌﾟﾛﾄﾀｲﾌﾟ宣言

// ｱｸｼｮﾝ種別管理
enum class ACT_QUE
{
	NON,													// 無し 万が一0の値が来た時に何もしないよう
	SHOT,													// 弾
	CHECK_HIT												// 当たり判定
};

using unipueBase = std::unique_ptr<BaseScene>;
//						ｱｸｼｮﾝ種別	objへの参照
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;			// どのｼｰﾝにもあるので純粋仮想
	virtual void RunActQue(std::vector<ActQueT> actList);	// 必要ないｼｰﾝもあるので仮想
};

