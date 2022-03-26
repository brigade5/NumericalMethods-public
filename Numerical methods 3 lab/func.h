#pragma once
#ifndef func_h
#define func_h

#include <iostream>
#include "CubicSpline.h"

// Генерация равномерной сетки отрезка [a, b], в зависимости от числа сегментов разбиения numberOfSegments и величины коэффициента разрядки r
std::vector<double> GetGridSplit(double a, double b, int numberOfSegments, double r);

// Вывод значений сплайна и его первых двух производных в отдельные файлы
void OutputSplineValuesInTheFile(CubicSpline cubicSpline, double outputStep);

// Получение значений табличной функции в узловых точках сетки
std::vector<double> GetFunctionValues(std::vector<double> grid, int stepen);

// Получение абсолютной погрешности аппроксимации исходной функции, а также её первой и второй производных
std::vector<double> AbsolutApproximationError(CubicSpline cubicSpline, double outputStep, int stepen, std::vector<double> result_h);

#endif