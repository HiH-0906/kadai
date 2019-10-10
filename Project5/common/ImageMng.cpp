#include <DxLib.h>
#include "ImageMng.h"


std::unique_ptr<ImageMng,ImageMng::ImageMngDeleter> ImageMng::sInstance(new ImageMng());


const VecInt & ImageMng::GetID(const std::string & key)
{
	return GetID(key,key);
}

const VecInt & ImageMng::GetID(const std::string & key, const std::string & fileName)
{
	// ‚·‚Å‚É‚ ‚é‚©Áª¯¸
	if (imgMap.find(key) == imgMap.end())
	{
		// ì¬
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());
	}
	return imgMap[key];
}

const VecInt & ImageMng::GetID(const std::string & key, const std::string & fileName, const Vector2 & divSize, const Vector2 & divCnt)
{
	// ‚·‚Å‚É‚ ‚é‚©Áª¯¸
	if (imgMap.find(key) == imgMap.end())
	{
		// ì¬
		imgMap[key].resize(divCnt.x*divCnt.y);
		LoadDivGraph(fileName.c_str(), divCnt.x*divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[key][0]);
	}
	return imgMap[key];
}

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
