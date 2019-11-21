#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 }, ScreenCenter{ ScreenSize / 2 }, GameScreenSize{ 500,390 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }	// ��ذ݂̊֌W�̍��W������
{
	fCnt = 0;
}


SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();
	// _drawList�������ɿ��
	std::sort(_drawList.begin(),_drawList.end(),
		// ��ׂ邩����
		[](const DrawQueT& dQueA, const DrawQueT& dQueB)
	{
		//// layer���Ⴄ�Ȃ�ڲ԰���ŕ��ёւ�
		//if (std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) != std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB))
		//{
		//	// layer�Ŕ�ׂ�
		//	return std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB);
		//}
		//else
		//{
		//	// _zOrder�Ŕ�ׂ�
		//	return std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB);
		//}

		// ��̓��e��1�s�� ����Ă��邱�Ƃ͑S������
		return
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));

	});

	for (auto id : LAYER())
	{
		SetDrawScreen(_screenID[id]);
		ClsDrawScreen();
	}

	// �����ɗ��܂��Ă���Que��`�悷��
	//	�͈�for��
	for (auto dQue:_drawList)
	{
		// tuple�̏����΂炵����ɕۑ�����ϐ���`
		double x, y,rad;
		int id;
		LAYER layer;

		// tuple���΂�΂��
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;
		// ���݂̕`�潸ذ݂ƈႦ�ΕύX
		if (_screenID[layer] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer]);
		}
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	// �eڲ԰��`��
	for (auto layer : LAYER())
	{
		if (layer == LAYER::CHAR)
		{
			DrawRotaGraph(ScreenCenter.x, ScreenCenter.y ,1.0, 0, _screenID[layer], true);
		}
		else
		{
			DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _screenID[layer], true);
		}
	}
	//// iteratorfor��
	//for (auto dQue = _drawList.begin(); dQue != _drawList.end; dQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}
	//// ���܂ł�for��
	//for (int i = 0; i < _drawList.size(); i++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[i]),
	//		true);
	//}

	ScreenFlip();
}


void SceneMng::Ran(void)
{
	SysInit();
	// �ư��߲���쐬
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();			// ؽĂ̍폜
		AddDrawQue({IMAGE_ID("�g")[0],400.0,300.0,0.0,0,LAYER::UI});
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		(*_activeScene).RunActQue(std::move(_actList));
		Draw();						// �`��
		fCnt++;
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// �摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}
	// Que��ǉ�
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::AddActQue(ActQueT aQue)
{
	// ����݌n�̷����ؽĂւ̒ǉ�
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetWindowText("1916035_���{ ��P �ۑ�5");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	// 800*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);							// true:Window flse:�ٽ�ذ�

	if (DxLib_Init() == -1)							// DXײ���؂̏������ݒ�
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);					// �`�ʐ���ޯ��ޯ̧�ɐݒ�
	
	for (auto id : LAYER())
	{
		// ��ذ݂̍쐬
		_screenID.try_emplace(id, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	}

	_dbgSetup(255);

	lpImageMng.GetID("�g","image/frame.png");

	return false;
}
