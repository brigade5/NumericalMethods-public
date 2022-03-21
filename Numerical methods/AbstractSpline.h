#pragma once
#ifndef AbstractSpline_h
#define AbstractSpline_h

#include "iostream"
#include "vector"
#include <cmath>

class AbstractSpline
{
public:
	virtual void UpdateSpline(const std::vector<double> points, const std::vector<double> f_value) = 0;
	virtual std::vector<double> GetValue(const double point) = 0;
};

#endif