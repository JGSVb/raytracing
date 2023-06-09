#pragma once
// #include <math.h>
#include <cmath>

class Vec3 {
	public:
	double e[3];

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	
	Vec3(void) : e{0, 0, 0} {}
	Vec3(double x, double y, double z) : e{x, y, z} {}

	double length(void){
		return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
	}
	Vec3 *normalize(void){
		double len = length();
		e[0] /= len;
		e[1] /= len;
		e[2] /= len;
		return this;
	}
};

Vec3 vec3_normalize(Vec3 vec);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_sum(Vec3 a, Vec3 b);
double vec3_distance(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);

using Point3 = Vec3;
using Color3 = Vec3;

typedef struct {
	double r,g,b,a;
} Color3;

typedef struct {
	Vec3 ori;
	Vec3 dir;
} Ray;

typedef struct {
	Color3 col;
} Material;
 
typedef struct {
	Vec3 center;
	double r;
} Sphere;

typedef struct {
	Point3 aa;
	Point3 bb;
	Point3 cc;
} Triangle;

typedef struct {
	Sphere   *sph;
	Triangle *tri;
	Material *mat;
} Hittable;

typedef struct {
	Vec3 pos;
	Vec3 dir;
} Camera;

typedef struct {
	Color3 *pixels;
	int wid, hei;
} Image;



Vec3 ray_point(Ray ray, double t);

Image *image_new(int wid, int hei);
void image_destroy(Image *img);
Color3 image_get_color(Image *img, int xx, int yy);
Color3 image_set_color(Image *img, int xx, int yy, Color3 *col);
Color3 image_set_pixel(Image *img, int xx, int yy, double r, double g, double b, double a);
