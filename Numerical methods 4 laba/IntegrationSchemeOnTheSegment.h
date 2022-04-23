#pragma once
#ifndef IntegrationSchemeOnTheSegment_h
#define IntegrationSchemeOnTheSegment_h

#include "IntegrationScheme.h"
#include <functional>

class IntegrationSchemeOnTheSegment : protected IntegrationScheme
{
public:

	IntegrationSchemeOnTheSegment(IntegrationSchemeType typeOfFormula);

	// ����� ���������� ������������� ���������
	double CalculateIntegral(const double& startOfTheSegment, const double& endOfTheSegment, int numberOfSegments, const std::function<double(const double& P)>& func) const;

};


#endif