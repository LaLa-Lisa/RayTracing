#pragma once
#include "vec3d.hpp"

class Camera {
public:
	vec3d<double> c_point; // центр
	vec3d<double> c_x; // координаты вектора
	vec3d<double> c_y;
	vec3d<double> c_z;
	double cs_dist = 2; // дистанция от камеры до экрана
	double view_angle = 50; // угол обзора
	double render_distance = 500; // дальность прорисовки

	//конструктор
	Camera(vec3d<double> _c_point, vec3d<double> _c_x, vec3d<double> _c_y, vec3d<double> _c_z)
		: c_point(_c_point),
		c_x(_c_x),
		c_y(_c_y),
		c_z(_c_z)
	{}

	//проверяет всё ли хорошо с камерой
	bool is_orthonormal() {

		// ...code....

		return true;
	}
};