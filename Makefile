CC = clang++
CFLAGS = -Wall -Wextra -Werror -lm

bin:
	mkdir -p ./bin

%: src/%.cpp bin
	$(CC) $(CFLAGS) src/$*.cpp -o bin/$*
	bin/$*

clean:
	rm -r ./bin
