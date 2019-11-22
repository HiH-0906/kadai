#pragma once
#include <vector>
#include <functional>
#include "BaseScene.h"
#include "Obj.h"
using funcAct = std::function<bool(ActQueT&, std::vector<sharedObj>&)>;

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
	std::map<ACT_QUE, funcAct> funcQue;
};

