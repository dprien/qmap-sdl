/* QMAP: Quake level viewer
 *
 *   mode.c    Copyright 1997 Sean Barett
 *
 *   General screen functions (set graphics
 *   mode, blit to framebuffer, set palette)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "s.h"
#include "mode.h"

const int RENDER_WIDTH = 320;
const int RENDER_HEIGHT = 200;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
char *rgb_buf = NULL;
char palette[256 * 3];

void blit(char *src)
{
    char *s = src, *d = rgb_buf;
    for (int y = 0; y < RENDER_HEIGHT; y++) {
        for (int x = 0; x < RENDER_WIDTH; x++, s++) {
            int index = *s * 3;
            *d++ = palette[index + 2];
            *d++ = palette[index + 1];
            *d++ = palette[index + 0];
            *d++ = -128;
        }
    }
    SDL_UpdateTexture(texture, NULL, rgb_buf, RENDER_WIDTH * sizeof(Uint32));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void set_pal(char *pal)
{
    memcpy(palette, pal, 3 * 256);
}

void set_mode(int mode);

bool graphics=0;
void set_lores(void)
{
    window = SDL_CreateWindow(
            "qmap",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1200,
            900,
            SDL_WINDOW_OPENGL);
    if (!window) {
        fatal("SDL_CreateWindow failed\n");
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fatal("SDL_CreateRenderer failed\n");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            RENDER_WIDTH,
            RENDER_HEIGHT);
    if (!texture) {
        fatal("SDL_CreateTexture failed\n");
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    rgb_buf = new char[RENDER_WIDTH * RENDER_HEIGHT * sizeof(Uint32)];

    graphics = 1;
}

void set_text(void)
{
    if (graphics) {
        delete [] rgb_buf;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        graphics = 0;
    }
}

void fatal_error(const char *message, const char *file, int line)
{
    set_text();
    printf("Error (%s line %d): %s\n", file, line, message);
    exit(1);
}
