NUKLEAR+=./nuklear_cross/nuklear_cross.h
DEPS-COUNT=1
ECHO-GREEN=\033[92m
ECHO-DEFAULT=\033[39m
NUKLEAR-STEP-COUNT=4


LIBGL:=$(shell pkg-config --libs --cflags gl)
LIBGLEW:=$(shell pkg-config --libs --cflags glew)
LIBSDL:=$(shell pkg-config --libs --cflags sdl2)
SDLBASE  = -DNKCD=NKC_SDL  $(LIBSDL)

all: $(NUKLEAR+)
	@echo -e "$(ECHO-GREEN)[INFO] [0/$(DEPS-COUNT)] Compiling nuklear_cross$(ECHO-DEFAULT)" && \
	cd ./nuklear_cross && \
	cc nuklear_cross.c -O2 -Wall -s -lm -std=c89 $(SDLBASE) -DNKC_USE_OPENGL=3  $(LIBGL) $(LIBGLEW) -c -o nuklear_cross.o && \
	echo -e "$(ECHO-GREEN)[INFO] [0/$(NUKLEAR-STEP-COUNT)] Creating binary and include directory" && \
	mkdir -p ../include ../bin && \
	echo -e "$(ECHO-GREEN)[INFO] [1/$(NUKLEAR-STEP-COUNT)] Zipping static library$(ECHO-DEFAULT)" && \
	ar rcs ../bin/libnuklear_cross.a nuklear_cross.o && \
	cp nuklear_cross.h ../include/ && \
	cp nuklear.h ../include/ && \
	cp -r nkc_frontend ../include/ && \
	cp -r nuklear_drivers ../include/ && \
	echo -e "$(ECHO-GREEN)[INFO] [2/$(NUKLEAR-STEP-COUNT)] Restore submodule repository$(ECHO-DEFAULT)" && \
	git restore . && \
	echo -e "$(ECHO-GREEN)[INFO] [3/$(NUKLEAR-STEP-COUNT)] Delete binary from submodule$(ECHO-DEFAULT)" &&\
	rm -f nuklear_cross.o && \
	echo -e "$(ECHO-GREEN)[INFO] [1/$(DEPS-COUNT)] Nuklear successfully compiled$(ECHO-DEFAULT)"

clear:
	@echo -e "$(ECHO-GREEN)[INFO] Removing dependencies$(ECHO-DEFAULT)" && \
	rm -rf ./bin ./include && \
	cd ./nuklear_cross/ && \
	git restore . && \
	rm -f nuklear_cross.o

