#pragma once
#include <memory>
#include <map>
#include <vector>
#include <Vector2.h>

using VecInt = std::vector<int>;

#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		return *sInstance;
	}

	const VecInt& GetID(const std::string& key);										// ゲーム内検索用
	const VecInt& GetID(const std::string& key,const std::string& fileName);			// 一枚絵用
	const VecInt& GetID(const std::string& key, const std::string& fileName,			// 分割用
						const Vector2& divSize,const Vector2& divCnt);

private:
	struct ImageMngDeleter																// ｶｽﾀﾑﾃﾞﾘｰﾀｰ
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();
	static std::unique_ptr<ImageMng, ImageMngDeleter> sInstance;
	
	std::map<std::string, VecInt> imgMap;												// 画像用配列

};

