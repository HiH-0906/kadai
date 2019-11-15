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
	IMAGE,					// �Ұ��
	X,						// X���W
	Y,						// Y���W
	RAD,					// �p�x
	ZORDER,					// ڲ԰���`�揇 �����̒Ⴂ�ق����� ���������̏ꍇ�o�^��
	LAYER					// �ǂ���ڲ԰�� ID���������ق������ɕ`��
};

enum class LAYER
{
	BG,						// �w�i
	CHAR,					// ���
	UI,						// UI
	MAX
};


//							image  x		y	��]�p	zOrder ڲ԰
using DrawQueT = std::tuple<int, double, double, double,int,LAYER>;

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

	bool AddDrawQue(DrawQueT dQue);				// ����𗭂߂�

	const Vector2 ScreenSize;					// ��ذݻ��� reedonly
private:
	static SceneMng* sInstance;					// �߲��

	unipueBase _activeScene;					// �ư��߲��

	void Draw(void);							// �`��

	std::map<LAYER, int> _screenID;				// �`��p��ذݕۑ��p�ϐ�

	std::vector<DrawQueT> _drawList;			// �`��p���

	SceneMng();									// �ݽ�׸�
	~SceneMng();								// �޽�׸�

	bool SysInit(void);							// ���ѲƯ�
};

