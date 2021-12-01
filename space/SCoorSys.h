#pragma once
#ifndef UNIVERSE_SPACE_SCOOR
#define UNIVERSE_SPACE_SCOOR
#include "SpaceBase.h"
#include "SModel.h"
class SCoorSysE {
protected:
	SMatrix Coor;
	SPoints PointGather;
public:
	SCoorSysE() { Coor = SMatrix::GetMatE(); };
	~SCoorSysE() { PointGather.clear(); };
};

class SCoorSys : public SCoorSysE {
public:
	std::vector<SModel*> Models;
public:
	SCoorSys() {};
	~SCoorSys();

	static SPoints GetAllPts(SModel mod);
	SPoints GetPtGather();

	void SetCoor(SMatrix coor);
	void GetCoor(SMatrix&Mat) { Mat = Coor; };
	void ToCoorSysE();
	void SetModels(SCoorSys *sys);
	void SetModels(SModel model);
	void SetModels(SModels models);
	void DelAllMod();
	std::vector<SModel*>& GetModels() { return Models; };

	void moveMod(SModel* mod, double x, double y, double z);
	void rateMod(SModel* mod, double x, double y, double z);

};
#endif // !UNIVERSE_SPACE_SCOOR