#include <type_traits>
#include "InputId.h"

// begin����[
INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::LEFT;
}
// end����[
INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID key)
{
	return key;
}

INPUT_ID operator++(INPUT_ID & key)
{
	// ���̌^�����ĉ]�X
	return key = static_cast<INPUT_ID>(std::underlying_type<INPUT_ID>::type(key) + 1);
}
