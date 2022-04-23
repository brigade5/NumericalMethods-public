#pragma once
#ifndef IntegrationScheme_h
#define IntegrationScheme_h

#include <vector>

// ����� ��������������
class IntegrationScheme
{

protected:
	// ���� ��������������
	std::vector<double> nodes;

	// ���� ������������ �������
	std::vector<double> weights;

public:

	// ���� ������������ ������
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