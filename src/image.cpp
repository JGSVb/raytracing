#include <stdlib.h>
#include "types.h"

Image *image_new(int wid, int hei){
	Image *img = (Image *)malloc(sizeof(Image));
	img->wid = wid;
	img->hei = hei;
	img->pixels = (Color *)malloc(sizeof(Color)*wid*hei);
	return img;
}

void image_destroy(Image *img){
	free(img->pixels);
	free(img);
}

Color image_get_color(Image *img, int xx, int yy){
	return img->pixels[yy*img->wid + xx];
}

Color image_set_pixel(Image *img, int xx, int yy, double r, double g, double b, double a){
	Color col = (Color){r,g,b,a};
	return image_set_color(img, xx, yy, &col);
}

Color image_set_color(Image *img, int xx, int yy, Color *col){
	Color old = image_get_color(img, xx, yy);
	img->pixels[yy*img->wid + xx] = *col;
	return old;
}
