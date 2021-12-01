#include "SCoorSys.h"

SCoorSys::~SCoorSys() {
	DelAllMod();
}

SPoints SCoorSys::GetAllPts(SModel mod)
{
	SPoints allpts = mod.sPoints;
	for (auto& line : mod.sLines) {
		allpts.push_back(line.star);
		allpts.push_back(line.end);
	}
	for (auto& face : mod.sFaces) {
		allpts.push_back(face.A);
		allpts.push_back(face.B);
		allpts.push_back(face.C);
	}
	for (auto& cube : mod.sCubes) {
		allpts.push_back(cube.top[0]);
		allpts.push_back(cube.top[1]);
		allpts.push_back(cube.top[2]);
		allpts.push_back(cube.top[3]);
	}
	for (auto& md : mod.GetModels()) {
		auto mdpts = GetAllPts(md);
		for (auto& mdpt : mdpts)
			allpts.push_back(mdpt);
	}
	return allpts;
}

SPoints SCoorSys::GetPtGather()
{
	PointGather.clear();
	for (auto& mod : Models) {
		auto mdpts = GetAllPts(*mod);
		for (auto& mdpt : mdpts)
			PointGather.push_back(mdpt);
	}return PointGather;
}

void SCoorSys::SetCoor(SMatrix coor)
{
	SMatrix tran;
	tran = Coor.GetInvMat();
	tran = tran * coor;
	for (auto& mod : Models)
		*mod *= tran;
	Coor = coor;
}

void SCoorSys::ToCoorSysE()
{
	SMatrix tran;
	tran = Coor.GetInvMat();
	for (auto& mod : Models)
		*mod *= tran;
	Coor = SMatrix::GetMatE();
}

void SCoorSys::SetModels(SCoorSys *sys)
{
	if (sys) {
		SMatrix transform;
		transform = sys->Coor.GetInvMat();
		transform = transform * Coor;
		for (auto& mod : sys->Models) {
			auto md = new SModel(mod->GetModelName());
			*md = *mod * transform;
			Models.push_back(md);
		}
	}
}

void SCoorSys::SetModels(SModel model)
{
	auto md = new SModel(model.GetModelName());
	*md = model;
	Models.push_back(md);
}

void SCoorSys::SetModels(SModels models)
{
	for (auto& model : models) {
		auto md = new SModel(model.GetModelName());
		*md = model;
		Models.push_back(md);
	}
}

void SCoorSys::DelAllMod()
{
	for (auto& mod : Models)
		delete mod;
	Models.clear();
}

void SCoorSys::moveMod(SModel* mod, double x, double y, double z)
{
	SVector t(x, y, z);
	*mod += t;
}

void SCoorSys::rateMod(SModel* mod, double x, double y, double z)
{
	SMatrix rtx, rty, rtz;
	rtx = SMatrix::GetRotateX(x);
	rty = SMatrix::GetRotateY(y);
	rtz = SMatrix::GetRotateY(z);
	*mod *= rtx * rty * rtz;
}
