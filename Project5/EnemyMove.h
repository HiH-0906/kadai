#pragma once

#include <common/Vector2.h>

class EnemyMove
{

public:
	EnemyMove(Vector2Template<int>& pos);		// ¡‰ñ‚Í‚í‚©‚è‚â‚·‚­‚·‚é‚½‚ß‚ÉQÆ‚Åó‚¯æ‚é –{“–‚ÍGetSet‚ª‚ ‚é‚Æ‚¢‚¢
	~EnemyMove();
	void Update(void);				// 
private:
	Vector2Template<int>& _pos;					// ‚à‚ç‚Á‚½´ÈĞ°‚Ìpos‚ÌêŠ•Û‘¶
};

