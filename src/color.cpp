#include <stdlib.h>
#include "types.h"

Color color_mix(Color a, Color b, double fac){
	Color col;
	col.r = (1-fac)*a.r + fac*b.r;
	col.g = (1-fac)*a.g + fac*b.g;
	col.b = (1-fac)*a.b + fac*b.b;
	col.a = (1-fac)*a.a + fac*b.a;
	return col;
}

Color color_div(Color a, double fac){
	Color col;
	col.r = a.r / fac;
	col.g = a.g / fac;
	col.b = a.b / fac;
	col.a = a.a / fac;
	return col;
}

Color color_mul(Color a, double fac){
	Color col;
	col.r = a.r * fac;
	col.g = a.g * fac;
	col.b = a.b * fac;
	col.a = a.a * fac;
	return col;
}

Color color_product(Color a, Color b){
	Color col;
	col.r = a.r * b.r;
	col.g = a.g * b.g;
	col.b = a.b * b.b;
	col.a = a.a * b.a;
	return col;
}

Color color_sum(Color a, Color b){
	Color col;
	col.r = a.r + b.r;
	col.g = a.g + b.g;
	col.b = a.b + b.b;
	col.a = a.a + b.a;
	return col;
}
