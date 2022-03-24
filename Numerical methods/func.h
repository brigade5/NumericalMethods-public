#pragma once
#ifndef func_h
#define func_h

#include <iostream>
#include "CubicSpline.h"


std::vector<double> GetGridSplit(double a, double b, int numberOfSegments, double r);

void OutputSplineValuesInTheFile(CubicSpline cubicSpline, double outputStep);

std::vector<double> GetFunctionValues(std::vector<double> grid, int stepen);

std::vector<double> AbsolutApproximationError(CubicSpline cubicSpline, double outputStep, int stepen, std::vector<double> result_h);

#endif