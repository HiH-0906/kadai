#include <DxLib.h>
#include "KeyState.h"
#include <_DebugConOut.h>



KeyState::KeyState()
{
	// あらかじめ数がわかっているのでﾒﾓﾘ確保 
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));		// ｴﾝﾄﾞを使ってINPUT_IDの終端を取得
	
	// ﾃﾞﾌｫﾙﾄｷｰｺﾝﾌｨｸﾞをｾｯﾄ
	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);
	
	// ﾌｧｲﾙ読み込み箇所

	// ｷｰｺﾝﾌｨｸﾞﾃﾞｰﾀをｺﾋﾟｰ
	_keyCon = _keyConDef;

	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀへ代入 明示的に名前空間を書かないとﾀﾞﾒ
	func = &KeyState::RefKeyData;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	// 1ﾌﾚｰﾑ前ｷｰ情報格納
	SetOld();
	// 全ｷｰの押下情報取得
	GetHitKeyStateAll(_buf);
	// 関数呼び出し
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// ﾃﾞｰﾀの書き込み
	int i = 0;
	for (auto id : INPUT_ID())
	{
		state(id,_buf[_keyCon[i]]);
		i++;
	}
	if (_buf[KEY_INPUT_F1] == 1)
	{
		func = &KeyState::SetKeyConfig;
		TREACE("\nSetKeyConfigだよー")
	}
}

void KeyState::SetKeyConfig(void)
{
	for (int i = 0; i < 256; i++)
	{
		if (_buf[i])
		{

		}
	}
}
