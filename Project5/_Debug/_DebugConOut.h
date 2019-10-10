#pragma once
#ifdef _DEBUG


#include <memory>

// ﾃﾞﾊﾞｯｸﾒｯｾｰｼﾞ用定義　　ﾃﾞﾊﾞｯｸﾓｰﾄﾞで書き間違い等があったらｳｨﾝﾄﾞｳを表示
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes,"%s %d行目\0",__FILE__,__LINE__);\
	MessageBox(0,ast_mes,"ｱｻｰﾄ表示",MB_OK);\
	}

#define TREACE(fmt, ...) printf(fmt, __VA_ARGS__);

class _DebugConOut
{
public:
	static _DebugConOut&GetInstance()
	{
		return *sInstance;
	}
private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut) const
		{
			delete _debugConOut;
		}

	};
	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
	static std::unique_ptr<_DebugConOut,_DebugConOutDeleter> sInstance;
};
#else // _DEBUG
#define AST()
#define TREACE(fmt, ...) 
#endif // _DEBUG

