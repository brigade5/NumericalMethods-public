#pragma once
#ifndef CubicSpline_h
#define CubicSpline_h

#include "AbstractSpline.h"

class CubicSpline : public AbstractSpline
{
private:
	std::vector<double> points;
	std::vector<double> a, b, c, d;

public:
	void UpdateSpline(const std::vector<double> points, const std::vector<double> f_value);
	std::vector<double> GetValue(const double point);
};


#endif