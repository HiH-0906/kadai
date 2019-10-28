#pragma once

// √ﬁÃ´Ÿƒ∑∞ÿΩƒ
enum class INPUT_ID
{
	LEFT,				// ç∂
	RIGHT,				// âE
	UP,					// è„
	DOWN,				// â∫
	BTN_1,				// Z
	BTN_2,				// X
	BTN_3,				// A
	BTN_4,				// S
	MAX
};

// µ- ﬁ∞€∞ƒﬁ

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);

