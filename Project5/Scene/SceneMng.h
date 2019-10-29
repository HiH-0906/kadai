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
	static SceneMng &GetInstance(void)			// �ݽ�׸���Ăяo���֐�
	{
		Create();								// static�Ȃ��̂����G��Ȃ�
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)				// ���łɂ��邩���f
		{
			sInstance = new SceneMng();			// �쐬
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)				// ���邩����
		{
			delete sInstance;					// �폜
		}
		sInstance = nullptr;
	}


	void Ran(void);								// ٰ��

	bool AddDrawQue(DrawQueT dQue);							// ����𗭂߂�

	const Vector2Template<int> ScreenSize;					// ��ذݻ��� reedonly
private:
	static SceneMng* sInstance;					// �߲��

	unipueBase _activeScene;					// �ư��߲��

	void Draw(void);							// �`��

	std::vector<DrawQueT> _drawList;			// �`��p���
	SceneMng();									// �ݽ�׸�
	~SceneMng();								// �޽�׸�
	bool SysInit(void);							// ���ѲƯ�
};

