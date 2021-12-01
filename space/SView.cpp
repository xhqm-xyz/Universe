#include "SView.h"

SView::SView()
{
	look = nullptr;
}

void SView::SetCoorSys(SCoorSys* inSys)
{
	look = inSys;
}

void SView::SetView(double w, double h, double ratio)
{
	SView_w = w;
	SView_h = h;
	SView_ratio = ratio;
}

void SView::UpView()
{
	ViewPot.clear();
	DelAllMod();
	SetModels(look);
	GetPtGather();
	SVector ori = Poit2Vect(origin);
	for (auto& point : PointGather) {
		point = point - ori;
		double ViewX = point.x * SView_ratio;
		double ViewY = point.y * SView_ratio;
		double ViewZ = point.z * SView_ratio;
		if ((0 < ViewX && ViewX < SView_w) && (0 < ViewY && ViewY < SView_h) && (0 < ViewZ)) {
			SPoint vie(ViewX, ViewY, ViewZ);
			vie.color = point.color;
			ViewPot.push_back(vie);
		}
	}Clearn(ViewPot);
}

void SView::Clearn(SPoints &pts)
{
	if (pts.size() == 0) return;
	double _xmin = pts[0].x;
	double _ymin = pts[0].y;
	double _xmax = pts[0].x;
	double _ymax = pts[0].y;
	for (auto& pt : pts) {
		_xmin = pt.x < _xmin ? pt.x : _xmin;
		_ymin = pt.y < _ymin ? pt.y : _ymin;
		_xmax = pt.x > _xmax ? pt.x : _xmax;
		_ymax = pt.y > _ymax ? pt.y : _ymax;
	}
	int x = _xmax - _xmin + 2;
	int y = _ymax - _ymin + 2;

	boxh _box;
	for (int i = 0; i < y; i++) {
		boxw _boxw;
		for (int j = 0; j < x; j++)
			_boxw.push_back(SPoints());
		_box.push_back(_boxw);
	}

	for (auto& pt : pts)
		_box[pt.y - _ymin + 1][pt.x - _xmin + 1].push_back(pt);

	pts.clear();
	for(auto & _boxw : _box)
		for (auto& _pts : _boxw)
			if (_pts.size() > 0) {
				SPoint zmin = _pts[0];
				for (auto& _pt : _pts)
					zmin = zmin.z < _pt.z ? zmin : _pt;
				pts.push_back(zmin);
			}
}





void SView::Transform(double tx, double ty, double tz, double rx, double ry, double rz)
{
	move(tx, ty, tz);
	rota(rx, ry, rz);
}

void SView::move(double x, double y, double z)
{
	SVector mvx(Coor[0][0], Coor[1][0], Coor[2][0]);
	SVector mvy(Coor[0][1], Coor[1][1], Coor[2][1]);
	SVector mvz(Coor[0][2], Coor[1][2], Coor[2][2]);
	origin = origin + x * mvx;
	origin = origin + y * mvy;
	origin = origin + z * mvz;
	UpView();
}

void SView::rota(double x, double y, double z)
{
	SMatrix rtx, rty, rtz;
	rtx = SMatrix::GetRotateX(x);
	rty = SMatrix::GetRotateY(y);
	rtz = SMatrix::GetRotateY(z);
	Coor = Coor * rtx * rty * rtz;
	origin = origin * rtx * rty * rtz;
	UpView();
}

void SView::moveX(double x)
{
	SVector mvx(Coor[0][0], Coor[1][0], Coor[2][0]);
	origin = origin + x * mvx;
	UpView();
}

void SView::moveY(double y)
{
	SVector mvy(Coor[0][1], Coor[1][1], Coor[2][1]);
	origin = origin + y * mvy;
	UpView();
}

void SView::moveZ(double z)
{
	SVector mvz(Coor[0][2], Coor[1][2], Coor[2][2]);
	origin = origin + z * mvz;
	UpView();
}

void SView::rotaX(double x)
{
	SMatrix rtx;
	rtx = SMatrix::GetRotateX(x);
	Coor = Coor * rtx;// *Coor;
	//origin = origin * rtx;
	UpView();
}

void SView::rotaY(double y)
{
	SMatrix rty;
	rty = SMatrix::GetRotateY(y);
	Coor = Coor * rty;// * Coor;
	//origin = origin * rty;
	UpView();
}

void SView::rotaZ(double z)
{
	SMatrix rtz;
	rtz = SMatrix::GetRotateZ(z);
	Coor = Coor * rtz;// * Coor;
	//origin = origin * rtz;
	UpView();
}
