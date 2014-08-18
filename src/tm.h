#ifndef INC_TM_H
#define INC_TM_H

#include "fix.h"

typedef struct {
    uchar *bits;
    int wid;
    int ht;
} bitmap;

extern void qmap_draw_affine(int n, char *dest, fix u, fix v, fix du, fix dv);
extern void qmap_draw_span(int y, int sx, int ex);
extern void qmap_set_output(uchar *where, int row);
extern void qmap_set_texture(bitmap *bm);
extern void qmap_set_texture_gradients(double *tmap_data);

#endif
