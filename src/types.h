#pragma once
#include <math.h>

typedef struct {
	double x,y,z;
} Vec3;

typedef Vec3 Point;

typedef struct {
	double r,g,b,a;
} Color;

typedef struct {
	Vec3 ori;
	Vec3 dir;
} Ray;

typedef struct {
	Color col;
} Material;
 
typedef struct {
	Vec3 center;
	double r;
} Sphere;

typedef struct {
	Point aa;
	Point bb;
	Point cc;
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
	Color *pixels;
	int wid, hei;
} Image;

double vec3_len(Vec3 vec);
Vec3 vec3_normalize(Vec3 vec);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_sum(Vec3 a, Vec3 b);
double vec3_distance(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);

Vec3 ray_point(Ray ray, double t);

Image *image_new(int wid, int hei);
void image_destroy(Image *img);
Color image_get_color(Image *img, int xx, int yy);
Color image_set_color(Image *img, int xx, int yy, Color *col);
Color image_set_pixel(Image *img, int xx, int yy, double r, double g, double b, double a);

Color color_mix(Color a, Color b, double fac);
Color color_div(Color a, double fac);
Color color_mul(Color a, double fac);
Color color_product(Color a, Color b);
Color color_sum(Color a, Color b);
