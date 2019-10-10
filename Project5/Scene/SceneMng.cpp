#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);			// �`���ݒ�
	ClsDrawScreen();

	// �����ɗ��܂��Ă���Que��`�悷��
	//	�͈�for��
	for (auto dQue:_drawList)
	{
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::Y)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
			true);
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
SceneMng::SceneMng():ScreenSize{800,600}
{
}


SceneMng::~SceneMng()
{
}

void SceneMng::Ran(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();			// ؽĂ̍폜
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();						// �`��
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

	return false;
}
