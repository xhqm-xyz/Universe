#include "SModel.h"
#include <time.h>

SModel::SModel(std::string name)
{
	ModelName = name;
}

SModel::~SModel()
{
	sPoints.clear();
	sLines.clear();
	sFaces.clear();
	sCubes.clear();
	sModels.clear();
}

std::vector<std::string> SModel::ListName()
{
	std::vector<std::string> list;
	for (auto& model : sModels)
		list.push_back(model.ModelName);
	return list;
}

void SModel::Copy(SModel model)
{
	sPoints.clear();
	 sLines.clear();
	 sFaces.clear();
	 sCubes.clear();
	sModels.clear();
	
	sPoints = model.sPoints;
	sLines  = model.sLines ;
	sFaces  = model.sFaces ;
	sCubes  = model.sCubes ;
	sModels = model.sModels;
}

bool SModel::AddModel(SModel model)
{
	if (FindModel(model.GetModelName()))
		return false;
	sModels.push_back(model);
	return true;
}

bool SModel::DelModel(std::string name)
{
	for (auto modelIt = sModels.begin(); modelIt != sModels.end(); modelIt++)
		if (modelIt->GetModelName() == name) {
			sModels.erase(modelIt);
			return true;
		}
	return false;
}

SModel* SModel::FindModel(std::string name)
{
	for (auto &model : sModels)
		if (model.GetModelName() == name) {
			return &model;
		}
	return nullptr;
}

void SModel::ReadSbmp(std::string path, std::string bmpname)
{
	int w, h, c, r = 0;
	SModel bmp(bmpname == "" ? path : bmpname);
	auto data = f_TImageLoad((char*)path.c_str(), &w, &h, &c, r);
	auto dataptr = data;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			SPoint pox(i, j);
			pox.color = SRGB(dataptr[0], dataptr[1], dataptr[2]);
			bmp.sPoints.push_back(pox);
			dataptr += 4;
		}
	}free(data);
	sModels.push_back(bmp);
}

void SModel::ReadSpng(std::string path, std::string pngname)
{
	int w, h, c, r = 0;
	SModel png(pngname == "" ? path : pngname);
	auto data = f_TImageLoad((char*)path.c_str(), &w, &h, &c, r);
	auto dataptr = data;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			SPoint pox(i, j);
			pox.color = SRGB(dataptr[0], dataptr[1], dataptr[2]);
			png.sPoints.push_back(pox);
			dataptr += 4;
		}
	}free(data);
	sModels.push_back(png);
}







SModel operator+(const SModel& M, const SVector& vec)
{
	int id = 0;
	SModel copy(std::to_string((long long)&id));
	copy.Copy(M);
	copy.sPoints+= vec;
	copy.sLines += vec;
	copy.sFaces += vec;
	copy.sCubes += vec;
	if(copy.sModels.size() == 0)
		return copy;
	for(auto &mo: copy.sModels)
		mo = mo + vec;
	return copy;
}

SModel operator-(const SModel& M, const SVector& vec)
{
	int id = 0;
	SModel copy(std::to_string((long long)&id));
	copy.Copy(M);
	copy.sPoints-= vec;
	copy.sLines -= vec;
	copy.sFaces -= vec;
	copy.sCubes -= vec;
	if (copy.sModels.size() == 0)
		return copy;
	for (auto& mo : copy.sModels)
		mo = mo - vec;
	return copy;
}

SModel operator*(const SModel& M, const SMatrix& mat)
{
	int id = 0;
	SModel copy(std::to_string((long long)&id));
	copy.Copy(M);
	copy.sPoints*= mat;
	copy.sLines *= mat;
	copy.sFaces *= mat;
	copy.sCubes *= mat;
	if (copy.sModels.size() == 0)
		return copy;
	for (auto& mo : copy.sModels)
		mo = mo * mat;
	return copy;
}



SModel SModel::operator=(const SModel& mod)
{
	ModelName = mod.ModelName;
	sPoints = mod.sPoints;
	sLines = mod.sLines;
	sFaces = mod.sFaces;
	sCubes = mod.sCubes;
	sModels = mod.sModels;
	return mod;
}

SModel SModel::operator+=(const SVector& vec)
{
	sPoints+= vec;
	sLines += vec;
	sFaces += vec;
	sCubes += vec;
	if (sModels.size() == 0)
		return *this;
	for (auto& mo : sModels)
		mo += vec;
	return *this;
}

SModel SModel::operator-=(const SVector& vec)
{
	sPoints-= vec;
	sLines -= vec;
	sFaces -= vec;
	sCubes -= vec;
	if (sModels.size() == 0)
		return *this;
	for (auto& mo : sModels)
		mo -= vec;
	return *this;
}

SModel SModel::operator*=(const SMatrix& mat)
{
	sPoints*= mat;
	sLines *= mat;
	sFaces *= mat;
	sCubes *= mat;
	if (sModels.size() == 0)
		return *this;
	for (auto& mo : sModels)
		mo *= mat;
	return *this;
}

SModels operator*(const SModels& models, const SMatrix& mat)
{
	SModels mods;
	for (auto& mod : models)
		mods.push_back(mod * mat);
	return mods;
}

SModels operator*=(SModels& models, const SMatrix& mat)
{
	for (auto& mod : models)
		mod *= mat;
	return models;
}


unsigned char* SModel::f_TImageLoad(char* fileName, int* width, int* height, int* component, int redcomp)
{
	unsigned char* tempData = stbi_load(fileName, width, height, component, redcomp);
	//printf("component:  %d", *component);
	//根据像素通道数component进行判断，分别将8/24/32位转换为32bgra格式数据
	if (*component == 4)
	{
		unsigned char* srcData = (unsigned char*)malloc(sizeof(unsigned char) * *width * *height * 4);
		unsigned char* pSrc = srcData;
		unsigned char* pTemp = tempData;
		for (int j = 0; j < *height; j++)
		{
			for (int i = 0; i < *width; i++)
			{
				pSrc[0] = pTemp[0];
				pSrc[1] = pTemp[1];
				pSrc[2] = pTemp[2];
				pSrc[3] = pTemp[3];
				pSrc += 4;
				pTemp += 4;
			}
		}
		free(tempData);
		return srcData;
	}
	else if (*component == 3)
	{
		unsigned char* srcData = (unsigned char*)malloc(sizeof(unsigned char) * *width * *height * 4);
		unsigned char* pSrc = srcData;
		unsigned char* pTemp = tempData;
		for (int j = 0; j < *height; j++)
		{
			for (int i = 0; i < *width; i++)
			{
				pSrc[0] = pTemp[0];
				pSrc[1] = pTemp[1];
				pSrc[2] = pTemp[2];
				pSrc[3] = 255;
				pSrc += 4;
				pTemp += 3;
			}
		}
		free(tempData);
		*component = 4;
		return srcData;
	}
	else if (*component == 1)
	{
		unsigned char* srcData = (unsigned char*)malloc(sizeof(unsigned char) * *width * *height * 4);
		unsigned char* pSrc = (unsigned char*)srcData;
		unsigned char* pTemp = tempData;
		for (int j = 0; j < *height; j++)
		{
			for (int i = 0; i < *width; i++)
			{
				int gray = *pTemp++;
				pSrc[0] = gray;
				pSrc[1] = gray;
				pSrc[2] = gray;
				pSrc[3] = 255;
				pSrc += 4;
			}
		}
		free(tempData);
		*component = 4;
		return srcData;
	}
	else
		return NULL;
};