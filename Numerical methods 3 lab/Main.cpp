#include "iostream"
#include <iomanip>
#include "func.h"

int main()
{
	// Равномерная сетка для отрезка [0, 1] с шагом 0,1
	std::vector<double> result_h = GetGridSplit(0.0, 1.0, 10, 1.0);

	// Равномерная сетка для отрезка [0, 1] с шагом 0,05
	std::vector<double> result_h_2 = GetGridSplit(0.0, 1.0, 20, 1.0);

	// Равномерная сетка для отрезка [0, 1] с шагом 0,025
	std::vector<double> result_h_4 = GetGridSplit(0.0, 1.0, 40, 1.0);

	// Значения табличной функции в узловых точках сетки
	std::vector<double> fValue_x_h = GetFunctionValues(result_h, 3);

	// Кубический интерполяционный сплайн
	CubicSpline cubicSpline;

	// Построение сплайна
	cubicSpline.UpdateSpline(result_h, fValue_x_h);

	// Вывод значений сплайна, а также его первой и второй производных, в отдельные файлы
	OutputSplineValuesInTheFile(cubicSpline, 0.005);

	// Расчёт абсолютной погрешности
	std::vector<double> l = AbsolutApproximationError(cubicSpline, 0.005, 3, result_h);

	std::cout << std::fixed << std::setprecision(10) << "max|f(x) - P(x)|: " << l[0] << std::endl; 
	std::cout << std::fixed << std::setprecision(10) << "max|f'(x) - P'(x)|: " << l[1] << std::endl;
	std::cout << std::fixed << std::setprecision(10) << "max|f''(x) - P''(x)|: " << l[2] << std::endl;

	return 0;
}