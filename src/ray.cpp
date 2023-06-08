#include "types.h"

Vec3 ray_point(Ray ray, double t){
	Vec3 vec;
	vec.x = ray.ori.x + ray.dir.x*t;
	vec.y = ray.ori.y + ray.dir.y*t;
	vec.z = ray.ori.z + ray.dir.z*t;
	return vec;
}

