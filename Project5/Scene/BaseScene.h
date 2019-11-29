#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;											// �׽���������ߐ錾

// ����ݎ�ʊǗ�
enum class ACT_QUE
{
	NON,													// ���� ������0�̒l���������ɉ������Ȃ��悤
	SHOT,													// �e
	CHECK_HIT												// �����蔻��
};

using unipueBase = std::unique_ptr<BaseScene>;
//						����ݎ��	obj�ւ̎Q��
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;			// �ǂ̼�݂ɂ�����̂ŏ������z
	virtual void RunActQue(std::vector<ActQueT> actList);	// �K�v�Ȃ���݂�����̂ŉ��z
};

