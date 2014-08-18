/*  QMAP: Quake level viewer
 *
 *   main.c    Copyright 1997 Sean Barett
 *
 *   General setup control, main "sim" loop
 */

#include <SDL2/SDL.h>
#include "s.h"
#include "bspfile.h"
#include "mode.h"
#include "3d.h"
#include "fix.h"
#include "scr.h"
#include "tm.h"
#include "render.h"
#include "bsp.h"
#include "surface.h"
#include "poly.h"

double chop_temp;

vector cam_loc, cam_vel, new_loc;
angvec cam_ang, cam_angvel;

uchar *scr_buf;
int   scr_row;

#define VEL_STEP  2.0

uchar colormap[64][256];

void run_sim(void)
{
    vector temp;

    scr_buf = new uchar[320 * 200];
    scr_row = 320;
    qmap_set_output(scr_buf, scr_row);

    cam_loc.x = 500;
    cam_loc.y = 240;
    cam_loc.z = 100;

    bool done = false;
    while (!done) {

        // RENDER

        set_view_info(&cam_loc, &cam_ang);
        render_world(&cam_loc);
        blit(scr_buf);

        // UI

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT: {
                    done = true;
                    break;
                }
                case SDL_KEYUP: {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        done = true;
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    cam_ang.tx += event.motion.yrel << 5;
                    cam_ang.tz += event.motion.xrel << 5;
                }
            }
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_A]) {
            cam_vel.x -= VEL_STEP;
        }
        if (keys[SDL_SCANCODE_D]) {
            cam_vel.x += VEL_STEP;
        }
        if (keys[SDL_SCANCODE_W]) {
            cam_vel.y += VEL_STEP;
        }
        if (keys[SDL_SCANCODE_S]) {
            cam_vel.y -= VEL_STEP;
        }
        if (keys[SDL_SCANCODE_C]) {
            cam_vel.z -= VEL_STEP;
        }
        if (keys[SDL_SCANCODE_SPACE]) {
            cam_vel.z += VEL_STEP;
        }

        // "PHYSICS"

        cam_ang.tx += cam_angvel.tx;
        cam_ang.ty += cam_angvel.ty;
        cam_ang.tz += cam_angvel.tz;
        set_view_info(&cam_loc, &cam_ang);

        temp.x = cam_vel.x; temp.y = 0; temp.z = 0;
        rotate_vec(&temp);
        cam_loc.x  += temp.x; cam_loc.y += temp.y; cam_loc.z += temp.z;

        temp.x = 0; temp.y = cam_vel.y; temp.z = 0;
        rotate_vec(&temp);
        cam_loc.x  += temp.x; cam_loc.y += temp.y; cam_loc.z += temp.z;

        temp.x = 0; temp.y = 0; temp.z = cam_vel.z;
        rotate_vec(&temp);
        cam_loc.x  += temp.x; cam_loc.y += temp.y; cam_loc.z += temp.z;

        cam_vel.x /= 1.4;
        cam_vel.y /= 1.4;
        cam_vel.z /= 1.4;
    }
}

void load_graphics(void)
{
    uchar pal[768];
    FILE *f;
    if ((f = fopen("palette.lmp", "rb")) == NULL)
        fatal("Couldn't read palette.lmp\n");
    fread(pal, 1, 768, f);
    fclose(f);
    set_pal(pal);
    if ((f = fopen("colormap.lmp", "rb")) == NULL)
        fatal("Couldn't read colormap.lmp\n");
    fread(colormap, 256, 64, f);
    fclose(f);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: qmap <bspfile>\n");
    } else {
        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            fatal("SDL_Init failed\n");
        }

        LoadBSPFile(argv[1]);
        set_lores();
        load_graphics();
        init_cache();
        setup_default_point_list();

        run_sim();
        set_text();
        SDL_Quit();
    }
    return 0;
}
