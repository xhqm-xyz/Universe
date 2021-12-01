#include "SLine.h"

double SLine::GetLength() {
	SPoint len(end.x - star.x, end.y - star.y, end.z - star.z);
	return len.GetModulus();
}

double SLine::AngleLine(SLine line) {
	SVector a(star, end);
	SVector b(line.star, line.end);
	return acos(SVector::GetCos(a, b));
}

double SLine::LenLine(SPoint point) {
	SVector bott(star, end);
	SVector edge(star, point);
	return abs(edge.GetModulus() * SVector::GetSin(edge, bott));
}

bool SLine::InLine(SPoint point) {
	SLine starpt(star, point);
	SLine ptend(point, end);
	double alllen = GetLength();
	double len = starpt.GetLength() + ptend.GetLength();
	return (len / alllen > 1 + SPRECI) ? false : true;
}

bool SLine::InLine(SLine line)
{
	if (InLine(line.star) && InLine(line.end))
		return true;
	return false;
}

SLine SLine::operator=(const SLine& line) {
	star = line.star;
	end = line.end;
	return line;
}

bool SLine::operator==(const SLine& line) {
	if (star == line.star && end == line.end)
		return true;
	return false;
}

bool SLine::operator!=(const SLine& line) {
	return !(*this == line);
}

SLine SLine::operator+=(const SVector& vec)
{
	star += vec;
	end += vec;
	return *this;
}

SLine SLine::operator-=(const SVector& vec)
{
	star -= vec;
	end -= vec;
	return *this;
}

SLine SLine::operator*=(const SMatrix& mat)
{
	star *= mat;
	end *= mat;
	return *this;
}

SLine operator+(const SLine& line, const SVector& vec)
{
	SPoint star = line.star + vec;
	SPoint end = line.end + vec;
	SLine res(star, end);
	res.color = line.color;
	return res;
}

SLine operator-(const SLine& line, const SVector& vec)
{
	SPoint star = line.star - vec;
	SPoint end = line.end - vec;
	SLine res(star, end);
	res.color = line.color;
	return res;
}

SLine operator*(const SLine& line, const SMatrix& mat)
{
	SPoint star = line.star * mat;
	SPoint end = line.end * mat;
	SLine res(star, end);
	res.color = line.color;
	return res;
}

SLine operator*(const SMatrix& mat, const SLine& line)
{
	SPoint star = mat * line.star;
	SPoint end = mat * line.end;
	SLine res(star, end);
	res.color = line.color;
	return res;
}


SCurveline::SCurveline(SLines lis)
{
	for (auto &line : lis)
		lines.push_back(line);
}

SCurveline::SCurveline(SPoints pts)
{
	for (auto pt = pts.begin(); pt != pts.end() - 1; pt++)
		lines.push_back(SLine(*pt, *(pt + 1)));
}

void SCurveline::push_back(SPoint point)
{
	lines.push_back(SLine(lines.end()->end, point));
}

double SCurveline::GetLength()
{
	double len = 0;
	for (auto pt = lines.begin(); pt != lines.end(); pt++)
		len += pt->GetLength();
	return len;
}

double SCurveline::LenCurveline(SPoint point)
{
	double len = lines[0].LenLine(point);
	for (auto line : lines)
		len = SMIN(len, line.LenLine(point));
	return len;
}

bool SCurveline::InCurveline(SPoint point)
{
	for (auto pt = lines.begin(); pt != lines.end(); pt++)
		if (pt->InLine(point))
			return true;
	return false;
}

bool SCurveline::InCurveline(SLine line)
{
	for (auto pt = lines.begin(); pt != lines.end(); pt++)
		if (pt->InLine(line.star) && pt->InLine(line.end))
			return true;
	return false;
}

SLine& SCurveline::operator[](const int n)
{
	return lines[n];
}

SCurveline SCurveline::operator=(const SCurveline& curveline)
{
	lines = curveline.lines;
	return curveline;
}

bool SCurveline::operator==(const SCurveline& curveline)
{
	if (curveline.lines.size() != lines.size())
		return false;
	auto line1 = lines.begin();
	auto line2 = curveline.lines.begin();
	for (; line1 != lines.end(); line1++, line2++)
		if (line1 != line2)
			return false;
	return true;
}

bool SCurveline::operator!=(const SCurveline& curveline)
{
	return !(*this == curveline);
}

SCurveline SCurveline::operator+=(const SVector& vec)
{
	for (auto& line : lines)
		line += vec;
	return *this;
}

SCurveline SCurveline::operator-=(const SVector& vec)
{
	for (auto& line : lines)
		line -= vec;
	return *this;
}

SCurveline SCurveline::operator*=(const SMatrix& mat)
{
	for (auto& line : lines)
		line *= mat;
	return *this;
}
