#include <iostream>
#include <iomanip>
#include <functional>
#include "IntegrationSchemeOnTheSegment.h"

int main()
{
	// Подынтегральная функция f(x) = 4x^3
	std::function<double(const double& P)> f = [](const double& P) { return 4 * pow(P, 3); };

	// Первообразная F(x) = x^4
	std::function<double(const double& P)> F = [](const double& P) { return pow(P, 4); };

	// Квадратурная формула Гаусс-1
	IntegrationSchemeOnTheSegment QuadratureFormula(IntegrationScheme::Gauss4);

	// Начало и конец отрезка интегрирования
	double begin = 0.0;
	double end = 1.0;

	const int Num_Segments = 1;

	// Точное значение интеграла
	double I_True = F(end) - F(begin);

	double I[3];

	for (int k{ 0 }; k < 3; k++)
	{
		I[k] = QuadratureFormula.CalculateIntegral(begin, end, Num_Segments * pow(2, k), f);

		std::cout << std::fixed;
		std::cout << "h = " << (end - begin) / double(Num_Segments * pow(2, k)) << std::setw(15);
		std::cout << "I = " << I[k] << std::endl;
		std::cout << std::scientific;
		std::cout << "|I - I_True| = " << fabs(I[k] - I_True) << std::endl << std::endl;
	}

}