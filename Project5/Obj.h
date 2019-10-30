#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <common/Vector2.h>

enum class STATE
{
	NORMAL,		// 通常
	EX,			// 特殊
	DEATH,		// 爆発(死亡)
	MAX
};
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	// 画像とｱﾆﾒｰｼｮﾝｶｳﾝﾄﾃﾞｰﾀ
using sharedObj = std::shared_ptr<Obj>;							// ｼｪｱﾄﾞﾎﾟｲﾝﾀ

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;								// 純粋仮想関数
	void Draw(void);											// ｱﾆﾒｰｼｮﾝありの描画
	void Draw(int id);											// ｱﾆﾒｰｼｮﾝなしの描画
	virtual ~Obj();

	bool state(const STATE state);								// ｱﾆﾒｰｼｮﾝｷｰの追加
	const STATE state(void) const;								// 現在のｱﾆﾒｰｼｮﾝｷｰの取得

	bool SetAnim(const STATE state, AnimVector& data);			// ﾃﾞｰﾀ格納用関数
	bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// 生きているか取得
	bool isDead(void) { return _dead; }							// 死んでいるか取得
	bool isAnimEnd(void);										// ｱﾆﾒｰｼｮﾝ状態取得	trueで終わっている
private:
	std::map<STATE, AnimVector> _animMap;						// ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ管理変数
	STATE _state;												// 状態管理用
	unsigned int _animFrame;									// 現在ｱﾆﾒｰｼｮﾝ
	unsigned int _animCount;									// ｶｳﾝﾄ

protected:
	bool DestroyProc(void);										// 生き死にとｱﾆﾒｰｼｮﾝ終了確認関数
	bool _alive;												// 生きているか
	bool _dead;													// 死んでいるか
	Vector2Dbl _pos;											// 座標
	Vector2Int _size;											// 当たり判定用ｻｲｽﾞ
};

