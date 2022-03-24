#include "SmoothingSpline.h"
#include <iostream>
#include <functional>

SmoothingSpline::SmoothingSpline(const double smooth)
{
	smoothing = smooth;
}

void SmoothingSpline::Transition(int numberOfSegment, const double X, double& ksi)
{
	ksi = 2.0 * (X - points[numberOfSegment]) / (points[numberOfSegment + 1] - points[numberOfSegment]) - 1.0;
}

double SmoothingSpline::Basis(int numberOfFunction, const double ksi)
{

	if (numberOfFunction == 1) return 0.5 * (1 - ksi);
	else if (numberOfFunction == 2) return 0.5 * (1 + ksi);
	else throw 0;

}

double SmoothingSpline::Der_Basis(int numberOfFunction, const double ksi)
{

	if (numberOfFunction == 1) return -0.5;
	else if (numberOfFunction == 2) return 0.5;
	else throw 1;

}

void SmoothingSpline::UpdateSpline(const std::vector<double> points_in, const std::vector<double> f_value)
{
	points.clear();
	for (auto& elem : points_in) points.push_back(elem);

	int countSegments{countSegments};

	alpha.resize(points.size());

	std::vector <double> a, b, c;

	a.resize(points.size());
	b.resize(points.size());
	c.resize(points.size());

    std::function<void(int countSegments, const double &P, const double &f_value, const double &omega)>
    Assembly = [&](int seg, const double &P, const double &f_value, const double &omega)
    {
        double x{P}, ksi;

        Transition(seg, x, ksi);

        double f1 = Basis(1,ksi), f2 = Basis(2,ksi);

        b[seg] += (1.0 - smoothing) * omega * f1 * f1;
        b[seg + 1] += (1.0 - smoothing) * omega * f2 * f2;
        a[seg + 1] += (1.0 - smoothing) * omega * f1 * f2;
        c[seg] += (1.0 - smoothing) * omega * f2 * f1;

        alpha[seg] += (1.0 - smoothing) * omega * f1 * f_value;
        alpha[seg + 1] += (1.0 - smoothing) * omega * f2 * f_value;

    };

    for (int i{0}; i < countSegments; ++i)
    {
        double Omega{1.0};
        Assembly(i, points[i], f_value[i], Omega);
        Assembly(i, points[i + 1], f_value[i + 1], Omega);

        double h = points[i + 1] - points[i];
        b[i] += 1.0 / h * smoothing;
        b[i + 1] += 1.0 / h * smoothing;
        a[i + 1] -= 1.0 / h * smoothing;
        c[i] -= 1.0 / h * smoothing;
    }

    for(int i{1}; i < countSegments + 1; ++i)
    {
        b[i] -= a[i] / b[i - 1] * c[i - 1];
        alpha[i] -= a[i] / b[i - 1] * alpha[i - 1];
    }
    alpha[countSegments] /= b[countSegments];

    for(int i{countSegments - 1}; i >= 0; --i)
        alpha[i] = (alpha[i] - alpha[i + 1] * c[i]) / b[i];
}

std::vector<double> SmoothingSpline::GetValue(const double point)
{
	double zero{1e-7};

	int countSegments = points.size() - 1;

	std::vector<double> result;

	for (int i{0}; i < countSegments; ++i)
	{

		if (point > points[i] && point < points[i + 1] || abs(point - points[i]) < zero || abs(point - points[i + 1]) < zero)
		{
			double h{points[i + 1] - points[i]}, ksi;

			Transition(i, point, ksi);

			result.push_back(alpha[i] * Basis(1, ksi) +alpha[i + 1] * Basis(2, ksi));
			result.push_back(alpha[i] * Der_Basis(1, ksi) + alpha[i + 1] * Der_Basis(2, ksi));
			result.push_back(0.0);

			return result;
		}

	}

	throw 2;

}