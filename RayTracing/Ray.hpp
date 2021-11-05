#pragma once
#include "vec3d.hpp"

class Ray {
public:
	vec3d<double> stPoint; // ��������� �����
	vec3d<double> vec; // ��� ������
	int countRecflections = 0;
	double intense = 1; // ������������� � ������ ������� �������� ����� ���������
	Ray(vec3d<double> _stPoint, vec3d<double> _vec) : stPoint(_stPoint), vec(_vec) {}
private:

};