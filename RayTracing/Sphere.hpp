#pragma once
#include "vec3d.hpp"

class Sphere {
public:
	vec3d<double> center;
	double radius;
	Sphere(vec3d<double> _center, double _radius) :
		center(_center),
		radius(_radius)
	{}
	double is_hitted(vec3d<double> ray_start_point, vec3d<double> ray) {
		double a = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
		double b = -2 * (center.x * ray.x + center.y * ray.y + center.z * ray.z);
		double c = center.x * center.x + center.y * center.y + center.z * center.z - radius * radius;

		//дискриминант 
		double Discriminant = b * b - 4 * a * c;
		if (Discriminant < 0) return 0;
		double coeff1 = (-b + sqrt(Discriminant)) / (2 * a);
		double coeff2 = (-b - sqrt(Discriminant)) / (2 * a);
		if (coeff1 <= 0 || coeff2 <= 0) return 0;
		return min(coeff1, coeff2);
	}
};