#pragma once
#include <vector>
#include <functional>
#include "BaseScene.h"
#include "Obj.h"

using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;		// ˆø”‚Æ•Ô‚è’l‚ª“¯‚¶‚à‚Ì‚ğ•ú‚è‚ß‚é

#define FORMATION 3
#define WAIT_TIME 50.0
#define CHAR_SIZE_X 30
#define CHAR_SIZE_Y 32
#define ENEMY_OFFSET_X  (CHAR_SIZE_X*2.5)
#define ENEMY_OFFSET_Y  40.0

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unipueBase Update(unipueBase own) override final;
private:
	std::vector<sharedObj> _objList;							// List‚Å‚Í‚È‚­Vector
	void RunActQue(std::vector<ActQueT> actList) override;
	void initFunc(void);
	std::map<ACT_QUE, funcAct> funcQue;
};

