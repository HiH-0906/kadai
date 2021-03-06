#pragma once
#include <memory>
#include <vector>
#include <map>
#include <tuple>
#include <Vector2.h>
#include "BaseScene.h"
#include "Layer.h"


#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,					// ｲﾒｰｼﾞ
	X,						// X座標
	Y,						// Y座標
	RAD,					// 角度
	ZORDER,					// ﾚｲﾔｰ内描画順 数字の低いほうが先 同じ数字の場合登録順
	LAYER,					// どこのﾚｲﾔｰか IDが小さいほうが奥に描画
	DRAW_MODE,				// 描画ﾓｰﾄﾞ
	DRAW_NUM				// 描画ﾓｰﾄﾞに渡す値
};



//							image  x		y	回転角	zOrder ﾚｲﾔｰ 描画ﾓｰﾄﾞ 描画ﾓｰﾄﾞに渡す値
using DrawQueT = std::tuple<int, double, double, double,int,LAYER,int,int>;

class SceneMng
{
public:
	static SceneMng &GetInstance(void)			// ｺﾝｽﾄﾗｸﾀｰ呼び出し関数
	{
		Create();								// staticなものしか触れない
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)				// すでにあるか判断
		{
			sInstance = new SceneMng();			// 作成
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)				// あるか判定
		{
			delete sInstance;					// 削除
		}
		sInstance = nullptr;
	}


	void Ran(void);								// ﾙｰﾌﾟ

	bool AddDrawQue(DrawQueT dQue);				// ｷｭｰを溜める
	bool AddActQue(ActQueT aQue);				// ｱｸｼｮﾝ用ｷｭｰ

	const Vector2 ScreenSize;					// ｽｸﾘｰﾝｻｲｽﾞ reedonly
	const Vector2 ScreenCenter;					// ｽｸﾘｰﾝの中心 reedonly
	const Vector2 GameScreenSize;				// ｹﾞｰﾑｽｸﾘｰﾝｻｲｽﾞ reedonly
	const Vector2 GameScreenOffset;				// ｹﾞｰﾑｽｸﾘｰﾝｵﾌｾｯﾄ reedonly
	int fCnt;									// ﾌﾚｰﾑ数ｶｳﾝﾀ
private:
	static SceneMng* sInstance;					// ﾎﾟｲﾝﾀ

	unipueBase _activeScene;					// ﾕﾆｰｸﾎﾟｲﾝﾀ

	void Draw(void);							// 描画

	int _layerGID;								// 描画用ｽｸﾘｰﾝ

	std::vector<DrawQueT> _drawList;			// 描画用ｷｭｰ
	std::vector<ActQueT> _actList;				// ｱｸｼｮﾝ用ｷｭｰ

	SceneMng();									// ｺﾝｽﾄﾗｸﾀ
	~SceneMng();								// ﾃﾞｽﾄﾗｸﾀ

	bool SysInit(void);							// ｼｽﾃﾑｲﾆｯﾄ
};

