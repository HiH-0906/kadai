#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <common/Vector2.h>

#define PI 3.141592

enum class STATE
{
	NORMAL,		// 通常
	EX,			// 特殊
	DEATH,		// 爆発(死亡)
	MAX
};

enum class UNIT_ID
{
	NON,		// 無し
	PLAYER,		// 自機
	ENEMY,		// 敵
	PL_BULLET,	// 自機弾
	EN_BULLET	// 敵弾
};
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	// 画像とｱﾆﾒｰｼｮﾝｶｳﾝﾄﾃﾞｰﾀ
using sharedObj = std::shared_ptr<Obj>;							// ｼｪｱﾄﾞﾎﾟｲﾝﾀ

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj) = 0;					// 純粋仮想関数
	virtual void Draw(void);									// ｱﾆﾒｰｼｮﾝありの描画
	void Draw(int id);											// ｱﾆﾒｰｼｮﾝなしの描画
	virtual ~Obj();

	bool state(const STATE state);								// ｱﾆﾒｰｼｮﾝｷｰの追加
	const STATE state(void) const;								// 現在のｱﾆﾒｰｼｮﾝｷｰの取得

	const Vector2Dbl pos(void);									// _posGetﾀﾞｾﾞ!
	const Vector2Dbl size(void);								// _sizeGetﾀﾞｾﾞ!
	const UNIT_ID unitID(void);									// _unitIDGetﾀﾞｾﾞ!

	bool SetAnim(const STATE state, AnimVector& data);			// ﾃﾞｰﾀ格納用関数
	virtual bool SetAlive(bool alive);							// 生きてるﾌﾗｸﾞ変更
	virtual bool exFlag(bool flag);								// 継承先で使い道が違うのでとりあえず仮想関数
	const bool exFlag(void)const;											// FlagのGet
	bool isAlive(void) { return _alive; }						// 生きているか取得
	bool isDead(void) { return _dead; }							// 死んでいるか取得
	bool isAnimEnd(void);										// ｱﾆﾒｰｼｮﾝ状態取得	trueで終わっている
private:
	unsigned int _animCount;									// ｶｳﾝﾄ

protected:
	bool DestroyProc(void);										// 生き死にとｱﾆﾒｰｼｮﾝ終了確認関数
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2Dbl _pos;											// 座標
	Vector2Dbl _size;											// 当たり判定用ｻｲｽﾞ
	UNIT_ID _unitID;											// 識別ﾀｸﾞ
	bool _exFlag;												// 外部からのｱｸｾｽ用Flag
	int _speed;													// ｽﾋﾟｰﾄﾞ
	double _rad;												// 角度
	int _zOrder;												// 描画優先度
	std::map<STATE, AnimVector> _animMap;						// ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ管理変数
	STATE _state;												// 状態管理用
	unsigned int _animFrame;									// 現在ｱﾆﾒｰｼｮﾝ
};

