#pragma once
#include "types.h"
#include <stdbool.h>

void render_init(void);
void render_quit(void);
void render(Image *img);

void render_set_camera(Camera *cam);
void render_set_depth(int depth);
void render_set_aa(int aa_samples, double aa_radius);
void render_add_hittable(Hittable *hittable);

