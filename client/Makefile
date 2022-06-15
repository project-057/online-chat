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
FONT-LINK="https://drive.google.com/uc?export=download&id=1K2qPtTU_-U77lU8nz3pxmQALDidocA2-"

client: $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -I$(DEPS-INCLUDE) -L$(DEPS-BINARY) $(NUKLEAR-FLAGS) $(SDLBASE) -DNKC_USE_OPENGL=3 $(LIBGLEW) $(LIBGL) -lm -o $@.o && \
	mkdir -p ./bin/ && \
	mv $@.o ./bin/ && \
	touch ./bin/UbuntuMono-R.ttf && \
	curl -L $(FONT-LINK) -o ./bin/UbuntuMono-R.ttf

.PHONY: deps
deps: $(DEPS-SOURCES)
	@echo "\033[92m[INFO] Compiling dependencies\033[39m"
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
	@echo "$(ECHO-GREEN)[INFO] Removing client sources$(ECHO-DEFAULT)" && \
	$(RM) -r ./bin/ && \
	cd ./deps/ && \
	make clear
