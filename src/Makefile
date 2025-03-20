CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
# CFLAGS += -pedantic
TFLAGS = -lgtest -pthread
TST_SRCS = tests/*.cpp
EXE = test_exe

.PHONY: all clean test gcov_report format check leaks leaks_for_mac sanitize

all: clean test

test: $(EXE)
	./$(EXE) > $(EXE).log

$(EXE): $(TST_SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(TFLAGS)

clean:
	rm -rf report
	rm -f *.gc* *.info $(EXE) *.log

format:
	clang-format -style=google -i *.h **/*.cpp **/*.h containers/*/*.h

leaks: clean $(EXE)
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--verbose --log-file=$(EXE)_valgrind.log ./$(EXE) > $(EXE).log

leaks_for_mac: clean $(EXE)
	leaks -atExit -- ./$(EXE) > $(EXE).log

sanitize: CFLAGS += -g -fsanitize=address
sanitize: clean test