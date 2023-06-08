#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "render.h"
#include "types.h"

#define DEFAULT_DEPTH 6
#define DEFAULT_AA_SAMPLES 1 
#define DEFAULT_AA_RADIUS 0.00007f

static struct {
	int depth;
	int    aa_samples;
	double aa_radius;
} G_settings;

static struct {
	Hittable **hittable_list;
	int hittable_count;
	Camera *cam;
} G_scene; 

static bool sphere_intersect(const Sphere *sphere, const Ray *ray, double *ret_x1, double *ret_x2);
static bool triangle_intersect(const Triangle *triangle, const Ray *ray, double *x1);
static bool solve_quadratic(double a, double b, double c, double *x1, double *x2);
static bool closest_intersection(const Ray *ray, double *t_return, Hittable **hit_return);
static Color get_color(const Ray *ray);
static double random_double(double a, double b);

void render_init(void){
	G_settings.depth  = DEFAULT_DEPTH;
	G_settings.aa_samples = DEFAULT_AA_SAMPLES;
	G_settings.aa_radius  = DEFAULT_AA_RADIUS;
	G_scene.hittable_count = 0;
	srand(time(NULL));
}

void render_quit(void){
	if(G_scene.hittable_count != 0){
		free(G_scene.hittable_list);
	}
}

void render_set_camera(Camera *cam){
	G_scene.cam = cam;
}
void render_set_depth(int depth){
	G_settings.depth = depth;
}
void render_set_aa(int aa_samples, double aa_radius){
	G_settings.aa_samples = aa_samples;
	G_settings.aa_radius = aa_radius;
}
void render_add_hittable(Hittable *hittable){
	int new_count = G_scene.hittable_count + 1;
	G_scene.hittable_list = (Hittable **)realloc(G_scene.hittable_list, sizeof(Hittable *)*new_count);
	G_scene.hittable_list[G_scene.hittable_count] = hittable;
	G_scene.hittable_count = new_count;
}

static bool solve_quadratic(double a, double b, double c, double *x1, double *x2){
	double delta = b*b - 4*a*c;
	if(delta < 0){
		return false;
	}

	*x1 = (-b + sqrt(delta)) / 2*a;
	*x2 = (-b - sqrt(delta)) / 2*a;
	return true;
}

static bool sphere_intersect(const Sphere *sphere, const Ray *ray, double *ret_x1, double *ret_x2){
	Vec3 L = vec3_sub(ray->ori, sphere->center);
	double a = vec3_dot(ray->dir, ray->dir);
	double b = 2 * vec3_dot(ray->dir, L);
	double c = vec3_dot(L, L) - sphere->r*sphere->r;

	double x1, x2;
	if(solve_quadratic(a,b,c, &x1, &x2)){
		*ret_x1 = x1;
		*ret_x2 = x2;
		return true;
	}
	return false;

}

static bool triangle_intersect(const Triangle *triangle, const Ray *ray, double *x1){
	return false;
}

static bool closest_intersection(const Ray *ray, double *t_return, Hittable **hit_return){
	Hittable *hit_rec = NULL;
	double    t_rec;

	for(int i = 0; i < G_scene.hittable_count; i++){
		bool hitten;
		double t1, t2;
		Hittable *h = G_scene.hittable_list[i];

		if(h->sph){
			hitten = sphere_intersect(h->sph, ray, &t1, &t2);
		} else if(h->tri){
			hitten = triangle_intersect(h->tri, ray, &t1);
		} else {
			continue;
		}

		if(!hitten){
			continue;
		}

		if((fabs(t1) < fabs(t_rec)) || i == 0){
			t_rec = t1;
			hit_rec = h;
		}

	}

	if(hit_rec == NULL){
		return false;
	}
	*t_return = t_rec;
	*hit_return = hit_rec;
	return true;
}

static Color get_color(const Ray *ray){
	double t_rec;
	Hittable *hit_rec;
	if(closest_intersection(ray, &t_rec, &hit_rec)){
		return hit_rec->mat->col;
	}

	Color col = {0,0,0,1};
	return col;
}

static double random_double(double a, double b){
	double r = (double)rand() / RAND_MAX;
	return a + (b-a)*r;
}

void render(Image *img){
	int maxdim = fmax(img->wid, img->hei);
	double aspect = img->wid/img->hei;
	double imd = 1/(double)maxdim;

	for(int ii = 0; ii < img->hei; ii++){
		for(int jj = 0; jj < img->wid; jj++){
			double ryy = (ii*imd)-(imd*img->hei/2);
			double rxx = (jj*imd)-(imd*img->wid/2);

			// TODO: para a direção funcionar corretamente, precisa também de ser alterada a origem do raio
			Ray r;
			r.ori = vec3_sum(G_scene.cam->pos, (Vec3){rxx,ryy,0});
			r.ori = vec3_sum(r.ori, G_scene.cam->dir);
			r.dir = G_scene.cam->dir;

			Color col = {0,0,0,1};

			int i = 0;
			Ray aa;
			aa.ori = r.ori;
			aa.dir = r.dir;
			do {
				Color t = color_div(get_color(&aa), G_settings.aa_samples + 1);
				col = color_sum(col, t);
				aa.ori.x += random_double(-G_settings.aa_radius, G_settings.aa_radius);
				aa.ori.y += random_double(-G_settings.aa_radius, G_settings.aa_radius);
				aa.ori.z += random_double(-G_settings.aa_radius, G_settings.aa_radius);
			} while((i++) < G_settings.aa_samples);

			image_set_color(img, jj, ii, &col);

		}
	}
}
