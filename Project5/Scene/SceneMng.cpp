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

		// layer��zOdar��r
		return
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));

	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	LAYER drawLayer  = begin(LAYER());
	int blendMode    = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	SetDrawScreen(_layerGID);							// �`��p��ذ݂ɕύX
	SetDrawBlendMode(blendMode, blendModeNum);		// �`��Ӱ�ޕύX
	ClsDrawScreen();

	// �����ɗ��܂��Ă���Que��`�悷��
	//	�͈�for��
	for (auto dQue:_drawList)
	{
		// tuple�̏����΂炵����ɕۑ�����ϐ���`
		double x, y,rad;
		int id;
		LAYER layer;

		// 1�O�̏��ۑ�
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tuple���΂�΂��
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;

		// ���o����Que�̓��e���O�܂ł�Layer���`��`�����Ⴄ�ꍇ��U�ޯ��ޯ̧�ɏ����o��
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGID�̓��e���ޯ��ޯ̧�ɕ`�悷��
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// ����Que�̂��߂ɏ��������Ĉꎞ�`���ɕύX
			SetDrawScreen(_layerGID);							// �`��p��ذ݂ɕύX
			SetDrawBlendMode(blendMode, blendModeNum);		// �`��Ӱ�ޕύX
			ClsDrawScreen();
		}
		// Que�̕`��
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	// for��������Ƃ��̍Ō��Que�`��
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);		// �`��Ӱ�ޕύX
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();
}


void SceneMng::Ran(void)
{
	SysInit();
	// �ư��߲���쐬
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();																				// ؽĂ̍폜
		AddDrawQue({ IMAGE_ID("�g")[0],400.0,300.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });			// �gQUE�o�^
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		(*_activeScene).RunActQue(std::move(_actList));													// Action���s
		Draw();																							// �`��
		fCnt++;																							// �ڰѶ���
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

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);					// 800*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);											// true:Window flse:�ٽ�ذ�

	if (DxLib_Init() == -1)											// DXײ���؂̏������ݒ�
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);									// �`�ʐ���ޯ��ޯ̧�ɐݒ�
	
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);		// �`��p��ذݍ쐬

	_dbgSetup(255);

	lpImageMng.GetID("�g", "image/frame.png");
	lpImageMng.GetID("��", "image/black.png");
	lpImageMng.GetID("��", "image/white.png");

	return false;
}
