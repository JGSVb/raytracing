#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "types.h"
#include "render.h"

#define SDL_ERR_EXIT(label) do { printf("%s: %s\n", label, SDL_GetError()); exit(-1); } while(0)

#define WINWID 1600
#define WINHEI 500
#define LOOPDELAY 30
static const char *WINTITLE = "RayTracing";

static struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Camera *camera;
	Image *image;
} G_app;

void graphics_init(void);
void graphics_quit(void);
bool compute_events(void);

void plot_pixel(int x, int y, double r, double g, double b, double a);
void graphics_show_image(Image *img);

void graphics_init(void){

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_ERR_EXIT("Impossível iniciar o vídeo SDL");
	}

	G_app.window = SDL_CreateWindow(WINTITLE,
				 SDL_WINDOWPOS_CENTERED,
				 SDL_WINDOWPOS_CENTERED,
				 WINWID,
				 WINHEI,
				 0);

	if(G_app.window == NULL){
		SDL_ERR_EXIT("Impossível criar janela");
	}

	G_app.renderer = SDL_CreateRenderer(G_app.window, -1, 0);

	if(G_app.renderer == NULL){
		SDL_ERR_EXIT("Impossível criar renderizador");
	}
}

void graphics_quit(void){
	SDL_DestroyRenderer(G_app.renderer);
	SDL_DestroyWindow(G_app.window);
	SDL_Quit();
}

void plot_pixel(int x, int y, double r, double g, double b, double a){
	SDL_SetRenderDrawColor(G_app.renderer, r*255, g*255, b*255, 255);
	SDL_RenderDrawPoint(G_app.renderer, x, y);
}

bool compute_events(void){
	SDL_Event ev;

	while(SDL_PollEvent(&ev)){
		switch(ev.type){
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN: {
				switch(ev.key.keysym.sym){
					case(SDLK_LEFT):
						G_app.camera->dir.x += 0.01;
						G_app.camera->dir = vec3_normalize(G_app.camera->dir);
						break;
					case(SDLK_RIGHT):
						G_app.camera->dir.x -= 0.01;
						G_app.camera->dir = vec3_normalize(G_app.camera->dir);
						break;
					default:
						break;

				}
				break;
			}
			default:
				break;
		}
	}

	return true;
}

void graphics_show_image(Image *img){
	for(int yy = 0; yy < img->hei; yy++){
		for(int xx = 0; xx < img->wid; xx++){
			Color pixel = image_get_color(img, xx,yy);
			plot_pixel(xx, yy, pixel.r, pixel.g, pixel.b, pixel.a);
		}
	}
}

int main(int argc, char **argv){

	render_init();

	Camera cam = {(Vec3){0, 0, 0}, (Vec3){0, 0, 1}};
	G_app.camera = &cam;

	Sphere sph1 = {
		.center = (Vec3){0,0,1},
		.r = 0.05,
	};
	Material mat1 = {
		.col = (Color){1,0,0,1},
	};

	Hittable hit1;
	hit1.sph = &sph1;
	hit1.tri = NULL;
	hit1.mat = &mat1;
	render_add_hittable(&hit1);

	render_set_camera(&cam);

	graphics_init();

	G_app.image = image_new(WINWID, WINHEI);

	while(compute_events()){
		render(G_app.image);
		graphics_show_image(G_app.image);
		SDL_RenderPresent(G_app.renderer);
		SDL_Delay(LOOPDELAY);
	}

	image_destroy(G_app.image);
	render_quit();
	graphics_quit();

	return 0;
}
