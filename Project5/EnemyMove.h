#pragma once

#include <Vector2.h>
#include <vector>

#define ENEMY_MAX 50

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR,
	SCALE
};

using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2Dbl>>;		// 行動目的地管理用型

class EnemyMove
{

public:
	EnemyMove(Vector2Dbl& pos,double& rad,int& speed);					// 今回はわかりやすくするために参照で受け取る 本当はGetSetがあるといい
	~EnemyMove();
	void Update(void);										// 更新
	bool SetMoveState(MoveState& state, bool newFlag);		// 行動ｾｯﾄ関数
private:
	void SetMovePrg(void);									// 行動切り替え

	void(EnemyMove::*_move)(void);							// ﾒﾝﾊﾞ関数ﾎﾟｲﾝﾀ move系
	void MoveSigmoid(void);									// ｼｸﾞﾓｲﾄﾞ
	void MoveSpiral(void);									// 魔法陣ｸﾙｸﾙ
	void PitIn(void);										// ﾋﾟｯﾄｲﾝ
	void Wait(void);										// 待機 aim[_aimCnt].secondの値まで回る
	void MoveLR(void);										// 左右
	void MoveScale(void);									// 拡大縮小

	int count;												// wait用ｶｳﾝﾄ

	MoveState _aim;											// 目標地点
	unsigned int _aimCnt;									// どの目的地かｶｳﾝﾄ

	Vector2Dbl _startPos;									// 各移動関数のｽﾀｰﾄ地点
	Vector2Dbl _endPos;										// 各移動関数のｴﾝﾄﾞ地点

	Vector2Dbl& _pos;										// もらったｴﾈﾐｰのposの場所保存
	Vector2Dbl _lenght;										// 距離
	Vector2Dbl _oneMoveVec;									// 1ﾌﾚｰﾑでの移送距離
	Vector2Dbl _oldPos;										// 角度求める用
	Vector2Dbl _center;										// 敵中心
	Vector2Dbl _range;										// 中心からの距離
	Vector2Dbl _nextRange;									// 拡大縮小後の距離
	Vector2Dbl _oneMoveRange;								// 1ﾌﾚｰﾑに移動する距離
	static int InCount;										// 敵ﾋﾟｯﾄｲﾝｶｳﾝﾄ
	double radius;											// 半径
	double& _rad;											// 角度
	double _tmpRad;											// 回転用角度
	double _cntRad;											// 今どれだけ回転したか
	double _moveRad;										// 1ﾌﾚｰﾑに回る角度
	double _moveGain;										// 移動管理
};

