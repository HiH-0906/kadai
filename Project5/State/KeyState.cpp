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
	FILE* fp = nullptr;
	if (fopen_s(&fp, "data/key.dat", "rb") != 0)
	{
		// ｷｰｺﾝﾌｨｸﾞﾃﾞｰﾀをｺﾋﾟｰ
		_keyCon = _keyConDef;
	}
	else
	{
		// 書き込む前に場所を確保
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		// 読み込みﾃﾞｰﾀを変数へ書き込み
		fread(_keyCon.data(),
			sizeof(_keyCon[0]),
			static_cast<size_t>(end(INPUT_ID())),
			fp);
		// ﾌｧｲﾙを閉じる
		fclose(fp);
	}

	// F1ｷｰのﾄﾘｶﾞｰ処理用
	_modeKeyOld = 1;

	// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀへ代入 明示的に名前空間を書かないとﾀﾞﾒ
	func = &KeyState::RefKeyData;
	_configID = INPUT_ID::LEFT;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	// 1ﾌﾚｰﾑ前ｷｰ情報格納
	SetOld();
	// F1ｷｰOld更新
	_modeKeyOld = _buf[KEY_INPUT_F1];
	// 全ｷｰの押下情報取得
	GetHitKeyStateAll(_buf);
	// 関数呼び出し 優先度の問題で()で囲む
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// ﾃﾞｰﾀの書き込み
	for (auto id : INPUT_ID())
	{
		state(id,_buf[_keyCon[static_cast<size_t>(id)]]);
	}
	// F1ｷｰで切り替え
	if (_buf[KEY_INPUT_F1] && !_modeKeyOld)
	{
		// ﾒﾝﾊﾞ関数ﾎﾟｲﾝﾀの切り替え
		func = &KeyState::SetKeyConfig;
		TREACE("ｷｰｺﾝﾌｨｸﾞ開始だよー\n");
		// 設定用IDのﾘｾｯﾄ
		_configID = INPUT_ID::LEFT;
		TREACE("次%d/%d番目のｷｰだよー\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));
	}
}

void KeyState::SetKeyConfig(void)
{
	// 0ｸﾘｱ
	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	auto CheckKey = [&](int id) {
		// 既に入力しているところまでのfor文
		for (auto ckId = begin(INPUT_ID()); ckId < _configID; ++ckId)
		{
			// 被っているかﾁｪｯｸ
			if (_keyCon[static_cast<int>(ckId)] == id)
			{
				return false;
			}
		}
		return true;
	};

	// 全ｷｰﾁｪｯｸ
	for (int id = 0; id < sizeof(_buf); id++)
	{
		// 被ってないかﾁｪｯｸ
		if (!CheckKey(id))
		{
			// 被っていたらcontinue
			continue;
		}
		// 押されているｷｰ探し
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			// ｷｰの設定
			_keyCon[static_cast<int>(_configID)] = id;
			// 前演算じゃないとなんのｵｰﾊﾞｰﾛｰﾄﾞかわからないのでNG
			++_configID;
			TREACE("%dを設定したよー\n", id);
			// 全部のｷｰの設定が終わっていたなら切り替え
			if (_configID == end(_configID))
			{
				// ｷｰ変更後に書き込み
				FILE* fp = nullptr;
				if (fopen_s(&fp, "data/key.dat", "wb") == 0)
				{
					// 書き込み
					fwrite(_keyCon.data(),
						sizeof(_keyCon[0]),
						_keyCon.size(),
						fp
					);
					// ﾌｧｲﾙを閉じる
					fclose(fp);
				}
				else
				{
					// ﾌｧｲﾙが存在しなかったらAST
					AST();
				}
				TREACE("ｷｰｺﾝﾌｨｸﾞ終了だよー\n");
				// ﾒﾝﾊﾞ関数ﾎﾟｲﾝﾀの変更
				func = &KeyState::RefKeyData;
				break;
			}
			TREACE("次%d/%d番目のｷｰだよー\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));
		}
	}
}
