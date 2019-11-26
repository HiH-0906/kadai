#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <common/Vector2.h>

#define PI 3.141592

enum class STATE
{
	NORMAL,		// ’Êí
	EX,			// “Áê
	DEATH,		// ”š”­(€–S)
	MAX
};

enum class UNIT_ID
{
	NON,		// –³‚µ
	PLAYER,		// ©‹@
	ENEMY,		// “G
	PL_BULLET,	// ©‹@’e
	EN_BULLET	// “G’e
};
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	// ‰æ‘œ‚Æ±ÆÒ°¼®İ¶³İÄÃŞ°À
using sharedObj = std::shared_ptr<Obj>;							// ¼ª±ÄŞÎß²İÀ

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj) = 0;								// ƒˆ‰¼‘zŠÖ”
	void Draw(void);											// ±ÆÒ°¼®İ‚ ‚è‚Ì•`‰æ
	void Draw(int id);											// ±ÆÒ°¼®İ‚È‚µ‚Ì•`‰æ
	virtual ~Obj();

	bool state(const STATE state);								// ±ÆÒ°¼®İ·°‚Ì’Ç‰Á
	const STATE state(void) const;								// Œ»İ‚Ì±ÆÒ°¼®İ·°‚Ìæ“¾

	const Vector2Dbl pos(void);									// _posGetÀŞ¾Ş!
	const Vector2Dbl size(void);								// _sizeGetÀŞ¾Ş!
	const UNIT_ID unitID(void);									// _unitIDGetÀŞ¾Ş!

	bool SetAnim(const STATE state, AnimVector& data);			// ÃŞ°ÀŠi”[—pŠÖ”
	bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// ¶‚«‚Ä‚¢‚é‚©æ“¾
	bool isDead(void) { return _dead; }							// €‚ñ‚Å‚¢‚é‚©æ“¾
	bool isAnimEnd(void);										// ±ÆÒ°¼®İó‘Ôæ“¾	true‚ÅI‚í‚Á‚Ä‚¢‚é
private:
	std::map<STATE, AnimVector> _animMap;						// ±ÆÒ°¼®İÃŞ°ÀŠÇ—•Ï”
	STATE _state;												// ó‘ÔŠÇ——p
	unsigned int _animFrame;									// Œ»İ±ÆÒ°¼®İ
	unsigned int _animCount;									// ¶³İÄ

protected:
	bool DestroyProc(void);										// ¶‚«€‚É‚Æ±ÆÒ°¼®İI—¹Šm”FŠÖ”
	bool _alive;												// ¶‚«‚Ä‚¢‚é‚©
	bool _dead;													// €‚ñ‚Å‚¢‚é‚©
	Vector2Dbl _pos;											// À•W
	Vector2Dbl _size;											// “–‚½‚è”»’è—p»²½Ş
	UNIT_ID _unitID;
	int _speed;													// ½Ëß°ÄŞ
	double _rad;												// Šp“x
	int _zOrder;												// •`‰æ—Dæ“x
};

