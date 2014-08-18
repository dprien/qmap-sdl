CXXFLAGS =\
 -std=c++11\
 -O2\
 -fno-strict-aliasing\
 -fno-common\
 -pedantic\
 -Wall\
 -Wextra\
 -Wno-unused-parameter\
 `sdl2-config --cflags`

INCLUDES =

LDFLAGS =\
 -Wl,--enable-new-dtags\
 -Wl,--sort-common

LIBS =\
 -lm\
 `sdl2-config --libs`

CSRCS =\
 main.cc\
 mode.cc\
 3d.cc\
 readbsp.cc\
 tm_c.cc\
 tmap3d.cc\
 surface.cc\
 clippoly.cc\
 poly.cc\
 bsp.cc\
 render.cc

OBJS = $(CSRCS:.cc=.o)
EXE = qmap

all: $(EXE)

depend:
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM $(CSRCS)

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

.SUFFIXES: .cc

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJS)

# DEPENDENCIES
# ===========================================================================
main.o: main.cc s.h bspfile.h cmdlib.h mode.h 3d.h fix.h scr.h tm.h \
 render.h bsp.h surface.h poly.h
mode.o: mode.cc s.h mode.h
3d.o: 3d.cc 3d.h s.h fix.h bspfile.h cmdlib.h
readbsp.o: readbsp.cc s.h bspfile.h cmdlib.h mode.h
tm_c.o: tm_c.cc s.h fix.h tm.h
tmap3d.o: tmap3d.cc 3d.h s.h fix.h bspfile.h cmdlib.h tmap3d.h tm.h
surface.o: surface.cc s.h tm.h fix.h bspfile.h cmdlib.h surface.h \
 tmap3d.h
clippoly.o: clippoly.cc 3d.h s.h fix.h bspfile.h cmdlib.h
poly.o: poly.cc bspfile.h cmdlib.h fix.h 3d.h s.h tm.h tmap3d.h surface.h
bsp.o: bsp.cc bspfile.h cmdlib.h 3d.h s.h fix.h bsp.h render.h
render.o: render.cc bspfile.h cmdlib.h 3d.h s.h fix.h render.h bsp.h \
 scr.h poly.h
