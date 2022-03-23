#pragma once
#ifndef func_h
#define func_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include "CubicSpline.h"


std::vector<double> GetGridSplit(double a, double b, int numberOfSegments, double r);

void OutputSplineValuesInTheFile(CubicSpline cubicSpline, double outputStep);

std::vector<double> GetFunctionValues(std::vector<double> grid);

std::vector<double> AbsolutApproximationError(CubicSpline cubicSpline, double outputStep);

#endif