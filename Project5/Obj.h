#pragma once
#include <string>
#include <vector>
#include <map>
#include <Vector2.h>

using AnimVector = std::vector<std::pair<int, unsigned int>>;

class Obj
{
public:
	Obj();
	void Update(void);
	void Draw(void);											// ±ÆÒ°¼®İ‚ ‚è‚Ì•`‰æ
	void Draw(int id);											// ±ÆÒ°¼®İ‚È‚µ‚Ì•`‰æ
	virtual ~Obj();

	bool animKey(const std::string key);						// ±ÆÒ°¼®İ·°‚Ì’Ç‰Á
	const std::string animKey(void) const;						// Œ»İ‚Ì±ÆÒ°¼®İ·°‚Ìæ“¾

	bool SetAnim(const std::string key, AnimVector& data);		// ÃŞ°ÀŠi”[—pŠÖ”
private:
	std::map<std::string, AnimVector> _animMap;					// ±ÆÒ°¼®İÃŞ°ÀŠÇ—•Ï”
	std::string _animKey;										// ÃŞ°À±¸¾½—p·°
	unsigned int _animFrame;									// Œ»İ±ÆÒ°¼®İ
	unsigned int _animCount;									// ¶³İÄ
protected:
	Vector2 _pos;												// À•W
	Vector2 _size;												// “–‚½‚è”»’è—p»²½Ş
};

