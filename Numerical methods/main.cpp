#include "iostream"
#include <iomanip>
#include "func.h"





int main()
{
	std::vector<double> result_h = GetGridSplit(2.0, 1.0, 10, 1.0);
	std::vector<double> result_h_2 = GetGridSplit(0.0, 1.0, 20, 1.0);
	std::vector<double> result_h_4 = GetGridSplit(0.0, 1.0, 40, 1.0);

	std::vector<double> fValue_x_h_4 = GetFunctionValues(result_h_4);

	CubicSpline cubicSpline;

	cubicSpline.UpdateSpline(result_h_4, fValue_x_h_4);

	OutputSplineValuesInTheFile(cubicSpline, 0.005);

	std::vector<double> l = AbsolutApproximationError(cubicSpline, 0.005);

	std::cout << std::fixed << std::setprecision(10) << l[0] << " " << l[1] << std::endl;

	return 0;
}