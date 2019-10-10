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
	void Draw(void);											// ��Ұ��݂���̕`��
	void Draw(int id);											// ��Ұ��݂Ȃ��̕`��
	virtual ~Obj();

	bool animKey(const std::string key);						// ��Ұ��ݷ��̒ǉ�
	const std::string animKey(void) const;						// ���݂̱�Ұ��ݷ��̎擾

	bool SetAnim(const std::string key, AnimVector& data);		// �ް��i�[�p�֐�
private:
	std::map<std::string, AnimVector> _animMap;					// ��Ұ����ް��Ǘ��ϐ�
	std::string _animKey;										// �ް������p��
	unsigned int _animFrame;									// ���ݱ�Ұ���
	unsigned int _animCount;									// ����
protected:
	Vector2 _pos;												// ���W
	Vector2 _size;												// �����蔻��p����
};

