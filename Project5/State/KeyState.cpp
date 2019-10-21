#include <DxLib.h>
#include "KeyState.h"



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
	GetHitKeyStateAll(_buf);
	(this->*func)();			// 呼び出し
}

void KeyState::RefKeyData(void)
{
}

void KeyState::SetKeyConfig(void)
{
}
