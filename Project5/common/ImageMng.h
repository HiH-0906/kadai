#pragma once
#include <memory>
#include <map>
#include <vector>
#include <common/Vector2.h>

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

	const VecInt& GetID(const std::string& key);										// Q[ΰυp
	const VecInt& GetID(const std::string& key,const std::string& fileName);			// κGp
	const VecInt& GetID(const std::string& key, const std::string& fileName,			// ͺp
						const Vector2& divSize,const Vector2& divCnt);

private:
	struct ImageMngDeleter																// Ά½ΐΡΓήΨ°ΐ°
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();
	static std::unique_ptr<ImageMng, ImageMngDeleter> sInstance;
	
	std::map<std::string, VecInt> imgMap;												// ζpzρ

};

