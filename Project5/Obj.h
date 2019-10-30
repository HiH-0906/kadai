#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <common/Vector2.h>

enum class STATE
{
	NORMAL,		// �ʏ�
	EX,			// ����
	DEATH,		// ����(���S)
	MAX
};
class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	// �摜�Ʊ�Ұ��ݶ����ް�
using sharedObj = std::shared_ptr<Obj>;							// ������߲��

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;								// �������z�֐�
	void Draw(void);											// ��Ұ��݂���̕`��
	void Draw(int id);											// ��Ұ��݂Ȃ��̕`��
	virtual ~Obj();

	bool state(const STATE state);								// ��Ұ��ݷ��̒ǉ�
	const STATE state(void) const;								// ���݂̱�Ұ��ݷ��̎擾

	bool SetAnim(const STATE state, AnimVector& data);			// �ް��i�[�p�֐�
	bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// �����Ă��邩�擾
	bool isDead(void) { return _dead; }							// ����ł��邩�擾
	bool isAnimEnd(void);										// ��Ұ��ݏ�Ԏ擾	true�ŏI����Ă���
private:
	std::map<STATE, AnimVector> _animMap;						// ��Ұ����ް��Ǘ��ϐ�
	STATE _state;												// ��ԊǗ��p
	unsigned int _animFrame;									// ���ݱ�Ұ���
	unsigned int _animCount;									// ����

protected:
	bool DestroyProc(void);										// �������ɂƱ�Ұ��ݏI���m�F�֐�
	bool _alive;												// �����Ă��邩
	bool _dead;													// ����ł��邩
	Vector2Dbl _pos;											// ���W
	Vector2Int _size;											// �����蔻��p����
};

