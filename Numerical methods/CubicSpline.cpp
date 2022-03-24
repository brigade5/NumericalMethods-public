#include "CubicSpline.h"

void CubicSpline::UpdateSpline(const std::vector<double> points_in, const std::vector<double> f_value)
{

	points.clear();
    for (auto & elem : points_in) points.push_back(elem);

	int countSegments = points.size() - 1;

	double h_current, h_next;

	a.resize(countSegments);
	b.resize(countSegments);
	c.resize(countSegments);
	d.resize(countSegments);

	std::vector<double> right(countSegments - 1);

	for(int i{0}; i < countSegments - 1; i++)
	{
		h_current = points[i + 1] - points[i];
		h_next = points[i + 2] - points[i + 1];

		a[i + 1] = h_current;
		b[i] = 2 * (h_current + h_next);
		d[i] = h_next;
        
		right[i] = 3.0 * ((f_value[i + 2] - f_value[i + 1]) / h_next - (f_value[i + 1] - f_value[i]) / h_current);      
	}
 
	for(int i{2}; i < countSegments; i++)
	{
		b[i - 1] -= a[i - 1] / b[i - 2] * d[i - 2];
		right[i - 1] -= a[i - 1] / b[i - 2] * right[i - 2];
	}

	c[countSegments - 1] = right[countSegments - 2] / b[countSegments - 2];
   
	for(int i{countSegments - 1}; i > 1; i--)
		c[i - 1] = (right[i - 2] - c[i] * d[i - 2]) / b[i - 2];

	c[0] = 0.0;

	for (int i {1}; i < countSegments; i++)
	{
		h_current = points[i] - points[i - 1];
		a[i - 1] = f_value[i - 1];
		b[i - 1] = (f_value[i] - f_value[i - 1]) / h_current - (c[i] + 2.0 * c[i - 1]) * h_current / 3.0;
		d[i - 1] = (c[i] - c[i - 1]) / h_current / 3.0;
	}


	h_current = points[countSegments] - points[countSegments - 1];

	a[countSegments - 1] = f_value[countSegments - 1];
	b[countSegments - 1] = (f_value[countSegments] - f_value[countSegments - 1]) / h_current - 2.0 * c[countSegments - 1] * h_current / 3.0;
	d[countSegments - 1] = -1*c[countSegments - 1] / (h_current * 3.0);

    
    return;
}

std::vector<double> CubicSpline::GetValue(const double point)
{
	double zero {1e-16};

	int countSegments = points.size() - 1;

	for (int i{0}; i < countSegments; i++)
	{

		if (point > points[i] && point < points[i + 1] || fabs(point - points[i]) < zero || fabs(point - points[i + 1]) < zero)
		{
			double diff{point - points[i]};

			std::vector<double> derivatives;

			derivatives.push_back(a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * diff * diff * diff);
			derivatives.push_back(b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * diff * diff);
			derivatives.push_back(2.0 * c[i] + 6.0 * d[i] * diff);

			return derivatives;
		}

	}
    throw 0;
}