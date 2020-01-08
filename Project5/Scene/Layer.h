#pragma once


enum class LAYER
{
	BG,						// ”wŒi
	CHAR,					// ·¬×
	UI,						// UI
	EX,						// “ÁŽêŒø‰Ê—p
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);
