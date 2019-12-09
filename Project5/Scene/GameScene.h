#pragma once
#include <vector>
#include <functional>
#include "BaseScene.h"
#include "Obj.h"

using funcAct = std::function<bool(ActQueT&, void*)>;						// 引数と返り値が同じものを放り込める

#define FORMATION 3															// 敵編隊隊員数
#define WAIT_TIME 50.0														// 編隊ごとの待ち時間
#define CHAR_SIZE_X 30														// 自機や敵のsize x
#define CHAR_SIZE_Y 32														// 自機や敵のsize y
#define ENEMY_OFFSET_X  (CHAR_SIZE_X*2.5)									// 敵ﾃﾞﾌｫﾙﾄ位置のx方向ｵﾌｾｯﾄ
#define ENEMY_OFFSET_Y  40.0												// 敵ﾃﾞﾌｫﾙﾄ位置のy方向ｵﾌｾｯﾄ

struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unipueBase Update(unipueBase own) override final;
private:
	friend FuncCheckHit;													// 友達
	friend FuncBullet;
	friend FuncShake;
	std::vector<sharedObj> _objList;										// ListではなくVector
	void RunActQue(std::vector<ActQueT> actList)override final;				// ActQueの実行
	void initFunc(void);													// funcQueへの関数ｵﾌﾞｼﾞｪｸﾄ代入
	std::map<ACT_QUE, funcAct> funcQue;										// 関数ｵﾌﾞｼﾞｪｸﾄ管理
	Vector2Dbl _enemyDefFomation;											// 敵ﾃﾞﾌｫﾙﾄ配置
	int _shakeCount;														// 画面が揺れるﾌﾚｰﾑ数
};

