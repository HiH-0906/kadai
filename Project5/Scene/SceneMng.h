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
	IMAGE,					// �Ұ��
	X,						// X���W
	Y,						// Y���W
	RAD,					// �p�x
	ZORDER,					// ڲ԰���`�揇 �����̒Ⴂ�ق����� ���������̏ꍇ�o�^��
	LAYER,					// �ǂ���ڲ԰�� ID���������ق������ɕ`��
	DRAW_MODE,				// �`��Ӱ��
	DRAW_NUM				// �`��Ӱ�ނɓn���l
};



//							image  x		y	��]�p	zOrder ڲ԰ �`��Ӱ�� �`��Ӱ�ނɓn���l
using DrawQueT = std::tuple<int, double, double, double,int,LAYER,int,int>;

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
	bool AddActQue(ActQueT aQue);				// ����ݗp���

	const Vector2 ScreenSize;					// ��ذݻ��� reedonly
	const Vector2 ScreenCenter;					// ��ذ݂̒��S reedonly
	const Vector2 GameScreenSize;				// �ްѽ�ذݻ��� reedonly
	const Vector2 GameScreenOffset;				// �ްѽ�ذݵ̾�� reedonly
	int fCnt;									// �ڰѐ�����
private:
	static SceneMng* sInstance;					// �߲��

	unipueBase _activeScene;					// �ư��߲��

	void Draw(void);							// �`��

	int _layerGID;								// �`��p��ذ�

	std::vector<DrawQueT> _drawList;			// �`��p���
	std::vector<ActQueT> _actList;				// ����ݗp���

	SceneMng();									// �ݽ�׸�
	~SceneMng();								// �޽�׸�

	bool SysInit(void);							// ���ѲƯ�
};

