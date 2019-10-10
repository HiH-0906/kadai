#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include <common/Vector2.h>
#include "BaseScene.h"

using DrawQueT = std::tuple<int, int, int>;

#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y
};

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

	bool AddDrawQue(DrawQueT dQue);							// ·­°‚ğ—­‚ß‚é

	const Vector2 ScreenSize;					// ½¸Ø°İ»²½Ş reedonly
private:
	static SceneMng* sInstance;					// Îß²İÀ

	unipueBase _activeScene;					// ÕÆ°¸Îß²İÀ

	void Draw(void);							// •`‰æ

	std::vector<DrawQueT> _drawList;			// •`‰æ—p·­°
	SceneMng();									// ºİ½Ä×¸À
	~SceneMng();								// ÃŞ½Ä×¸À
	bool SysInit(void);							// ¼½ÃÑ²Æ¯Ä
};

