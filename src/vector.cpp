#include <math.h>
#include "types.h"

double vec3_len(Vec3 vec){
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

Vec3 vec3_normalize(Vec3 vec){
	Vec3 ret;
	double len = vec3_len(vec);
	ret.x = vec.x/len;
	ret.y = vec.y/len;
	ret.z = vec.z/len;
	return ret;
}

Vec3 vec3_sub(Vec3 a, Vec3 b){
	Vec3 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

Vec3 vec3_sum(Vec3 a, Vec3 b){
	Vec3 ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

double vec3_dot(Vec3 a, Vec3 b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

double vec3_distance(Vec3 a, Vec3 b){
	return sqrt((a.x-b.x)*(a.x-b.x) +
		(a.y-b.y)*(a.y-b.y) +
		(a.z+b.z)*(a.z+b.z));
}
