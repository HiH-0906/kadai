#pragma once
#include <memory>
#include <Obj.h>

class BaseScene;											// �׽���������ߐ錾

// ����ݎ�ʊǗ�
enum class ACT_QUE
{
	NON,													// ���� ������0�̒l���������ɉ������Ȃ��悤
	SHOT													// �e
};

using unipueBase = std::unique_ptr<BaseScene>;
//						����ݎ��	obj�ւ̎Q��
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unipueBase Update(unipueBase own) = 0;
	virtual void RunActQue(std::vector<ActQueT> actList);
};

