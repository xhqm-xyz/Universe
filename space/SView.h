#pragma once
#ifndef UNIVERSE_SPACE_SVIEW
#define UNIVERSE_SPACE_SVIEW
#include "SpaceBase.h"
#include "SCoorSys.h"
typedef std::vector<SPoints> boxw;
typedef std::vector<std::vector<SPoints>> boxh;


class SView : public SCoorSys
{
protected:
	SPoint origin;
	SCoorSys *look;
	SPoints ViewPot;
public:
	double SView_w = 100;
	double SView_h = 100;
	double SView_ratio = 1;

public:
	SView();
	~SView() { };

	void SetCoorSys(SCoorSys* inSys);
	void SetView(double w, double h, double ratio = 1);
	void UpView();

	void moveX(double x);
	void moveY(double y);
	void moveZ(double z);
	void rotaX(double x);
	void rotaY(double y);
	void rotaZ(double z);
	void move(double x, double y, double z);
	void rota(double x, double y, double z);
	void Transform(double tx, double ty, double tz, double rx, double ry, double rz);

	void Clearn(SPoints &pts);
};
#endif // !UNIVERSE_SPACE_SVIEW