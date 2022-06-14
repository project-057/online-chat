NUKLEAR+=./nuklear_cross/nuklear_cross.h
all: $(NUKLEAR+)
	cd ./nuklear_cross && \
	echo "#define NKC_IMPLEMENTATION\n#include \"nuklear_cross.h\"" > nuklear_cross.c && \
	gcc nuklear_cross.c -O2 -Wall -DNDEBUG -s -lm -std=c89 -DNKCD=NKC_GLFW -lglfw -lGL -c -o nuklear_cross.o && \
	mkdir -p ../include ../bin && \
	ar rcs ../bin/libnuklear_cross.a nuklear_cross.o && \
	cp nuklear_cross.h ../include/ && \
	git restore . && \
	rm nuklear_cross.o

clear: ./bin/ ./include/
	rm -rf ./bin ./include && \
	cd ./nuklear_cross/ && \
	git restore . && \
	rm nuklear_cross.o

