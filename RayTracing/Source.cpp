#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <cmath>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "vec3d.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

auto convert_to_rad = [](double angle) { return angle * PI / 180.0; };


class Scene {
private:
	//размеры сцены
	const int width;
	const int height;

	//длина экрана в пространстве
	double scr_size;

	// соотношени€ замера диспле€ к его размеру в 3д
	double coeff_width;
	double coeff_height;


	//ширина плитки пола (квадрат)
	double tile_size = 5;

	bool is_floor(vec3d<double> ray_start_point, vec3d<double> ray) {
		double floor_level = 0;
		if (ray.z * ray_start_point.z < 0) {
			double coeff = -1 * ray_start_point.z / ray.z;
			if (coeff >= camera.render_distance) return false;
			return is_tile(ray_start_point.x + coeff * ray.x, ray_start_point.y + coeff * ray.y);
		}
		else return false;
	}
	bool is_tile(double x, double y) {
		int x_p = x / tile_size + 1;
		int y_p = y / tile_size + 1;
		if ((x_p + y_p) % 2) return true;
		return false;
	}
public:
	Camera camera;
	std::vector<Sphere> balls;

	//конструктор
	Scene(Camera _camera, const int _width, const int _height)
		: camera(_camera),
		width(_width),
		height(_height)
	{
		scr_size = 2 * camera.cs_dist * tan(convert_to_rad(camera.view_angle) / 2);
		coeff_width = scr_size / (double)width;
		coeff_height = scr_size / (double)height;
	}

	//создаЄт картинку котора€ будет передаватьс€ дисплею
	///(отдать јлексу)
	std::vector<std::vector<olc::Pixel>> make_picture() {
		if (!camera.is_orthonormal()) throw("invalid cameraman");

		std::vector<std::vector<olc::Pixel>> res(width);

		for (int i = 0; i < width; ++i)
		{
			res[i].resize(height);

			for (int j = 0; j < height; ++j)
			{
				// преобразование к локальным вещественным координатам
				double scr_loc_x = (double)j * coeff_height - scr_size / 2;
				double scr_loc_y = (double)(width - i) * coeff_width - scr_size / 2;

				// получение глобальной координаты точки на экране
				vec3d<double> scr_dot = camera.c_point + camera.cs_dist * camera.c_z + scr_loc_x * camera.c_x + scr_loc_y * camera.c_y;

				vec3d<double> ray = scr_dot - camera.c_point;

				olc::Pixel color = olc::BLUE;
				color = is_floor(camera.c_point, ray) ? olc::WHITE : olc::BLUE;
				for (auto& sph : balls) {
					double intense = sph.is_hitted(camera.c_point, ray);
					if (intense) {
						color = olc::Pixel((int)(intense * 80) % 255, (int)(intense * 80) * 1000 % 255, (int)(intense * 80) * 100 % 255);
					}
				}
				res[i][j] = color;
			}
		}

		return res;
	}

	void add_ball(vec3d<double> _center, double _radius) {
		balls.push_back(Sphere(_center, _radius));
	}
};

class Display : public olc::PixelGameEngine {
public:

	Display(int _width, int _height, Camera camera) :
		width(_width), 
		height(_height), 
		scene(Scene(camera, _width, _height))
	{
		vec3d<double> ball_center(0, -20, 2);
		scene.add_ball(ball_center, 5);
	}
	void print(std::vector<std::vector<olc::Pixel>> image) {
		for (int i = 0; i < min(image.size(), width); ++i) {
			for (int j = 0; j < min(image[i].size(), height); ++j) {
				Draw(j, i, image[i][j]);
			}
		}
	}
	std::pair<int, int> getResolution() {
		return std::make_pair(this->width, this->height);
	}

	bool OnUserCreate() override
	{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		std::vector<std::vector<olc::Pixel>> imageP = scene.make_picture();
		scene.camera.c_y = rotateByAxis(scene.camera.c_x, scene.camera.c_y, 0.01);
		scene.camera.c_z = rotateByAxis(scene.camera.c_x, scene.camera.c_z, 0.01);
		this->print(imageP);
		return true;
	}

private:
	Scene scene;
	const int width = -1;
	const int height = -1;
	clock_t Lasttime = clock();
};


int main()
{
	vec3d<double> a(3, 3, 20);
	vec3d<double> b(1, 0, 0);
	vec3d<double> c(0, 1, 0);
	vec3d<double> d(0, 0, 1);
	Camera camera(a, b, c, d);
	Display demo(720, 720, camera);
	if (demo.Construct(720, 720, 1, 1))
		demo.Start();

	return 0;
}