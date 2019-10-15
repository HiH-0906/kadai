#include "InputState.h"

InputState::InputState()
{
}


InputState::~InputState()
{
}

const KeyMap & InputState::state()const
{
	return _state;
}

const KeyPair & InputState::state(INPUT_ID & id) const
{
	if (_state.find(id) == _state.end())
	{

	}
	return _state[id];
}



