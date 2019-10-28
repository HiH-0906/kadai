#include "InputState.h"
#include <_DebugConOut.h>

InputState::InputState()
{
	// 初期値ｾｯﾄ
	for (auto id:INPUT_ID())
	{
		_state.try_emplace(id, KeyPair{ 0,1 });
	}
}


InputState::~InputState()
{
}

const KeyMap & InputState::state()const
{
	// そのまま返す
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const
{
	// 例外の時の返り値用ﾀﾞﾐｰｷｰ
	static KeyPair defData = { 0,0 };
	try
	{
		// とりあえずtry
		return _state.at(id);
	}
	catch (...)					// どんなｴﾗｰか指定 今回は全部　...は1個以上の複数の場合
	{
		// ｴﾗｰが起きたらやる処理を描く
		AST();
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	// idが存在しているかﾁｪｯｸ
	if (_state.find(id) != _state.end())
	{
		// firstがnew
		_state[id].first = data;
		return true;
	}
	// 存在しなかったら何もしない
	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			// もし無かったら作成
			AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}



