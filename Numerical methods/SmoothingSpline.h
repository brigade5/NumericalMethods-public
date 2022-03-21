#pragma once
#ifndef SmoothingSpline_h
#define SmoothingSpline_h

#include "AbstractSpline.h"

class SmoothingSpline : public AbstractSpline
{
private:
	double smoothing;

	std::vector<double> points;
	std::vector<double> alpha;

	void Transition(int numberOfSegment, const double X, double &ksi);
	double Basis(int numberOfFunction, const double ksi);
	double Der_Basis(int numberOfFunction, const double ksi);


public:
	SmoothingSpline(const double smooth);
	void UpdateSpline(const std::vector<double> points_in, const std::vector<double> f_value);
	std::vector<double> GetValue(const double point);
};

#endif