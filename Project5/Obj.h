#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <common/Vector2.h>

#define PI 3.141592

enum class STATE
{
	NORMAL,		// �ʏ�
	EX,			// ����
	DEATH,		// ����(���S)
	MAX
};

enum class UNIT_ID
{
	NON,		// ����
	PLAYER,		// ���@
	ENEMY,		// �G
	PL_BULLET,	// ���@�e
	EN_BULLET	// �G�e
};
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	// �摜�Ʊ�Ұ��ݶ����ް�
using sharedObj = std::shared_ptr<Obj>;							// ������߲��

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj) = 0;					// �������z�֐�
	virtual void Draw(void);									// ��Ұ��݂���̕`��
	void Draw(int id);											// ��Ұ��݂Ȃ��̕`��
	virtual ~Obj();

	bool state(const STATE state);								// ��Ұ��ݷ��̒ǉ�
	const STATE state(void) const;								// ���݂̱�Ұ��ݷ��̎擾

	const Vector2Dbl pos(void);									// _posGet�޾�!
	const Vector2Dbl size(void);								// _sizeGet�޾�!
	const UNIT_ID unitID(void);									// _unitIDGet�޾�!

	bool SetAnim(const STATE state, AnimVector& data);			// �ް��i�[�p�֐�
	virtual bool SetAlive(bool alive);							// �����Ă��׸ޕύX
	virtual bool exFlag(bool flag);								// �p����Ŏg�������Ⴄ�̂łƂ肠�������z�֐�
	const bool exFlag(void)const;											// Flag��Get
	bool isAlive(void) { return _alive; }						// �����Ă��邩�擾
	bool isDead(void) { return _dead; }							// ����ł��邩�擾
	bool isAnimEnd(void);										// ��Ұ��ݏ�Ԏ擾	true�ŏI����Ă���
private:
	unsigned int _animCount;									// ����

protected:
	bool DestroyProc(void);										// �������ɂƱ�Ұ��ݏI���m�F�֐�
	bool _alive;												// �����Ă��邩
	bool _dead;													// ����ł��邩
	Vector2Dbl _pos;											// ���W
	Vector2Dbl _size;											// �����蔻��p����
	UNIT_ID _unitID;											// �������
	bool _exFlag;												// �O������̱����pFlag
	int _speed;													// ��߰��
	double _rad;												// �p�x
	int _zOrder;												// �`��D��x
	std::map<STATE, AnimVector> _animMap;						// ��Ұ����ް��Ǘ��ϐ�
	STATE _state;												// ��ԊǗ��p
	unsigned int _animFrame;									// ���ݱ�Ұ���
};

