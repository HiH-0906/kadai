#pragma once
#include <map>
#include "InputId.h"

using KeyPair = std::pair<int, int>;				// ·°î•ñŠi”[—p old‚Ænew first‚ªnew
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update(void) = 0;					// ±¯ÌßÃŞ°ÄŠÖ”
	const KeyMap& state(void)const;					// _stateŠÛXæ“¾
	const KeyPair& state(INPUT_ID id)const;			// _state“à‚ÌKeyPair‚ğæ“¾
	bool state(INPUT_ID id, int data);				// _state‚ÌXV
	void SetOld(void);								// 1ÌÚ°Ñ‘O‚Ìî•ñŠi”[—p
private:
	KeyMap _state;									// ·°î•ñŠi”[—p•Ï”
};

