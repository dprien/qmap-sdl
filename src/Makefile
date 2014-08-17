CFLAGS =\
 -funsigned-char\
 -std=c99\
 -O2\
 -fno-strict-aliasing\
 -fno-common\
 -pedantic\
 -Wall\
 -Wextra\
 -Wno-unused-parameter

INCLUDES =\
 `sdl2-config --cflags`

LDFLAGS =\
 -Wl,--enable-new-dtags\
 -Wl,--sort-common\
 -lm\
 `sdl2-config --libs`

LIBS =

CSRCS =\
 main.c\
 mode.c\
 3d.c\
 readbsp.c\
 tm_c.c\
 tmap3d.c\
 surface.c\
 clippoly.c\
 poly.c\
 bsp.c\
 render.c

OBJS = $(CSRCS:.c=.o)
EXE = qmap

all: $(EXE)

depend:
	@$(CC) $(CFLAGS) $(INCLUDES) -MM $(CSRCS)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

.SUFFIXES: .c

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJS)

# DEPENDENCIES
# ===========================================================================
main.o: main.c bspfile.h cmdlib.h mode.h 3d.h s.h fix.h scr.h tm.h \
 render.h bsp.h surface.h poly.h
mode.o: mode.c s.h mode.h
3d.o: 3d.c 3d.h s.h fix.h bspfile.h cmdlib.h
readbsp.o: readbsp.c bspfile.h cmdlib.h mode.h
tm_c.o: tm_c.c s.h fix.h tm.h
tmap3d.o: tmap3d.c 3d.h s.h fix.h bspfile.h cmdlib.h tmap3d.h tm.h
surface.o: surface.c s.h tm.h fix.h bspfile.h cmdlib.h surface.h tmap3d.h
clippoly.o: clippoly.c 3d.h s.h fix.h bspfile.h cmdlib.h
poly.o: poly.c bspfile.h cmdlib.h fix.h 3d.h s.h tm.h tmap3d.h surface.h
bsp.o: bsp.c bspfile.h cmdlib.h 3d.h s.h fix.h bsp.h render.h
render.o: render.c bspfile.h cmdlib.h 3d.h s.h fix.h render.h bsp.h scr.h \
 poly.h
