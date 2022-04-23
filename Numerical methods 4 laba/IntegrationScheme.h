#pragma once
#ifndef IntegrationScheme_h
#define IntegrationScheme_h

#include <vector>

// Схема интегрирования
class IntegrationScheme
{

protected:
	// Узлы интегрирования
	std::vector<double> nodes;

	// Веса квадратурной формулы
	std::vector<double> weights;

public:

	// Типы квадратурных формул
	enum IntegrationSchemeType
	{
		Gauss1,
		Gauss2,
		Gauss3,
		Gauss4,
		Gauss5,
		Trapezoid,
		Parabola,
	};

};

#endif