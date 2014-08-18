CXXFLAGS =\
 -funsigned-char\
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
