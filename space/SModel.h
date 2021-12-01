#pragma once
#ifndef UNIVERSE_SPACE_SMODEL
#define UNIVERSE_SPACE_SMODEL
//#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include "SpaceBase.h"
#include "stb_image.h"
#include "stb_image_write.h"
class SModel;
typedef std::vector<SModel> SModels;

class SModel {
protected:
	SModels sModels;
	std::string ModelName;
public:
	SPoints sPoints;
	SLines  sLines;
	SFaces  sFaces;
	SCubes  sCubes;

public:
	SModel(std::string name);
	~SModel();

	std::string GetModelName() { return ModelName; }
	std::vector<std::string> ListName();
	SModels& GetModels() { return sModels; };

	void Copy(SModel model);
	bool AddModel(SModel model);
	bool DelModel(std::string name);
	SModel* FindModel(std::string name);

	void ReadSstl(std::string path, std::string stlname);
	void ReadSxyz(std::string path, std::string xyzname);
	void ReadSbmp(std::string path, std::string bmpname);
	void ReadSpng(std::string path, std::string pngname);

	SModel operator = (const SModel& mod);
	SModel operator += (const SVector& vec);
	SModel operator -= (const SVector& vec);
	SModel operator *= (const SMatrix& mat);
	friend SModel operator + (const SModel& M, const SVector& vec);
	friend SModel operator - (const SModel& M, const SVector& vec);
	friend SModel operator * (const SModel& M, const SMatrix& mat);

	static unsigned char* f_TImageLoad(char* fileName, int* width, int* height, int* component, int redcomp);

	//void SetPoints(SPoints points) {sPoints = points; };
	//void SetLines (SLines  lines ) {sLines  = lines ; };
	//void SetFaces (SFaces  faces ) {sFaces  = faces ; };
	//void SetCubes (SCubes  cubes ) {sCubes  = cubes ; };
	//void SetModels(SModels models) {sModels = models; };
	//void AddPoint(SPoint point) {sPoints.push_back(point); };
	//void AddLine (SLine  line ) { sLines.push_back(line ); };
	//void AddFace (SFace  face ) { sFaces.push_back(face ); };
	//void AddCube (SCube  cube ) { sCubes.push_back(cube ); };
	//void AddModel(SModel model) {sModels.push_back(model); };
};

SModels operator * (const SModels& models, const SMatrix& mat);
SModels operator *= (SModels& models, const SMatrix& mat);

#endif UNIVERSE_SPACE_SMODEL