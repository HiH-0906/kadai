#include <type_traits>
#include "Layer.h"

LAYER begin(LAYER)
{
	return LAYER::BG;
}

LAYER end(LAYER)
{
	return LAYER::MAX;
}

LAYER operator*(LAYER key)
{
	return key;
}

LAYER operator++(LAYER & key)
{
	// Šî’ê‚ÌŒ^‚ğŒ©‚Ä‰]X
	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1);
}