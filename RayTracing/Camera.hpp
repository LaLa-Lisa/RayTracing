#pragma once
#include "vec3d.hpp"

class Camera {
public:
	vec3d<double> c_point; // �����
	vec3d<double> c_x; // ���������� �������
	vec3d<double> c_y;
	vec3d<double> c_z;
	double cs_dist = 2; // ��������� �� ������ �� ������
	double view_angle = 50; // ���� ������
	double render_distance = 500; // ��������� ����������

	//�����������
	Camera(vec3d<double> _c_point, vec3d<double> _c_x, vec3d<double> _c_y, vec3d<double> _c_z)
		: c_point(_c_point),
		c_x(_c_x),
		c_y(_c_y),
		c_z(_c_z)
	{}

	//��������� �� �� ������ � �������
	bool is_orthonormal() {

		// ...code....

		return true;
	}
};