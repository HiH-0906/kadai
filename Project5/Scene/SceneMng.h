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
	IMAGE,					// ²Ò°¼Ş
	X,						// XÀ•W
	Y,						// YÀ•W
	RAD,					// Šp“x
	ZORDER,					// Ú²Ô°“à•`‰æ‡ ”š‚Ì’á‚¢‚Ù‚¤‚ªæ “¯‚¶”š‚Ìê‡“o˜^‡
	LAYER,					// ‚Ç‚±‚ÌÚ²Ô°‚© ID‚ª¬‚³‚¢‚Ù‚¤‚ª‰œ‚É•`‰æ
	DRAW_MODE,				// •`‰æÓ°ÄŞ
	DRAW_NUM				// •`‰æÓ°ÄŞ‚É“n‚·’l
};



//							image  x		y	‰ñ“]Šp	zOrder Ú²Ô° •`‰æÓ°ÄŞ •`‰æÓ°ÄŞ‚É“n‚·’l
using DrawQueT = std::tuple<int, double, double, double,int,LAYER,int,int>;

class SceneMng
{
public:
	static SceneMng &GetInstance(void)			// ºİ½Ä×¸À°ŒÄ‚Ño‚µŠÖ”
	{
		Create();								// static‚È‚à‚Ì‚µ‚©G‚ê‚È‚¢
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)				// ‚·‚Å‚É‚ ‚é‚©”»’f
		{
			sInstance = new SceneMng();			// ì¬
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)				// ‚ ‚é‚©”»’è
		{
			delete sInstance;					// íœ
		}
		sInstance = nullptr;
	}


	void Ran(void);								// Ù°Ìß

	bool AddDrawQue(DrawQueT dQue);				// ·­°‚ğ—­‚ß‚é
	bool AddActQue(ActQueT aQue);				// ±¸¼®İ—p·­°

	const Vector2 ScreenSize;					// ½¸Ø°İ»²½Ş reedonly
	const Vector2 ScreenCenter;					// ½¸Ø°İ‚Ì’†S reedonly
	const Vector2 GameScreenSize;				// ¹Ş°Ñ½¸Ø°İ»²½Ş reedonly
	const Vector2 GameScreenOffset;				// ¹Ş°Ñ½¸Ø°İµÌ¾¯Ä reedonly
	int fCnt;									// ÌÚ°Ñ”¶³İÀ
private:
	static SceneMng* sInstance;					// Îß²İÀ

	unipueBase _activeScene;					// ÕÆ°¸Îß²İÀ

	void Draw(void);							// •`‰æ

	int _layerGID;								// •`‰æ—p½¸Ø°İ

	std::vector<DrawQueT> _drawList;			// •`‰æ—p·­°
	std::vector<ActQueT> _actList;				// ±¸¼®İ—p·­°

	SceneMng();									// ºİ½Ä×¸À
	~SceneMng();								// ÃŞ½Ä×¸À

	bool SysInit(void);							// ¼½ÃÑ²Æ¯Ä
};

