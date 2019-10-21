#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;					// ±¯ÌßÃŞ°Ä
private:
	void RefKeyData(void);						// ÃŞÌ«ÙÄ—p
	void SetKeyConfig(void);					// ºİÌ¨¸Ş¾¯Ä—p

	void (KeyState::*func)(void);				// ÒİÊŞ°ŠÖ”Îß²İÀ

	std::vector<int> _keyCon;					// ·°ºİÌ¨¸Şî•ñ
	std::vector<int> _keyConDef;				// ÃŞÌ«ÙÄ·°ºİÌ¨¸Şî•ñ
	char _buf[256];								// ·°‰Ÿ‰ºî•ñŠi”[—p
};

