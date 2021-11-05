#pragma once
#include <iostream>
//#define double float
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define PI 3.14159265358979323846

template<typename T>
class vec3d {
public:
	T x, y, z;
	vec3d(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	vec3d(const vec3d<T>& in_vec) : x(in_vec.x), y(in_vec.y), z(in_vec.z) {}
	T lenght() {
		return sqrt(x * x + y * y + z * z);
	}
	void normalize() {
		T len = this->lenght();
		if (!len) throw("ded already inside");
		x /= len;
		y /= len;
		z /= len;
	}

	void rotateYZ(T rot_angle) {
		y = y * cos(rot_angle) - z * sin(rot_angle);
		z = y * sin(rot_angle) + z * cos(rot_angle);
		this->normalize();
	}
};

template<typename T>
T operator* (const vec3d<T>& vec1, const vec3d<T>& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

template<typename T>
vec3d<T> operator* (const T scalar, const vec3d<T>& vec) {
	return vec3d<T>(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

template<typename T>
vec3d<T> operator+ (const vec3d<T>& vec1, const vec3d<T>& vec2) {
	return vec3d<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

template<typename T>
vec3d<T> operator- (const vec3d<T>& vec1, const vec3d<T>& vec2) {
	return vec3d<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

template<typename T>
vec3d<T> cross_product(vec3d<T>& vec1, vec3d<T>& vec2) {
	T i = vec1.y * vec2.z - vec2.y * vec1.z;
	T j = vec2.x * vec1.z - vec1.x * vec2.z;
	T k = vec1.x * vec2.y - vec2.x * vec1.y;
	return vec3d<T>(i, j, k);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const vec3d<T>& vec) {
	stream << vec.x << " " << vec.y << " " << vec.z << "\n";
	return stream;
}


template class vec3d<float>;
template class vec3d<double>;