#pragma once
#ifndef IntegrationSchemeOnTheSegment_h
#define IntegrationSchemeOnTheSegment_h

#include "IntegrationScheme.h"
#include <functional>

class IntegrationSchemeOnTheSegment : protected IntegrationScheme
{
public:

	IntegrationSchemeOnTheSegment(IntegrationSchemeType typeOfFormula);

	// ћетод вычислени€ определенного интеграла
	double CalculateIntegral(const double& startOfTheSegment, const double& endOfTheSegment, int numberOfSegments, const std::function<double(const double& P)>& func) const;

};


#endif