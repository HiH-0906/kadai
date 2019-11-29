#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>

class Player :
	public Obj
{
public:
	Player(Vector2Dbl pos, Vector2Dbl size);		// ��ڲ԰�z�u�����t���ݽ�׸��
	void Update(sharedObj plObj) override final;
	~Player();
private:
	void Init(void);
	std::shared_ptr<InputState>_input;				// ���߯Ă��ư��߲���錾
};

