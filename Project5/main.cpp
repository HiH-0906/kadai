#include <DxLib.h> // Dx×²ÌÞ×Ø‚ÌŽg—p
#include <Scene/SceneMng.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//SceneMng sceneMng;
	//sceneMng.Ran();

	SceneMng::GetInstance().Ran();
	SceneMng::Destroy();

	return 0;
}