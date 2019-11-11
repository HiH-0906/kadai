#ifdef _DEBUG
#include <windows.h>
#include <DxLib.h>
#include <scene/SceneMng.h>
#include "_DebugDispOut.h"

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut);
_DebugDispOut::_DebugDispOut()
{
	_DbgScreen = -1;
	_waitTime  = 0;
}

_DebugDispOut::~_DebugDispOut()
{
}

void _DebugDispOut::SetScreen(void)
{
	ghBefor = GetDrawScreen();
	SetDrawScreen(_DbgScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
}

void _DebugDispOut::RevScreen(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
}

void _DebugDispOut::WaitMode(void)
{
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime+=100;
		}
		else
		{
			_waitTime++;
		}
	}
	if (CheckHitKey(KEY_INPUT_SUBTRACT))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime -= 100;
		}
		else
		{
			_waitTime--;
		}
		if (_waitTime < 0.0)
		{
			_waitTime = 0.0;
		}
	}
	if (CheckHitKey(KEY_INPUT_DIVIDE))
	{
		_waitTime = 0.0;
	}
	if (_waitTime)
	{
		_startTime = std::chrono::system_clock::now();
		do {
			if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				break;
			}
			_endTime = std::chrono::system_clock::now();
		} while (std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count() < _waitTime);
	}
}

int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawGraph(x , y , GrHandle, TransFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawBox(x1 , y1 , x2 , y2 , Color, FillFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawString(int x, int y, char* String, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawString(x, y, String, Color);
	RevScreen();
	return rtnFlag;
}
//
//int _DebugDispOut::DrawFormatString(int x, int y, unsigned int Color, std::string FormatString, ...)
//{
//	va_list arglist;
//	va_start(arglist, FormatString);
//	SetScreen();
//	int rtnFlag = DxLib::DrawFormatString(x , y , Color, FormatString.c_str(), va_arg(arglist, int), va_arg(arglist, int));
//	RevScreen();
//	va_end(arglist);
//	return rtnFlag;
//}

int _DebugDispOut::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawLine(x1 , y1 , x2 , y2 , Color);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawCircle(x , y , r, Color, FillFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawPixel(int x, int y, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawPixel(x , y , Color);
	RevScreen();
	return rtnFlag;
}

bool _DebugDispOut::StartDrawDebug(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_DbgScreen);
	ClsDrawScreen();
	SetDrawScreen(ghBefor);
	return true;
}

bool _DebugDispOut::AddDrawDebug(void)
{
	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		dispFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_PGDN))
	{
		dispFlag = false;
	}
	if (dispFlag)
	{
		lpSceneMng.AddDrawQue({ _DbgScreen,lpSceneMng.ScreenSize.x/2,lpSceneMng.ScreenSize.y / 2,0 });
	}
	WaitMode();
	return true;
}

bool _DebugDispOut::SetAlpha(int alpha)
{
	_alpha = alpha;

	return true;
}

bool _DebugDispOut::Setup(int alpha)
{
	if (_DbgScreen == -1)
	{
		_DbgScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	}
	SetAlpha(alpha);
	return false;
}

bool _DebugDispOut::SetWait(double timeCnt)
{
	_waitTime = timeCnt;
	return true;
}

#endif	// _DEBUG
