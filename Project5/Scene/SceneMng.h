#pragma once
#include <memory>
#include <vector>
#include <map>
#include <tuple>
#include <common/Vector2.h>
#include "BaseScene.h"


#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,					// ²Ò°¼Ş
	X,						// XÀ•W
	Y,						// YÀ•W
	RAD,					// Šp“x
	ZORDER,					// Ú²Ô°“à•`‰æ‡ ”š‚Ì’á‚¢‚Ù‚¤‚ªæ “¯‚¶”š‚Ìê‡“o˜^‡
	LAYER					// ‚Ç‚±‚ÌÚ²Ô°‚© ID‚ª¬‚³‚¢‚Ù‚¤‚ªŒã‚ë‚É•`‰æ
};

enum class LAYER
{
	BG,						// ”wŒi
	CHAR,					// ·¬×
	UI,						// UI
	MAX
};


//							image  x		y	‰ñ“]Šp	zOrder Ú²Ô°
using DrawQueT = std::tuple<int, double, double, double,int,LAYER>;

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

	const Vector2 ScreenSize;					// ½¸Ø°İ»²½Ş reedonly
private:
	static SceneMng* sInstance;					// Îß²İÀ

	unipueBase _activeScene;					// ÕÆ°¸Îß²İÀ

	void Draw(void);							// •`‰æ

	std::map<LAYER, int> _screenID;				// •`‰æ—p½¸Ø°İ•Û‘¶—p•Ï”

	std::vector<DrawQueT> _drawList;			// •`‰æ—p·­°

	SceneMng();									// ºİ½Ä×¸À
	~SceneMng();								// ÃŞ½Ä×¸À

	bool SysInit(void);							// ¼½ÃÑ²Æ¯Ä
};

