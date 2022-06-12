CC=gcc
RM=rm -f
CLANG-FORMAT=clang-format
STD=-std=c89

WARNING=-Wall -Wextra -Werror
FLAGS=$(WARNING) $(STD)
DEPS=src/main.c

client: $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o $@.o

.PHONY: isformatted
isformatted: $(DEPS)
	$(CLANG-FORMAT) -dry-run -Werror $(DEPS)

.PHONY: format
format: $(DEPS)
	$(CLANG-FORMAT) -i $(DEPS)

.PHONY: clean
clean:
	$(RM) calculator
