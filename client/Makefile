ECHO-GREEN=\033[92m
ECHO-DEFAULT=\033[39m
CC=gcc
RM=rm -f
CLANG-FORMAT=clang-format
STD=

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) $(STD) $(INCLUDE) -O2
DEPS=src/main.c src/Application.c src/MessageList.c ./src/RenderData.c ./src/ApplicationState.c ./src/Client.c

DEPS-INCLUDE=./deps/include/
DEPS-BINARY=./deps/bin/
DEPS-NUKLEAR-FOLDER=deps/nuklear_cross/
DEPS-NUKLEAR-SOURCES=$(DEPS-NUKLEAR-FOLDER)nuklear_cross.c
DEPS-SOURCES=$(DEPS-NUKLEAR-SOURCES)

LIBGL:=$(shell pkg-config --libs --cflags gl)
LIBGLEW:=$(shell pkg-config --libs --cflags glew)
LIBSDL:=$(shell pkg-config --libs --cflags sdl2)
SDLBASE  = -DNKCD=NKC_SDL  $(LIBSDL)

NUKLEAR-FLAGS=-lnuklear_cross

client: $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -I$(DEPS-INCLUDE) -L$(DEPS-BINARY) $(NUKLEAR-FLAGS) $(SDLBASE) -DNKC_USE_OPENGL=3 $(LIBGLEW) $(LIBGL) -lm -o $@.o

.PHONY: deps
deps: $(DEPS-SOURCES)
	@echo -e "\033[92m[INFO] Compiling dependencies\033[39m"
	@cd ./deps/ && \
	make

.PHONY: isformatted
isformatted: $(DEPS)
	$(CLANG-FORMAT) -dry-run -Werror $(DEPS)

.PHONY: format
format: $(DEPS)
	$(CLANG-FORMAT) -i $(DEPS)

.PHONY: clean
clean:
	@echo -e "$(ECHO-GREEN)[INFO] Removing client sources$(ECHO-DEFAULT)" && \
	$(RM) client.o && \
	cd ./deps/ && \
	make clear
