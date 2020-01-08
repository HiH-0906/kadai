#pragma once


enum class LAYER
{
	BG,						// �w�i
	CHAR,					// ���
	UI,						// UI
	EX,						// ������ʗp
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);
