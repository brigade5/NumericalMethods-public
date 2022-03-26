#include "func.h"
#include <fstream>
#include <iomanip>

std::vector<double> GetGridSplit(double a, double b, int numberOfSegments, double r)
{

	if (a >= b || r <= 0 || numberOfSegments < 1)
	{
		throw 0;
	}

	auto lengthOfTheFirstSegment = (r != 1) ? (b - a) * (r - 1) / (pow(r, numberOfSegments) - 1) : (b - a) / numberOfSegments;

	std::vector<double> grid = { a, a + lengthOfTheFirstSegment };

	for (int i{ 2 }; i <= numberOfSegments; ++i)
	{
		auto lengthOfThePreviousSegment = grid[i - 1] - grid[i - 2];
		grid.push_back(grid[i - 1] + lengthOfThePreviousSegment * r);
	}

	return grid;
}

void OutputSplineValuesInTheFile(CubicSpline cubicSpline, double outputStep)
{
	std::ofstream file1("Function_Results.txt");
	std::ofstream file2("Der1_Results.txt");
	std::ofstream file3("Der2_Results.txt");

	double step{ 0.0 };

	std::vector<double> res;

	while (step < 1.00)
	{
		res = cubicSpline.GetValue(step);
		file1 << std::fixed << std::setprecision(10) << step << "            " << res[0] << std::endl;
		file2 << std::fixed << std::setprecision(10) << step << "            " << res[1] << std::endl;
		file3 << std::fixed << std::setprecision(10) << step << "            " << res[2] << std::endl;
		step += outputStep;
	}

	file1.close();
	file2.close();
	file3.close();

	return;
}

std::vector<double> GetFunctionValues(std::vector<double> grid, int stepen)
{
	std::vector<double> result;

	for (const auto& elem : grid)
	{
		result.push_back(pow(elem, stepen));
	}

	return result;
}

std::vector<double> AbsolutApproximationError(CubicSpline cubicSpline, double outputStep, int stepen, std::vector<double> result_h)
{
	double step{ 0.0 };

	std::vector<double> res;
	std::vector<double> errorValues = { 0.0, 0.0, 0.0 };

	bool flag = false;

	while (step < 1.00)
	{

		for (const auto& elem : result_h)
		{
			if (step == elem) flag = true;
		}

		if (flag) 
		{
			flag = false;
			step += outputStep;
			continue;
		}

		res = cubicSpline.GetValue(step); 

		if (errorValues[0] < fabs(pow(step, stepen) - res[0]))
		{
			errorValues[0] = fabs(pow(step, stepen) - res[0]);
		}

		if (errorValues[1] < fabs(stepen * pow(step, stepen - 1) - res[1]))
		{
			errorValues[1] = fabs(stepen * pow(step, stepen - 1) - res[1]);
		}

		if (errorValues[2] < fabs(stepen * (stepen - 1) * pow(step, stepen - 2) - res[2]))
		{
			errorValues[2] = fabs(stepen * (stepen - 1) * pow(step, stepen - 2) - res[2]);
		}

		step += outputStep;
	}

	return errorValues;
}