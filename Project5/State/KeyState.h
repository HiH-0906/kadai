#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;					// ｱｯﾌﾟﾃﾞｰﾄ
private:
	void RefKeyData(void);						// ﾃﾞﾌｫﾙﾄ用
	void SetKeyConfig(void);					// ｺﾝﾌｨｸﾞｾｯﾄ用
	void (KeyState::*func)(void);				// ﾒﾝﾊﾞｰ関数ﾎﾟｲﾝﾀ

	std::vector<int> _keyCon;					// ｷｰｺﾝﾌｨｸﾞ情報
	std::vector<int> _keyConDef;				// ﾃﾞﾌｫﾙﾄｷｰｺﾝﾌｨｸﾞ情報
	char _buf[256];								// ｷｰ押下情報格納用
	int _modeKeyOld;							// F1用のｵｰﾙﾄﾞ
	INPUT_ID _configID;							// ｷｰｺﾝﾌｨｸﾞ時何番目か判断
};

