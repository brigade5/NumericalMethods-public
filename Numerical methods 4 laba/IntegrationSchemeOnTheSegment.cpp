#include "IntegrationSchemeOnTheSegment.h"

IntegrationSchemeOnTheSegment::IntegrationSchemeOnTheSegment(IntegrationSchemeType typeOfFormula)
{
	// ���������� �������� ����� � ����� ��������������
	switch (typeOfFormula)
	{

	// ����� �����-1
	case Gauss1:
	{

		nodes = { 0.0 };
		weights = { 2.0 };

		break;
	}

	// ����� �����-2
	case Gauss2:
	{

		weights = { 1.0, 1.0 };
		nodes = { -1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };

		break;
	}

	// ����� �����-3
	case Gauss3:
	{

		weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
		nodes = { -sqrt(3.0 / 5.0), 0, sqrt(3.0 / 5.0) };

		break;
	}

	// ����� �����-4
	case Gauss4:
	{

		weights = 
		{ 
		  (18.0 + sqrt(30.0)) / 36.0, 
		  (18.0 + sqrt(30.0)) / 36.0, 
		  (18.0 - sqrt(30.0)) / 36.0, 
		  (18.0 - sqrt(30.0)) / 36.0
		};

		nodes = 
		{ 
		  sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0), 
		 -sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0), 
		  sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0), 
		 -sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0) 
		};

		break;
	}

	// ����� �����-5
	case Gauss5:
	{
		weights = 
		{ 
		   128.0 / 225.0, 
		  (322.0 + 13.0 * sqrt(70.0)) / 900.0, 
		  (322.0 + 13.0 * sqrt(70.0)) / 900.0, 
		  (322.0 - 13.0 * sqrt(70.0)) / 900.0, 
		  (322.0 - 13.0 * sqrt(70.0)) / 900.0 
		};

		nodes = 
		{ 
		   0.0, 
		  (1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)), 
		 -(1.0 / 3.0) * sqrt(5.0 - 2.0 * sqrt(10.0 / 7.0)), 
		  (1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)), 
		 -(1.0 / 3.0) * sqrt(5.0 + 2.0 * sqrt(10.0 / 7.0)) 
		};

		break;
	}

	// ����� ��������
	case Trapezoid:
	{
		weights = { 1.0, 1.0 };
		nodes = { -1.0, 1.0 };

		break;
	}

	// ����� �������
	case Parabola:
	{
		weights = { 4.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0 };
		nodes = { 0.0, 1.0, -1.0 };

		break;
	}

	}
}

double IntegrationSchemeOnTheSegment::CalculateIntegral(const double& startOfTheSegment, const double& endOfTheSegment, int numberOfSegments, const std::function<double(const double& P)>& func) const
{

	double result = 0.0;

	double x0;

	double h = (endOfTheSegment - startOfTheSegment) / numberOfSegments;

	// ����� �� ���� ��������� ���������
	for (int i = 0; i < numberOfSegments; i++)
	{
		// ��������� ����� ��������
		x0 = startOfTheSegment + i * h;

		// ����� �� ����� ��������������
		for (int i{ 0 }; i < nodes.size(); i++)
		{
			double P = x0 + (1 + nodes[i]) * h / 2.0;
			result += weights[i] * func(P);
		}
	}

	// ��������� ���������
	return result * (h / 2.0);
}